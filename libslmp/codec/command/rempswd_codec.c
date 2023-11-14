/*
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\RemotePassword.cge by CCGEN program.
 */

#include "cmdcodec_priv.h" 
#include "slmp/command/rempswd.h" 
#include "slmp/codec/rempswd_codec.h" 

SLMPAPI size_t SLMPCALL slmp_encode_req_password_lock(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_password_lock_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_password_lock_t, 0); 

    var_part_size += (size_t)(cmd->len); 
    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        2 + var_part_size, 
        2 + var_part_size, 
        4 + var_part_size, 
        4 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->len); 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->pwd, cmd->len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->len); 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->pwd, cmd->len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_password_lock( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_password_lock_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_password_lock_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_password_lock_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->len)); 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->pwd, cmd->len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->len)); 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->pwd, cmd->len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_password_unlock(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_password_unlock_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_password_unlock_t, 0); 

    var_part_size += (size_t)(cmd->len); 
    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        2 + var_part_size, 
        2 + var_part_size, 
        4 + var_part_size, 
        4 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->len); 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->pwd, cmd->len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->len); 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->pwd, cmd->len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_password_unlock( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_password_unlock_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_password_unlock_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_password_unlock_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->len)); 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->pwd, cmd->len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->len)); 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->pwd, cmd->len); 
    } 

    return &(cmd->hdr); 
}

