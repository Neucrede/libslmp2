/*
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\DualPortMemory.cge by CCGEN program.
 */

#include "cmdcodec_priv.h" 
#include "slmp/command/dpmem.h" 
#include "slmp/codec/dpmem_codec.h" 

SLMPAPI size_t SLMPCALL slmp_encode_req_memory_read(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_memory_read_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_memory_read_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(6, 6, 12, 12); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* addr_begin */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin); 
        /* len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* addr_begin */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin); 
        /* len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_memory_read( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_memory_read_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 6, 12, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_memory_read_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_memory_read_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* addr_begin */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin)); 
        /* len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->len)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* addr_begin */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin)); 
        /* len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->len)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_memory_write(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_memory_write_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_memory_write_t, 1); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        6 + var_part_size, 
        6 + var_part_size, 
        12 + var_part_size, 
        12 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* addr_begin */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin); 
        /* len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* addr_begin */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin); 
        /* len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_memory_write( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_memory_write_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 6, 12, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_memory_write_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_memory_write_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* addr_begin */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin)); 
        /* len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* addr_begin */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin)); 
        /* len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

