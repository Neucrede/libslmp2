/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include "cmdcodec_priv.h" 

SLMPAPI size_t SLMPCALL slmp_encode_array(
    void *array, size_t elem_size, size_t n, uint8_t *stream, int type)
{
    char *_array = array;
    size_t min_buf_size = 0;
    size_t m = 0; /* Codeword length of one octet. */
    pfn_codec_ptr_t encp;
    size_t i;

    if (n == 0) {
        return 0;
    }

    assert(array != NULL);
    if (array == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_POINTER);
        return 0;
    }

    assert((elem_size == 1) || (elem_size == 2) || (elem_size == 4));
    if (!((elem_size == 1) || (elem_size == 2) || (elem_size == 4))) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    assert((type == SLMP_BINARY_STREAM) || (type == SLMP_ASCII_STREAM));
    switch (type) {
    case SLMP_BINARY_STREAM:
        m = 1;
        switch (elem_size) {
        case 1:
            encp = encode_bin_8b_ptr;
            break;
        case 2:
            encp = encode_bin_16b_ptr;
            break;
        case 4:
            encp = encode_bin_32b_ptr;
            break;
        default:
            return 0;
        }
        break;
    case SLMP_ASCII_STREAM:
        m = 2;
        switch (elem_size) {
        case 1:
            encp = encode_ascii_8b_ptr;
            break;
        case 2:
            encp = encode_ascii_16b_ptr;
            break;
        case 4:
            encp = encode_ascii_32b_ptr;
            break;
        default:
            return 0;
        }
        break;
    default:
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    min_buf_size = n * m * elem_size;
    if (stream == NULL) {
        return min_buf_size;
    }

    if ((type == SLMP_BINARY_STREAM) && (elem_size == 1)) {
        memcpy(stream, _array, min_buf_size);
        return min_buf_size;
    }

    for (i = 0; i != n; ++i) {
        encp(_array, stream);
        _array += elem_size;
        stream += m * elem_size;
    }

    return min_buf_size;
}


SLMPAPI void* SLMPCALL slmp_decode_array(
    uint8_t *stream, size_t len, size_t elem_size, int type)
{
    size_t m; /* Codeword length of one octet. */
    pfn_codec_ptr_t decp;
    size_t n, i;
    void *array = NULL;
    char *_array = NULL;

    assert(stream != NULL);
    if (stream == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return NULL;
    }

    assert((elem_size == 1) || (elem_size == 2) || (elem_size == 4));
    if (!((elem_size == 1) || (elem_size == 2) || (elem_size == 4))) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return NULL;
    }

    assert((type == SLMP_BINARY_STREAM) || (type == SLMP_ASCII_STREAM));
    switch (type) {
    case SLMP_BINARY_STREAM:
        m = 1;
        switch (elem_size) {
        case 1:
            decp = decode_bin_8b_ptr;
            break;
        case 2:
            decp = decode_bin_16b_ptr;
            break;
        case 4:
            decp = decode_bin_32b_ptr;
            break;
        default:
            return 0;
        }
        break;
    case SLMP_ASCII_STREAM:
        m = 2;
        switch (elem_size) {
        case 1:
            decp = decode_ascii_8b_ptr;
            break;
        case 2:
            decp = decode_ascii_16b_ptr;
            break;
        case 4:
            decp = decode_ascii_32b_ptr;
            break;
        default:
            return 0;
        }
        break;
    default:
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    n = len / elem_size;
    if (n == 0) {
        slmp_set_errno(SLMP_ERROR_BUFFER_TOO_SHORT);
        return NULL;
    }

    _array = array = slmp_malloc(n * elem_size);
    if (array == NULL) {
        slmp_set_errno(SLMP_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    if ((type == SLMP_BINARY_STREAM) && (elem_size == 1)) {
        memcpy(array, stream, n * elem_size);
        return array;
    }

    for (i = 0; i != n; ++i) {
        decp(stream, _array);
        stream += m * elem_size;
        _array += elem_size;
    }

    return array;
}

