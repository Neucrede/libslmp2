/*
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\RemoteControl.cge by CCGEN program.
 */

#include "cmdcodec_priv.h" 
#include "slmp/command/remctrl.h" 
#include "slmp/codec/remctrl_codec.h" 

SLMPAPI size_t SLMPCALL slmp_encode_req_remote_run(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_remote_run_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_remote_run_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(4, 4, 8, 8); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
        /* clear_mode */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->clear_mode); 
        /* reserved1 */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->reserved1); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
        /* clear_mode */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->clear_mode); 
        /* reserved1 */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->reserved1); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_remote_run( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_remote_run_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_remote_run_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_remote_run_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
        /* clear_mode */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->clear_mode)); 
        /* reserved1 */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->reserved1)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
        /* clear_mode */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->clear_mode)); 
        /* reserved1 */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->reserved1)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_remote_stop(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_remote_stop_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_remote_stop_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(2, 2, 4, 4); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_remote_stop( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_remote_stop_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_remote_stop_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_remote_stop_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_remote_pause(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_remote_pause_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_remote_pause_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(2, 2, 4, 4); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_remote_pause( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_remote_pause_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_remote_pause_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_remote_pause_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_remote_latch_clear(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_remote_latch_clear_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_remote_latch_clear_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(2, 2, 4, 4); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_remote_latch_clear( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_remote_latch_clear_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_remote_latch_clear_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_remote_latch_clear_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_remote_reset(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_remote_reset_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_remote_reset_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(2, 2, 4, 4); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_remote_reset( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_remote_reset_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_remote_reset_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_remote_reset_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_read_type_name(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_read_type_name_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_read_type_name_t, 0); 

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

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_read_type_name( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_read_type_name_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(0, 0, 0, 0); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_read_type_name_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_read_type_name_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_read_type_name(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_read_type_name_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_read_type_name_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(18, 18, 20, 20); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* type */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->type), 16); 
        /* type_code */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->type_code); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* type */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->type), 16); 
        /* type_code */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->type_code); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_read_type_name( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_read_type_name_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(18, 18, 20, 20); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_read_type_name_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_read_type_name_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* type */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->type), 16); 
        /* type_code */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->type_code)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* type */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->type), 16); 
        /* type_code */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->type_code)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_node_indication(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_node_indication_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_node_indication_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(8, 8, 0, 0); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mac_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mac_addr), 6); 
        /* start_stop */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->start_stop); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mac_addr */ 
        /* start_stop */ 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_node_indication( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_node_indication_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(8, 8, 0, 0); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_node_indication_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_node_indication_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mac_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mac_addr), 6); 
        /* start_stop */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->start_stop)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mac_addr */ 
        /* start_stop */ 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_node_indication(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_node_indication_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_node_indication_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(6, 6, 0, 0); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mac_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mac_addr), 6); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mac_addr */ 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_node_indication( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_node_indication_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 6, 0, 0); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_node_indication_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_node_indication_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mac_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mac_addr), 6); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mac_addr */ 
    } 

    return &(cmd->hdr); 
}

