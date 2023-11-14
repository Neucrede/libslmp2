/*
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\NodeConnect.cge by CCGEN program.
 */

#include "cmdcodec_priv.h" 
#include "slmp/command/nodeconn.h" 
#include "slmp/codec/nodeconn_codec.h" 

SLMPAPI size_t SLMPCALL slmp_encode_req_node_search(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_node_search_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_node_search_t, 1); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        7 + var_part_size, 
        7 + var_part_size, 
        14 + var_part_size, 
        14 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mac_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mac_addr), 6); 
        /* ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->ip_addr_size); 
        /* ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ip_addr), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mac_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mac_addr), 6); 
        /* ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->ip_addr_size); 
        /* ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ip_addr), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_node_search( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_node_search_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(7, 7, 14, 14); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_node_search_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_node_search_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mac_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mac_addr), 6); 
        /* ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->ip_addr_size)); 
        /* ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ip_addr), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mac_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mac_addr), 6); 
        /* ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->ip_addr_size)); 
        /* ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ip_addr), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_node_search(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_node_search_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_node_search_t, 0); 

    var_part_size += (size_t)(cmd->cli_ip_addr_size); 
    var_part_size += (size_t)(cmd->svr_ip_addr_size); 
    var_part_size += (size_t)(cmd->svr_ip_addr_size); 
    var_part_size += (size_t)(cmd->svr_ip_addr_size); 
    var_part_size += (size_t)(cmd->svr_hostname_size); 
    var_part_size += (size_t)(cmd->tgt_ip_addr_size); 
    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        26 + var_part_size, 
        26 + var_part_size, 
        51 + var_part_size, 
        51 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* cli_mac */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->cli_mac), 6); 
        /* cli_ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->cli_ip_addr_size); 
        /* cli_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->cli_ip_addr, cmd->cli_ip_addr_size); 
        /* svr_mac_addr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_mac_addr); 
        /* svr_ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_ip_addr_size); 
        /* svr_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_ip_addr, cmd->svr_ip_addr_size); 
        /* svr_subnet_mask */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_subnet_mask, cmd->svr_ip_addr_size); 
        /* svr_default_gateway */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_default_gateway, cmd->svr_ip_addr_size); 
        /* svr_hostname_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_hostname_size); 
        /* svr_hostname */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_hostname, cmd->svr_hostname_size); 
        /* svr_vendor_code */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->svr_vendor_code); 
        /* svr_model_code */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->svr_model_code); 
        /* svr_machine_version */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->svr_machine_version); 
        /* tgt_ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->tgt_ip_addr_size); 
        /* tgt_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->tgt_ip_addr, cmd->tgt_ip_addr_size); 
        /* tgt_port_num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->tgt_port_num); 
        /* svr_status */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->svr_status); 
        /* svr_port_num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->svr_port_num); 
        /* svr_protocol */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_protocol); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* cli_mac */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->cli_mac), 6); 
        /* cli_ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->cli_ip_addr_size); 
        /* cli_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->cli_ip_addr, cmd->cli_ip_addr_size); 
        /* svr_mac_addr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_mac_addr); 
        /* svr_ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_ip_addr_size); 
        /* svr_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_ip_addr, cmd->svr_ip_addr_size); 
        /* svr_subnet_mask */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_subnet_mask, cmd->svr_ip_addr_size); 
        /* svr_default_gateway */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_default_gateway, cmd->svr_ip_addr_size); 
        /* svr_hostname_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_hostname_size); 
        /* svr_hostname */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_hostname, cmd->svr_hostname_size); 
        /* svr_vendor_code */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->svr_vendor_code); 
        /* svr_model_code */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->svr_model_code); 
        /* svr_machine_version */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->svr_machine_version); 
        /* tgt_ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->tgt_ip_addr_size); 
        /* tgt_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->tgt_ip_addr, cmd->tgt_ip_addr_size); 
        /* tgt_port_num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->tgt_port_num); 
        /* svr_status */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->svr_status); 
        /* svr_port_num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->svr_port_num); 
        /* svr_protocol */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_protocol); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_node_search( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_node_search_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(26, 26, 51, 51); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_node_search_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_node_search_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* cli_mac */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->cli_mac), 6); 
        /* cli_ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->cli_ip_addr_size)); 
        /* cli_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->cli_ip_addr, cmd->cli_ip_addr_size); 
        /* svr_mac_addr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_mac_addr)); 
        /* svr_ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_ip_addr_size)); 
        /* svr_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_ip_addr, cmd->svr_ip_addr_size); 
        /* svr_subnet_mask */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_subnet_mask, cmd->svr_ip_addr_size); 
        /* svr_default_gateway */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_default_gateway, cmd->svr_ip_addr_size); 
        /* svr_hostname_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_hostname_size)); 
        /* svr_hostname */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_hostname, cmd->svr_hostname_size); 
        /* svr_vendor_code */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->svr_vendor_code)); 
        /* svr_model_code */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->svr_model_code)); 
        /* svr_machine_version */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->svr_machine_version)); 
        /* tgt_ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->tgt_ip_addr_size)); 
        /* tgt_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->tgt_ip_addr, cmd->tgt_ip_addr_size); 
        /* tgt_port_num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->tgt_port_num)); 
        /* svr_status */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->svr_status)); 
        /* svr_port_num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->svr_port_num)); 
        /* svr_protocol */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_protocol)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* cli_mac */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->cli_mac), 6); 
        /* cli_ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->cli_ip_addr_size)); 
        /* cli_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->cli_ip_addr, cmd->cli_ip_addr_size); 
        /* svr_mac_addr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_mac_addr)); 
        /* svr_ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_ip_addr_size)); 
        /* svr_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_ip_addr, cmd->svr_ip_addr_size); 
        /* svr_subnet_mask */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_subnet_mask, cmd->svr_ip_addr_size); 
        /* svr_default_gateway */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_default_gateway, cmd->svr_ip_addr_size); 
        /* svr_hostname_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_hostname_size)); 
        /* svr_hostname */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_hostname, cmd->svr_hostname_size); 
        /* svr_vendor_code */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->svr_vendor_code)); 
        /* svr_model_code */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->svr_model_code)); 
        /* svr_machine_version */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->svr_machine_version)); 
        /* tgt_ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->tgt_ip_addr_size)); 
        /* tgt_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->tgt_ip_addr, cmd->tgt_ip_addr_size); 
        /* tgt_port_num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->tgt_port_num)); 
        /* svr_status */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->svr_status)); 
        /* svr_port_num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->svr_port_num)); 
        /* svr_protocol */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_protocol)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_set_ip_address(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_set_ip_address_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_set_ip_address_t, 0); 

    var_part_size += (size_t)(cmd->cli_ip_addr_size); 
    var_part_size += (size_t)(cmd->svr_ip_addr_size); 
    var_part_size += (size_t)(cmd->svr_ip_addr_size); 
    var_part_size += (size_t)(cmd->svr_ip_addr_size); 
    var_part_size += (size_t)(cmd->svr_hostname_size); 
    var_part_size += (size_t)(cmd->tgt_ip_addr_size); 
    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        14 + var_part_size, 
        14 + var_part_size, 
        28 + var_part_size, 
        28 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* cli_mac_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->cli_mac_addr), 6); 
        /* cli_ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->cli_ip_addr_size); 
        /* cli_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->cli_ip_addr, cmd->cli_ip_addr_size); 
        /* svr_mac_addr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_mac_addr); 
        /* svr_ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_ip_addr_size); 
        /* svr_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_ip_addr, cmd->svr_ip_addr_size); 
        /* svr_subnet_mask */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_subnet_mask, cmd->svr_ip_addr_size); 
        /* svr_default_gateway */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_default_gateway, cmd->svr_ip_addr_size); 
        /* svr_hostname_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_hostname_size); 
        /* svr_hostname */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_hostname, cmd->svr_hostname_size); 
        /* tgt_ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->tgt_ip_addr_size); 
        /* tgt_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->tgt_ip_addr, cmd->tgt_ip_addr_size); 
        /* tgt_port_num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->tgt_port_num); 
        /* svr_protocol */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_protocol); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* cli_mac_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->cli_mac_addr), 6); 
        /* cli_ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->cli_ip_addr_size); 
        /* cli_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->cli_ip_addr, cmd->cli_ip_addr_size); 
        /* svr_mac_addr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_mac_addr); 
        /* svr_ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_ip_addr_size); 
        /* svr_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_ip_addr, cmd->svr_ip_addr_size); 
        /* svr_subnet_mask */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_subnet_mask, cmd->svr_ip_addr_size); 
        /* svr_default_gateway */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_default_gateway, cmd->svr_ip_addr_size); 
        /* svr_hostname_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_hostname_size); 
        /* svr_hostname */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_hostname, cmd->svr_hostname_size); 
        /* tgt_ip_addr_size */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->tgt_ip_addr_size); 
        /* tgt_ip_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->tgt_ip_addr, cmd->tgt_ip_addr_size); 
        /* tgt_port_num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->tgt_port_num); 
        /* svr_protocol */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->svr_protocol); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_set_ip_address( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_set_ip_address_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(14, 14, 28, 28); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_set_ip_address_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_set_ip_address_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* cli_mac_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->cli_mac_addr), 6); 
        /* cli_ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->cli_ip_addr_size)); 
        /* cli_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->cli_ip_addr, cmd->cli_ip_addr_size); 
        /* svr_mac_addr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_mac_addr)); 
        /* svr_ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_ip_addr_size)); 
        /* svr_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_ip_addr, cmd->svr_ip_addr_size); 
        /* svr_subnet_mask */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_subnet_mask, cmd->svr_ip_addr_size); 
        /* svr_default_gateway */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_default_gateway, cmd->svr_ip_addr_size); 
        /* svr_hostname_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_hostname_size)); 
        /* svr_hostname */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_hostname, cmd->svr_hostname_size); 
        /* tgt_ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->tgt_ip_addr_size)); 
        /* tgt_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->tgt_ip_addr, cmd->tgt_ip_addr_size); 
        /* tgt_port_num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->tgt_port_num)); 
        /* svr_protocol */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_protocol)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* cli_mac_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->cli_mac_addr), 6); 
        /* cli_ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->cli_ip_addr_size)); 
        /* cli_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->cli_ip_addr, cmd->cli_ip_addr_size); 
        /* svr_mac_addr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_mac_addr)); 
        /* svr_ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_ip_addr_size)); 
        /* svr_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_ip_addr, cmd->svr_ip_addr_size); 
        /* svr_subnet_mask */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_subnet_mask, cmd->svr_ip_addr_size); 
        /* svr_default_gateway */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_default_gateway, cmd->svr_ip_addr_size); 
        /* svr_hostname_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_hostname_size)); 
        /* svr_hostname */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->svr_hostname, cmd->svr_hostname_size); 
        /* tgt_ip_addr_size */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->tgt_ip_addr_size)); 
        /* tgt_ip_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->tgt_ip_addr, cmd->tgt_ip_addr_size); 
        /* tgt_port_num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->tgt_port_num)); 
        /* svr_protocol */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->svr_protocol)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_set_ip_address(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_set_ip_address_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_set_ip_address_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(6, 6, 12, 12); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* cli_mac_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->cli_mac_addr), 6); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* cli_mac_addr */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->cli_mac_addr), 6); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_set_ip_address( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_set_ip_address_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 6, 12, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_set_ip_address_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_set_ip_address_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* cli_mac_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->cli_mac_addr), 6); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* cli_mac_addr */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->cli_mac_addr), 6); 
    } 

    return &(cmd->hdr); 
}

