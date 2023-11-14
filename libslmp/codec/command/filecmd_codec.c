/*
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\File.cge by CCGEN program.
 */

#include "cmdcodec_priv.h" 
#include "slmp/command/filecmd.h" 
#include "slmp/codec/filecmd_codec.h" 

SLMPAPI size_t SLMPCALL slmp_encode_req_get_file_info(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_get_file_info_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_get_file_info_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(10, 10, 20, 20); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* file_num_begin */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->file_num_begin); 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* file_num_begin */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->file_num_begin); 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_get_file_info( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_get_file_info_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(10, 10, 20, 20); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_get_file_info_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_get_file_info_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* file_num_begin */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->file_num_begin)); 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* file_num_begin */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->file_num_begin)); 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_get_file_num_usage(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_get_file_num_usage_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_get_file_num_usage_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(6, 6, 12, 12); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_get_file_num_usage( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_get_file_num_usage_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 6, 12, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_get_file_num_usage_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_get_file_num_usage_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_get_file_info(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_get_file_info_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_get_file_info_t, 1); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        4 + var_part_size, 
        4 + var_part_size, 
        8 + var_part_size, 
        8 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num_total */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_total); 
        /* num_info */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_info); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_total */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_total); 
        /* num_info */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_info); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_get_file_info( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_get_file_info_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_get_file_info_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_get_file_info_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num_total */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_total)); 
        /* num_info */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_info)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_total */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_total)); 
        /* num_info */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_info)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_get_file_info_entry(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_get_file_info_entry_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_get_file_info_entry_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(22, 22, 32, 32); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
        /* last_edit_time */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_time); 
        /* last_edit_date */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_date); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
        /* last_edit_time */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_time); 
        /* last_edit_date */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_date); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_get_file_info_entry( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_get_file_info_entry_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(22, 22, 32, 32); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_get_file_info_entry_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_get_file_info_entry_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
        /* last_edit_time */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_time)); 
        /* last_edit_date */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_date)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->size)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
        /* last_edit_time */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_time)); 
        /* last_edit_date */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_date)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->size)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_get_file_info_detail_entry(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_get_file_info_detail_entry_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_get_file_info_detail_entry_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(54, 54, 64, 64); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
        /* last_edit_time */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_time); 
        /* last_edit_date */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_date); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->size); 
        /* hdr_text */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->hdr_text), 32); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
        /* last_edit_time */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_time); 
        /* last_edit_date */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_date); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->size); 
        /* hdr_text */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->hdr_text), 32); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_get_file_info_detail_entry( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_get_file_info_detail_entry_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(54, 54, 64, 64); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_get_file_info_detail_entry_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_get_file_info_detail_entry_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
        /* last_edit_time */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_time)); 
        /* last_edit_date */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_date)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->size)); 
        /* hdr_text */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->hdr_text), 32); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
        /* last_edit_time */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_time)); 
        /* last_edit_date */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_date)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->size)); 
        /* hdr_text */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->hdr_text), 32); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_change_file_edit_time(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_change_file_edit_time_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_change_file_edit_time_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(26, 26, 40, 40); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
        /* pattern */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->pattern); 
        /* last_edit_time */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_time); 
        /* last_edit_date */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_date); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
        /* pattern */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->pattern); 
        /* last_edit_time */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_time); 
        /* last_edit_date */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_date); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_change_file_edit_time( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_change_file_edit_time_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(26, 26, 40, 40); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_change_file_edit_time_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_change_file_edit_time_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
        /* pattern */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->pattern)); 
        /* last_edit_time */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_time)); 
        /* last_edit_date */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_date)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
        /* pattern */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->pattern)); 
        /* last_edit_time */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_time)); 
        /* last_edit_date */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_date)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_change_file_info(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_change_file_info_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_change_file_info_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(40, 40, 56, 56); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* old_name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->old_name), 8); 
        /* old_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->old_ext), 3); 
        /* old_attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->old_attr); 
        /* pattern */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->pattern); 
        /* new_name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->new_name), 8); 
        /* new_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->new_ext), 3); 
        /* new_attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->new_attr); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->size); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* old_name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->old_name), 8); 
        /* old_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->old_ext), 3); 
        /* old_attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->old_attr); 
        /* pattern */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->pattern); 
        /* new_name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->new_name), 8); 
        /* new_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->new_ext), 3); 
        /* new_attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->new_attr); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->size); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_change_file_info( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_change_file_info_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(40, 40, 56, 56); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_change_file_info_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_change_file_info_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* old_name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->old_name), 8); 
        /* old_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->old_ext), 3); 
        /* old_attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->old_attr)); 
        /* pattern */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->pattern)); 
        /* new_name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->new_name), 8); 
        /* new_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->new_ext), 3); 
        /* new_attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->new_attr)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->size)); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* old_name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->old_name), 8); 
        /* old_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->old_ext), 3); 
        /* old_attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->old_attr)); 
        /* pattern */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->pattern)); 
        /* new_name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->new_name), 8); 
        /* new_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->new_ext), 3); 
        /* new_attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->new_attr)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->size)); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_file_search(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_search_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_file_search_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(18, 18, 24, 24); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_file_search( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_search_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(18, 18, 24, 24); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_file_search_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_file_search_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_file_search(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_file_search_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_file_search_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(6, 6, 12, 12); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_file_search( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_file_search_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 6, 12, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_file_search_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_file_search_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->size)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->size)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_file_read(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_read_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_file_read_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(26, 26, 40, 40); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
        /* offset */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->offset); 
        /* num_bytes */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_bytes); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
        /* offset */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->offset); 
        /* num_bytes */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_bytes); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_file_read( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_read_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(26, 26, 40, 40); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_file_read_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_file_read_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
        /* offset */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->offset)); 
        /* num_bytes */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_bytes)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
        /* offset */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->offset)); 
        /* num_bytes */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_bytes)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_file_read(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_file_read_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_file_read_t, 1); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        0 + var_part_size, 
        0 + var_part_size, 
        0 + var_part_size, 
        0 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_file_read( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_file_read_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(0, 0, 0, 0); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_file_read_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_file_read_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_file_write(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_write_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_file_write_t, 0); 

    var_part_size += (size_t)(cmd->num_bytes); 
    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        26 + var_part_size, 
        26 + var_part_size, 
        40 + var_part_size, 
        40 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
        /* offset */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->offset); 
        /* num_bytes */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_bytes); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->num_bytes); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
        /* offset */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->offset); 
        /* num_bytes */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_bytes); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->num_bytes); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_file_write( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_write_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(26, 26, 40, 40); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_file_write_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_file_write_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
        /* offset */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->offset)); 
        /* num_bytes */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_bytes)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->num_bytes); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
        /* offset */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->offset)); 
        /* num_bytes */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_bytes)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->num_bytes); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_file_set_reset_file_lock(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_set_reset_file_lock_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_file_set_reset_file_lock_t, 0); 

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

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_file_set_reset_file_lock( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_set_reset_file_lock_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(0, 0, 0, 0); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_file_set_reset_file_lock_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_file_set_reset_file_lock_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_file_set_reset_file_lock(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_file_set_reset_file_lock_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_file_set_reset_file_lock_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(18, 18, 24, 24); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_file_set_reset_file_lock( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_file_set_reset_file_lock_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(18, 18, 24, 24); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_file_set_reset_file_lock_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_file_set_reset_file_lock_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_file_copy_a(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_copy_a_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_file_copy_a_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(52, 52, 80, 80); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* src_pwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->src_flag); 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->src_pwd); 
        /* src_drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->src_drv_name); 
        /* src_fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->src_fnum); 
        /* src_name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->src_name), 8); 
        /* src_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->src_ext), 3); 
        /* src_attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->src_attr); 
        /* src_offset */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->src_offset); 
        /* num_bytes */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_bytes); 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
        /* dst_pwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->dst_flag); 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->dst_pwd); 
        /* dst_drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->dst_drv_name); 
        /* dst_fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->dst_fnum); 
        /* dst_name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dst_name), 8); 
        /* dst_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dst_ext), 3); 
        /* dst_attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->dst_attr); 
        /* dst_offset */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->dst_offset); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* src_pwd */ 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->src_pwd); 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->src_flag); 
        /* src_drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->src_drv_name); 
        /* src_fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->src_fnum); 
        /* src_name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->src_name), 8); 
        /* src_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->src_ext), 3); 
        /* src_attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->src_attr); 
        /* src_offset */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->src_offset); 
        /* num_bytes */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_bytes); 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
        /* dst_pwd */ 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->dst_pwd); 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->dst_flag); 
        /* dst_drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->dst_drv_name); 
        /* dst_fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->dst_fnum); 
        /* dst_name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dst_name), 8); 
        /* dst_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dst_ext), 3); 
        /* dst_attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->dst_attr); 
        /* dst_offset */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->dst_offset); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_file_copy_a( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_copy_a_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(52, 52, 80, 80); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_file_copy_a_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_file_copy_a_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* src_pwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->src_flag)); 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->src_pwd)); 
        /* src_drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->src_drv_name)); 
        /* src_fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->src_fnum)); 
        /* src_name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->src_name), 8); 
        /* src_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->src_ext), 3); 
        /* src_attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->src_attr)); 
        /* src_offset */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->src_offset)); 
        /* num_bytes */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_bytes)); 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
        /* dst_pwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dst_flag)); 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->dst_pwd)); 
        /* dst_drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->dst_drv_name)); 
        /* dst_fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->dst_fnum)); 
        /* dst_name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dst_name), 8); 
        /* dst_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dst_ext), 3); 
        /* dst_attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dst_attr)); 
        /* dst_offset */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->dst_offset)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* src_pwd */ 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->src_pwd)); 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->src_flag)); 
        /* src_drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->src_drv_name)); 
        /* src_fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->src_fnum)); 
        /* src_name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->src_name), 8); 
        /* src_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->src_ext), 3); 
        /* src_attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->src_attr)); 
        /* src_offset */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->src_offset)); 
        /* num_bytes */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_bytes)); 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
        /* dst_pwd */ 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->dst_pwd)); 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dst_flag)); 
        /* dst_drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->dst_drv_name)); 
        /* dst_fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->dst_fnum)); 
        /* dst_name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dst_name), 8); 
        /* dst_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dst_ext), 3); 
        /* dst_attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dst_attr)); 
        /* dst_offset */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->dst_offset)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_file_copy_b(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_copy_b_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_file_copy_b_t, 0); 

    var_part_size += (size_t)(cmd->dst_name_len); 
    var_part_size += (size_t)(cmd->src_name_len); 
    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        24 + var_part_size, 
        24 + var_part_size, 
        40 + var_part_size, 
        40 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* dummy */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dummy), 8); 
        /* dst_pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dst_pwd), 4); 
        /* dst_drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->dst_drv_name); 
        /* dst_name_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->dst_name_len); 
        /* dst_name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->dst_name, cmd->dst_name_len); 
        /* src_pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->src_pwd), 4); 
        /* src_drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->src_drv_name); 
        /* src_name_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->src_name_len); 
        /* src_name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->src_name, cmd->src_name_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* dummy */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dummy), 8); 
        /* dst_pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dst_pwd), 4); 
        /* dst_drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->dst_drv_name); 
        /* dst_name_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->dst_name_len); 
        /* dst_name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->dst_name, cmd->dst_name_len); 
        /* src_pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->src_pwd), 4); 
        /* src_drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->src_drv_name); 
        /* src_name_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->src_name_len); 
        /* src_name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->src_name, cmd->src_name_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_file_copy_b( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_copy_b_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(24, 24, 40, 40); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_file_copy_b_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_file_copy_b_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* dummy */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dummy), 8); 
        /* dst_pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dst_pwd), 4); 
        /* dst_drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->dst_drv_name)); 
        /* dst_name_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->dst_name_len)); 
        /* dst_name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->dst_name, cmd->dst_name_len); 
        /* src_pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->src_pwd), 4); 
        /* src_drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->src_drv_name)); 
        /* src_name_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->src_name_len)); 
        /* src_name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->src_name, cmd->src_name_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* dummy */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dummy), 8); 
        /* dst_pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dst_pwd), 4); 
        /* dst_drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->dst_drv_name)); 
        /* dst_name_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->dst_name_len)); 
        /* dst_name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->dst_name, cmd->dst_name_len); 
        /* src_pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->src_pwd), 4); 
        /* src_drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->src_drv_name)); 
        /* src_name_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->src_name_len)); 
        /* src_name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->src_name, cmd->src_name_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_file_delete_a(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_delete_a_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_file_delete_a_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(20, 20, 28, 28); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_file_delete_a( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_delete_a_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(20, 20, 28, 28); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_file_delete_a_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_file_delete_a_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_file_delete_b(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_delete_b_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_file_delete_b_t, 0); 

    var_part_size += (size_t)(cmd->name_len); 
    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        8 + var_part_size, 
        8 + var_part_size, 
        12 + var_part_size, 
        12 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* name_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->name_len); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* name_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->name_len); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_file_delete_b( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_delete_b_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(8, 8, 12, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_file_delete_b_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_file_delete_b_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* name_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->name_len)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* name_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->name_len)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_read_dir_unicode(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_read_dir_unicode_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_read_dir_unicode_t, 0); 

    var_part_size += (size_t)(cmd->name_len); 
    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        13 + var_part_size, 
        13 + var_part_size, 
        21 + var_part_size, 
        21 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* reserved4 */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->reserved4); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* fnum_begin */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum_begin); 
        /* num_files */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_files); 
        /* name_len */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->name_len); 
        /* name_utf16le */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name_utf16le, cmd->name_len); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* reserved4 */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->reserved4); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* fnum_begin */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum_begin); 
        /* num_files */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_files); 
        /* name_len */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->name_len); 
        /* name_utf16le */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name_utf16le, cmd->name_len); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_read_dir_unicode( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_read_dir_unicode_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(13, 13, 21, 21); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_read_dir_unicode_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_read_dir_unicode_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* reserved4 */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->reserved4)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* fnum_begin */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum_begin)); 
        /* num_files */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_files)); 
        /* name_len */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->name_len)); 
        /* name_utf16le */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name_utf16le, cmd->name_len); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* reserved4 */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->reserved4)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* fnum_begin */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum_begin)); 
        /* num_files */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_files)); 
        /* name_len */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->name_len)); 
        /* name_utf16le */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name_utf16le, cmd->name_len); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_read_dir_unicode(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_read_dir_unicode_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_read_dir_unicode_t, 1); 

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
        /* num_entries */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_entries); 
        /* last_fnum */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->last_fnum); 
        /* entries */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->entries), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_entries */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_entries); 
        /* last_fnum */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->last_fnum); 
        /* entries */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->entries), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_read_dir_unicode( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_read_dir_unicode_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 6, 12, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_read_dir_unicode_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_read_dir_unicode_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num_entries */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_entries)); 
        /* last_fnum */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->last_fnum)); 
        /* entries */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->entries), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_entries */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_entries)); 
        /* last_fnum */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->last_fnum)); 
        /* entries */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->entries), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_read_dir_unicode_entry(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_read_dir_unicode_entry_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_read_dir_unicode_entry_t, 0); 

    var_part_size += (size_t)(cmd->name_len); 
    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        23 + var_part_size, 
        23 + var_part_size, 
        46 + var_part_size, 
        46 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* name_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->name_len); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->attr); 
        /* reserved7 */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->reserved7.bin), 7); 
        /* reserved2_1 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2_1); 
        /* last_edit_time */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_time); 
        /* last_edit_date */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_date); 
        /* reserved2_2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2_2); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* name_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->name_len); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->attr); 
        /* reserved7 */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->reserved7.ascii), 14); 
        /* reserved2_1 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2_1); 
        /* last_edit_time */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_time); 
        /* last_edit_date */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->last_edit_date); 
        /* reserved2_2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2_2); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_read_dir_unicode_entry( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_read_dir_unicode_entry_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(23, 23, 46, 46); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_read_dir_unicode_entry_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_read_dir_unicode_entry_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* name_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->name_len)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->attr)); 
        /* reserved7 */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->reserved7.bin), 7); 
        /* reserved2_1 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2_1)); 
        /* last_edit_time */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_time)); 
        /* last_edit_date */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_date)); 
        /* reserved2_2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2_2)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->size)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* name_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->name_len)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->attr)); 
        /* reserved7 */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->reserved7.ascii), 14); 
        /* reserved2_1 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2_1)); 
        /* last_edit_time */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_time)); 
        /* last_edit_date */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->last_edit_date)); 
        /* reserved2_2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2_2)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->size)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_search_dir_file(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_search_dir_file_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_search_dir_file_t, 0); 

    var_part_size += (size_t)(cmd->num_file_name); 
    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        10 + var_part_size, 
        10 + var_part_size, 
        16 + var_part_size, 
        16 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* num_dir_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_dir_name); 
        /* num_file_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_file_name); 
        /* file_name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->file_name, cmd->num_file_name); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* num_dir_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_dir_name); 
        /* num_file_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_file_name); 
        /* file_name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->file_name, cmd->num_file_name); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_search_dir_file( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_search_dir_file_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(10, 10, 16, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_search_dir_file_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_search_dir_file_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* num_dir_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_dir_name)); 
        /* num_file_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_file_name)); 
        /* file_name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->file_name, cmd->num_file_name); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* num_dir_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_dir_name)); 
        /* num_file_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_file_name)); 
        /* file_name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->file_name, cmd->num_file_name); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_search_dir_file(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_search_dir_file_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_search_dir_file_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(2, 2, 4, 4); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_search_dir_file( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_search_dir_file_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_search_dir_file_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_search_dir_file_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_new_file_a(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_new_file_a_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_new_file_a_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(28, 28, 44, 44); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* reserved4 */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->reserved4); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->size); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_24B(cmd->pwd); 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->flag); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* reserved4 */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->reserved4); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->attr); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->size); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_new_file_a( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_new_file_a_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(28, 28, 44, 44); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_new_file_a_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_new_file_a_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* reserved4 */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->reserved4)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->size)); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_24B(&(cmd->pwd)); 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->flag)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* reserved4 */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->reserved4)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->name), 8); 
        /* ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext), 3); 
        /* attr */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->attr)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->size)); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_new_file_a(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_new_file_a_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_new_file_a_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(2, 2, 4, 4); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fnum */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fnum); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_new_file_a( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_new_file_a_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_new_file_a_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_new_file_a_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fnum */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fnum)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_new_file_b(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_new_file_b_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_new_file_b_t, 0); 

    var_part_size += (size_t)(cmd->name_len); 
    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        12 + var_part_size, 
        12 + var_part_size, 
        20 + var_part_size, 
        20 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->size); 
        /* name_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->name_len); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* size */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->size); 
        /* name_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->name_len); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_new_file_b( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_new_file_b_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(12, 12, 20, 20); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_new_file_b_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_new_file_b_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->size)); 
        /* name_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->name_len)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* size */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->size)); 
        /* name_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->name_len)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_file_change_date(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_change_date_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_file_change_date_t, 0); 

    var_part_size += (size_t)(cmd->name_len); 
    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        12 + var_part_size, 
        12 + var_part_size, 
        20 + var_part_size, 
        20 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* date */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->date); 
        /* time */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->time); 
        /* name_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->name_len); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* date */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->date); 
        /* time */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->time); 
        /* name_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->name_len); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_file_change_date( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_file_change_date_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(12, 12, 20, 20); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_file_change_date_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_file_change_date_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* date */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->date)); 
        /* time */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->time)); 
        /* name_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->name_len)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* date */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->date)); 
        /* time */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->time)); 
        /* name_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->name_len)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_open_file(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_open_file_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_open_file_t, 0); 

    var_part_size += (size_t)(cmd->name_len); 
    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        10 + var_part_size, 
        10 + var_part_size, 
        16 + var_part_size, 
        16 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* name_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->name_len); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* mode */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->mode); 
        /* drv_name */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->drv_name); 
        /* name_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->name_len); 
        /* name */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_open_file( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_open_file_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(10, 10, 16, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_open_file_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_open_file_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* name_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->name_len)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* pwd */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->pwd), 4); 
        /* mode */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mode)); 
        /* drv_name */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->drv_name)); 
        /* name_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->name_len)); 
        /* name */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->name, cmd->name_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_open_file(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_open_file_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_open_file_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(2, 2, 4, 4); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fp */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fp); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fp */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fp); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_open_file( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_open_file_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_open_file_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_open_file_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fp */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fp)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fp */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fp)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_read_file(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_read_file_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_read_file_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(8, 8, 16, 16); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fp */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fp); 
        /* offset */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->offset); 
        /* num_bytes */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_bytes); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fp */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fp); 
        /* offset */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->offset); 
        /* num_bytes */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_bytes); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_read_file( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_read_file_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(8, 8, 16, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_read_file_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_read_file_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fp */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fp)); 
        /* offset */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->offset)); 
        /* num_bytes */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_bytes)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fp */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fp)); 
        /* offset */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->offset)); 
        /* num_bytes */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_bytes)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_read_file(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_read_file_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_read_file_t, 1); 

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
        /* num_bytes */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_bytes); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_bytes */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_bytes); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_read_file( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_read_file_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_read_file_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_read_file_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num_bytes */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_bytes)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_bytes */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_bytes)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_write_file(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_write_file_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_write_file_t, 1); 

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
        /* fp */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fp); 
        /* offset */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->offset); 
        /* num_bytes */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_bytes); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fp */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fp); 
        /* offset */ 
        ENCODE_AND_ADVANCE_STREAM_32B(cmd->offset); 
        /* num_bytes */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_bytes); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_write_file( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_write_file_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(8, 8, 16, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_write_file_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_write_file_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fp */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fp)); 
        /* offset */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->offset)); 
        /* num_bytes */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_bytes)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fp */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fp)); 
        /* offset */ 
        DECODE_AND_ADVANCE_STREAM_32B(&(cmd->offset)); 
        /* num_bytes */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_bytes)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_write_file(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_write_file_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_write_file_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(2, 2, 4, 4); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num_bytes */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_bytes); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_bytes */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_bytes); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_write_file( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_write_file_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_write_file_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_write_file_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num_bytes */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_bytes)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_bytes */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_bytes)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_close_file(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_close_file_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_close_file_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(4, 4, 8, 8); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fp */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fp); 
        /* type */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->type); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fp */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->fp); 
        /* type */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->type); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_close_file( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_close_file_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_close_file_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_close_file_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* fp */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fp)); 
        /* type */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->type)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* fp */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->fp)); 
        /* type */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->type)); 
    } 

    return &(cmd->hdr); 
}

