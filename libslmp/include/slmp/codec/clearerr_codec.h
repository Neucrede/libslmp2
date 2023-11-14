/**
 * \file clearerr_codec.h
 * 
 * \brief Clear Error.
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\ClearError.cge by CCGEN program.
 */

#ifndef CLEARERR_CODEC_H
#define CLEARERR_CODEC_H

#include "slmp/slmpapi.h" 
#include "slmp/command/cmdhdr.h" 

#ifdef __cplusplus 
extern "C" { 
#endif 

SLMPAPI size_t SLMPCALL slmp_encode_req_clear_error_code(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_clear_error_code(
    uint8_t *stream, size_t len, int type, int addr_width);

SLMPAPI size_t SLMPCALL slmp_encode_req_clear_error_history(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_clear_error_history(
    uint8_t *stream, size_t len, int type, int addr_width);

#ifdef __cplusplus 
} 
#endif 

#endif /* CLEARERR_CODEC_H */
