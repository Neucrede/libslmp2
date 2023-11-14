/**
 * \file selftest_codec.h
 * 
 * \brief Loopback Test.
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\SelfTest.cge by CCGEN program.
 */

#ifndef SELFTEST_CODEC_H
#define SELFTEST_CODEC_H

#include "slmp/slmpapi.h" 
#include "slmp/command/cmdhdr.h" 

#ifdef __cplusplus 
extern "C" { 
#endif 

SLMPAPI size_t SLMPCALL slmp_encode_req_self_test(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_self_test(
    uint8_t *stream, size_t len, int type, int addr_width);

SLMPAPI size_t SLMPCALL slmp_encode_res_self_test(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_self_test(
    uint8_t *stream, size_t len, int type, int addr_width);

#ifdef __cplusplus 
} 
#endif 

#endif /* SELFTEST_CODEC_H */
