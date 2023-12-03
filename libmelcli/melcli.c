/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include "melcli_priv.h"

/* **************************************************************************/

static int split_dev_addr(const char* addr, char* prefix, char* trailing);
static int lookup_dev_type(const char* prefix, uint16_t* mem_type, 
    int* unit_type);
static int cvt_dev_addr_s(const char* addr, uint8_t* mem_type, 
    uint32_t* addr_begin, int* unit_type);
static int cvt_dev_addr_l(const char* addr, uint16_t* mem_type, 
    uint32_t* addr_begin, int* unit_type);
static int parse_dev_addr(const char* addr, uint8_t* mem_type_s, 
    uint16_t* mem_type_l, uint32_t* addr_begin, int* use_32bit_addr, 
    int* unit_type);
static slmp_frame_t* build_req_frame(melcli_ctx_t* ctx, 
    const melcli_station_t* station, int cmd, int sub_cmd, slmp_cmd_hdr_t* hdr, 
    slmp_command_encode_t pfn_enc, int* serial);
static int send_frame(melcli_ctx_t* ctx, const melcli_station_t* station,
    slmp_frame_t** frame, int free_after_sent);
static int receive_frame(melcli_ctx_t* ctx, int serial, slmp_frame_t** frame);
static int extract_units_read_data(const uint8_t* resp_data, int unit_type, 
    int n, uint8_t** buf, int* data_len);
static int fill_units_write_data(const char* src, int unit_type, int n, 
    uint8_t* data);
static int encode_dev_random_read_units(const char** addrs, int* use_32bit_addr, 
    uint8_t** pstrm);
static int fill_dev_random_write_bit_units(const char** addrs, 
    const uint8_t* data, int* use_32bit_addr, uint8_t** pstrm);
static int fill_dev_random_write_word_units(const char** addrs, 
    const uint16_t* data, int* use_32bit_addr, uint8_t** pstrm);
static int fill_dev_random_write_dword_units(const char** addrs, 
    const uint32_t* data, int* use_32bit_addr, uint8_t** pstrm);

static const err_msg_desc_t err_msg[] = {
    { MELCLI_ERROR_SUCCESS, "Succeeded" },
    { MELCLI_ERROR_INVALID_POINTER, "Invalid pointer." }, 
    { MELCLI_ERROR_INVALID_ARGUMENTS, "Invalid arguments." },
    { MELCLI_ERROR_INVALID_ADDRESS, "Invalid address." },
    { MELCLI_ERROR_UNIT_TYPE_NOT_SUPPORTED, "Unit type not supported." },
    { MELCLI_ERROR_BUILD_REQUEST_FRAME, "Unable to build request frame." },
    { MELCLI_ERROR_OUT_OF_MEMORY, "Run out of memory." },
    { MELCLI_ERROR_DECODE_FRAME, "Unable to decode a response frame." },
    { MELCLI_ERROR_ENCODE_COMMAND, "An error occured in command encoding." },
    { MELCLI_ERROR_CONNECT_FAILED, "Unable to establish a connection." },
    { MELCLI_ERROR_SEND_FRAMES, "Unable to send frames." },
    { MELCLI_ERROR_RECEIVE_FRAMES, "Error receiving frames." },
    { MELCLI_ERROR_OPERATION_FAILED, "Operation failed." },
    { MELCLI_ERROR_FRAME_SERIAL_MISMATCH, "Frame serial mismatch." },
    { MELCLI_ERROR_SELF_TEST_FAILED, "Self test failed." },

    { -1, NULL }
};

/* **************************************************************************/

MELCLIAPI int MELCLICALL melcli_init()
{
    return slmp_init();
}

MELCLIAPI int MELCLICALL melcli_uninit()
{
    return slmp_uninit();
}

MELCLIAPI const char* MELCLICALL melcli_get_err_msg(int err)
{
    err_msg_desc_t const *desc = &err_msg[0];
    
    do {
        if (desc->err == err) {
            return desc->msg;
        }

        ++desc;
    } while (desc->msg != NULL);

    return "Unknown error.";
}

MELCLIAPI melcli_ctx_t* MELCLICALL melcli_new_context(
    int type, const char* remote_ipaddr, int remote_port, 
    const char* local_ipaddr, int local_port,
    const melcli_station_t* station, const melcli_timeout_t* timeout)
{
    melcli_ctx_t *ctx = NULL;
    slmp_pktio_t *pktio = NULL;

    switch (type) {
    case MELCLI_TYPE_TCPIP:
        pktio = slmp_pktio_new_tcpip(SLMP_PKTIO_CLIENT, remote_ipaddr, 
            remote_port);
        break;
    case MELCLI_TYPE_UDPIP:
        pktio = slmp_pktio_new_udpip(
            (local_ipaddr != NULL) ? local_ipaddr : "0.0.0.0", 
            local_port, remote_ipaddr, remote_port);
        break;
    default:
        break;
    }

    if (pktio == NULL) {
        return NULL;
    }
    else if (slmp_pktio_init(pktio) != SLMP_ERROR_SUCCESS) {
        slmp_pktio_free(pktio);
        return NULL;
    }
    
    if ((type == MELCLI_TYPE_TCPIP) && (local_ipaddr != NULL)) {
        slmp_pktio_tcpip_set_client_addr(pktio, local_ipaddr);
    }

    ctx = malloc(sizeof(melcli_ctx_t));
    if (ctx == NULL) {
        slmp_pktio_free(pktio);
        return NULL;
    }
    else {
        memset(ctx, 0, sizeof(melcli_ctx_t));
    }

    if (station != NULL) {
        ctx->station = *station;
    }
    else {
        melcli_station_t connected_station = MELCLI_CONNECTED_STATION;
        memcpy(&(ctx->station), &connected_station, sizeof(melcli_station_t));
    }

    if (timeout != NULL) {
        memcpy(&(ctx->timeout), timeout, sizeof(melcli_timeout_t));
    }
    else {
        melcli_timeout_t timeout_default = MELCLI_TIMEOUT_DEFAULT;
        memcpy(&(ctx->timeout), &timeout_default, sizeof(melcli_timeout_t));
    }

    switch (type) {
    case MELCLI_TYPE_TCPIP:
        slmp_pktio_tcpip_set_conn_timeout(pktio, ctx->timeout.conn_timeout);
        slmp_pktio_tcpip_set_recv_timeout(pktio, ctx->timeout.recv_timeout);
        break;
    case MELCLI_TYPE_UDPIP:
        slmp_pktio_udpip_set_conn_timeout(pktio, ctx->timeout.conn_timeout);
        slmp_pktio_udpip_set_recv_timeout(pktio, ctx->timeout.recv_timeout);
        break;
    default:
        break;
    }

    ctx->dbgprint = &printf;
    ctx->pktio = pktio;
    ctx->serial = 0;
    ctx->debug = FALSE;

    return ctx;
}

MELCLIAPI void MELCLICALL melcli_free_context(
    melcli_ctx_t* ctx)
{
    if (ctx == NULL) {
        return;
    }

    slmp_pktio_free(ctx->pktio);
    memset(ctx, 0, sizeof(melcli_ctx_t));
    free(ctx);
}

MELCLIAPI void MELCLICALL melcli_set_dbgprint_fcn(
    melcli_ctx_t* ctx, int (CDECLCALL* pfn)(const char*, ...))
{
    if (ctx == NULL) {
        return;
    }

    if (pfn) {
        ctx->dbgprint = pfn;
    }
    else {
        ctx->dbgprint = &printf;
    }
}

MELCLIAPI int MELCLICALL melcli_connect(
    melcli_ctx_t* ctx)
{
    if (ctx == NULL) {
        return MELCLI_ERROR_INVALID_POINTER;
    }
    
    if (ctx->debug) {
        ctx->dbgprint("[INFO] Connecting...\n");
    }
    
    if (slmp_pktio_open(ctx->pktio) != SLMP_ERROR_SUCCESS) {
        if (ctx->debug) {
            ctx->dbgprint("[ERROR] %s\n", slmp_get_err_msg(slmp_get_errno()));
        }

        return MELCLI_ERROR_CONNECT_FAILED;
    }
    else if (ctx->debug) {
        ctx->dbgprint("[INFO] Connected.\n");
    }

    return MELCLI_ERROR_SUCCESS;
}

MELCLIAPI void MELCLICALL melcli_disconnect(
    melcli_ctx_t* ctx)
{
    if (ctx == NULL) {
        return;
    }
    
    slmp_pktio_close(ctx->pktio);
    
    if (ctx->debug) {
        ctx->dbgprint("[INFO] Connection closed.\n");
    }
}

MELCLIAPI void MELCLICALL melcli_set_debug(
    melcli_ctx_t* ctx, int debug)
{
    if (ctx == NULL) {
        return;
    }

    ctx->debug = debug;
    slmp_pktio_set_echo(ctx->pktio, debug);
    
    if (debug) {
        ctx->dbgprint("[INFO] Debug mode enabled.\n");
    }
    else {
        ctx->dbgprint("[INFO] Debug mode disabled.\n");
    }
}

MELCLIAPI void MELCLICALL melcli_free(
    void* p)
{
    free(p);
}

MELCLIAPI int MELCLICALL melcli_batch_read(
    melcli_ctx_t* ctx, const melcli_station_t* station, const char* addr,
    int n, char** data, int* data_len)
{
    int ret = MELCLI_ERROR_SUCCESS;
    uint8_t mem_type_s;
    uint16_t mem_type_l;
    int use_32bit_addr;
    uint32_t addr_begin;
    int unit_type;
    size_t expected_resp_data_len;
    slmp_req_device_read_t req;
    uint16_t subcmd;
    slmp_frame_t *frame = NULL;
    int serial = -1;

    if ((ctx == NULL) || (addr == NULL) || (data == NULL)) {
        ret = MELCLI_ERROR_INVALID_POINTER;
        goto __done;
    }

    if ((n <= 0) || (n >= 65536)) {
        ret = MELCLI_ERROR_INVALID_ARGUMENTS;
        goto __done;
    }

    if (!parse_dev_addr(addr, &mem_type_s, &mem_type_l, &addr_begin, 
        &use_32bit_addr, &unit_type))
    {
        if (ctx->debug) {
            ctx->dbgprint("[ERROR] Invalid address: %s\n", addr);
        }

        ret = MELCLI_ERROR_INVALID_ADDRESS;
        goto __done;
    }
    
    switch (unit_type) {
    case UNIT_BIT:
        subcmd = use_32bit_addr ? SLMP_SUBCMD_MEM_BIT_ADDR_32 
            : SLMP_SUBCMD_MEM_BIT_ADDR_16;
        expected_resp_data_len = (n + 1) / 2;
        break;
    case UNIT_WORD:
        subcmd = use_32bit_addr ? SLMP_SUBCMD_MEM_WORD_ADDR_32 
            : SLMP_SUBCMD_MEM_WORD_ADDR_16;
        expected_resp_data_len = 2 * n;
        break;
    case UNIT_DWORD:
        subcmd = use_32bit_addr ? SLMP_SUBCMD_MEM_WORD_ADDR_32 
            : SLMP_SUBCMD_MEM_WORD_ADDR_16;
        expected_resp_data_len = 4 * n;
        break;
    default:
        ret = MELCLI_ERROR_UNIT_TYPE_NOT_SUPPORTED;
        goto __done;
    }
    
    memset(&req, 0, sizeof(slmp_req_device_read_t));
    req.hdr.size = sizeof(slmp_req_device_read_t);
    req.hdr.addr_width = use_32bit_addr ? SLMP_ADDRESS_32BIT 
        : SLMP_ADDRESS_16BIT;

    if (use_32bit_addr) {
        req.mem_type.bin.l = mem_type_l;
        req.addr_begin.bin.l = addr_begin;
    }
    else {
        req.mem_type.bin.s = mem_type_s;
        req.addr_begin.bin.s = addr_begin;
    }
    
    req.num = n;

    frame = build_req_frame(ctx, station, SLMP_CMD_MEM_BATCH_READ, subcmd, 
        &(req.hdr), slmp_encode_req_device_read, &serial);
    if (frame == NULL) {
        ret = MELCLI_ERROR_BUILD_REQUEST_FRAME;
        goto __done;
    }
     
    ret = send_frame(ctx, station, &frame, 1);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }

    ret = receive_frame(ctx, serial, &frame);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }
    
    if (SLMP_FRAME_RAW_DATA_SIZE(frame) < expected_resp_data_len) {
        if (ctx->debug) {
            ctx->dbgprint("[ERROR] Failed to decode the response frame. "
                    "Length of the data received is shorter than expected.\n");
        }
        
        ret = MELCLI_ERROR_DECODE_FRAME;
        goto __done;
    }

    if (!extract_units_read_data(frame->raw_data, unit_type, n, 
        (uint8_t**)(data), data_len)) 
    {
        ret = MELCLI_ERROR_OUT_OF_MEMORY;
        goto __done;
    }

__done:
    slmp_free(frame);
    return ret;
}

MELCLIAPI int MELCLICALL melcli_batch_write(
    melcli_ctx_t* ctx, const melcli_station_t* station, const char* addr,
    int n, const char* data)
{
    int ret = MELCLI_ERROR_SUCCESS;
    uint8_t mem_type_s;
    uint16_t mem_type_l;
    int use_32bit_addr;
    uint32_t addr_begin;
    int unit_type;
    slmp_req_device_write_t *req = NULL;
    size_t req_data_len;
    size_t req_size;
    uint16_t subcmd;
    slmp_frame_t *frame = NULL;
    int serial = -1;

    if ((ctx == NULL) || (addr == NULL) || (data == NULL)) {
        ret = MELCLI_ERROR_INVALID_POINTER;
        goto __done;
    }

    if ((n <= 0) || (n >= 65536)) {
        ret = MELCLI_ERROR_INVALID_ARGUMENTS;
        goto __done;
    }

    if (!parse_dev_addr(addr, &mem_type_s, &mem_type_l, &addr_begin, 
        &use_32bit_addr, &unit_type))
    {
        if (ctx->debug) {
            ctx->dbgprint("[ERROR] Invalid address: %s\n", addr);
        }

        ret = MELCLI_ERROR_INVALID_ADDRESS;
        goto __done;
    }
    
    switch (unit_type) {
    case UNIT_BIT:
        subcmd = use_32bit_addr ? SLMP_SUBCMD_MEM_BIT_ADDR_32 
            : SLMP_SUBCMD_MEM_BIT_ADDR_16;
        req_data_len = (n + 1) / 2;
        break;
    case UNIT_WORD:
        subcmd = use_32bit_addr ? SLMP_SUBCMD_MEM_WORD_ADDR_32 
            : SLMP_SUBCMD_MEM_WORD_ADDR_16;
        req_data_len = 2 * n;
        break;
    case UNIT_DWORD:
        subcmd = use_32bit_addr ? SLMP_SUBCMD_MEM_WORD_ADDR_32 
            : SLMP_SUBCMD_MEM_WORD_ADDR_16;
        req_data_len = 4 * n;
        break;
    default:
        ret = MELCLI_ERROR_UNIT_TYPE_NOT_SUPPORTED;
        goto __done;
    }

    req_size = sizeof(slmp_req_device_write_t) + req_data_len - 1;
    req = (slmp_req_device_write_t*)calloc(1, req_size);
    if (req == NULL) {
        ret = MELCLI_ERROR_OUT_OF_MEMORY;
        goto __done;
    }
        
    req->hdr.size = req_size;
    req->hdr.addr_width = use_32bit_addr ? SLMP_ADDRESS_32BIT 
        : SLMP_ADDRESS_16BIT;

    if (use_32bit_addr) {
        req->mem_type.bin.l = mem_type_l;
        req->addr_begin.bin.l = addr_begin;
    }
    else {
        req->mem_type.bin.s = mem_type_s;
        req->addr_begin.bin.s = addr_begin;
    }
    
    req->num = n;
    fill_units_write_data(data, unit_type, n, req->data);

    frame = build_req_frame(ctx, station, SLMP_CMD_MEM_BATCH_WRITE, subcmd, 
        &(req->hdr), slmp_encode_req_device_write, &serial);
    if (frame == NULL) {
        ret = MELCLI_ERROR_BUILD_REQUEST_FRAME;
        goto __done;
    }
     
    ret = send_frame(ctx, station, &frame, 1);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }

    ret = receive_frame(ctx, serial, &frame);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }

__done:
    free(req);
    slmp_free(frame);
    return ret;
}

MELCLIAPI int MELCLICALL melcli_random_read(
    melcli_ctx_t* ctx, const melcli_station_t* station, 
    const char** word_unit_addrs, const char** dword_unit_addrs, 
    uint16_t** word_data, int* word_data_len, uint32_t** dword_data,
    int* dword_data_len)
{
    int ret = MELCLI_ERROR_SUCCESS;
    const char** addr;
    size_t num_word_units = 0, num_dword_units = 0;
    int use_32bit_addr = FALSE;
    size_t per_req_unit_data_len, req_data_len, req_size;
    slmp_req_device_read_random_unit_t req_unit;
    slmp_req_device_read_random_t *req = NULL;
    uint8_t *strm = NULL;
    slmp_frame_t *frame = NULL;
    int serial = -1;
    
    if ((ctx == NULL)
        || ((word_unit_addrs == NULL) && (dword_unit_addrs == NULL)))
    {
        ret = MELCLI_ERROR_INVALID_POINTER;
        goto __done;
    }
    
    for (addr = word_unit_addrs; (word_unit_addrs != NULL) && (*addr != NULL); 
        ++addr) 
    {
        ++num_word_units;
    }
    
    for (addr = dword_unit_addrs; (dword_unit_addrs != NULL) && (*addr != NULL); 
        ++addr) 
    {
        ++num_dword_units;
    }
        
    if (    ((num_word_units == 0) && (num_dword_units == 0))
        ||  (num_word_units > 255) 
        ||  (num_dword_units > 255)) 
    {
        ret = MELCLI_ERROR_INVALID_ARGUMENTS;
        goto __done;
    }
    
    if (((num_word_units != 0) && (word_data == NULL))
        || ((num_dword_units != 0) && (dword_data == NULL)))
    {
        ret = MELCLI_ERROR_INVALID_POINTER;
        goto __done;
    }
    
    if (word_data) {
        *word_data = NULL;
    }
    
    if (dword_data) {
        *dword_data = NULL;
    }
    
    req_unit.hdr.size = sizeof(slmp_req_device_read_random_unit_t);
    req_unit.hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
    per_req_unit_data_len = slmp_encode_req_device_read_random_unit(
        (slmp_cmd_hdr_t*)(&req_unit), NULL, SLMP_BINARY_STREAM); 
    req_data_len = per_req_unit_data_len * (num_word_units + num_dword_units);
        
    req_size = sizeof(slmp_req_device_read_random_t) + req_data_len - 1;
    req = (slmp_req_device_read_random_t*)calloc(1, req_size);
    if (req == NULL) {
        ret = MELCLI_ERROR_OUT_OF_MEMORY;
        goto __done;
    }
    else {
        req->hdr.size = req_size;
        req->hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
        req->num_wd = (uint8_t)num_word_units;
        req->num_dwd = (uint8_t)num_dword_units;
        strm = req->data;
    }
    
    ret = encode_dev_random_read_units(word_unit_addrs, &use_32bit_addr, &strm);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }
    
    ret = encode_dev_random_read_units(dword_unit_addrs, &use_32bit_addr, &strm);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }
    
    frame = build_req_frame(ctx, station, SLMP_CMD_MEM_RANDOM_READ, 
        use_32bit_addr ? SLMP_SUBCMD_MEM_WORD_ADDR_32 : SLMP_SUBCMD_MEM_WORD_ADDR_16,
        &(req->hdr), slmp_encode_req_device_read_random, &serial);
    if (frame == NULL) {
        ret = MELCLI_ERROR_BUILD_REQUEST_FRAME;
        goto __done;
    }

    ret = send_frame(ctx, station, &frame, 1);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }

    ret = receive_frame(ctx, serial, &frame);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }
    
    if (word_data &&
        !extract_units_read_data(frame->raw_data, UNIT_WORD, num_word_units, 
            (uint8_t**)(word_data), word_data_len))
    {
        ret = MELCLI_ERROR_OUT_OF_MEMORY;
        goto __done;
    }
    
    if (dword_data &&
        !extract_units_read_data(frame->raw_data + (num_word_units * 2), 
            UNIT_DWORD, num_dword_units, (uint8_t**)(dword_data), 
            dword_data_len))
    {
        if (word_data) {
            free(*word_data);
            *word_data = NULL;
        }
        ret = MELCLI_ERROR_OUT_OF_MEMORY;
        goto __done;
    }
    
__done:
    free(req);
    slmp_free(frame);
    return ret;
}

MELCLIAPI int MELCLICALL melcli_random_read_word(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char** addrs, uint16_t** data, int* data_len)
{
    return melcli_random_read(ctx, station, addrs, NULL, data, data_len, NULL, NULL);
}

MELCLIAPI int MELCLICALL melcli_random_read_dword(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char** addrs, uint32_t** data, int* data_len)
{
    return melcli_random_read(ctx, station, NULL, addrs, NULL, NULL, data, data_len);
}

MELCLIAPI int MELCLICALL melcli_random_write(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char** bit_unit_addrs, const char** word_unit_addrs, 
    const char** dword_unit_addrs, const uint8_t* bit_data, 
    const uint16_t* word_data, const uint32_t* dword_data)
{
    int ret = MELCLI_ERROR_SUCCESS;
    const char** addr;
    size_t num_bit_units = 0, num_word_units = 0, num_dword_units = 0;
    int use_32bit_addr = FALSE;
    slmp_req_device_write_random_bit_unit_t req_unit_b;
    slmp_req_device_write_random_word_unit_t req_unit_w;
    slmp_req_device_write_random_dword_unit_t req_unit_dw;
    size_t per_req_unit_b_len, per_req_unit_w_len, per_req_unit_dw_len;
    size_t req_data_len, req_size;
    slmp_req_device_write_random_bit_t *req_bits = NULL;
    slmp_req_device_write_random_t *req_words = NULL;
    uint8_t *strm;
    slmp_frame_t *frame = NULL;
    int serial = -1;

    if ((ctx == NULL)
        || ((bit_unit_addrs == NULL) && (word_unit_addrs == NULL) 
            && (dword_unit_addrs == NULL)))
    {
        ret = MELCLI_ERROR_INVALID_POINTER;
        goto __done;
    }
    
    for (addr = bit_unit_addrs; (bit_unit_addrs != NULL) && (*addr != NULL); 
        ++addr) 
    {
        ++num_bit_units;
    }

    for (addr = word_unit_addrs; (word_unit_addrs != NULL) && (*addr != NULL); 
        ++addr) 
    {
        ++num_word_units;
    }
    
    for (addr = dword_unit_addrs; (dword_unit_addrs != NULL) && (*addr != NULL); 
        ++addr) 
    {
        ++num_dword_units;
    }
        
    if (    ((num_bit_units == 0) && (num_word_units == 0) 
            && (num_dword_units == 0))
        ||  (num_bit_units > 255)
        ||  (num_word_units > 255) 
        ||  (num_dword_units > 255)) 
    {
        ret = MELCLI_ERROR_INVALID_ARGUMENTS;
        goto __done;
    }
    
    if (    ((num_bit_units != 0) && (bit_data == NULL))
        ||  ((num_word_units != 0) && (word_data == NULL))
        ||  ((num_dword_units != 0) && (dword_data == NULL)))
    {
        ret = MELCLI_ERROR_INVALID_POINTER;
        goto __done;
    }
    
    if (num_bit_units != 0) {
        req_unit_b.hdr.size = sizeof(slmp_req_device_write_random_bit_unit_t);
        req_unit_b.hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
        per_req_unit_b_len = slmp_encode_req_device_write_random_bit_unit(
            (slmp_cmd_hdr_t*)(&req_unit_b), NULL, SLMP_BINARY_STREAM);
        req_data_len = per_req_unit_b_len * num_bit_units;
        req_size = sizeof(slmp_req_device_write_random_bit_t) + req_data_len - 1;

        req_bits = (slmp_req_device_write_random_bit_t*)calloc(1, req_size);
        if (req_bits == NULL) {
            ret = MELCLI_ERROR_OUT_OF_MEMORY;
            goto __done;
        }
        else {
            req_bits->hdr.size = req_size;
            req_bits->hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
            req_bits->num = (uint8_t)num_bit_units;
            strm = req_bits->data;
        }

        ret = fill_dev_random_write_bit_units(bit_unit_addrs, bit_data, 
            &use_32bit_addr, &strm);
        if (ret != MELCLI_ERROR_SUCCESS) {
            goto __done;
        }

        frame = build_req_frame(ctx, station, SLMP_CMD_MEM_RANDOM_WRITE,
            use_32bit_addr ? SLMP_SUBCMD_MEM_BIT_ADDR_32 : SLMP_SUBCMD_MEM_BIT_ADDR_16,
            (slmp_cmd_hdr_t*)(req_bits), slmp_encode_req_device_write_random_bit, 
            &serial);
        if (frame == NULL) {
            ret = MELCLI_ERROR_BUILD_REQUEST_FRAME;
            goto __done;
        }

        ret = send_frame(ctx, station, &frame, 1);
        if (ret != MELCLI_ERROR_SUCCESS) {
            goto __done;
        }

        ret = receive_frame(ctx, serial, &frame);
        if (ret != MELCLI_ERROR_SUCCESS) {
            goto __done;
        }
    }

    if ((num_word_units != 0) || (num_dword_units) != 0) {
        req_unit_w.hdr.size = sizeof(slmp_req_device_write_random_word_unit_t);
        req_unit_w.hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
        per_req_unit_w_len = slmp_encode_req_device_write_random_word_unit(
            (slmp_cmd_hdr_t*)(&req_unit_w), NULL, SLMP_BINARY_STREAM);
        req_unit_dw.hdr.size = sizeof(slmp_req_device_write_random_dword_unit_t);
        req_unit_dw.hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
        per_req_unit_dw_len = slmp_encode_req_device_write_random_dword_unit(
            (slmp_cmd_hdr_t*)(&req_unit_dw), NULL, SLMP_BINARY_STREAM);
        req_data_len = 
                per_req_unit_w_len * num_word_units
            +   per_req_unit_dw_len * num_dword_units;
        req_size = sizeof(slmp_req_device_write_random_t) + req_data_len - 1;

        req_words = (slmp_req_device_write_random_t*)calloc(1, req_size);
        if (req_words == NULL) {
            ret = MELCLI_ERROR_OUT_OF_MEMORY;
            goto __done;
        }
        else {
            req_words->hdr.size = req_size;
            req_words->hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
            req_words->num_wd = (uint8_t)num_word_units;
            req_words->num_dwd = (uint8_t)num_dword_units;
            strm = req_words->data;
        }
        
        use_32bit_addr = FALSE;

        ret = fill_dev_random_write_word_units(word_unit_addrs, word_data,
            &use_32bit_addr, &strm);
        if (ret != MELCLI_ERROR_SUCCESS) {
            goto __done;
        }

        ret = fill_dev_random_write_dword_units(dword_unit_addrs, dword_data,
            &use_32bit_addr, &strm);
        if (ret != MELCLI_ERROR_SUCCESS) {
            goto __done;
        }

        frame = build_req_frame(ctx, station, SLMP_CMD_MEM_RANDOM_WRITE,
            use_32bit_addr ? SLMP_SUBCMD_MEM_WORD_ADDR_32 : SLMP_SUBCMD_MEM_WORD_ADDR_16,
            (slmp_cmd_hdr_t*)(req_words), slmp_encode_req_device_write_random, 
            &serial);
        if (frame == NULL) {
            ret = MELCLI_ERROR_BUILD_REQUEST_FRAME;
            goto __done;
        }

        ret = send_frame(ctx, station, &frame, 1);
        if (ret != MELCLI_ERROR_SUCCESS) {
            goto __done;
        }

        ret = receive_frame(ctx, serial, &frame);
        if (ret != MELCLI_ERROR_SUCCESS) {
            goto __done;
        }
    }
    
__done:
    free(req_bits);
    free(req_words);
    slmp_free(frame);
    return ret;
}

MELCLIAPI int MELCLICALL melcli_random_write_bit(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char** addrs, const uint8_t* data)
{
    return melcli_random_write(ctx, station, addrs, NULL, NULL, data, NULL,
        NULL);
}

MELCLIAPI int MELCLICALL melcli_random_write_word(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char** addrs, const uint16_t* data)
{
    return melcli_random_write(ctx, station, NULL, addrs, NULL, NULL, data,
        NULL);
}

MELCLIAPI int MELCLICALL melcli_random_write_dword(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char** addrs, const uint32_t* data)
{
    return melcli_random_write(ctx, station, NULL, NULL, addrs, NULL, NULL,
        data);
}

MELCLIAPI int MELCLICALL melcli_buffer_read(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    uint32_t addr, int n, uint16_t** data, int* data_len)
{
    int ret = MELCLI_ERROR_SUCCESS;
    slmp_req_memory_read_t req;
    slmp_frame_t *frame = NULL;
    int serial = -1;

    if ((ctx == NULL) || (data == NULL)) {
        ret = MELCLI_ERROR_INVALID_POINTER;
        goto __done;
    }

    if ((n <= 0) || (n >= 65536)) {
        ret = MELCLI_ERROR_INVALID_ARGUMENTS;
        goto __done;
    }

    memset(&req, 0, sizeof(slmp_req_memory_read_t));
    req.hdr.size = sizeof(slmp_req_memory_read_t);
    req.hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
    req.addr_begin = addr;
    req.len = n;

    frame = build_req_frame(ctx, station, SLMP_CMD_DPMEM_BATCH_READ, 0x0000,
        &(req.hdr), slmp_encode_req_memory_read, &serial);
    if (frame == NULL) {
        ret = MELCLI_ERROR_BUILD_REQUEST_FRAME;
        goto __done;
    }

    ret = send_frame(ctx, station, &frame, 1);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }

    ret = receive_frame(ctx, serial, &frame);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }

    if (SLMP_FRAME_RAW_DATA_SIZE(frame) < (size_t)(2 * n)) {
        if (ctx->debug) {
            ctx->dbgprint("[ERROR] Failed to decode the response frame. "
                    "Length of the data received is shorter than expected.\n");
        }
        
        ret = MELCLI_ERROR_DECODE_FRAME;
        goto __done;
    }

    if (!extract_units_read_data(frame->raw_data, UNIT_WORD, n, 
        (uint8_t**)(data), data_len)) 
    {
        ret = MELCLI_ERROR_OUT_OF_MEMORY;
        goto __done;
    }

__done:
    slmp_free(frame);
    return ret;
}

MELCLIAPI int MELCLICALL melcli_buffer_write(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    uint32_t addr, int n, const uint16_t* data)
{
    int ret = MELCLI_ERROR_SUCCESS;
    slmp_req_memory_write_t *req = NULL;
    size_t req_data_len, req_size;
    slmp_frame_t *frame = NULL;
    int serial = -1;

    if ((ctx == NULL) || (data == NULL)) {
        ret = MELCLI_ERROR_INVALID_POINTER;
        goto __done;
    }

    if ((n <= 0) || (n >= 65536)) {
        ret = MELCLI_ERROR_INVALID_ARGUMENTS;
        goto __done;
    }

    req_data_len = 2 * n;
    req_size = sizeof(slmp_req_memory_write_t) + req_data_len - 1;
    req = (slmp_req_memory_write_t*)calloc(1, req_size);
    if (req == NULL) {
        ret = MELCLI_ERROR_OUT_OF_MEMORY;
        goto __done;
    }

    req->hdr.size = req_size;
    req->hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
    req->len = n;
    fill_units_write_data((const char*)data, UNIT_WORD, n, req->data);

    frame = build_req_frame(ctx, station, SLMP_CMD_DPMEM_BATCH_WRITE, 0x0000,
        &(req->hdr), slmp_encode_req_memory_write, &serial);
    if (frame == NULL) {
        ret = MELCLI_ERROR_BUILD_REQUEST_FRAME;
        goto __done;
    }
     
    ret = send_frame(ctx, station, &frame, 1);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }

    ret = receive_frame(ctx, serial, &frame);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }

__done:
    free(req);
    slmp_free(frame);

    return ret;
}

MELCLIAPI int MELCLICALL melcli_remote_control(
    melcli_ctx_t* ctx, const melcli_station_t* station, int ctl_code,
    int flag, char** type_name, int* type_code)
{
    int ret = MELCLI_ERROR_SUCCESS;
    size_t req_size;
    slmp_cmd_hdr_t *req_hdr = NULL, *res_hdr = NULL;
    slmp_frame_t *frame = NULL;
    int serial = -1;

    if (ctx == NULL) {
        ret = MELCLI_ERROR_INVALID_POINTER;
        goto __done;
    }

    switch (ctl_code) {
    case MELCLI_REMOTE_RUN:
        req_size = sizeof(slmp_req_remote_run_t);
        break;
    case MELCLI_REMOTE_STOP:
        req_size = sizeof(slmp_req_remote_stop_t);
        break;
    case MELCLI_REMOTE_RESET:
        req_size = sizeof(slmp_req_remote_reset_t);
        break;
    case MELCLI_REMOTE_PAUSE:
        req_size = sizeof(slmp_req_remote_pause_t);
        break;
    case MELCLI_REMOTE_LATCH_CLEAR:
        req_size = sizeof(slmp_req_remote_latch_clear_t);
        break;
    case MELCLI_REMOTE_READ_TYPE_NAME:
        if ((type_name == NULL) || (type_code == NULL)) {
            ret = MELCLI_ERROR_INVALID_POINTER;
            goto __done;
        }
        else {
            *type_name = NULL;
            *type_code = 0;
        }
        req_size = sizeof(slmp_req_read_type_name_t);
        break;
    default:
        ret = MELCLI_ERROR_INVALID_ARGUMENTS;
        goto __done;
    }

    req_hdr = (slmp_cmd_hdr_t*)calloc(1, req_size);
    if (req_hdr == NULL) {
        ret = MELCLI_ERROR_OUT_OF_MEMORY;
        goto __done;
    }
    else {
        req_hdr->size = req_size;
        req_hdr->addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
    }

    if (ctl_code == MELCLI_REMOTE_RUN) {
        slmp_req_remote_run_t *req = (slmp_req_remote_run_t*)(req_hdr);
        if (flag & MELCLI_FORCE_MODE) {
            req->mode = 0x0003;
        }
        else {
            req->mode = 0x0001;
        }
        
        if (flag & MELCLI_CLEAR_EXCLUDE_LATCHED) {
            req->clear_mode = 0x01;
        }
        else if (flag & MELCLI_CLEAR_ALL) {
            req->clear_mode = 0x02;
        }
        else {
            req->clear_mode = 0x00;
        }
        
        frame = build_req_frame(ctx, station, SLMP_CMD_REMOTE_RUN, 0, req_hdr,
            slmp_encode_req_remote_run, &serial);
    }
    else if (ctl_code == MELCLI_REMOTE_PAUSE) {
        slmp_req_remote_pause_t *req = (slmp_req_remote_pause_t*)(req_hdr);
        if (flag & MELCLI_FORCE_MODE) {
            req->mode = 0x0003;
        }
        else {
            req->mode = 0x0001;
        }
        
        frame = build_req_frame(ctx, station, SLMP_CMD_REMOTE_PAUSE, 0, req_hdr,
            slmp_encode_req_remote_pause, &serial);
    }
    else if (ctl_code == MELCLI_REMOTE_READ_TYPE_NAME) {
        frame = build_req_frame(ctx, station, SLMP_CMD_REMOTE_READ_PROCESSOR_TYPE,
            0, req_hdr, slmp_encode_req_read_type_name, &serial);
    }
    else if (ctl_code == MELCLI_REMOTE_STOP) {
        slmp_req_remote_stop_t *req = (slmp_req_remote_stop_t*)(req_hdr);
        req->mode = 0x0001;
        
        frame = build_req_frame(ctx, station, SLMP_CMD_REMOTE_STOP, 0, req_hdr,
            slmp_encode_req_remote_stop, &serial);
    }
    else if (ctl_code == MELCLI_REMOTE_LATCH_CLEAR) {
        slmp_req_remote_latch_clear_t *req 
            = (slmp_req_remote_latch_clear_t*)(req_hdr);
        req->mode = 0x0001;
        
        frame = build_req_frame(ctx, station, SLMP_CMD_REMOTE_LATCH_CLEAR, 0, 
            req_hdr, slmp_encode_req_remote_latch_clear, &serial);
    }
    else if (ctl_code == MELCLI_REMOTE_RESET) {
        slmp_req_remote_reset_t *req = (slmp_req_remote_reset_t*)(req_hdr);
        req->mode = 0x0001;
        
        frame = build_req_frame(ctx, station, SLMP_CMD_REMOTE_RESET, 0, req_hdr,
            slmp_encode_req_remote_reset, &serial);
    }
    
    if (frame == NULL) {
        ret = MELCLI_ERROR_BUILD_REQUEST_FRAME;
        goto __done;
    }
    
    ret = send_frame(ctx, station, &frame, 1);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }

    if (ctl_code == MELCLI_REMOTE_READ_TYPE_NAME) {
        slmp_res_read_type_name_t *res = NULL;
        
        ret = receive_frame(ctx, serial, &frame);
        if (ret != MELCLI_ERROR_SUCCESS) {
            goto __done;
        }

        res_hdr = slmp_decode_res_read_type_name(frame->raw_data,
            SLMP_FRAME_RAW_DATA_SIZE(frame), SLMP_BINARY_STREAM, 
            SLMP_ADDRESS_WIDTH_DONT_CARE);
        if (res_hdr == NULL) {
            if (ctx->debug) {
                ctx->dbgprint("[ERROR] Failed to decode the response frame. %s\n",
                    slmp_get_err_msg(slmp_get_errno()));
                ret = MELCLI_ERROR_DECODE_FRAME;
                goto __done;
            }
        }
        else {
            res = (slmp_res_read_type_name_t*)(res_hdr);
        }
        
        *type_name = (char*)calloc(1, sizeof(res->type) + 1);
        if (*type_name == NULL) {
            free(*type_name);
            ret = MELCLI_ERROR_OUT_OF_MEMORY;
            goto __done;
        }
        
        strlcpy(*type_name, (const char*)(res->type), sizeof(res->type) + 1);
        *type_code = (int)(res->type_code);
    }
    else {
        slmp_pktio_discard(ctx->pktio);
    }
    
__done:
    free(req_hdr);
    slmp_free(frame);
    slmp_free(res_hdr);
    return ret;
}

MELCLIAPI int MELCLICALL melcli_remote_run(
    melcli_ctx_t* ctx, const melcli_station_t* station, int flag)
{
    return melcli_remote_control(ctx, station, MELCLI_REMOTE_RUN, flag,
        NULL, NULL);
}

MELCLIAPI int MELCLICALL melcli_remote_stop(
    melcli_ctx_t* ctx, const melcli_station_t* station)
{
    return melcli_remote_control(ctx, station, MELCLI_REMOTE_STOP, 0,
        NULL, NULL);
}

MELCLIAPI int MELCLICALL melcli_remote_reset(
    melcli_ctx_t* ctx, const melcli_station_t* station)
{
    return melcli_remote_control(ctx, station, MELCLI_REMOTE_RESET, 0,
        NULL, NULL);
}

MELCLIAPI int MELCLICALL melcli_remote_pause(
    melcli_ctx_t* ctx, const melcli_station_t* station, int flag)
{
    return melcli_remote_control(ctx, station, MELCLI_REMOTE_PAUSE, flag,
        NULL, NULL);
}

MELCLIAPI int MELCLICALL melcli_remote_latch_clear(
    melcli_ctx_t* ctx, const melcli_station_t* station)
{
    return melcli_remote_control(ctx, station, MELCLI_REMOTE_LATCH_CLEAR, 0,
        NULL, NULL);
}

MELCLIAPI int MELCLICALL melcli_remote_read_type_name(
    melcli_ctx_t* ctx, const melcli_station_t* station, char** type_name, 
    int* type_code)
{
    return melcli_remote_control(ctx, station, MELCLI_REMOTE_READ_TYPE_NAME, 0,
        type_name, type_code);
}

MELCLIAPI int MELCLICALL melcli_remote_password(
    melcli_ctx_t* ctx, const melcli_station_t* station, int lock,
    const char* password)
{
    int ret = MELCLI_ERROR_SUCCESS;
    size_t req_size;
    slmp_cmd_hdr_t *req_hdr = NULL;
    slmp_frame_t *frame = NULL;
    int serial = -1;
    size_t pswd_len;

    if ((ctx == NULL) || (password == NULL)) {
        ret = MELCLI_ERROR_INVALID_POINTER;
        goto __done;
    }

    if ((pswd_len = strlen(password)) == 0) {
        ret = MELCLI_ERROR_INVALID_ARGUMENTS;
        goto __done;
    }

    if (lock) {
        req_size = sizeof(slmp_req_password_lock_t);
    }
    else {
        req_size = sizeof(slmp_req_password_unlock_t);
    }

    req_hdr = (slmp_cmd_hdr_t*)calloc(1, req_size);
    if (req_hdr == NULL) {
        ret = MELCLI_ERROR_OUT_OF_MEMORY;
        goto __done;
    }
    else {
        req_hdr->size = req_size;
        req_hdr->addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
    }

    if (lock) {
        slmp_req_password_lock_t *req = (slmp_req_password_lock_t*)(req_hdr);
        req->len = (uint16_t)pswd_len;
        req->pwd = (uint8_t*)password;

        frame = build_req_frame(ctx, station, SLMP_CMD_REMOTE_PASSWORD_LOCK, 0,
            req_hdr, slmp_encode_req_password_lock, &serial);
    }
    else {
        slmp_req_password_unlock_t *req = (slmp_req_password_unlock_t*)(req_hdr);
        req->len = (uint16_t)pswd_len;
        req->pwd = (uint8_t*)password;

        frame = build_req_frame(ctx, station, SLMP_CMD_REMOTE_PASSWORD_UNLOCK, 0,
            req_hdr, slmp_encode_req_password_unlock, &serial);
    }
    
    if (frame == NULL) {
        ret = MELCLI_ERROR_BUILD_REQUEST_FRAME;
        goto __done;
    }
    
    ret = send_frame(ctx, station, &frame, 0);
    slmp_pktio_discard(ctx->pktio);

__done:
    free(req_hdr);
    slmp_free(frame);
    return ret;
}

MELCLIAPI int MELCLICALL melcli_remote_lock(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char* password)
{
    return melcli_remote_password(ctx, station, 1, password);
}

MELCLIAPI int MELCLICALL melcli_remote_unlock(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char* password)
{
    return melcli_remote_password(ctx, station, 0, password);
}

MELCLIAPI int MELCLICALL melcli_self_test(
    melcli_ctx_t* ctx, const melcli_station_t* station)
{
    static const char test_data[] = 
        "bGlic2xtcDIubGlibWVsY2xpIFNlbGYgVGVzdCBEYXRhCmFiY2RlZmdoaWprbG1ub3Bx"
        "cnN0dXZ3eHl6CkFCQ0RFRkdISUpLTE1OT1BRUlNUVVZXWFlaCjAxMjM0NTY3ODkKfiFA"
        "IyQlXiYqKClfK3t9OiI8Pj8sLi87J1tdLT1cfGAKTmV1Y3JlZGUKbGlxaW5wZW5nMjAx"
        "NEBzaW5hLmNvbQ==";

    int ret = MELCLI_ERROR_SUCCESS;
    size_t data_len, req_size;
    slmp_req_self_test_t *req = NULL;
    slmp_frame_t *frame = NULL;
    slmp_res_self_test_t *resp = NULL;
    int serial = -1;

    if (ctx == NULL) {
        ret = MELCLI_ERROR_INVALID_POINTER;
        goto __done;
    }

    data_len = strlen(test_data);
    req_size = sizeof(slmp_req_self_test_t) + data_len - 1;

    req = (slmp_req_self_test_t*)calloc(1, req_size);
    if (req == NULL) {
        ret = MELCLI_ERROR_OUT_OF_MEMORY;
        goto __done;
    }
    else {
        req->hdr.size = req_size;
        req->hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
        req->len = (uint16_t)data_len;
        memcpy(req->data, test_data, data_len);
    }

    frame = build_req_frame(ctx, station, SLMP_CMD_LOOPBACK_TEST, 0,
        (slmp_cmd_hdr_t*)(req), slmp_encode_req_self_test, &serial);
    if (frame == NULL) {
        ret = MELCLI_ERROR_BUILD_REQUEST_FRAME;
        goto __done;
    }

    ret = send_frame(ctx, station, &frame, 1);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }

    ret = receive_frame(ctx, serial, &frame);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }

    resp = (slmp_res_self_test_t*)slmp_decode_res_self_test(frame->raw_data, 
        SLMP_FRAME_RAW_DATA_SIZE(frame), SLMP_BINARY_STREAM, 
        SLMP_ADDRESS_WIDTH_DONT_CARE);
    if (resp == NULL) {
        if (ctx->debug) {
            ctx->dbgprint("[ERROR] Failed to decode the response frame. %s\n",
                slmp_get_err_msg(slmp_get_errno()));
        }
        ret = MELCLI_ERROR_DECODE_FRAME;
        goto __done;
    }
    
    if (resp->len != data_len) {
        if (ctx->debug) {
            ctx->dbgprint("[ERROR] Inconsistent data length.\n");
        }

        ret = MELCLI_ERROR_SELF_TEST_FAILED;
        goto __done;
    }

    if (memcmp(test_data, resp->data, resp->len) != 0) {
        if (ctx->debug) {
            ctx->dbgprint("[ERROR] The received data doesn't match the data "
                "that was sent.\n");
        }

        ret = MELCLI_ERROR_SELF_TEST_FAILED;
        goto __done;
    }

__done:
    free(req);
    slmp_free(resp);
    slmp_free(frame);
    return ret;
}

MELCLIAPI int MELCLICALL melcli_clear_error_code(
    melcli_ctx_t* ctx, const melcli_station_t* station)
{
    int ret = MELCLI_ERROR_SUCCESS;
    slmp_req_clear_error_code_t req;
    slmp_frame_t *frame = NULL;

    req.hdr.size = sizeof(slmp_req_clear_error_code_t);
    req.hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;

    frame = build_req_frame(ctx, station, SLMP_CMD_ERROR_CODE_INIT, 0,
        (slmp_cmd_hdr_t*)(&req), slmp_encode_req_clear_error_code, NULL);
    if (frame == NULL) {
        ret = MELCLI_ERROR_BUILD_REQUEST_FRAME;
        goto __done;
    }

    ret = send_frame(ctx, station, &frame, 0);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }
    
    slmp_pktio_discard(ctx->pktio);

__done:
    slmp_free(frame);
    return ret;
}

MELCLIAPI int MELCLICALL melcli_clear_error_history(
    melcli_ctx_t* ctx, const melcli_station_t* station)
{
    int ret = MELCLI_ERROR_SUCCESS;
    slmp_req_clear_error_history_t req;
    slmp_frame_t *frame = NULL;

    req.hdr.size = sizeof(slmp_req_clear_error_history_t);
    req.hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;

    frame = build_req_frame(ctx, station, SLMP_CMD_ERROR_HISTORY_INIT, 0,
        (slmp_cmd_hdr_t*)(&req), slmp_encode_req_clear_error_history, NULL);
    if (frame == NULL) {
        ret = MELCLI_ERROR_BUILD_REQUEST_FRAME;
        goto __done;
    }

    ret = send_frame(ctx, station, &frame, 0);
    if (ret != MELCLI_ERROR_SUCCESS) {
        goto __done;
    }
    
    slmp_pktio_discard(ctx->pktio);

__done:
    slmp_free(frame);
    return ret;
}

/* **************************************************************************/

#define MAX_DEV_ADDR_PREFIX_LEN     4

static const struct dev_type_lookup_entry {
    const char* prefix;
    uint16_t mem_type;
    int unit_type;
} dev_type_lookup_table[] = {
    { "SM", DEVICE_SM, UNIT_BIT },
    { "SD", DEVICE_SD, UNIT_WORD },
    { "X", DEVICE_X, UNIT_BIT },
    { "Y", DEVICE_Y, UNIT_BIT },
    { "M", DEVICE_M, UNIT_BIT },
    { "L", DEVICE_L, UNIT_BIT },
    { "F", DEVICE_F, UNIT_BIT },
    { "V", DEVICE_V, UNIT_BIT },
    { "B", DEVICE_B, UNIT_BIT },
    { "D", DEVICE_D, UNIT_WORD },
    { "W", DEVICE_W, UNIT_WORD },
    { "TS", DEVICE_TS, UNIT_BIT },
    { "TC", DEVICE_TC, UNIT_BIT },
    { "TN", DEVICE_TN, UNIT_WORD },
    { "LTS", DEVICE_LTS, UNIT_BIT },
    { "LTC", DEVICE_LTC, UNIT_BIT },
    { "LTN", DEVICE_LTN, UNIT_DWORD },
    { "STS", DEVICE_STS, UNIT_BIT },
    { "STC", DEVICE_STC, UNIT_BIT },
    { "STN", DEVICE_STN, UNIT_WORD },
    { "LSTS", DEVICE_LSTS, UNIT_BIT },
    { "LSTC", DEVICE_LSTC, UNIT_BIT },
    { "LSTN", DEVICE_LSTN, UNIT_DWORD },
    { "CS", DEVICE_CS, UNIT_BIT },
    { "CC", DEVICE_CC, UNIT_BIT },
    { "CN", DEVICE_CN, UNIT_WORD },
    { "LCS", DEVICE_LCS, UNIT_BIT },
    { "LCC", DEVICE_LCC, UNIT_BIT },
    { "LCN", DEVICE_LCN, UNIT_DWORD },
    { "SB", DEVICE_SB, UNIT_BIT },
    { "SW", DEVICE_SW, UNIT_WORD },
    { "DX", DEVICE_DX, UNIT_BIT },
    { "DY", DEVICE_DY, UNIT_BIT },
    { "Z", DEVICE_Z, UNIT_WORD },
    { "LZ", DEVICE_LZ, UNIT_DWORD },
    { "R", DEVICE_R, UNIT_WORD },
    { "ZR", DEVICE_ZR, UNIT_WORD },
    { "RD", DEVICE_RD, UNIT_WORD },
    { NULL, 0, 0 }
};

static int split_dev_addr(const char* addr, char* prefix, char* trailing)
{
    size_t len = strlen(addr);
    size_t i, j;

    memset(prefix, 0, MAX_DEV_ADDR_PREFIX_LEN + 1);
    memset(trailing, 0, len + 1);
    j = 0;

    for (i = 0; i != len; ++i) {
        char ch = addr[i];
        
        /* Skip spaces and tabs. */
        if ((ch == '\x20') || (ch == '\t')) {
            continue;
        }

        if (isalpha(ch)) {
            prefix[j] = toupper(ch);
            if (++j >= MAX_DEV_ADDR_PREFIX_LEN) {
                break;
            }
        }
    }

    if (j == 0) {
        return FALSE;
    }
    else if (j < len) {
        strlcpy(trailing, addr + j, len + 1);
    }

    return TRUE;
}

static int lookup_dev_type(const char* prefix, uint16_t* mem_type, 
    int* unit_type)
{
    size_t prefix_len;
    const struct dev_type_lookup_entry* entry;

    prefix_len = strlen(prefix);
    if (prefix_len == 0) {
        return FALSE;
    }

    for (entry = dev_type_lookup_table; entry->prefix != NULL; ++entry) {
        if (strcmp(entry->prefix, prefix) == 0) {
            break;
        }
    }

    if (entry->prefix == NULL) {
        return FALSE;
    }

    *mem_type = entry->mem_type;
    *unit_type = entry->unit_type;
    return TRUE;
}

static int cvt_dev_addr_l(const char* addr, uint16_t* mem_type, 
    uint32_t* addr_begin, int* unit_type)
{
    int ret = FALSE;
    size_t addr_len = strlen(addr);
    char prefix[MAX_DEV_ADDR_PREFIX_LEN + 1];
    char *trailing;
    size_t trailing_len;
    size_t i;
    int offset;

    do {
        trailing = malloc(addr_len + 1);
        if (trailing == NULL) {
            break;
        }

        if (!split_dev_addr(addr, prefix, trailing)) {
            break;
        }

        trailing_len = strlen(trailing);
        if (trailing_len == 0) {
            break;
        }

        for (i = 0; i != trailing_len; ++i) {
            if (!isdigit(trailing[i])) {
                break;
            }
        }

        if (!lookup_dev_type(prefix, mem_type, unit_type)) {
            break;
        }

        offset = atoi(trailing);
        *addr_begin = (uint32_t)offset;

        ret = TRUE;
    } while (0);

    free(trailing);
    return ret;
}

static int cvt_dev_addr_s(const char* addr, uint8_t* mem_type, 
    uint32_t* addr_begin, int* unit_type)
{
    uint16_t _mem_type;
    uint32_t _addr_begin;

    if (!cvt_dev_addr_l(addr, &_mem_type, &_addr_begin, unit_type)) {
        return FALSE;
    }

    if (_addr_begin >= 65536) {
        return FALSE;
    }

    *mem_type = (uint8_t)_mem_type;
    *addr_begin = _addr_begin & 0x0000FFFF;
    return TRUE;
}

static int parse_dev_addr(const char* addr, uint8_t* mem_type_s, 
    uint16_t* mem_type_l, uint32_t* addr_begin, int* use_32bit_addr, 
    int* unit_type)
{
    uint16_t mem_type;

    if (!cvt_dev_addr_l(addr, mem_type_l, addr_begin, unit_type)) {
        return FALSE;
    }

    mem_type = *mem_type_l;
    if ((mem_type == DEVICE_LTS) || (mem_type == DEVICE_LTC) 
        || (mem_type == DEVICE_LTN) || (mem_type == DEVICE_LSTS) 
        || (mem_type == DEVICE_LSTC) || (mem_type == DEVICE_LSTN) 
        || (mem_type == DEVICE_LCS) || (mem_type == DEVICE_LCC) 
        || (mem_type == DEVICE_LCN)  || (mem_type == DEVICE_LZ)
        || (mem_type == DEVICE_RD))
    {
        *use_32bit_addr = 1;
    }
    else if (*addr_begin <= 65535) {
        if (!cvt_dev_addr_s(addr, mem_type_s, addr_begin, unit_type)) {
            return FALSE;
        }
        else {
            *use_32bit_addr = 0;
        }
    }
    else {
        *use_32bit_addr = 1;
    }

    return TRUE;
}

static slmp_frame_t* build_req_frame(melcli_ctx_t* ctx, 
    const melcli_station_t* station, int cmd, int sub_cmd, slmp_cmd_hdr_t* hdr, 
    slmp_command_encode_t pfn_enc, int* serial)
{
    slmp_frame_t *frame;
    size_t data_len = pfn_enc(hdr, NULL, SLMP_BINARY_STREAM);
    const melcli_station_t *_station = station ? station : &(ctx->station);

    do {
        frame = slmp_calloc(1, SLMP_FRAME_STRUCT_SIZE(data_len));
        if (frame == NULL) {
            break;
        }

        frame->size = SLMP_FRAME_STRUCT_SIZE(data_len);

        frame->hdr.ftype = SLMP_FTYPE_REQ_MT;
        frame->hdr.serial = ++(ctx->serial);

        frame->sub_hdr.mt.net_no = _station->net_num;
        frame->sub_hdr.mt.node_no = _station->node_num;
        frame->sub_hdr.mt.dst_proc_no = _station->dst_proc_num;
        frame->sub_hdr.mt.data_len = (uint16_t)data_len;
        frame->sub_hdr.mt.un.timer = ctx->timeout.frame_timer;

        frame->cmd_data.mt.cmd = cmd;
        frame->cmd_data.mt.sub_cmd = sub_cmd;

        if (pfn_enc(hdr, frame->raw_data, SLMP_BINARY_STREAM) != data_len) {
            slmp_free(frame);
            frame = NULL;
            break;
        }
    } while (0);

    if (frame == NULL) {
        if (ctx->debug) {
            ctx->dbgprint("[ERROR] %s\n", slmp_get_err_msg(slmp_get_errno()));
        }
    }
    else if (serial) {
        *serial = ctx->serial;
    }

    return frame;
}

static int send_frame(melcli_ctx_t* ctx, const melcli_station_t* station,
    slmp_frame_t** frame, int free_after_sent)
{
    int ret = MELCLI_ERROR_SUCCESS;

    if (slmp_send_frames(ctx->pktio, frame, 1, SLMP_BINARY_STREAM, 0) != 1) {
        if (ctx->debug) {
            ctx->dbgprint("[ERROR] %s\n", slmp_get_err_msg(slmp_get_errno()));
        }

        ret = MELCLI_ERROR_SEND_FRAMES;
        goto __done;
    }

__done:
    if (free_after_sent) {
        slmp_free(*frame);
        *frame = NULL;
    }
    return ret;
}

static int receive_frame(melcli_ctx_t* ctx, int serial, slmp_frame_t** frame)
{
    int timeout;
    int frame_wait_time = ctx->timeout.frame_timer * 250;
    int stm_type;
      
    if (ctx->timeout.frame_timer == 0) {
        timeout = 0;
    }
    else if (ctx->timeout.frame_timeout > frame_wait_time) {
        timeout = ctx->timeout.frame_timeout;
    }
    else {
        timeout = frame_wait_time;
    }
    
    if (slmp_receive_frames(ctx->pktio, frame, 1, &stm_type, timeout) != 1)
    {
        if (ctx->debug) {
            ctx->dbgprint("[ERROR] %s\n", slmp_get_err_msg(slmp_get_errno()));
        }

        return MELCLI_ERROR_RECEIVE_FRAMES;
    }

    if ((*frame)->hdr.serial != serial) {
        if (ctx->debug) {
            ctx->dbgprint("[ERROR] Frame serial mismatch. "
                "Expected '%d' but received '%d'.\n", 
                serial, (*frame)->hdr.serial);
        }

        return MELCLI_ERROR_FRAME_SERIAL_MISMATCH;
    }

    if ((*frame)->hdr.ftype == SLMP_FTYPE_ERR_MT) {
        if (ctx->debug) {
            ctx->dbgprint("[ERROR] Endcode (0x%04X): %s\n", 
                    (*frame)->sub_hdr.mt.un.end_code,
                    slmp_get_endcode_msg((*frame)->sub_hdr.mt.un.end_code));
        }

        return MELCLI_ERROR_OPERATION_FAILED;
    }

    return MELCLI_ERROR_SUCCESS;
}

static int extract_units_read_data(const uint8_t* resp_data, int unit_type, 
    int n, uint8_t** buf, int* data_len)
{
    if (unit_type == UNIT_BIT) {
        uint8_t *buf_bit;
        int i, j;

        buf_bit = (uint8_t*)malloc(n * sizeof(uint8_t));
        if (buf_bit == NULL) {
            return FALSE;
        }
        else {
            *buf = buf_bit;
        }

        for (i = j = 0; i != (n + 1) / 2; ++i) {
            buf_bit[j++] = (resp_data[i] & 0xF0) ? 1 : 0;

            if (j >= n) {
                break;
            }
            else {
                buf_bit[j++] = (resp_data[i] & 0x0F) ? 1 : 0;
            }
        }

        if (data_len != NULL) {
            *data_len = n;
        }
    }
    else if (unit_type == UNIT_WORD) {
        uint16_t *buf_word;
        int i;

        buf_word = (uint16_t*)malloc(n * sizeof(uint16_t));
        if (buf_word == NULL) {
            return FALSE;
        }
        else {
            *buf = (uint8_t*)buf_word;
        }

        for (i = 0; i != n; ++i) {
            buf_word[i] 
                = (uint16_t)(resp_data[2 * i]) 
                | ((uint16_t)(resp_data[2 * i + 1]) << 8);
        }

        if (data_len != NULL) {
            *data_len = 2 * n;
        }
    }
    else if (unit_type == UNIT_DWORD) {
        uint32_t *buf_dword;
        int i;

        buf_dword = (uint32_t*)malloc(n * sizeof(uint32_t));
        if (buf_dword == NULL) {
            return FALSE;
        }
        else {
            *buf = (uint8_t*)buf_dword;
        }

        for (i = 0; i != n; ++i) {
            buf_dword[i] 
                = (uint32_t)(resp_data[4 * i]) 
                | ((uint32_t)(resp_data[4 * i + 1]) << 8)
                | ((uint32_t)(resp_data[4 * i + 2]) << 16)
                | ((uint32_t)(resp_data[4 * i + 3]) << 24);
        }

        if (data_len != NULL) {
            *data_len = 4 * n;
        }
    }
    else {
        return FALSE;
    }

    return TRUE;
}

static int fill_units_write_data(const char* src, int unit_type, int n, 
    uint8_t* data)
{
    int bytes_filled = 0;

    if (unit_type == UNIT_BIT) {
        int i, j;
        for (i = j = 0; i != (n + 1) / 2; ++i) {
            data[i] = src[j++] ? 0x10 : 0x00;

            if (j >= n) {
                break;
            }
            else {
                data[i] |= src[j++] ? 0x01 : 0x00;
            }
        }

        bytes_filled = (n + 1) / 2;
    }
    else if (unit_type == UNIT_WORD) {
        uint16_t *src_word = (uint16_t*)(src);
        int i;
        for (i = 0; i != n; ++i) {
            data[2 * i] = (uint8_t)(src_word[i] & 0xFF);
            data[2 * i + 1] = (uint8_t)((src_word[i] >> 8) & 0xFF);
        }

        bytes_filled = 2 * n;
    }
    else if (unit_type == UNIT_DWORD) {
        uint32_t *src_dword = (uint32_t*)(src);
        int i;
        for (i = 0; i != n; ++i) {
            data[4 * i] = (uint8_t)(src_dword[i] & 0xFF);
            data[4 * i + 1] = (uint8_t)((src_dword[i] >> 8) & 0xFF);
            data[4 * i + 2] = (uint8_t)((src_dword[i] >> 16) & 0xFF);
            data[4 * i + 3] = (uint8_t)((src_dword[i] >> 24) & 0xFF);
        }

        bytes_filled = 4 * n;
    }
    else {
        return -1;
    }

    return bytes_filled;
}

static int encode_dev_random_read_units(const char** addrs, int* use_32bit_addr, 
    uint8_t** pstrm)
{
    const char** addr;
    uint8_t mem_type_s;
    uint16_t mem_type_l;
    uint32_t addr_begin;
    int _use_32bit_addr;
    int unit_type;
    slmp_req_device_read_random_unit_t req_unit;
    size_t bytes_wr;
    
    req_unit.hdr.size = sizeof(slmp_req_device_read_random_unit_t);
    req_unit.hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
    
    for (addr = addrs; (addrs != NULL) && (*addr != NULL); ++addr) {
        if (!parse_dev_addr(*addr, &mem_type_s, &mem_type_l, &addr_begin, 
            &_use_32bit_addr, &unit_type))
        {
            return MELCLI_ERROR_INVALID_ADDRESS;
        }
        
        if (_use_32bit_addr) {
            *use_32bit_addr = TRUE;
            
            req_unit.mem_type.bin.l = mem_type_l;
            req_unit.addr.bin.l = addr_begin;
        }
        else {
            req_unit.mem_type.bin.s = mem_type_s;
            req_unit.addr.bin.s = addr_begin;
        }
        
        bytes_wr = slmp_encode_req_device_read_random_unit(
            (slmp_cmd_hdr_t*)(&req_unit), *pstrm, SLMP_BINARY_STREAM);
        if (bytes_wr == 0) {
            return MELCLI_ERROR_ENCODE_COMMAND;
        }
        else {
            *pstrm += bytes_wr;
        }
    }
    
    return MELCLI_ERROR_SUCCESS;
}

static int fill_dev_random_write_bit_units(const char** addrs, 
    const uint8_t* data, int* use_32bit_addr, uint8_t** pstrm)
{
    const char** addr;
    uint8_t mem_type_s;
    uint16_t mem_type_l;
    uint32_t addr_begin;
    int _use_32bit_addr;
    int unit_type;
    slmp_req_device_write_random_bit_unit_t req_unit;
    size_t bytes_wr;
    
    req_unit.hdr.size = sizeof(slmp_req_device_write_random_bit_unit_t);
    req_unit.hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
    
    for (addr = addrs; (addrs != NULL) && (*addr != NULL); ++addr) {
        if (!parse_dev_addr(*addr, &mem_type_s, &mem_type_l, &addr_begin, 
            &_use_32bit_addr, &unit_type))
        {
            return MELCLI_ERROR_INVALID_ADDRESS;
        }
        
        if (_use_32bit_addr) {
            *use_32bit_addr = TRUE;
            
            req_unit.mem_type.bin.l = mem_type_l;
            req_unit.addr.bin.l = addr_begin;
            req_unit.data.bin.l = *(data++) ? 1 : 0;
        }
        else {
            req_unit.mem_type.bin.s = mem_type_s;
            req_unit.addr.bin.s = addr_begin;
            req_unit.data.bin.s = *(data++) ? 1 : 0;
        }
        
        bytes_wr = slmp_encode_req_device_write_random_bit_unit(
            (slmp_cmd_hdr_t*)(&req_unit), *pstrm, SLMP_BINARY_STREAM);
        if (bytes_wr == 0) {
            return MELCLI_ERROR_ENCODE_COMMAND;
        }
        else {
            *pstrm += bytes_wr;
        }
    }
    
    return MELCLI_ERROR_SUCCESS;
}

static int fill_dev_random_write_word_units(const char** addrs, 
    const uint16_t* data, int* use_32bit_addr, uint8_t** pstrm)
{
    const char** addr;
    uint8_t mem_type_s;
    uint16_t mem_type_l;
    uint32_t addr_begin;
    int _use_32bit_addr;
    int unit_type;
    slmp_req_device_write_random_word_unit_t req_unit;
    size_t bytes_wr;
    
    req_unit.hdr.size = sizeof(slmp_req_device_write_random_word_unit_t);
    req_unit.hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
    
    for (addr = addrs; (addrs != NULL) && (*addr != NULL); ++addr) {
        if (!parse_dev_addr(*addr, &mem_type_s, &mem_type_l, &addr_begin, 
            &_use_32bit_addr, &unit_type))
        {
            return MELCLI_ERROR_INVALID_ADDRESS;
        }
        
        if (_use_32bit_addr) {
            *use_32bit_addr = TRUE;
            
            req_unit.mem_type.bin.l = mem_type_l;
            req_unit.addr.bin.l = addr_begin;
            req_unit.data = *(data++);
        }
        else {
            req_unit.mem_type.bin.s = mem_type_s;
            req_unit.addr.bin.s = addr_begin;
            req_unit.data = *(data++);
        }
        
        bytes_wr = slmp_encode_req_device_write_random_word_unit(
            (slmp_cmd_hdr_t*)(&req_unit), *pstrm, SLMP_BINARY_STREAM);
        if (bytes_wr == 0) {
            return MELCLI_ERROR_ENCODE_COMMAND;
        }
        else {
            *pstrm += bytes_wr;
        }
    }
    
    return MELCLI_ERROR_SUCCESS;
}

static int fill_dev_random_write_dword_units(const char** addrs, 
    const uint32_t* data, int* use_32bit_addr, uint8_t** pstrm)
{
    const char** addr;
    uint8_t mem_type_s;
    uint16_t mem_type_l;
    uint32_t addr_begin;
    int _use_32bit_addr;
    int unit_type;
    slmp_req_device_write_random_dword_unit_t req_unit;
    size_t bytes_wr;
    
    req_unit.hdr.size = sizeof(slmp_req_device_write_random_dword_unit_t);
    req_unit.hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
    
    for (addr = addrs; (addrs != NULL) && (*addr != NULL); ++addr) {
        if (!parse_dev_addr(*addr, &mem_type_s, &mem_type_l, &addr_begin, 
            &_use_32bit_addr, &unit_type))
        {
            return MELCLI_ERROR_INVALID_ADDRESS;
        }
        
        if (_use_32bit_addr) {
            *use_32bit_addr = TRUE;
            
            req_unit.mem_type.bin.l = mem_type_l;
            req_unit.addr.bin.l = addr_begin;
            req_unit.data = *(data++);
        }
        else {
            req_unit.mem_type.bin.s = mem_type_s;
            req_unit.addr.bin.s = addr_begin;
            req_unit.data = *(data++);
        }
        
        bytes_wr = slmp_encode_req_device_write_random_dword_unit(
            (slmp_cmd_hdr_t*)(&req_unit), *pstrm, SLMP_BINARY_STREAM);
        if (bytes_wr == 0) {
            return MELCLI_ERROR_ENCODE_COMMAND;
        }
        else {
            *pstrm += bytes_wr;
        }
    }
    
    return MELCLI_ERROR_SUCCESS;
}

