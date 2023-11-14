/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include "framecodec.h"

SLMPAPI size_t SLMPCALL slmp_encode_frame(
    slmp_frame_t *frame, uint8_t *stream, int type)
{
    pfn_encode_frame_t encode_frame = NULL;

    assert(frame != NULL);
    if (frame == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    assert((type == SLMP_BINARY_STREAM) || (type == SLMP_ASCII_STREAM));
    if (!((type == SLMP_BINARY_STREAM) || (type == SLMP_ASCII_STREAM))) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    switch (frame->hdr.ftype) {
    case SLMP_FTYPE_REQ_ST:
    case SLMP_FTYPE_RES_ST:
    case SLMP_FTYPE_ERR_ST:
        encode_frame = &encode_frame_st;
        break;
    case SLMP_FTYPE_REQ_MT:
    case SLMP_FTYPE_RES_MT:
    case SLMP_FTYPE_ERR_MT:
        encode_frame = &encode_frame_mt;
        break;
    case SLMP_FTYPE_REQ_EMT:
    case SLMP_FTYPE_PUSH_EMT:
    case SLMP_FTYPE_RES_EMT:
        encode_frame = &encode_frame_emt;
        break;
    case SLMP_FTYPE_REQ_LMT:
    case SLMP_FTYPE_RES_LMT:
    case SLMP_FTYPE_ERR_LMT:
        assert(type != SLMP_ASCII_STREAM);
        if (type == SLMP_ASCII_STREAM) {
            slmp_set_errno(SLMP_ERROR_BAD_STREAM_TYPE);
            return 0;
        }
        encode_frame = &encode_frame_lmt;
        break;
    default:
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    slmp_set_errno(SLMP_ERROR_SUCCESS);
    return encode_frame(frame, stream, type);
}

SLMPAPI slmp_frame_t* SLMPCALL slmp_decode_frame(
    uint8_t *stream, size_t len, int type, size_t *len_remains)
{
    pfn_codec_ptr_t dec16bp = NULL;
    pfn_decode_frame_t decode_frame = NULL;
    uint16_t ftype;

    assert(stream != NULL);
    if (stream == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return NULL;
    }

    assert((type == SLMP_BINARY_STREAM) || (type == SLMP_ASCII_STREAM));
    if (!((type == SLMP_BINARY_STREAM) || (type == SLMP_ASCII_STREAM))) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return NULL;
    }

    assert(len >= SLMP_MIN_FRAME_STREAM_LENGTH);
    if (len < SLMP_MIN_FRAME_STREAM_LENGTH) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return NULL;
    }

    if (type == SLMP_BINARY_STREAM) {
        dec16bp = &decode_bin_16b_ptr;
    }
    else {
        dec16bp = &decode_ascii_16b_ptr;
    }

    /* FTYPE is always at the very beginning of the stream. */
    dec16bp(stream, &ftype);

    switch (ftype) {
    case SLMP_FTYPE_REQ_ST:
    case SLMP_FTYPE_RES_ST:
        decode_frame = &decode_frame_st;
        break;
    case SLMP_FTYPE_REQ_MT:
    case SLMP_FTYPE_RES_MT:
        decode_frame = &decode_frame_mt;
        break;
    case SLMP_FTYPE_REQ_EMT:
    case SLMP_FTYPE_PUSH_EMT:
    case SLMP_FTYPE_RES_EMT:
        decode_frame = &decode_frame_emt;
        break;
    case SLMP_FTYPE_REQ_LMT:
    case SLMP_FTYPE_RES_LMT:
        assert(type != SLMP_ASCII_STREAM);
        if (type == SLMP_ASCII_STREAM) {
            slmp_set_errno(SLMP_ERROR_BAD_STREAM_TYPE);
            return 0;
        }
        decode_frame = &decode_frame_lmt;
        break;
    default:
        return NULL;
    }
    
    slmp_set_errno(SLMP_ERROR_SUCCESS);
    return decode_frame(stream, len, type, len_remains);
}

size_t encode_frame_st(slmp_frame_t *frame, uint8_t *stream, int type)
{
    ENCODE_FRAME_DECLARE_LOCAL_VARIABLES();
    ENCODE_FRAME_INITIALIZE_LOCAL_VARIABLES_1();
    ENCODE_FRAME_BEGIN_SWITCH_FTYPE()
        ENCODE_FRAME_CASE_FTYPE(REQ_ST)
        ENCODE_FRAME_CASE_FTYPE(RES_ST)
        ENCODE_FRAME_CASE_FTYPE(ERR_ST)
    ENCODE_FRAME_END_SWITCH_FTYPE()
    ENCODE_FRAME_INITIALIZE_LOCAL_VARIABLES_2();

    if (stream == NULL) {
        return min_buf_size;
    }

    /* Header */
    enc16b((uint16_t)(frame->hdr.ftype & SLMP_FTYPE_MASK),
        &(stream[m * SLMP_ST_HDR_FTYPE_OFFSET]));

    /* Sub header*/
    enc8b(frame->sub_hdr.st.net_no,
        &(stream[m * SLMP_ST_SUBHDR_NET_NO_OFFSET]));
    enc8b(frame->sub_hdr.st.node_no,
        &(stream[m * SLMP_ST_SUBHDR_NODE_NO_OFFSET]));
    enc16b(frame->sub_hdr.st.dst_proc_no,
        &(stream[m * SLMP_ST_SUBHDR_DST_PROC_NO_OFFSET]));
    enc8b(0, &(stream[m * SLMP_ST_SUBHDR_RESERVED1_OFFSET]));
    enc16b((uint16_t)dl, &(stream[m * SLMP_ST_SUBHDR_DL_OFFSET]));
    enc16bp(&(frame->sub_hdr.st.un),
        &(stream[m * SLMP_ST_SUBHDR_TIMER_ENDCODE_RESERVED2_OFFSET]));

    switch (frame->hdr.ftype) {
    case SLMP_FTYPE_REQ_ST:
        /* Command */
        enc16b(frame->cmd_data.st.cmd, &(stream[m * SLMP_ST_CMD_OFFSET]));
        /* Sub-command */
        enc16b(frame->cmd_data.st.sub_cmd,
            &(stream[m * SLMP_ST_SUBCMD_OFFSET]));
        /* Request data */
        encnp(frame->raw_data, &(stream[m * SLMP_ST_REQDATA_OFFSET]),
            raw_data_len);
        break;
    case SLMP_FTYPE_RES_ST:
        /* Response data */
        encnp(frame->raw_data, &(stream[m * SLMP_ST_RESDATA_OFFSET]),
            raw_data_len);
        break;
    case SLMP_FTYPE_ERR_ST:
        /* Error information */
        enc8b(frame->err_info.st.net_no,
            &(stream[m * SLMP_ST_ERRINFO_NET_NO_OFFSET]));
        enc8b(frame->err_info.st.node_no,
            &(stream[m * SLMP_ST_ERRINFO_NODE_NO_OFFSET]));
        enc16b(frame->err_info.st.dst_proc_no,
            &(stream[m * SLMP_ST_ERRINFO_DST_PROC_NO_OFFSET]));
        enc8b(0, &(stream[m * SLMP_ST_ERRINFO_RESERVED1_OFFSET]));
        enc16b(frame->err_info.st.cmd,
            &(stream[m * SLMP_ST_ERRINFO_CMD_OFFSET]));
        enc16b(frame->err_info.st.sub_cmd,
            &(stream[m * SLMP_ST_ERRINFO_SUBCMD_OFFSET]));
        /* Response data */
        encnp(frame->raw_data, &(stream[m * SLMP_ST_ERRDATA_OFFSET]),
            raw_data_len);
        break;
    default:
        break;
    }

    slmp_set_errno(SLMP_ERROR_SUCCESS);
    return min_buf_size;
}

size_t encode_frame_mt(slmp_frame_t *frame, uint8_t *stream, int type)
{
    ENCODE_FRAME_DECLARE_LOCAL_VARIABLES();
    ENCODE_FRAME_INITIALIZE_LOCAL_VARIABLES_1();
    ENCODE_FRAME_BEGIN_SWITCH_FTYPE()
        ENCODE_FRAME_CASE_FTYPE(REQ_MT)
        ENCODE_FRAME_CASE_FTYPE(RES_MT)
        ENCODE_FRAME_CASE_FTYPE(ERR_MT)
    ENCODE_FRAME_END_SWITCH_FTYPE()
    ENCODE_FRAME_INITIALIZE_LOCAL_VARIABLES_2();

    if (stream == NULL) {
        return min_buf_size;
    }

    /* Header */
    enc16b((uint16_t)(frame->hdr.ftype & SLMP_FTYPE_MASK),
        &(stream[m * SLMP_MT_HDR_FTYPE_OFFSET]));
    enc16b(frame->hdr.serial, &(stream[m * SLMP_MT_HDR_SERIAL_OFFSET]));
    enc16b(0, &(stream[m * SLMP_MT_HDR_RESERVED1_OFFSET]));

    /* Sub-header */
    enc8b(frame->sub_hdr.mt.net_no,
        &(stream[m * SLMP_MT_SUBHDR_NET_NO_OFFSET]));
    enc8b(frame->sub_hdr.mt.node_no,
        &(stream[m * SLMP_MT_SUBHDR_NODE_NO_OFFSET]));
    enc16b(frame->sub_hdr.mt.dst_proc_no,
        &(stream[m * SLMP_MT_SUBHDR_DST_PROC_NO_OFFSET]));
    enc8b(0, &(stream[m * SLMP_MT_SUBHDR_RESERVED1_OFFSET]));
    enc16b((uint16_t)dl, &(stream[m * SLMP_MT_SUBHDR_DL_OFFSET]));
    enc16bp(&(frame->sub_hdr.mt.un),
        &(stream[m * SLMP_MT_SUBHDR_TIMER_ENDCODE_RESERVED3_OFFSET]));

    switch (frame->hdr.ftype) {
    case SLMP_FTYPE_REQ_MT:
        /* Command */
        enc16b(frame->cmd_data.mt.cmd, &(stream[m * SLMP_MT_CMD_OFFSET]));
        /* Sub-command */
        enc16b(frame->cmd_data.mt.sub_cmd,
            &(stream[m * SLMP_MT_SUBCMD_OFFSET]));
        /* Request data */
        encnp(frame->raw_data, &(stream[m * SLMP_MT_REQDATA_OFFSET]),
            raw_data_len);
        break;
    case SLMP_FTYPE_RES_MT:
        /* Response data */
        encnp(frame->raw_data, &(stream[m * SLMP_MT_RESDATA_OFFSET]),
            raw_data_len);
        break;
    case SLMP_FTYPE_ERR_MT:
        /* Error information */
        enc8b(frame->err_info.mt.net_no,
            &(stream[m * SLMP_MT_ERRINFO_NET_NO_OFFSET]));
        enc8b(frame->err_info.mt.node_no,
            &(stream[m * SLMP_MT_ERRINFO_NODE_NO_OFFSET]));
        enc16b(frame->err_info.mt.dst_proc_no,
            &(stream[m * SLMP_MT_ERRINFO_DST_PROC_NO_OFFSET]));
        enc8b(0, &(stream[m * SLMP_MT_ERRINFO_RESERVED1_OFFSET]));
        enc16b(frame->err_info.mt.cmd,
            &(stream[m * SLMP_MT_ERRINFO_CMD_OFFSET]));
        enc16b(frame->err_info.mt.sub_cmd,
            &(stream[m * SLMP_MT_ERRINFO_SUBCMD_OFFSET]));
        /* Response data */
        encnp(frame->raw_data, &(stream[m * SLMP_MT_ERRDATA_OFFSET]),
            raw_data_len);
        break;
    default:
        break;
    }

    return min_buf_size;
}

size_t encode_frame_emt(slmp_frame_t *frame, uint8_t *stream, int type)
{
    ENCODE_FRAME_DECLARE_LOCAL_VARIABLES();
    ENCODE_FRAME_INITIALIZE_LOCAL_VARIABLES_1();
    ENCODE_FRAME_BEGIN_SWITCH_FTYPE()
        ENCODE_FRAME_CASE_FTYPE(REQ_EMT)
        ENCODE_FRAME_CASE_FTYPE(RES_EMT)
        ENCODE_FRAME_CASE_FTYPE(PUSH_EMT)
    ENCODE_FRAME_END_SWITCH_FTYPE()
    ENCODE_FRAME_INITIALIZE_LOCAL_VARIABLES_2();

    if (stream == NULL) {
        return min_buf_size;
    }

    /* Header */
    enc16b((uint16_t)(frame->hdr.ftype & SLMP_FTYPE_MASK),
        &(stream[m * SLMP_EMT_HDR_FTYPE_OFFSET]));
    enc16b(frame->hdr.serial, &(stream[m * SLMP_EMT_HDR_SERIAL_OFFSET]));
    enc16b(0, &(stream[m * SLMP_EMT_HDR_RESERVED2_OFFSET]));

    /* Sub-header */
    enc8b(frame->sub_hdr.emt.dst_net_no,
        &(stream[m * SLMP_EMT_SUBHDR_DST_NET_NO_OFFSET]));
    enc8b(frame->sub_hdr.emt.dst_node_no,
        &(stream[m * SLMP_EMT_SUBHDR_DST_NODE_NO_OFFSET]));
    enc16b(frame->sub_hdr.emt.dst_proc_no,
        &(stream[m * SLMP_EMT_SUBHDR_DST_PROC_NO_OFFSET]));
    enc8b(frame->sub_hdr.emt.src_net_no,
        &(stream[m * SLMP_EMT_SUBHDR_SRC_NET_NO_OFFSET]));
    enc8b(frame->sub_hdr.emt.src_node_no,
        &(stream[m * SLMP_EMT_SUBHDR_SRC_NODE_NO_OFFSET]));
    enc16b(frame->sub_hdr.emt.src_proc_no,
        &(stream[m * SLMP_EMT_SUBHDR_SRC_PROC_NO_OFFSET]));
    enc8b(frame->sub_hdr.emt.pkt_type,
        &(stream[m * SLMP_EMT_SUBHDR_PKT_TYPE_OFFSET]));
    enc8b(0, &(stream[m * SLMP_EMT_SUBHDR_RESERVED1_OFFSET]));
    enc16b(frame->sub_hdr.emt.flgm,
        &(stream[m * SLMP_EMT_SUBHDR_FLGM_OFFSET]));
    enc16b((uint16_t)dl, &(stream[m * SLMP_EMT_SUBHDR_DL_OFFSET]));

    switch (frame->hdr.ftype) {
    case SLMP_FTYPE_REQ_EMT:
        /* fall-through */
    case SLMP_FTYPE_PUSH_EMT:
        /* Command */
        enc16b(frame->cmd_data.emt.cmd, &(stream[m * SLMP_EMT_CMD_OFFSET]));
        /* Sub-command */
        enc16b(frame->cmd_data.emt.sub_cmd,
            &(stream[m * SLMP_EMT_SUBCMD_OFFSET]));
        /* Request data */
        encnp(frame->raw_data, &(stream[m * SLMP_EMT_REQDATA_OFFSET]),
            raw_data_len);
        break;
    case SLMP_FTYPE_RES_EMT:
        /* Command */
        enc16b(frame->cmd_data.emt.cmd, &(stream[m * SLMP_EMT_CMD_OFFSET]));
        /* Sub-command */
        enc16b(frame->cmd_data.emt.sub_cmd,
            &(stream[m * SLMP_EMT_SUBCMD_OFFSET]));
        /* End code */
        enc16b(frame->cmd_data.emt.end_code,
            &(stream[m * SLMP_EMT_ENDCODE_OFFSET]));
        /* Response data */
        encnp(frame->raw_data, &(stream[m * SLMP_EMT_RESDATA_OFFSET]),
            raw_data_len);
        break;
    default:
        break;
    }

    return min_buf_size;
}

size_t encode_frame_lmt(slmp_frame_t *frame, uint8_t *stream, int type)
{
    ENCODE_FRAME_DECLARE_LOCAL_VARIABLES();

    /* The station number extended MT type has only binary mode. */
    assert(type != SLMP_ASCII_STREAM);

    ENCODE_FRAME_INITIALIZE_LOCAL_VARIABLES_1();
    ENCODE_FRAME_BEGIN_SWITCH_FTYPE()
        ENCODE_FRAME_CASE_FTYPE(REQ_LMT)
        ENCODE_FRAME_CASE_FTYPE(RES_LMT)
        ENCODE_FRAME_CASE_FTYPE(ERR_LMT)
    ENCODE_FRAME_END_SWITCH_FTYPE()
    ENCODE_FRAME_INITIALIZE_LOCAL_VARIABLES_2();

    if (stream == NULL) {
        return min_buf_size;
    }

    /* Header */
    enc16b((uint16_t)(frame->hdr.ftype & SLMP_FTYPE_MASK),
        &(stream[m * SLMP_LMT_HDR_FTYPE_OFFSET]));
    enc16b(frame->hdr.serial, &(stream[m * SLMP_LMT_HDR_SERIAL_OFFSET]));
    enc16b(0, &(stream[m * SLMP_LMT_HDR_RESERVED1_OFFSET]));

    /* Sub-header */
    enc8b(frame->sub_hdr.lmt.net_no,
        &(stream[m * SLMP_LMT_SUBHDR_NET_NO_OFFSET]));
    enc8b(frame->sub_hdr.lmt.node_no,
        &(stream[m * SLMP_LMT_SUBHDR_NODE_NO_OFFSET]));
    enc16b(frame->sub_hdr.lmt.dst_proc_no,
        &(stream[m * SLMP_LMT_SUBHDR_DST_PROC_NO_OFFSET]));
    enc8b(frame->sub_hdr.lmt.dst_proc_sub_no,
        &(stream[m * SLMP_LMT_SUBHDR_DST_PROC_SUB_NO_OFFSET]));
    enc8b(0, &(stream[m * SLMP_LMT_SUBHDR_RESERVED2_OFFSET]));
    enc16b(frame->sub_hdr.lmt.large_node_no,
        &(stream[m * SLMP_LMT_SUBHDR_LARGE_NODE_NO_OFFSET]));
    enc16b((uint16_t)dl, &(stream[m * SLMP_LMT_SUBHDR_DL_OFFSET]));
    enc16bp(&(frame->sub_hdr.lmt.un),
        &(stream[m * SLMP_LMT_SUBHDR_TIMER_ENDCODE_OFFSET]));

    /* Command */
    enc16b(frame->cmd_data.lmt.cmd,
        &(stream[m * SLMP_LMT_CMD_OFFSET]));

    /* Sub-command */
    enc16b(frame->cmd_data.lmt.sub_cmd,
        &(stream[m * SLMP_LMT_SUBCMD_OFFSET]));
    enc8b(0, &(stream[m * SLMP_LMT_RESERVED3_OFFSET]));

    /* Packet division information */
    enc8b(frame->cmd_data.lmt.data_id,
        &(stream[m * SLMP_LMT_DATA_ID_OFFSET]));
    enc16b(frame->cmd_data.lmt.data_div_total,
        &(stream[m * SLMP_LMT_DATA_DIVIDE_NUM_OFFSET]));
    enc16b(frame->cmd_data.lmt.div_no,
        &(stream[m * SLMP_LMT_DATA_NUMBER_OFFSET]));

    switch (frame->hdr.ftype) {
    case SLMP_FTYPE_REQ_LMT:
        /* Request data */
        encnp(frame->raw_data, &(stream[m * SLMP_LMT_REQDATA_OFFSET]),
            raw_data_len);
        break;
    case SLMP_FTYPE_RES_LMT:
        /* Response data */
        encnp(frame->raw_data, &(stream[m * SLMP_LMT_RESDATA_OFFSET]),
            raw_data_len);
        break;
    case SLMP_FTYPE_ERR_LMT:
        /* Error information */
        enc8b(frame->err_info.lmt.net_no,
            &(stream[m * SLMP_LMT_ERRINFO_NET_NO_OFFSET]));
        enc8b(frame->err_info.lmt.node_no,
            &(stream[m * SLMP_LMT_ERRINFO_NODE_NO_OFFSET]));
        enc16b(frame->err_info.lmt.dst_proc_no,
            &(stream[m * SLMP_LMT_ERRINFO_DST_PROC_NO_OFFSET]));
        enc8b(frame->err_info.lmt.dst_proc_sub_no,
            &(stream[m * SLMP_LMT_ERRINFO_DST_PROC_SUB_NO_OFFSET]));
        enc16b(0, &(stream[m * SLMP_LMT_ERRINFO_RESERVED2_OFFSET]));
        enc16b(frame->err_info.lmt.large_node_no,
            &(stream[m * SLMP_LMT_ERRINFO_LARGE_NODE_NO_OFFSET]));
        /* Response data */
        encnp(frame->raw_data, &(stream[m * SLMP_LMT_ERRDATA_OFFSET]),
            raw_data_len);
        break;
    default:
        break;
    }

    return min_buf_size;
}

slmp_frame_t* decode_frame_st(uint8_t *stream, size_t len, int type, size_t *len_remains)
{
    DECODE_FRAME_DECLARE_LOCAL_VARIABLES();
    DECODE_FRAME_INITIALIZE_LOCAL_VARIABLES_1(ST);

    if (ftype == SLMP_FTYPE_RES_ST) {
        dec16bp(&(stream[m * SLMP_ST_SUBHDR_TIMER_ENDCODE_RESERVED2_OFFSET]),
            &end_code);
        if (end_code > 0) {
            ftype |= SLMP_FTYPE_ERR_MASK;
        }
    }

    DECODE_FRAME_BEGIN_SWITCH_FTYPE()
        DECODE_FRAME_CASE_FTYPE(REQ, ST)
        DECODE_FRAME_CASE_FTYPE(RES, ST)
        DECODE_FRAME_CASE_FTYPE(ERR, ST)
    DECODE_FRAME_END_SWITCH_FTYPE()

    DECODE_FRAME_INITIALIZE_LOCAL_VARIABLES_2();

    /* Header */
    frame->hdr.ftype = ftype;

    /* Sub-header */
    dec8bp(&(stream[m * SLMP_ST_SUBHDR_NET_NO_OFFSET]),
        &(frame->sub_hdr.st.net_no));
    dec8bp(&(stream[m * SLMP_ST_SUBHDR_NODE_NO_OFFSET]),
        &(frame->sub_hdr.st.node_no));
    dec16bp(&(stream[m * SLMP_ST_SUBHDR_DST_PROC_NO_OFFSET]),
        &(frame->sub_hdr.st.dst_proc_no));
    frame->sub_hdr.st.data_len = dl;
    dec16bp(&(stream[m * SLMP_ST_SUBHDR_TIMER_ENDCODE_RESERVED2_OFFSET]),
        &(frame->sub_hdr.st.un));

    switch (ftype) {
    case SLMP_FTYPE_REQ_ST:
        /* Command */
        dec16bp(&(stream[m * SLMP_ST_CMD_OFFSET]), &(frame->cmd_data.st.cmd));
        /* Sub-command */
        dec16bp(&(stream[m * SLMP_ST_SUBCMD_OFFSET]),
            &(frame->cmd_data.st.sub_cmd));
        /* Request data*/
        decnp(&(stream[m * SLMP_ST_REQDATA_OFFSET]), frame->raw_data,
            m * raw_data_len);
        break;
    case SLMP_FTYPE_RES_ST:
        /* Response data*/
        decnp(&(stream[m * SLMP_ST_RESDATA_OFFSET]), frame->raw_data,
            m * raw_data_len);
        break;
    case SLMP_FTYPE_ERR_ST:
        /* Error information */
        dec8bp(&(stream[m * SLMP_ST_ERRINFO_NET_NO_OFFSET]),
            &(frame->err_info.st.net_no));
        dec8bp(&(stream[m * SLMP_ST_ERRINFO_NODE_NO_OFFSET]),
            &(frame->err_info.st.node_no));
        dec16bp(&(stream[m * SLMP_ST_ERRINFO_DST_PROC_NO_OFFSET]),
            &(frame->err_info.st.dst_proc_no));
        dec16bp(&(stream[m * SLMP_ST_ERRINFO_CMD_OFFSET]),
            &(frame->err_info.st.cmd));
        dec16bp(&(stream[m * SLMP_ST_ERRINFO_SUBCMD_OFFSET]),
            &(frame->err_info.st.sub_cmd));
        /* Response data */
        decnp(&(stream[m * SLMP_ST_ERRDATA_OFFSET]), frame->raw_data,
            m * raw_data_len);
        break;
    default:
        break;
    }

    return frame;
}

slmp_frame_t* decode_frame_mt(uint8_t *stream, size_t len, int type, size_t *len_remains)
{
    DECODE_FRAME_DECLARE_LOCAL_VARIABLES();
    DECODE_FRAME_INITIALIZE_LOCAL_VARIABLES_1(MT);

    if (ftype == SLMP_FTYPE_RES_MT) {
        dec16bp(&(stream[m * SLMP_MT_SUBHDR_TIMER_ENDCODE_RESERVED3_OFFSET]),
            &end_code);
        if (end_code > 0) {
            ftype |= SLMP_FTYPE_ERR_MASK;
        }
    }

    DECODE_FRAME_BEGIN_SWITCH_FTYPE()
        DECODE_FRAME_CASE_FTYPE(REQ, MT)
        DECODE_FRAME_CASE_FTYPE(RES, MT)
        DECODE_FRAME_CASE_FTYPE(ERR, MT)
    DECODE_FRAME_END_SWITCH_FTYPE()

    DECODE_FRAME_INITIALIZE_LOCAL_VARIABLES_2();

    /* Header */
    frame->hdr.ftype = ftype;
    dec16bp(&(stream[m * SLMP_MT_HDR_SERIAL_OFFSET]), &(frame->hdr.serial));

    /* Sub-header */
    dec8bp(&(stream[m * SLMP_MT_SUBHDR_NET_NO_OFFSET]),
        &(frame->sub_hdr.mt.net_no));
    dec8bp(&(stream[m * SLMP_MT_SUBHDR_NODE_NO_OFFSET]),
        &(frame->sub_hdr.mt.node_no));
    dec16bp(&(stream[m * SLMP_MT_SUBHDR_DST_PROC_NO_OFFSET]),
        &(frame->sub_hdr.mt.dst_proc_no));
    frame->sub_hdr.mt.data_len = dl;
    dec16bp(&(stream[m * SLMP_MT_SUBHDR_TIMER_ENDCODE_RESERVED3_OFFSET]),
        &(frame->sub_hdr.mt.un));

    switch (ftype) {
    case SLMP_FTYPE_REQ_MT:
        /* Command */
        dec16bp(&(stream[m * SLMP_MT_CMD_OFFSET]), &(frame->cmd_data.mt.cmd));
        /* Sub-command */
        dec16bp(&(stream[m * SLMP_MT_SUBCMD_OFFSET]),
            &(frame->cmd_data.mt.sub_cmd));
        /* Request data */
        decnp(&(stream[m * SLMP_MT_REQDATA_OFFSET]), frame->raw_data,
            m * raw_data_len);
        break;
    case SLMP_FTYPE_RES_MT:
        /* Response data */
        decnp(&(stream[m * SLMP_MT_RESDATA_OFFSET]), frame->raw_data,
            m * raw_data_len);
        break;
    case SLMP_FTYPE_ERR_MT:
        /* Error information */
        dec8bp(&(stream[m * SLMP_MT_ERRINFO_NET_NO_OFFSET]),
            &(frame->err_info.mt.net_no));
        dec8bp(&(stream[m * SLMP_MT_ERRINFO_NODE_NO_OFFSET]),
            &(frame->err_info.mt.node_no));
        dec16bp(&(stream[m * SLMP_MT_ERRINFO_DST_PROC_NO_OFFSET]),
            &(frame->err_info.mt.dst_proc_no));
        dec16bp(&(stream[m * SLMP_MT_ERRINFO_CMD_OFFSET]),
            &(frame->err_info.mt.cmd));
        dec16bp(&(stream[m * SLMP_MT_ERRINFO_SUBCMD_OFFSET]),
            &(frame->err_info.mt.sub_cmd));
        /* Response data */
        decnp(&(stream[m * SLMP_MT_ERRDATA_OFFSET]), frame->raw_data,
            m * raw_data_len);
        break;
    default:
        break;
    }

    return frame;
}

slmp_frame_t* decode_frame_emt(uint8_t *stream, size_t len, int type, size_t *len_remains)
{
    DECODE_FRAME_DECLARE_LOCAL_VARIABLES();
    DECODE_FRAME_INITIALIZE_LOCAL_VARIABLES_1(EMT);
    DECODE_FRAME_BEGIN_SWITCH_FTYPE()
        DECODE_FRAME_CASE_FTYPE(REQ, EMT)
        DECODE_FRAME_CASE_FTYPE(RES, EMT)
        DECODE_FRAME_CASE_FTYPE(PUSH, EMT)
    DECODE_FRAME_END_SWITCH_FTYPE()
    DECODE_FRAME_INITIALIZE_LOCAL_VARIABLES_2();

    /* Header */
    frame->hdr.ftype = ftype;
    dec16bp(&(stream[m * SLMP_EMT_HDR_FTYPE_OFFSET]), &(frame->hdr.serial));

    /* Sub-header */
    dec8bp(&(stream[m * SLMP_EMT_SUBHDR_DST_NET_NO_OFFSET]),
        &(frame->sub_hdr.emt.dst_net_no));
    dec8bp(&(stream[m * SLMP_EMT_SUBHDR_DST_NODE_NO_OFFSET]),
        &(frame->sub_hdr.emt.dst_node_no));
    dec16bp(&(stream[m * SLMP_EMT_SUBHDR_DST_PROC_NO_OFFSET]),
        &(frame->sub_hdr.emt.dst_proc_no));
    dec8bp(&(stream[m * SLMP_EMT_SUBHDR_SRC_NET_NO_OFFSET]),
        &(frame->sub_hdr.emt.src_net_no));
    dec8bp(&(stream[m * SLMP_EMT_SUBHDR_SRC_NODE_NO_OFFSET]),
        &(frame->sub_hdr.emt.src_node_no));
    dec16bp(&(stream[m * SLMP_EMT_SUBHDR_SRC_PROC_NO_OFFSET]),
        &(frame->sub_hdr.emt.src_proc_no));
    dec8bp(&(stream[m * SLMP_EMT_SUBHDR_PKT_TYPE_OFFSET]),
        &(frame->sub_hdr.emt.pkt_type));
    dec16bp(&(stream[m * SLMP_EMT_SUBHDR_FLGM_OFFSET]),
        &(frame->sub_hdr.emt.flgm));
    frame->sub_hdr.emt.data_len = dl;

    switch (ftype) {
    case SLMP_FTYPE_REQ_EMT:
        /* fall through */
    case SLMP_FTYPE_PUSH_EMT:
        /* Command */
        dec16bp(&(stream[m * SLMP_EMT_CMD_OFFSET]),
            &(frame->cmd_data.emt.cmd));
        /* Sub-command */
        dec16bp(&(stream[m * SLMP_EMT_SUBCMD_OFFSET]),
            &(frame->cmd_data.emt.sub_cmd));
        /* Request data */
        decnp(&(stream[m * SLMP_EMT_REQDATA_OFFSET]), frame->raw_data,
            m * raw_data_len);
        break;
    case SLMP_FTYPE_RES_EMT:
        /* Command */
        dec16bp(&(stream[m * SLMP_EMT_CMD_OFFSET]),
            &(frame->cmd_data.emt.cmd));
        /* Sub-command */
        dec16bp(&(stream[m * SLMP_EMT_SUBCMD_OFFSET]),
            &(frame->cmd_data.emt.sub_cmd));
        /* End code */
        dec16bp(&(stream[m * SLMP_EMT_ENDCODE_OFFSET]),
            &(frame->cmd_data.emt.end_code));
        /* Response data */
        decnp(&(stream[m * SLMP_EMT_RESDATA_OFFSET]), frame->raw_data,
            m * raw_data_len);
        break;
    default:
        break;
    }

    return frame;
}

slmp_frame_t* decode_frame_lmt(uint8_t *stream, size_t len, int type, size_t *len_remains)
{
    DECODE_FRAME_DECLARE_LOCAL_VARIABLES();

    /* The station number extended MT type has only binary mode. */
    assert(type != SLMP_ASCII_STREAM);

    DECODE_FRAME_INITIALIZE_LOCAL_VARIABLES_1(LMT);

    if (ftype == SLMP_FTYPE_RES_LMT) {
        dec16bp(&(stream[m * SLMP_LMT_SUBHDR_TIMER_ENDCODE_OFFSET]),
            &end_code);
        if (end_code > 0) {
            ftype |= SLMP_FTYPE_ERR_MASK;
        }
    }

    DECODE_FRAME_BEGIN_SWITCH_FTYPE()
        DECODE_FRAME_CASE_FTYPE(REQ, LMT)
        DECODE_FRAME_CASE_FTYPE(RES, LMT)
        DECODE_FRAME_CASE_FTYPE(ERR, LMT)
    DECODE_FRAME_END_SWITCH_FTYPE()

    DECODE_FRAME_INITIALIZE_LOCAL_VARIABLES_2();

    /* Header */
    frame->hdr.ftype = ftype;
    dec16bp(&(stream[m * SLMP_LMT_HDR_SERIAL_OFFSET]), &(frame->hdr.serial));

    /* Sub-header */
    dec8bp(&(stream[m * SLMP_LMT_SUBHDR_NET_NO_OFFSET]),
        &(frame->sub_hdr.lmt.net_no));
    dec8bp(&(stream[m * SLMP_LMT_SUBHDR_NODE_NO_OFFSET]),
        &(frame->sub_hdr.lmt.node_no));
    dec16bp(&(stream[m * SLMP_LMT_SUBHDR_DST_PROC_NO_OFFSET]),
        &(frame->sub_hdr.lmt.dst_proc_no));
    dec8bp(&(stream[m * SLMP_LMT_SUBHDR_DST_PROC_SUB_NO_OFFSET]),
        &(frame->sub_hdr.lmt.dst_proc_sub_no));
    dec16bp(&(stream[m * SLMP_LMT_SUBHDR_LARGE_NODE_NO_OFFSET]),
        &(frame->sub_hdr.lmt.large_node_no));
    frame->sub_hdr.lmt.data_len = dl;
    dec16bp(&(stream[m * SLMP_LMT_SUBHDR_TIMER_ENDCODE_OFFSET]),
        &(frame->sub_hdr.lmt.un));

    /* Command */
    dec16bp(&(stream[m * SLMP_LMT_CMD_OFFSET]), &(frame->cmd_data.lmt.cmd));

    /* Sub-command */
    dec16bp(&(stream[m * SLMP_LMT_SUBCMD_OFFSET]),
        &(frame->cmd_data.lmt.sub_cmd));

    /* Packet division information */
    dec8bp(&(stream[m * SLMP_LMT_DATA_ID_OFFSET]),
        &(frame->cmd_data.lmt.data_id));
    dec16bp(&(stream[m * SLMP_LMT_DATA_DIVIDE_NUM_OFFSET]),
        &(frame->cmd_data.lmt.data_div_total));
    dec16bp(&(stream[m * SLMP_LMT_DATA_NUMBER_OFFSET]),
        &(frame->cmd_data.lmt.div_no));

    switch (ftype) {
    case SLMP_FTYPE_REQ_LMT:
        /* Request data */
        decnp(&(stream[m * SLMP_LMT_REQDATA_OFFSET]), frame->raw_data,
            m * raw_data_len);
        break;
    case SLMP_FTYPE_RES_LMT:
        /* Response data */
        decnp(&(stream[m * SLMP_LMT_RESDATA_OFFSET]), frame->raw_data,
            m * raw_data_len);
        break;
    case SLMP_FTYPE_ERR_LMT:
        /* Error information */
        dec8bp(&(stream[m * SLMP_LMT_ERRINFO_NET_NO_OFFSET]),
            &(frame->err_info.lmt.net_no));
        dec8bp(&(stream[m * SLMP_LMT_ERRINFO_NODE_NO_OFFSET]),
            &(frame->err_info.lmt.node_no));
        dec16bp(&(stream[m * SLMP_LMT_ERRINFO_DST_PROC_NO_OFFSET]),
            &(frame->err_info.lmt.dst_proc_no));
        dec8bp(&(stream[m * SLMP_LMT_ERRINFO_DST_PROC_SUB_NO_OFFSET]),
            &(frame->err_info.lmt.dst_proc_sub_no));
        dec16bp(&(stream[m * SLMP_LMT_ERRINFO_LARGE_NODE_NO_OFFSET]),
            &(frame->err_info.lmt.large_node_no));
        /* Response data */
        decnp(&(stream[m * SLMP_LMT_ERRDATA_OFFSET]), frame->raw_data,
            m * raw_data_len);
        break;
    default:
        break;
    }

    return frame;
}

