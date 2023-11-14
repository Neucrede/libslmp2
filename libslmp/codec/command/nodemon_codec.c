/*
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\NodeMonitoring.cge by CCGEN program.
 */

#include "cmdcodec_priv.h" 
#include "slmp/command/nodemon.h" 
#include "slmp/codec/nodemon_codec.h" 

SLMPAPI size_t SLMPCALL slmp_encode_req_status_read(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_status_read_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_status_read_t, 0); 

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

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_status_read( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_status_read_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(0, 0, 0, 0); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_status_read_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_status_read_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_status_read(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_status_read_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_status_read_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(4, 4, 8, 8); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
        /* status */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->status); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
        /* status */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->status); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_status_read( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_status_read_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_status_read_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_status_read_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
        /* status */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->status)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
        /* status */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->status)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_status_read_multi(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_status_read_multi_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_status_read_multi_t, 0); 

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

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_status_read_multi( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_status_read_multi_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(0, 0, 0, 0); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_status_read_multi_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_status_read_multi_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_status_read_multi(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_status_read_multi_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_status_read_multi_t, 0); 

    var_part_size += (size_t)(cmd->ip_addr_size); 
    var_part_size += (size_t)(cmd->ip_addr_size); 
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
        /* ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->ip_addr_size); 
        /* svr_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_ip_addr, cmd->ip_addr_size); 
        /* tgt_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->tgt_ip_addr, cmd->ip_addr_size); 
        /* svr_state */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_state); 
        /* status */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->status); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->ip_addr_size); 
        /* svr_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_ip_addr, cmd->ip_addr_size); 
        /* tgt_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->tgt_ip_addr, cmd->ip_addr_size); 
        /* svr_state */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_state); 
        /* status */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->status); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_status_read_multi( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_status_read_multi_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 6, 12, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_status_read_multi_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_status_read_multi_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->ip_addr_size)); 
        /* svr_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_ip_addr, cmd->ip_addr_size); 
        /* tgt_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->tgt_ip_addr, cmd->ip_addr_size); 
        /* svr_state */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_state)); 
        /* status */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->status)); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->ip_addr_size)); 
        /* svr_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_ip_addr, cmd->ip_addr_size); 
        /* tgt_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->tgt_ip_addr, cmd->ip_addr_size); 
        /* svr_state */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_state)); 
        /* status */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->status)); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_get_comm_settings(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_get_comm_settings_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_get_comm_settings_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(2, 2, 4, 4); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* target */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->target); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* target */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->target); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_get_comm_settings( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_get_comm_settings_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_get_comm_settings_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_get_comm_settings_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* target */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->target)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* target */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->target)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_get_comm_settings(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_get_comm_settings_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_get_comm_settings_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(8, 8, 16, 16); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* target */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->target); 
        /* port_num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->port_num); 
        /* timeout */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->timeout); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* target */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->target); 
        /* port_num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->port_num); 
        /* timeout */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->timeout); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_get_comm_settings( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_get_comm_settings_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(8, 8, 16, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_get_comm_settings_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_get_comm_settings_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* target */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->target)); 
        /* port_num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->port_num)); 
        /* timeout */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->timeout)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* target */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->target)); 
        /* port_num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->port_num)); 
        /* timeout */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->timeout)); 
    } 

    return &(cmd->hdr); 
}

