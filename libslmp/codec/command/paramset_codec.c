/*
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\ParameterSetting.cge by CCGEN program.
 */

#include "cmdcodec_priv.h" 
#include "slmp/command/paramset.h" 
#include "slmp/codec/paramset_codec.h" 

SLMPAPI size_t SLMPCALL slmp_encode_req_device_info_compare(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_info_compare_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_info_compare_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(10, 10, 20, 20); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* target */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->target); 
        /* vendor_code */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->vendor_code); 
        /* model_code */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->model_code); 
        /* machine_version */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->machine_version); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* target */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->target); 
        /* vendor_code */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->vendor_code); 
        /* model_code */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->model_code); 
        /* machine_version */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->machine_version); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_info_compare( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_info_compare_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(10, 10, 20, 20); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_info_compare_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_info_compare_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* target */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->target)); 
        /* vendor_code */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->vendor_code)); 
        /* model_code */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->model_code)); 
        /* machine_version */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->machine_version)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* target */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->target)); 
        /* vendor_code */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->vendor_code)); 
        /* model_code */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->model_code)); 
        /* machine_version */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->machine_version)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_device_info_compare(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_device_info_compare_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_device_info_compare_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(4, 4, 8, 8); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* target */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->target); 
        /* result */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->result); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* target */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->target); 
        /* result */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->result); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_device_info_compare( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_device_info_compare_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_device_info_compare_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_device_info_compare_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* target */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->target)); 
        /* result */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->result)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* target */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->target)); 
        /* result */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->result)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_get_param(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_get_param_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_get_param_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(4, 4, 8, 8); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* id */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->id); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* id */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->id); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_get_param( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_get_param_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_get_param_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_get_param_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* id */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->id)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* id */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->id)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_get_param(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_get_param_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_get_param_t, 1); 

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
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* id */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->id); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->size); 
        /* value */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->value), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* id */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->id); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->size); 
        /* value */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->value), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_get_param( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_get_param_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 6, 12, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_get_param_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_get_param_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* id */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->id)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->size)); 
        /* value */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->value), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* id */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->id)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->size)); 
        /* value */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->value), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_set_param(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_set_param_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_set_param_t, 1); 

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
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* id */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->id); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->size); 
        /* value */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->value), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* id */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->id); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->size); 
        /* value */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->value), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_set_param( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_set_param_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 6, 12, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_set_param_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_set_param_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* id */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->id)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->size)); 
        /* value */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->value), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* id */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->id)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->size)); 
        /* value */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->value), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_param_set_start(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_param_set_start_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_param_set_start_t, 0); 

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

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_param_set_start( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_param_set_start_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(0, 0, 0, 0); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_param_set_start_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_param_set_start_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_param_set_end(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_param_set_end_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_param_set_end_t, 0); 

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

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_param_set_end( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_param_set_end_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(0, 0, 0, 0); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_param_set_end_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_param_set_end_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_param_set_cancel(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_param_set_cancel_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_param_set_cancel_t, 0); 

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

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_param_set_cancel( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_param_set_cancel_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(0, 0, 0, 0); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_param_set_cancel_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_param_set_cancel_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
    } 

    return &(cmd->hdr); 
}

