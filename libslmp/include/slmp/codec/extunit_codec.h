/**
 * \file extunit_codec.h
 * 
 * \brief Extension Module (ExtendUnit) Commands
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\ExtensionModule.cge by CCGEN program.
 */

#ifndef EXTUNIT_CODEC_H
#define EXTUNIT_CODEC_H

#include "slmp/slmpapi.h" 
#include "slmp/command/cmdhdr.h" 

#ifdef __cplusplus 
extern "C" { 
#endif 

SLMPAPI size_t SLMPCALL slmp_encode_req_extend_unit_read(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_extend_unit_read(
    uint8_t *stream, size_t len, int type, int addr_width);

SLMPAPI size_t SLMPCALL slmp_encode_req_extend_unit_write(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_extend_unit_write(
    uint8_t *stream, size_t len, int type, int addr_width);

#ifdef __cplusplus 
} 
#endif 

#endif /* EXTUNIT_CODEC_H */
