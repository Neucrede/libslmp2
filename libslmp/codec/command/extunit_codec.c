/*
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\ExtensionModule.cge by CCGEN program.
 */

#include "cmdcodec_priv.h" 
#include "slmp/command/extunit.h" 
#include "slmp/codec/extunit_codec.h" 

SLMPAPI size_t SLMPCALL slmp_encode_req_extend_unit_read(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_extend_unit_read_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_extend_unit_read_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(8, 8, 16, 16); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* addr_begin */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin); 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* unit */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->unit); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* addr_begin */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin); 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* unit */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->unit); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_extend_unit_read( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_extend_unit_read_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(8, 8, 16, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_extend_unit_read_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_extend_unit_read_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* addr_begin */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin)); 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* unit */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->unit)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* addr_begin */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin)); 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* unit */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->unit)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_extend_unit_write(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_extend_unit_write_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_extend_unit_write_t, 1); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        8 + var_part_size, 
        8 + var_part_size, 
        16 + var_part_size, 
        16 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* addr_begin */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin); 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* unit */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->unit); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* addr_begin */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin); 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* unit */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->unit); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_extend_unit_write( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_extend_unit_write_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(8, 8, 16, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_extend_unit_write_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_extend_unit_write_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* addr_begin */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin)); 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* unit */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->unit)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* addr_begin */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin)); 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* unit */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->unit)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

