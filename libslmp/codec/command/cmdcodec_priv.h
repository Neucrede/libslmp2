/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#ifndef __CMDCODEC_PRIV_H__
#define __CMDCODEC_PRIV_H__

#include <assert.h>
#include <string.h>

#include "slmp/slmpdef.h"
#include "slmp/slmpmem.h"
#include "slmp/slmperr.h"
#include "slmp/codec/cmdcodec.h"

#include "../word/wordcodec.h"


#define ADVANCE_STREAM_PTR(_m, _n)                                          \
    stream += _m * _n                                                       \


#define ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(_cmd_type)                   \
    /* Min buffer size required. */                                         \
    size_t min_buf_size = 0;                                                \
    /* Size of variable part. */                                            \
    size_t var_part_size = 0;                                               \
    /* Codeword length of one octet. */                                     \
    size_t m;                                                               \
    /* Encode functions. */                                                 \
    pfn_codec_8b_t enc8b;                                                   \
    pfn_codec_16b_t enc16b;                                                 \
    pfn_codec_24b_t enc24b;                                                 \
    pfn_codec_32b_t enc32b;                                                 \
    pfn_codec_ptr_t enc8bp, enc16bp, enc24bp, enc32bp;                      \
    pfn_codec_n_ptr_t encnp;                                                \
    /* Command */                                                           \
    _cmd_type *cmd = (_cmd_type*)(hdr)                                      \


#define ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(_cmd_type, _v)            \
    assert(hdr != NULL);                                                    \
    if (hdr == NULL) {                                                      \
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);                       \
        return 0;                                                           \
    }                                                                       \
    assert((type == SLMP_BINARY_STREAM) || (type == SLMP_ASCII_STREAM));    \
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
    else if (type == SLMP_ASCII_STREAM) {                                   \
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
    else {                                                                  \
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);                       \
        return 0;                                                           \
    }                                                                       \
    assert(hdr->size >= sizeof(_cmd_type) - _v);                            \
    if (hdr->size < sizeof(_cmd_type) - _v) {                               \
        slmp_set_errno(SLMP_ERROR_INCORRECT_SIZE);                          \
        return 0;                                                           \
    }                                                                       \
    else {                                                                  \
        var_part_size = hdr->size - sizeof(_cmd_type) + _v;                 \
    }                                                                       \


#define ENCODE_COMMAND_SET_MIN_BUF_SIZE(_size_16b_bin, _size_32b_bin,       \
    _size_16b_ascii, _size_32b_ascii)                                       \
    switch (cmd->hdr.addr_width) {                                          \
    case SLMP_ADDRESS_16BIT:                                                \
        min_buf_size =                                                      \
            (type == SLMP_BINARY_STREAM) ? _size_16b_bin : _size_16b_ascii; \
        break;                                                              \
    case SLMP_ADDRESS_32BIT:                                                \
        min_buf_size =                                                      \
            (type == SLMP_BINARY_STREAM) ? _size_32b_bin : _size_32b_ascii; \
        break;                                                              \
    default:                                                                \
        assert(0 && "Bad address width.");                                  \
        slmp_set_errno(SLMP_ERROR_BAD_ADDRESS_WIDTH);                       \
        return 0;                                                           \
    }                                                                       \


#define ENCODE_AND_ADVANCE_STREAM_8B(_value)                                \
    enc8b((_value), stream);                                                \
    ADVANCE_STREAM_PTR(m, 1)                                                \


#define ENCODE_AND_ADVANCE_STREAM_16B(_value)                               \
    enc16b((_value), stream);                                               \
    ADVANCE_STREAM_PTR(m, 2)                                                \


#define ENCODE_AND_ADVANCE_STREAM_24B(_value)                               \
    enc24b((_value), stream);                                               \
    ADVANCE_STREAM_PTR(m, 3)                                                \


#define ENCODE_AND_ADVANCE_STREAM_32B(_value)                               \
    enc32b((_value), stream);                                               \
    ADVANCE_STREAM_PTR(m, 4)                                                \


#define ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(_src, _size)                  \
    do { if (_size != 0) {                                                  \
        memcpy(stream, (_src), _size);                                      \
        ADVANCE_STREAM_PTR(1, _size);                                       \
    } } while (0)                                                           \


#define ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(_src, _size)                \
    do { if (_src != NULL) {                                                \
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(_src, _size);                 \
    } else if (_size != 0) {                                                \
        slmp_set_errno(SLMP_ERROR_INVALID_POINTER);                         \
        return 0;                                                           \
    } } while (0)                                                           \


#define DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(_cmd_type)                   \
    uint8_t *stream0 = stream;                                              \
    /* Min stream size required. */                                         \
    size_t min_stream_size = 0;                                             \
    /* Size of variable part. */                                            \
    size_t var_part_size = 0;                                               \
    /* Codeword length of one octet. */                                     \
    size_t m;                                                               \
    /* Decode functions.*/                                                  \
    pfn_codec_ptr_t dec8bp, dec16bp, dec24bp, dec32bp;                      \
    pfn_codec_n_ptr_t decnp;                                                \
    /* Command */                                                           \
    _cmd_type *cmd = NULL                                                   \


#define DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES()                         \
    (void)(stream0);                                                        \
    (void)(var_part_size);                                                  \
    assert(stream != NULL);                                                 \
    if (stream == NULL) {                                                   \
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);                       \
        return 0;                                                           \
    }                                                                       \
    assert((type == SLMP_BINARY_STREAM) || (type == SLMP_ASCII_STREAM));    \
    if (type == SLMP_BINARY_STREAM) {                                       \
        m = 1;                                                              \
        dec8bp = decode_bin_8b_ptr;                                         \
        dec16bp = decode_bin_16b_ptr;                                       \
        dec24bp = decode_bin_24b_ptr;                                       \
        dec32bp = decode_bin_32b_ptr;                                       \
        decnp = decode_bin_n_ptr;                                           \
    }                                                                       \
    else if (type == SLMP_ASCII_STREAM) {                                   \
        m = 2;                                                              \
        dec8bp = decode_ascii_8b_ptr;                                       \
        dec16bp = decode_ascii_16b_ptr;                                     \
        dec24bp = decode_ascii_24b_ptr;                                     \
        dec32bp = decode_ascii_32b_ptr;                                     \
        decnp = decode_ascii_n_ptr;                                         \
    }                                                                       \
    else {                                                                  \
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);                       \
        return 0;                                                           \
    }                                                                       \

#define DECODE_COMMAND_ALLOC_MEMORY(_cmd_type)                              \
    cmd = (_cmd_type*)(slmp_calloc(1, sizeof(_cmd_type) + var_part_size - 1));  \
    assert(cmd != NULL);                                                    \
    do { if (cmd == NULL) {                                                 \
        slmp_set_errno(SLMP_ERROR_OUT_OF_MEMORY);                           \
        return NULL;                                                        \
    } } while (0);                                                          \


#define DECODE_COMMAND_CHECK_STREAM_LENGTH(_size_16b_bin, _size_32b_bin,    \
    _size_16b_ascii, _size_32b_ascii)                                       \
    switch (addr_width) {                                                   \
    case SLMP_ADDRESS_16BIT:                                                \
        min_stream_size =                                                   \
            (type == SLMP_BINARY_STREAM) ? _size_16b_bin : _size_16b_ascii; \
        break;                                                              \
    case SLMP_ADDRESS_32BIT:                                                \
        min_stream_size =                                                   \
            (type == SLMP_BINARY_STREAM) ? _size_32b_bin : _size_32b_ascii; \
        break;                                                              \
    default:                                                                \
        assert(0 && "Bad address width.");                                  \
        slmp_set_errno(SLMP_ERROR_BAD_ADDRESS_WIDTH);                       \
        return NULL;                                                        \
    }                                                                       \
    do { if (len < min_stream_size) {                                       \
            slmp_set_errno(SLMP_ERROR_BUFFER_TOO_SHORT);                    \
            return NULL;                                                    \
        } else { var_part_size = len - min_stream_size + 1; }               \
    } while (0)                                                             \


#define DECODE_COMMAND_FILL_COMMAND_HEADER(_cmd_type)                       \
    cmd->hdr.size = var_part_size + sizeof(_cmd_type) - 1;                  \
    cmd->hdr.addr_width = addr_width                                        \


#define DECODE_AND_ADVANCE_STREAM_8B(_ptr)                                  \
    dec8bp(stream, (_ptr));                                                 \
    ADVANCE_STREAM_PTR(m, 1)                                                \


#define DECODE_AND_ADVANCE_STREAM_16B(_ptr)                                 \
    dec16bp(stream, (_ptr));                                                \
    ADVANCE_STREAM_PTR(m, 2)                                                \


#define DECODE_AND_ADVANCE_STREAM_24B(_ptr)                                 \
    dec24bp(stream, (_ptr));                                                \
    ADVANCE_STREAM_PTR(m, 3)                                                \


#define DECODE_AND_ADVANCE_STREAM_32B(_ptr)                                 \
    dec32bp(stream, (_ptr));                                                \
    ADVANCE_STREAM_PTR(m, 4)                                                \


#define DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(_dest, _size)                 \
    do { if (_size != 0) {                                                  \
        memcpy((_dest), stream, _size);                                     \
        ADVANCE_STREAM_PTR(1, _size);                                       \
    } } while (0)                                                           \


#define DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(_dest, _size)               \
    do { if (_size != 0) {                                                  \
        if ((uintptr_t)(stream + _size) > (uintptr_t)(stream0)              \
                + (uintptr_t)(len))                                         \
        {                                                                   \
            slmp_free(cmd);                                                 \
            slmp_set_errno(SLMP_ERROR_BUFFER_TOO_SHORT);                    \
            return NULL;                                                    \
        }                                                                   \
        _dest = (uint8_t*)slmp_malloc((size_t)(_size));                     \
        assert (_dest != NULL);                                             \
        if (_dest == NULL) {                                                \
            slmp_free(cmd);                                                 \
            slmp_set_errno(SLMP_ERROR_OUT_OF_MEMORY);                       \
            return NULL;                                                    \
        } else {                                                            \
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(_dest, _size);            \
        }                                                                   \
    } else { _dest = NULL; } } while (0)                                    \


#endif /* __CMDCODEC_PRIV_H__ */
