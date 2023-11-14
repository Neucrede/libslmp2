/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include <assert.h>
#include <string.h>

#include "wordcodec.h"

#define HI_NIBBLE(x)    ((uint8_t)((x & 0xF0) >> 4))
#define LO_NIBBLE(x)    ((uint8_t)(x & 0x0F))

uint8_t nibble_to_ascii(uint8_t n)
{
    uint8_t x = n & 0x0F;

    if (x < 0x0A) {
        return 0x30 + x;
    }
    else {
        return 0x41 + (x - 0x0A);
    }
}

uint8_t ascii_to_nibble(uint8_t a)
{
    if ((0x30 <= a) && (a <= 0x46)) {
        if (a <= 0x39) {
            return a - 0x30;
        }
        else if (a >= 0x41) {
            return 0x0A + (a - 0x41);
        }
    }

    return 0;
}

void decode_bin_8b_ptr(void *src, void *dest)
{
    uint8_t *src_bytes = src;
    uint8_t *dest_8b = dest;

    assert(src != NULL);
    assert(dest != NULL);
    *dest_8b = src_bytes[0];
}

void decode_bin_8b(uint8_t src, void *dest)
{
    decode_bin_8b_ptr(&src, dest);
}

void encode_bin_8b_ptr(void *src, void *dest)
{
    uint8_t src_8b = src ? *((uint8_t*)src) : 0;
    uint8_t *dest_8b = dest;

    assert(dest != NULL);
    *dest_8b = src_8b;
}

void encode_bin_8b(uint8_t src, void *dest)
{
    encode_bin_8b_ptr(&src, dest);
}

void decode_bin_16b_ptr(void *src, void *dest)
{
    uint16_t *dest_16b = dest;
    uint8_t *src_bytes = src;

    assert(src != NULL);
    assert(dest != NULL);
    *dest_16b = src_bytes[0] | (((uint16_t)src_bytes[1]) << 8);
}

void decode_bin_16b(uint16_t src, void *dest)
{
    decode_bin_16b_ptr(&src, dest);
}

void encode_bin_16b_ptr(void *src, void *dest)
{
    uint16_t src_16b = src ? *((uint16_t*)src) : 0;
    uint8_t *dest_16b = dest;

    assert(dest != NULL);
    dest_16b[0] = (src_16b & 0x00FF);
    dest_16b[1] = (src_16b & 0xFF00) >> 8;
}

void encode_bin_16b(uint16_t src, void *dest)
{
    encode_bin_16b_ptr(&src, dest);
}

void decode_bin_24b_ptr(void *src, void *dest)
{
    uint32_t *dest_24b = dest;
    uint8_t *src_bytes = src;

    assert(src != NULL);
    assert(dest != NULL);
    *dest_24b = src_bytes[0] |
        (((uint32_t)src_bytes[1]) << 8) |
        (((uint32_t)src_bytes[2]) << 16);
}

void decode_bin_24b(uint32_t src, void *dest)
{
    decode_bin_24b_ptr(&src, dest);
}

void encode_bin_24b_ptr(void *src, void *dest)
{
    uint32_t src_24b = src ? *((uint32_t*)src) : 0;
    uint8_t *dest_24b = dest;

    assert(dest != NULL);
    dest_24b[0] = (src_24b & 0x0000FF);
    dest_24b[1] = (src_24b & 0x00FF00) >> 8;
    dest_24b[2] = (src_24b & 0xFF0000) >> 16;
}

void encode_bin_24b(uint32_t src, void *dest)
{
    encode_bin_24b_ptr(&src, dest);
}

void decode_bin_32b_ptr(void *src, void *dest)
{
    uint32_t *dest_32b = dest;
    uint8_t *src_bytes = src;

    assert(src != NULL);
    assert(dest != NULL);
    *dest_32b = src_bytes[0] |
        (((uint32_t)src_bytes[1]) << 8) |
        (((uint32_t)src_bytes[2]) << 16) |
        (((uint32_t)src_bytes[3]) << 24);
}

void decode_bin_32b(uint32_t src, void *dest)
{
    decode_bin_32b_ptr(&src, dest);
}

void encode_bin_32b_ptr(void *src, void *dest)
{
    uint32_t src_32b = src ? *((uint32_t*)src) : 0;
    uint8_t *dest_32b = dest;

    assert(dest != NULL);
    dest_32b[0] = (src_32b & 0x000000FF);
    dest_32b[1] = (src_32b & 0x0000FF00) >> 8;
    dest_32b[2] = (src_32b & 0x00FF0000) >> 16;
    dest_32b[3] = (src_32b & 0xFF000000) >> 24;
}

void encode_bin_32b(uint32_t src, void *dest)
{
    encode_bin_32b_ptr(&src, dest);
}

void decode_ascii_8b_ptr(void *src, void *dest)
{
    uint8_t *src_bytes = src;
    uint8_t *dest_8b = dest;

    assert(src != NULL);
    assert(dest != NULL);
    *dest_8b = (ascii_to_nibble(src_bytes[0]) << 4) |
        ascii_to_nibble(src_bytes[1]);
}

void encode_ascii_8b_ptr(void *src, void *dest)
{
    uint8_t src_8b = src ? *((uint8_t*)src) : 0;
    uint8_t *dest_8b = dest;

    assert(dest != NULL);
    dest_8b[0] = nibble_to_ascii(HI_NIBBLE(src_8b));
    dest_8b[1] = nibble_to_ascii(LO_NIBBLE(src_8b));
}

void encode_ascii_8b(uint8_t src, void *dest)
{
    encode_ascii_8b_ptr(&src, dest);
}

void decode_ascii_16b_ptr(void *src, void *dest)
{
    uint16_t *dest_16b = dest;
    uint8_t *src_bytes = src;
    uint8_t hi_byte, lo_byte;

    assert(dest != NULL);
    decode_ascii_8b_ptr(&src_bytes[0], &hi_byte);
    decode_ascii_8b_ptr(&src_bytes[2], &lo_byte);
    *dest_16b = (((uint16_t)hi_byte) << 8) | lo_byte;
}

void encode_ascii_16b_ptr(void *src, void *dest)
{
    uint16_t src_16b = src ? *((uint16_t*)src) : 0;
    uint8_t *dest_16b = dest;
    uint8_t hi_byte, lo_byte;

    assert(dest != NULL);
    hi_byte = (src_16b & 0xFF00) >> 8;
    lo_byte = src_16b & 0x00FF;
    encode_ascii_8b_ptr(&hi_byte, &dest_16b[0]);
    encode_ascii_8b_ptr(&lo_byte, &dest_16b[2]);
}

void encode_ascii_16b(uint16_t src, void *dest)
{
    encode_ascii_16b_ptr(&src, dest);
}

void decode_ascii_24b_ptr(void *src, void *dest)
{
    uint32_t *dest_24b = dest;
    uint8_t *src_bytes = src;
    uint8_t byte2, byte1, byte0;

    assert(src != NULL);
    assert(dest != NULL);
    decode_ascii_8b_ptr(&src_bytes[0], &byte2);
    decode_ascii_8b_ptr(&src_bytes[2], &byte1);
    decode_ascii_8b_ptr(&src_bytes[4], &byte0);
    *dest_24b = byte0 |
        (((uint32_t)byte1) << 8) |
        (((uint32_t)byte2) << 16);
}

void encode_ascii_24b_ptr(void *src, void *dest)
{
    uint32_t src_24b = src ? *((uint32_t*)src) : 0;
    uint8_t *dest_24b = dest;
    uint8_t byte2, byte1, byte0;

    assert(dest != NULL);
    byte0 = (src_24b & 0x0000FF);
    byte1 = (src_24b & 0x00FF00) >> 8;
    byte2 = (src_24b & 0xFF0000) >> 16;
    encode_ascii_8b_ptr(&byte2, &dest_24b[0]);
    encode_ascii_8b_ptr(&byte1, &dest_24b[2]);
    encode_ascii_8b_ptr(&byte0, &dest_24b[4]);
}

void encode_ascii_24b(uint32_t src, void *dest)
{
    encode_ascii_24b_ptr(&src, dest);
}

void decode_ascii_32b_ptr(void *src, void *dest)
{
    uint32_t *dest_32b = dest;
    uint8_t *src_bytes = src;
    uint8_t byte3, byte2, byte1, byte0;

    assert(src != NULL);
    assert(dest != NULL);
    decode_ascii_8b_ptr(&src_bytes[0], &byte3);
    decode_ascii_8b_ptr(&src_bytes[2], &byte2);
    decode_ascii_8b_ptr(&src_bytes[4], &byte1);
    decode_ascii_8b_ptr(&src_bytes[6], &byte0);
    *dest_32b = byte0 |
        (((uint32_t)byte1) << 8) |
        (((uint32_t)byte2) << 16) |
        (((uint32_t)byte3) << 24);
}

void encode_ascii_32b_ptr(void *src, void *dest)
{
    uint32_t src_32b = src ? *((uint32_t*)src) : 0;
    uint8_t *dest_32b = dest;
    uint8_t byte3, byte2, byte1, byte0;

    assert(dest != NULL);
    byte0 = (src_32b & 0x000000FF);
    byte1 = (src_32b & 0x0000FF00) >> 8;
    byte2 = (src_32b & 0x00FF0000) >> 16;
    byte3 = (src_32b & 0xFF000000) >> 24;
    encode_ascii_8b_ptr(&byte3, &dest_32b[0]);
    encode_ascii_8b_ptr(&byte2, &dest_32b[2]);
    encode_ascii_8b_ptr(&byte1, &dest_32b[4]);
    encode_ascii_8b_ptr(&byte0, &dest_32b[6]);
}

void encode_ascii_32b(uint32_t src, void *dest)
{
    encode_ascii_32b_ptr(&src, dest);
}

void encode_bin_n_ptr(void *src, void *dest, size_t n)
{
    if (n == 0) return;

    assert(src != NULL);
    assert(dest != NULL);
    memmove(dest, src, n);
}

void decode_bin_n_ptr(void *src, void *dest, size_t n)
{
    if (n == 0) return;

    assert(src != NULL);
    assert(dest != NULL);
    memmove(dest, src, n);
}

void encode_ascii_n_ptr(void *src, void *dest, size_t n)
{
    size_t i;
    uint8_t *src_8b = src;
    uint8_t *dest_8b = dest;

    if (n == 0) return;

    assert(src != NULL);
    assert(dest != NULL);

    for (i = 0; i != n; ++i) {
        encode_ascii_8b_ptr(src_8b, dest_8b);
        ++src_8b;
        dest_8b += 2;
    }
}

void decode_ascii_n_ptr(void *src, void *dest, size_t n)
{
    size_t i;
    uint8_t *src_8b = src;
    uint8_t *dest_8b = dest;

    if (n == 0) return;

    assert(src != NULL);
    assert(dest != NULL);

    for (i = 0; i != n / 2; ++i) {
        decode_ascii_8b_ptr(src_8b, dest_8b);
        src_8b += 2;
        ++dest_8b;
    }
}
