/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "slmp/slmp.h"
#include "slmp/command/intmem.h"

#define BUFFER_SIZE         1024

static void hex_dump(void* data, int n);
static void print_errmsg();

int main(int argc, char *argv[])
{
    int ret = 0;
    
    slmp_req_device_read_t *req = NULL;
    size_t req_len;
    slmp_frame_t *frame = NULL;
    uint8_t buf[BUFFER_SIZE];
    size_t len;
    
    printf(
        "**************************************** \n"
        "  Frame & Command Codec Functions Demo   \n"
        "**************************************** \n\n"
    );

    /* ***********************************************************************/
    printf("Encode\n");

    /* Allocate memory for request command. */
    req = (slmp_req_device_read_t*)slmp_malloc(sizeof(slmp_req_device_read_t));
    if (req == NULL) {
        printf("Out of memory. \n");
        ret = 1;
        goto __cleanup;
    }
    
    /* Fill in request info. */
    memset(req, 0, sizeof(slmp_req_device_read_t));
    req->hdr.addr_width = SLMP_ADDRESS_16BIT;
    req->hdr.size = sizeof(slmp_req_device_read_t);
    req->mem_type.bin.s = 0x9D;
    req->addr_begin.bin.s = 0x000000;
    req->num = 8;
    
    /* Compute minimum stream length required for command encoding. */
    req_len = slmp_encode_req_device_read(&(req->hdr), NULL, SLMP_BINARY_STREAM);
    if (req_len == 0) {
        printf("slmp_encode_req_device_read() failed. ");
        print_errmsg();
        
        ret = 1;
        goto __cleanup;
    }
    else {
        printf("slmp_encode_req_device_read() succeeded. \n");
    }

    /* Allocate memory for frame. */
    frame = slmp_calloc(1, SLMP_FRAME_STRUCT_SIZE(req_len));
    if (frame == NULL) {
        printf("Out of memory. \n");
        ret = 1;
        goto __cleanup;
    }
    
    /* 
     * Use SLMP_FRAME_STRUCT_SIZE() macro to compute `size` field from encoded
     * raw data length.
     */
    frame->size = SLMP_FRAME_STRUCT_SIZE(req_len);
    frame->hdr.ftype = SLMP_FTYPE_REQ_ST;
    frame->sub_hdr.st.net_no = SLMP_NETWORK_CONNECTED;
    frame->sub_hdr.st.node_no = 0xFF;
    frame->sub_hdr.st.dst_proc_no = SLMP_PROC_DEFAULT;
    frame->sub_hdr.st.un.timer = 0x05;
    frame->cmd_data.st.cmd = SLMP_CMD_MEM_BATCH_READ;
    frame->cmd_data.st.sub_cmd = SLMP_SUBCMD_MEM_BIT_ADDR_16;
    
    /* Encode command. */ 
    if (slmp_encode_req_device_read(&(req->hdr), frame->raw_data, 
        SLMP_BINARY_STREAM) != req_len)
    {
        printf("slmp_encode_req_device_read() failed. ");
        print_errmsg();
        
        ret = 1;
        goto __cleanup;
    }
    else {
        printf("slmp_encode_req_device_read() succeeded. \n");
    }
    
    /* Encode frame. */
    len = slmp_encode_frame(frame, buf, SLMP_BINARY_STREAM);
    if (len == 0) {    
        printf("slmp_encode_frame() failed. ");
        print_errmsg();
        
        ret = 1;
        goto __cleanup;
    }
    else {
        printf("slmp_encode_frame() succeeded. \n");
    }
    
    printf("Data stream: ");
    hex_dump(buf, len);
    
    slmp_free(frame);
    slmp_free(req);

    /* ***********************************************************************/
    printf("\nDecode\n");

    /* Decode the data stream created by previous call of slmp_encode_frame(). */
    frame = slmp_decode_frame(buf, len, SLMP_BINARY_STREAM, NULL);
    if (frame == NULL) {
        printf("slmp_decode_frame() failed. ");
        print_errmsg();
        
        ret = 1;
        goto __cleanup;
    }
    else {
        printf("slmp_decode_frame() succeeded. \n");
    }

    /* 
     * Decode the request command from frame payload. Note the usage of macro
     * SLMP_FRAME_RAW_DATA_SIZE().
     */
    req = (slmp_req_device_read_t*)slmp_decode_req_device_read(frame->raw_data, 
        SLMP_FRAME_RAW_DATA_SIZE(frame), SLMP_BINARY_STREAM, SLMP_ADDRESS_16BIT);
    if (req == NULL) {
        printf("slmp_decode_req_device_read() failed. ");
        print_errmsg();
        
        ret = 1;
        goto __cleanup;
    }
    else {
        printf("slmp_decode_req_device_read() succeeded. \n");
    }
    
__cleanup:
    /* Release resources. */
    slmp_free(frame);
    slmp_free(req);

    return ret;
}

static void hex_dump(void* data, int n)
{
    int i;
    
    for (i = 0; i != n; ++i) {
        printf("%02X ", ((unsigned char*)(data))[i] & 0xFF);
    }
    printf("\n");
}

static void print_errmsg()
{
    int err = slmp_get_errno();
    const char* errmsg = slmp_get_err_msg(err);
    
    printf("Error (%d): %s\n", err, errmsg);
}
