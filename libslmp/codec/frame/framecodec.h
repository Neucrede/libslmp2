/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#ifndef __FRAMECODEC_H__
#define __FRAMECODEC_H__

#include <assert.h>

#include "slmp/slmpdef.h"
#include "slmp/slmpapi.h"
#include "slmp/slmpmem.h"
#include "slmp/slmperr.h"
#include "slmp/slmpframe.h"

#include "../word/wordcodec.h"


#define SLMP_MIN_FRAME_STREAM_LENGTH                    11

/* 
 * Number of bytes between dl and first byte of payload data in a binary packet
 * stream. For ASCII packet streams, these values should be doubled.
 */
#define SLMP_REQ_ST_DATA_DL_OFFSET                      6
#define SLMP_RES_ST_DATA_DL_OFFSET                      2
#define SLMP_ERR_ST_DATA_DL_OFFSET                      11
#define SLMP_REQ_MT_DATA_DL_OFFSET                      6
#define SLMP_RES_MT_DATA_DL_OFFSET                      2
#define SLMP_ERR_MT_DATA_DL_OFFSET                      11
#define SLMP_REQ_EMT_DATA_DL_OFFSET                     4
#define SLMP_PUSH_EMT_DATA_DL_OFFSET                    4
#define SLMP_RES_EMT_DATA_DL_OFFSET                     6
#define SLMP_REQ_LMT_DATA_DL_OFFSET                     12
#define SLMP_RES_LMT_DATA_DL_OFFSET                     12
#define SLMP_ERR_LMT_DATA_DL_OFFSET                     20

/* 
 * Length of the fixed portion of the frame encoded as a binary packet stream.
 * For ASCII packet streams, these values should be doubled.
 */
#define SLMP_REQ_ST_FIXED_PART_LEN                      15
#define SLMP_RES_ST_FIXED_PART_LEN                      11
#define SLMP_ERR_ST_FIXED_PART_LEN                      20
#define SLMP_REQ_MT_FIXED_PART_LEN                      19
#define SLMP_RES_MT_FIXED_PART_LEN                      15
#define SLMP_ERR_MT_FIXED_PART_LEN                      24
#define SLMP_REQ_EMT_FIXED_PART_LEN                     24
#define SLMP_PUSH_EMT_FIXED_PART_LEN                    24
#define SLMP_RES_EMT_FIXED_PART_LEN                     26
#define SLMP_REQ_LMT_FIXED_PART_LEN                     28
#define SLMP_RES_LMT_FIXED_PART_LEN                     28
#define SLMP_ERR_LMT_FIXED_PART_LEN                     36

/* 
 * Offsets of frame item in a binary packet stream.
 * For ASCII packet streams, these values should be doubled.
 */
#define SLMP_ST_HDR_FTYPE_OFFSET                        0
#define SLMP_ST_SUBHDR_NET_NO_OFFSET                    2
#define SLMP_ST_SUBHDR_NODE_NO_OFFSET                   3
#define SLMP_ST_SUBHDR_DST_PROC_NO_OFFSET               4
#define SLMP_ST_SUBHDR_RESERVED1_OFFSET                 6
#define SLMP_ST_SUBHDR_DL_OFFSET                        7
#define SLMP_ST_SUBHDR_TIMER_ENDCODE_RESERVED2_OFFSET   9
#define SLMP_ST_CMD_OFFSET                              11
#define SLMP_ST_SUBCMD_OFFSET                           13
#define SLMP_ST_REQDATA_OFFSET                          15
#define SLMP_ST_RESDATA_OFFSET                          11
#define SLMP_ST_ERRINFO_NET_NO_OFFSET                   11
#define SLMP_ST_ERRINFO_NODE_NO_OFFSET                  12
#define SLMP_ST_ERRINFO_DST_PROC_NO_OFFSET              13
#define SLMP_ST_ERRINFO_RESERVED1_OFFSET                15
#define SLMP_ST_ERRINFO_CMD_OFFSET                      16
#define SLMP_ST_ERRINFO_SUBCMD_OFFSET                   18
#define SLMP_ST_ERRDATA_OFFSET                          20

#define SLMP_MT_HDR_FTYPE_OFFSET                        0
#define SLMP_MT_HDR_SERIAL_OFFSET                       2
#define SLMP_MT_HDR_RESERVED1_OFFSET                    4
#define SLMP_MT_SUBHDR_NET_NO_OFFSET                    6
#define SLMP_MT_SUBHDR_NODE_NO_OFFSET                   7
#define SLMP_MT_SUBHDR_DST_PROC_NO_OFFSET               8
#define SLMP_MT_SUBHDR_RESERVED1_OFFSET                 10
#define SLMP_MT_SUBHDR_DL_OFFSET                        11
#define SLMP_MT_SUBHDR_TIMER_ENDCODE_RESERVED3_OFFSET   13
#define SLMP_MT_CMD_OFFSET                              15
#define SLMP_MT_SUBCMD_OFFSET                           17
#define SLMP_MT_REQDATA_OFFSET                          19
#define SLMP_MT_RESDATA_OFFSET                          15
#define SLMP_MT_ERRINFO_NET_NO_OFFSET                   15
#define SLMP_MT_ERRINFO_NODE_NO_OFFSET                  16
#define SLMP_MT_ERRINFO_DST_PROC_NO_OFFSET              17
#define SLMP_MT_ERRINFO_RESERVED1_OFFSET                19
#define SLMP_MT_ERRINFO_CMD_OFFSET                      20
#define SLMP_MT_ERRINFO_SUBCMD_OFFSET                   22
#define SLMP_MT_ERRDATA_OFFSET                          24

#define SLMP_EMT_HDR_FTYPE_OFFSET                       0
#define SLMP_EMT_HDR_SERIAL_OFFSET                      2
#define SLMP_EMT_HDR_RESERVED2_OFFSET                   4
#define SLMP_EMT_SUBHDR_DST_NET_NO_OFFSET               6
#define SLMP_EMT_SUBHDR_DST_NODE_NO_OFFSET              7
#define SLMP_EMT_SUBHDR_DST_PROC_NO_OFFSET              8
#define SLMP_EMT_SUBHDR_SRC_NET_NO_OFFSET               10
#define SLMP_EMT_SUBHDR_SRC_NODE_NO_OFFSET              11
#define SLMP_EMT_SUBHDR_SRC_PROC_NO_OFFSET              12
#define SLMP_EMT_SUBHDR_PKT_TYPE_OFFSET                 14
#define SLMP_EMT_SUBHDR_RESERVED1_OFFSET                15
#define SLMP_EMT_SUBHDR_FLGM_OFFSET                     16
#define SLMP_EMT_SUBHDR_DL_OFFSET                       18
#define SLMP_EMT_CMD_OFFSET                             20
#define SLMP_EMT_SUBCMD_OFFSET                          22
#define SLMP_EMT_REQDATA_OFFSET                         24
#define SLMP_EMT_PUSHDATA_OFFSET                        24
#define SLMP_EMT_ENDCODE_OFFSET                         24
#define SLMP_EMT_RESDATA_OFFSET                         26

#define SLMP_LMT_HDR_FTYPE_OFFSET                       0
#define SLMP_LMT_HDR_SERIAL_OFFSET                      2
#define SLMP_LMT_HDR_RESERVED1_OFFSET                   4
#define SLMP_LMT_SUBHDR_NET_NO_OFFSET                   6
#define SLMP_LMT_SUBHDR_NODE_NO_OFFSET                  7
#define SLMP_LMT_SUBHDR_DST_PROC_NO_OFFSET              8
#define SLMP_LMT_SUBHDR_DST_PROC_SUB_NO_OFFSET          10
#define SLMP_LMT_SUBHDR_RESERVED2_OFFSET                11
#define SLMP_LMT_SUBHDR_LARGE_NODE_NO_OFFSET            12
#define SLMP_LMT_SUBHDR_DL_OFFSET                       14
#define SLMP_LMT_SUBHDR_TIMER_ENDCODE_OFFSET            16
#define SLMP_LMT_CMD_OFFSET                             18
#define SLMP_LMT_SUBCMD_OFFSET                          20
#define SLMP_LMT_RESERVED3_OFFSET                       22
#define SLMP_LMT_DATA_ID_OFFSET                         23
#define SLMP_LMT_DATA_DIVIDE_NUM_OFFSET                 24
#define SLMP_LMT_DATA_NUMBER_OFFSET                     26
#define SLMP_LMT_REQDATA_OFFSET                         28
#define SLMP_LMT_RESDATA_OFFSET                         28
#define SLMP_LMT_ERRINFO_NET_NO_OFFSET                  28
#define SLMP_LMT_ERRINFO_NODE_NO_OFFSET                 29
#define SLMP_LMT_ERRINFO_DST_PROC_NO_OFFSET             30
#define SLMP_LMT_ERRINFO_DST_PROC_SUB_NO_OFFSET         32
#define SLMP_LMT_ERRINFO_RESERVED2_OFFSET               33
#define SLMP_LMT_ERRINFO_LARGE_NODE_NO_OFFSET           34
#define SLMP_LMT_ERRDATA_OFFSET                         36


/* ***************************************************************************/


typedef size_t (*pfn_encode_frame_t)(slmp_frame_t* /* frame */,
    uint8_t* /* stream */, int /* type */);

typedef slmp_frame_t* (*pfn_decode_frame_t)(uint8_t* /* stream */, 
    size_t /* len */, int /* type */, size_t* /* len_remains */);

size_t encode_frame_st(slmp_frame_t *frame, uint8_t *stream, int type);
size_t encode_frame_mt(slmp_frame_t *frame, uint8_t *stream, int type);
size_t encode_frame_emt(slmp_frame_t *frame, uint8_t *stream, int type);
size_t encode_frame_lmt(slmp_frame_t *frame, uint8_t *stream, int type);

slmp_frame_t* decode_frame_st(uint8_t *stream, size_t len, int type, size_t *len_remains);
slmp_frame_t* decode_frame_mt(uint8_t *stream, size_t len, int type, size_t *len_remains);
slmp_frame_t* decode_frame_emt(uint8_t *stream, size_t len, int type, size_t *len_remains);
slmp_frame_t* decode_frame_lmt(uint8_t *stream, size_t len, int type, size_t *len_remains);


/* ***************************************************************************/

#define ENCODE_FRAME_DECLARE_LOCAL_VARIABLES()                              \
    /* DL field of sub-header. */                                           \
    uint32_t dl = 0;                                                        \
    /* Min buffer size required. */                                         \
    size_t min_buf_size = 0;                                                \
    /* Codeword length of one octet. */                                     \
    size_t m;                                                               \
    /* Number of bytes between DL field and first byte of payload data. */  \
    size_t dl_offset;                                                       \
    /* Length of fixed part of the PDU. */                                  \
    size_t fixed_part_len;                                                  \
    /* Length of binary raw data. */                                        \
    size_t raw_data_len;                                                    \
    /* Encode functions. */                                                 \
    pfn_codec_8b_t enc8b;                                                   \
    pfn_codec_16b_t enc16b;                                                 \
    pfn_codec_24b_t enc24b;                                                 \
    pfn_codec_32b_t enc32b;                                                 \
    pfn_codec_ptr_t enc8bp, enc16bp, enc24bp, enc32bp;                      \
    pfn_codec_n_ptr_t encnp                                                 \


#define ENCODE_FRAME_INITIALIZE_LOCAL_VARIABLES_1()                         \
    assert(frame != NULL);                                                  \
    assert(frame->size >= sizeof(slmp_frame_t) - 1);                        \
    assert((type == SLMP_BINARY_STREAM) || (type == SLMP_ASCII_STREAM));    \
                                                                            \
    if (type == SLMP_BINARY_STREAM) {                                       \
        m = 1;                                                              \
        enc8b = encode_bin_8b;                                              \
        enc16b = encode_bin_16b;                                            \
        enc24b = encode_bin_24b;                                            \
        enc32b = encode_bin_32b;                                            \
        enc8bp = encode_bin_8b_ptr;                                         \
        enc16bp = encode_bin_16b_ptr;                                       \
        enc24bp = encode_bin_24b_ptr;                                       \
        enc32bp = encode_bin_32b_ptr;                                       \
        encnp = encode_bin_n_ptr;                                           \
    }                                                                       \
    else {                                                                  \
        m = 2;                                                              \
        enc8b = encode_ascii_8b;                                            \
        enc16b = encode_ascii_16b;                                          \
        enc24b = encode_ascii_24b;                                          \
        enc32b = encode_ascii_32b;                                          \
        enc8bp = encode_ascii_8b_ptr;                                       \
        enc16bp = encode_ascii_16b_ptr;                                     \
        enc24bp = encode_ascii_24b_ptr;                                     \
        enc32bp = encode_ascii_32b_ptr;                                     \
        encnp = encode_ascii_n_ptr;                                         \
    }                                                                       \
                                                                            \


#define ENCODE_FRAME_BEGIN_SWITCH_FTYPE()                                   \
    switch (frame->hdr.ftype) {                                             \


#define ENCODE_FRAME_CASE_FTYPE(x)                                          \
    case SLMP_FTYPE_##x:                                                    \
        dl_offset = SLMP_##x##_DATA_DL_OFFSET;                              \
        fixed_part_len = SLMP_##x##_FIXED_PART_LEN;                         \
        break;                                                              \


#define ENCODE_FRAME_END_SWITCH_FTYPE()                                     \
    default:                                                                \
        assert(0 && "Bad FTYPE.");                                          \
        slmp_set_errno(SLMP_ERROR_BAD_FTYPE);                               \
        return 0;                                                           \
    }                                                                       \


#define ENCODE_FRAME_INITIALIZE_LOCAL_VARIABLES_2()                         \
    if (frame->size > sizeof(slmp_frame_t) - 1) {                           \
        raw_data_len = frame->size - sizeof(slmp_frame_t) + 1;              \
    } else { raw_data_len = 0; }                                            \
    dl = (uint32_t)(m * (raw_data_len + dl_offset));                        \
    min_buf_size = raw_data_len + m * fixed_part_len;                       \


/* ***************************************************************************/


#define DECODE_FRAME_DECLARE_LOCAL_VARIABLES()                              \
    slmp_frame_t *frame = NULL;                                             \
    /* FTYPE field of header. */                                            \
    uint16_t ftype = 0;                                                     \
    /* DL field of sub-header. */                                           \
    uint16_t dl = 0;                                                        \
    /* ENDCODE field of sub-header. */                                      \
    uint16_t end_code = 0;                                                  \
    /* Codeword length of one octet. */                                     \
    size_t m;                                                               \
    /* Number of bytes between DL field and first byte of payload data. */  \
    size_t dl_offset;                                                       \
    /* Length of fixed part of the PDU. */                                  \
    size_t fixed_part_len;                                                  \
    /* Length of binary raw data. */                                        \
    size_t raw_data_len;                                                    \
    /* Decode functions.*/                                                  \
    pfn_codec_ptr_t dec8bp, dec16bp, dec24bp, dec32bp;                      \
    pfn_codec_n_ptr_t decnp                                                 \


#define DECODE_FRAME_INITIALIZE_LOCAL_VARIABLES_1(x)                        \
    assert(stream != NULL);                                                 \
    assert((type == SLMP_BINARY_STREAM) || (type == SLMP_ASCII_STREAM));    \
    if (type == SLMP_BINARY_STREAM) {                                       \
        m = 1;                                                              \
        dec8bp = decode_bin_8b_ptr;                                         \
        dec16bp = decode_bin_16b_ptr;                                       \
        dec24bp = decode_bin_24b_ptr;                                       \
        dec32bp = decode_bin_32b_ptr;                                       \
        decnp = decode_bin_n_ptr;                                           \
    }                                                                       \
    else {                                                                  \
        m = 2;                                                              \
        dec8bp = decode_ascii_8b_ptr;                                       \
        dec16bp = decode_ascii_16b_ptr;                                     \
        dec24bp = decode_ascii_24b_ptr;                                     \
        dec32bp = decode_ascii_32b_ptr;                                     \
        decnp = decode_ascii_n_ptr;                                         \
    }                                                                       \
    if (len < m * (SLMP_##x##_HDR_FTYPE_OFFSET + 2)) {                      \
        slmp_set_errno(SLMP_ERROR_BUFFER_TOO_SHORT);                        \
        return NULL;                                                        \
    }                                                                       \
    dec16bp(&(stream[m * SLMP_##x##_HDR_FTYPE_OFFSET]), &ftype)             \


#define DECODE_FRAME_BEGIN_SWITCH_FTYPE()                                   \
    switch (ftype) {                                                        \


#define DECODE_FRAME_CASE_FTYPE(x, y)                                       \
    case SLMP_FTYPE_##x##_##y:                                              \
        dl_offset = SLMP_##x##_##y##_DATA_DL_OFFSET;                        \
        fixed_part_len = SLMP_##x##_##y##_FIXED_PART_LEN;                   \
        assert(len >= m * fixed_part_len);                                  \
        if (len < m * fixed_part_len) {                                     \
            slmp_set_errno(SLMP_ERROR_BUFFER_TOO_SHORT);                    \
            return NULL;                                                    \
        }                                                                   \
        dec16bp(&(stream[m * SLMP_##y##_SUBHDR_DL_OFFSET]), &dl);           \
        break;                                                              \


#define DECODE_FRAME_END_SWITCH_FTYPE()                                     \
    default:                                                                \
        assert(0 && "Bad FTYPE.");                                          \
        slmp_set_errno(SLMP_ERROR_BAD_FTYPE);                               \
        return NULL;                                                        \
    }                                                                       \


#define DECODE_FRAME_INITIALIZE_LOCAL_VARIABLES_2()                         \
    assert(dl >= m * dl_offset);                                            \
    if (dl < m * dl_offset) {                                               \
        slmp_set_errno(SLMP_ERROR_BAD_FRAME_PACKET);                        \
        return NULL;                                                        \
    }                                                                       \
    raw_data_len = (dl - m * dl_offset) / m;                                \
    assert(len >= m * (fixed_part_len + raw_data_len));                     \
    if (len < m * (fixed_part_len + raw_data_len)) {                        \
        slmp_set_errno(SLMP_ERROR_BUFFER_TOO_SHORT);                        \
        return NULL;                                                        \
    }                                                                       \
    else if (len_remains != NULL) {                                         \
        *len_remains = len - m * (fixed_part_len + raw_data_len);           \
    }                                                                       \
    frame =                                                                 \
      (slmp_frame_t*)slmp_calloc(1, SLMP_FRAME_STRUCT_SIZE(raw_data_len));  \
    assert(frame != NULL);                                                  \
    if (frame == NULL) {                                                    \
        slmp_set_errno(SLMP_ERROR_OUT_OF_MEMORY);                           \
        return NULL;                                                        \
    }                                                                       \
    frame->size = SLMP_FRAME_STRUCT_SIZE(raw_data_len)                      \


#endif /* __FRAMECODEC_H__ */
