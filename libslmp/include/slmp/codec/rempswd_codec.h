/**
 * \file rempswd_codec.h
 * 
 * \brief Remote Password Commands
 * 
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\RemotePassword.cge by CCGEN program.
 */

#ifndef REMPSWD_CODEC_H
#define REMPSWD_CODEC_H

#include "slmp/slmpapi.h" 
#include "slmp/command/cmdhdr.h" 

#ifdef __cplusplus 
extern "C" { 
#endif 

SLMPAPI size_t SLMPCALL slmp_encode_req_password_lock(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_password_lock(
    uint8_t *stream, size_t len, int type, int addr_width);

SLMPAPI size_t SLMPCALL slmp_encode_req_password_unlock(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_password_unlock(
    uint8_t *stream, size_t len, int type, int addr_width);

#ifdef __cplusplus 
} 
#endif 

#endif /* REMPSWD_CODEC_H */
