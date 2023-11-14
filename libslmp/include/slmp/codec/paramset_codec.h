/**
 * \file paramset_codec.h
 * 
 * \brief Setting Parameters (ParameterSetting)
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\ParameterSetting.cge by CCGEN program.
 */

#ifndef PARAMSET_CODEC_H
#define PARAMSET_CODEC_H

#include "slmp/slmpapi.h" 
#include "slmp/command/cmdhdr.h" 

#ifdef __cplusplus 
extern "C" { 
#endif 

SLMPAPI size_t SLMPCALL slmp_encode_req_device_info_compare(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_info_compare(
    uint8_t *stream, size_t len, int type, int addr_width);

SLMPAPI size_t SLMPCALL slmp_encode_res_device_info_compare(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_device_info_compare(
    uint8_t *stream, size_t len, int type, int addr_width);

SLMPAPI size_t SLMPCALL slmp_encode_req_get_param(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_get_param(
    uint8_t *stream, size_t len, int type, int addr_width);

SLMPAPI size_t SLMPCALL slmp_encode_res_get_param(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_get_param(
    uint8_t *stream, size_t len, int type, int addr_width);

SLMPAPI size_t SLMPCALL slmp_encode_req_set_param(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_set_param(
    uint8_t *stream, size_t len, int type, int addr_width);

SLMPAPI size_t SLMPCALL slmp_encode_req_param_set_start(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_param_set_start(
    uint8_t *stream, size_t len, int type, int addr_width);

SLMPAPI size_t SLMPCALL slmp_encode_req_param_set_end(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_param_set_end(
    uint8_t *stream, size_t len, int type, int addr_width);

SLMPAPI size_t SLMPCALL slmp_encode_req_param_set_cancel(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_param_set_cancel(
    uint8_t *stream, size_t len, int type, int addr_width);

#ifdef __cplusplus 
} 
#endif 

#endif /* PARAMSET_CODEC_H */
