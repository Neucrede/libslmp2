/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#ifndef __WORDCODEC_H__
#define __WORDCODEC_H__

#include <stdint.h>


typedef void (*pfn_codec_8b_t)(uint8_t /* src */, void* /* dest */);
typedef void (*pfn_codec_16b_t)(uint16_t /* src */, void* /* dest */);
typedef void (*pfn_codec_24b_t)(uint32_t /* src */, void* /* dest */);
typedef void (*pfn_codec_32b_t)(uint32_t /* src */, void* /* dest */);
typedef void (*pfn_codec_ptr_t)(void* /* src */, void* /* dest */);
typedef void (*pfn_codec_n_ptr_t)(void* /* src */, void*  /* dest */,
    size_t /* n */);


uint8_t nibble_to_ascii(uint8_t n);
uint8_t ascii_to_nibble(uint8_t a);

void decode_bin_8b_ptr(void *src, void *dest);
void decode_bin_8b(uint8_t src, void *dest);
void encode_bin_8b_ptr(void *src, void *dest);
void encode_bin_8b(uint8_t src, void *dest);

void decode_bin_16b_ptr(void *src, void *dest);
void decode_bin_16b(uint16_t src, void *dest);
void encode_bin_16b_ptr(void *src, void *dest);
void encode_bin_16b(uint16_t src, void *dest);

void decode_bin_24b_ptr(void *src, void *dest);
void decode_bin_24b(uint32_t src, void *dest);
void encode_bin_24b_ptr(void *src, void *dest);
void encode_bin_24b(uint32_t src, void *dest);

void decode_bin_32b_ptr(void *src, void *dest);
void decode_bin_32b(uint32_t src, void *dest);
void encode_bin_32b_ptr(void *src, void *dest);
void encode_bin_32b(uint32_t src, void *dest);

void decode_ascii_8b_ptr(void *src, void *dest);
void encode_ascii_8b_ptr(void *src, void *dest);
void encode_ascii_8b(uint8_t src, void *dest);

void decode_ascii_16b_ptr(void *src, void *dest);
void encode_ascii_16b_ptr(void *src, void *dest);
void encode_ascii_16b(uint16_t src, void *dest);

void decode_ascii_24b_ptr(void *src, void *dest);
void encode_ascii_24b_ptr(void *src, void *dest);
void encode_ascii_24b(uint32_t src, void *dest);

void decode_ascii_32b_ptr(void *src, void *dest);
void encode_ascii_32b_ptr(void *src, void *dest);
void encode_ascii_32b(uint32_t src, void *dest);

void encode_bin_n_ptr(void *src, void *dest, size_t n);
void decode_bin_n_ptr(void *src, void *dest, size_t n);
void encode_ascii_n_ptr(void *src, void *dest, size_t n);
void decode_ascii_n_ptr(void *src, void *dest, size_t n);


#endif /* __WORDCODEC_H__ */
