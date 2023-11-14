/*
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\SelfTest.cge by CCGEN program.
 */

#include "cmdcodec_priv.h" 
#include "slmp/command/selftest.h" 
#include "slmp/codec/selftest_codec.h" 

SLMPAPI size_t SLMPCALL slmp_encode_req_self_test(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_self_test_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_self_test_t, 1); 

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
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_self_test( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_self_test_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_self_test_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_self_test_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_self_test(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_self_test_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_self_test_t, 1); 

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
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_self_test( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_self_test_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_self_test_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_self_test_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

