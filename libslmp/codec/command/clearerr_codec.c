/*
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\ClearError.cge by CCGEN program.
 */

#include "cmdcodec_priv.h" 
#include "slmp/command/clearerr.h" 
#include "slmp/codec/clearerr_codec.h" 

SLMPAPI size_t SLMPCALL slmp_encode_req_clear_error_code(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_clear_error_code_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_clear_error_code_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(0, 0, 0, 0); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_clear_error_code( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_clear_error_code_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(0, 0, 0, 0); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_clear_error_code_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_clear_error_code_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_clear_error_history(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_clear_error_history_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_clear_error_history_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(0, 0, 0, 0); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_clear_error_history( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_clear_error_history_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(0, 0, 0, 0); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_clear_error_history_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_clear_error_history_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
    } 

    return &(cmd->hdr); 
}

