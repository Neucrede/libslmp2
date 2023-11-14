/*
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\InternalMemory.cge by CCGEN program.
 */

#include "cmdcodec_priv.h" 
#include "slmp/command/intmem.h" 
#include "slmp/codec/intmem_codec.h" 

SLMPAPI size_t SLMPCALL slmp_encode_req_device_read(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_read_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(6, 8, 12, 16); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr_begin.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_read( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 8, 12, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_read_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_read_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr_begin.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_read_ext(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_ext_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_read_ext_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(13, 15, 24, 32); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->dir_mem_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr_begin.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec_mod.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.bin); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->dir_mem_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec_mod.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.bin); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.s), 3); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.s), 3); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 10); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.l), 4); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_read_ext( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_ext_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(13, 15, 24, 32); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_read_ext_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_read_ext_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dir_mem_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr_begin.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec_mod.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.bin)); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dir_mem_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec_mod.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.bin)); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.s), 3); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.s), 3); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 10); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.l), 4); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_t, 1); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        6 + var_part_size, 
        8 + var_part_size, 
        12 + var_part_size, 
        16 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr_begin.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 8, 12, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr_begin.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_ext(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_ext_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_ext_t, 1); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        13 + var_part_size, 
        15 + var_part_size, 
        24 + var_part_size, 
        32 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->dir_mem_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr_begin.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec_mod.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.bin); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->dir_mem_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec_mod.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.bin); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.ascii); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.s), 3); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.s), 3); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.ascii); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 10); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.l), 4); 
            /* deviceNum */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_ext( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_ext_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(13, 15, 24, 32); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_ext_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_ext_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dir_mem_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr_begin.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec_mod.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.bin)); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dir_mem_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec_mod.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.bin)); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.ascii)); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.s), 3); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.s), 3); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* tarDevice */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.ascii)); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 10); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.l), 4); 
            /* deviceNum */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_read_random(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_random_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_read_random_t, 1); 

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
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* num_wd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
            /* num_dwd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_dwd); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* num_wd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
            /* num_dwd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_dwd); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* num_wd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
            /* num_dwd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_dwd); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* num_wd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
            /* num_dwd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_dwd); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_read_random( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_random_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_read_random_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_read_random_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* num_wd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
            /* num_dwd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_dwd)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* num_wd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
            /* num_dwd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_dwd)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* num_wd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
            /* num_dwd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_dwd)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* num_wd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
            /* num_dwd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_dwd)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_read_random_unit(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_random_unit_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_read_random_unit_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(4, 6, 8, 12); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* unit */ 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* unit */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 8); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_read_random_unit( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_random_unit_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 6, 8, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_read_random_unit_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_read_random_unit_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* unit */ 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* unit */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 8); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_read_random_ext(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_random_ext_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_read_random_ext_t, 1); 

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
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* num_wd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
            /* num_dwd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_dwd); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* num_wd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
            /* num_dwd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_dwd); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* num_wd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
            /* num_dwd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_dwd); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* num_wd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
            /* num_dwd */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_dwd); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_read_random_ext( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_random_ext_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_read_random_ext_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_read_random_ext_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* num_wd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
            /* num_dwd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_dwd)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* num_wd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
            /* num_dwd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_dwd)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* num_wd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
            /* num_dwd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_dwd)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* num_wd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
            /* num_dwd */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_dwd)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_read_random_ext_word_unit(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_random_ext_word_unit_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_read_random_ext_word_unit_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(11, 13, 20, 28); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* word_unit */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->dir_mem_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec_mod.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.bin); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* word_unit */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->dir_mem_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec_mod.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.bin); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* word_unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.s), 3); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.s), 3); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* word_unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 10); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.l), 4); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_read_random_ext_word_unit( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_random_ext_word_unit_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(11, 13, 20, 28); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_read_random_ext_word_unit_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_read_random_ext_word_unit_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* word_unit */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dir_mem_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec_mod.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.bin)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* word_unit */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dir_mem_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec_mod.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.bin)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* word_unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.s), 3); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.s), 3); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* word_unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 10); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.l), 4); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_read_random_ext_dword_unit(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_random_ext_dword_unit_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_read_random_ext_dword_unit_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(4, 6, 8, 12); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* dword_unit */ 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* dword_unit */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* dword_unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* dword_unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 8); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_read_random_ext_dword_unit( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_random_ext_dword_unit_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 6, 8, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_read_random_ext_dword_unit_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_read_random_ext_dword_unit_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* dword_unit */ 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* dword_unit */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* dword_unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* dword_unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 8); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_random(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_random_t, 1); 

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
        /* num_wd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
        /* num_dwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_dwd); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_wd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
        /* num_dwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_dwd); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_random( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_random_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_random_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num_wd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
        /* num_dwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_dwd)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_wd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
        /* num_dwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_dwd)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_random_word_unit(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_word_unit_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_random_word_unit_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(6, 8, 12, 16); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* word_unit */ 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->data); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* word_unit */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->data); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* word_unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->data); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* word_unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 8); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->data); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_random_word_unit( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_word_unit_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 8, 12, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_random_word_unit_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_random_word_unit_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* word_unit */ 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* word_unit */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* word_unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* word_unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 8); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data)); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_random_dword_unit(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_dword_unit_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_random_dword_unit_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(8, 10, 16, 20); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* dword_unit */ 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->data); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* dword_unit */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->data); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* dword_unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->data); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* dword_unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 8); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->data); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_random_dword_unit( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_dword_unit_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(8, 10, 16, 20); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_random_dword_unit_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_random_dword_unit_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* dword_unit */ 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->data)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* dword_unit */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->data)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* dword_unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->data)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* dword_unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 8); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->data)); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_random_bit(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_bit_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_random_bit_t, 1); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        1 + var_part_size, 
        1 + var_part_size, 
        2 + var_part_size, 
        2 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_random_bit( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_bit_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(1, 1, 2, 2); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_random_bit_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_random_bit_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_random_bit_unit(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_bit_unit_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_random_bit_unit_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(5, 8, 10, 16); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* bit_unit */ 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->data.bin.s); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* bit_unit */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->data.bin.l); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* bit_unit */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.ascii.s); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->data.ascii.s); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* bit_unit */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->mem_type.ascii.l); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 8); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->data.ascii.l); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_random_bit_unit( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_bit_unit_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(5, 8, 10, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_random_bit_unit_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_random_bit_unit_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* bit_unit */ 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->data.bin.s)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* bit_unit */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data.bin.l)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* bit_unit */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.ascii.s)); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data.ascii.s)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* bit_unit */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->mem_type.ascii.l)); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 8); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->data.ascii.l)); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_random_ext(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_t, 1); 

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
        /* num_wd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
        /* num_dwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_dwd); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_wd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
        /* num_dwd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_dwd); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_random_ext( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_random_ext_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_random_ext_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num_wd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
        /* num_dwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_dwd)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_wd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
        /* num_dwd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_dwd)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_random_ext_word_unit(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_word_unit_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_word_unit_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(13, 15, 24, 32); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* word_unit */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->dir_mem_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec_mod.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.bin); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->data); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* word_unit */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->dir_mem_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec_mod.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.bin); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->data); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* word_unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.s), 3); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->dev_mod.ascii.s); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->data); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* word_unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 10); 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->dev_mod.ascii.l); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->data); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_random_ext_word_unit( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_word_unit_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(13, 15, 24, 32); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_random_ext_word_unit_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_random_ext_word_unit_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* word_unit */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dir_mem_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec_mod.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.bin)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* word_unit */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dir_mem_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec_mod.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.bin)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* word_unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.s), 3); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->dev_mod.ascii.s)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* word_unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 10); 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->dev_mod.ascii.l)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data)); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_random_ext_dword_unit(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_dword_unit_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_dword_unit_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(8, 10, 16, 20); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* dword_unit */ 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->data); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* dword_unit */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->data); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* dword_unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->data); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* dword_unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 8); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->data); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_random_ext_dword_unit( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_dword_unit_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(8, 10, 16, 20); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_random_ext_dword_unit_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_random_ext_dword_unit_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* dword_unit */ 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->data)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* dword_unit */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->data)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* dword_unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->data)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* dword_unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 8); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->data)); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_random_ext_bit(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_bit_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_bit_t, 1); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        1 + var_part_size, 
        1 + var_part_size, 
        2 + var_part_size, 
        2 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_random_ext_bit( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_bit_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(1, 1, 2, 2); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_random_ext_bit_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_random_ext_bit_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_random_ext_bit_unit(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_bit_unit_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_bit_unit_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(12, 15, 22, 32); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* bit_unit */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->dir_mem_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec_mod.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.bin); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->data.bin.s); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* bit_unit */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->dir_mem_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec_mod.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.bin); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->data.bin.l); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* bit_unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.s), 3); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->dev_mod.ascii.s); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->data.ascii.s); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* bit_unit */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 10); 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->dev_mod.ascii.l); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->data.ascii.l); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_random_ext_bit_unit( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_random_ext_bit_unit_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(12, 15, 22, 32); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_random_ext_bit_unit_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_random_ext_bit_unit_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* bit_unit */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dir_mem_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec_mod.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.bin)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->data.bin.s)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* bit_unit */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dir_mem_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec_mod.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.bin)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data.bin.l)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* bit_unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.s), 3); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.s), 6); 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->dev_mod.ascii.s)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data.ascii.s)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* bit_unit */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr.ascii.l), 10); 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->dev_mod.ascii.l)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->data.ascii.l)); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_read_block(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_block_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_read_block_t, 1); 

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
        /* num_wd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
        /* num_bit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_bit); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_wd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
        /* num_bit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_bit); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_read_block( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_block_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_read_block_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_read_block_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num_wd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
        /* num_bit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_bit)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_wd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
        /* num_bit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_bit)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_read_block_word_block(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_block_word_block_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_read_block_word_block_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(6, 8, 12, 16); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr_begin.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_read_block_word_block( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_block_word_block_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 8, 12, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_read_block_word_block_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_read_block_word_block_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr_begin.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_read_block_bit_block(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_block_bit_block_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_read_block_bit_block_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(6, 8, 12, 16); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr_begin.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_read_block_bit_block( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_block_bit_block_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 8, 12, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_read_block_bit_block_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_read_block_bit_block_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr_begin.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_read_block_ext(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_block_ext_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_read_block_ext_t, 1); 

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
        /* num_wd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
        /* num_bit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_bit); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_wd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
        /* num_bit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_bit); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_read_block_ext( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_block_ext_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_read_block_ext_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_read_block_ext_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num_wd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
        /* num_bit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_bit)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_wd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
        /* num_bit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_bit)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_read_block_ext_word_block(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_block_ext_word_block_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_read_block_ext_word_block_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(13, 15, 24, 32); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->dir_mem_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr_begin.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec_mod.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.bin); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->dir_mem_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec_mod.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.bin); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.s), 3); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.s), 3); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 10); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.l), 4); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_read_block_ext_word_block( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_block_ext_word_block_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(13, 15, 24, 32); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_read_block_ext_word_block_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_read_block_ext_word_block_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dir_mem_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr_begin.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec_mod.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.bin)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dir_mem_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec_mod.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.bin)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.s), 3); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.s), 3); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 10); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.l), 4); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_read_block_ext_bit_block(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_block_ext_bit_block_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_read_block_ext_bit_block_t, 0); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE(6, 8, 12, 16); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr_begin.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_read_block_ext_bit_block( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_read_block_ext_bit_block_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 8, 12, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_read_block_ext_bit_block_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_read_block_ext_bit_block_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr_begin.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_block(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_block_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_block_t, 1); 

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
        /* num_wd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
        /* num_bit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_bit); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_wd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
        /* num_bit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_bit); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_block( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_block_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_block_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_block_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num_wd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
        /* num_bit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_bit)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_wd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
        /* num_bit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_bit)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_block_word_block(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_block_word_block_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_block_word_block_t, 1); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        6 + var_part_size, 
        8 + var_part_size, 
        12 + var_part_size, 
        16 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr_begin.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_block_word_block( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_block_word_block_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 8, 12, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_block_word_block_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_block_word_block_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr_begin.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_block_bit_block(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_block_bit_block_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_block_bit_block_t, 1); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        6 + var_part_size, 
        8 + var_part_size, 
        12 + var_part_size, 
        16 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr_begin.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_block_bit_block( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_block_bit_block_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 8, 12, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_block_bit_block_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_block_bit_block_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr_begin.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_block_ext(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_block_ext_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_block_ext_t, 1); 

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
        /* num_wd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
        /* num_bit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_bit); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_wd */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_wd); 
        /* num_bit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num_bit); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_block_ext( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_block_ext_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_block_ext_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_block_ext_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num_wd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
        /* num_bit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_bit)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num_wd */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_wd)); 
        /* num_bit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num_bit)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_block_ext_word_block(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_block_ext_word_block_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_block_ext_word_block_t, 1); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        13 + var_part_size, 
        15 + var_part_size, 
        24 + var_part_size, 
        32 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->dir_mem_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr_begin.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec_mod.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.bin); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->dir_mem_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec_mod.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->ext_spec.bin); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->indir_spec.bin); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.s), 3); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.s), 3); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 10); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.l), 4); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_block_ext_word_block( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_block_ext_word_block_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(13, 15, 24, 32); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_block_ext_word_block_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_block_ext_word_block_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dir_mem_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr_begin.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec_mod.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.bin)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->dir_mem_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec_mod.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->ext_spec.bin)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->indir_spec.bin)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.s), 3); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.s), 3); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeWdDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->indir_spec.ascii), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec.ascii), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->ext_spec_mod.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 10); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->dev_mod.ascii.l), 4); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_device_write_block_ext_bit_block(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_block_ext_bit_block_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_device_write_block_ext_bit_block_t, 1); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        6 + var_part_size, 
        8 + var_part_size, 
        12 + var_part_size, 
        16 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_24B(cmd->addr_begin.bin.s); 
            ENCODE_AND_ADVANCE_STREAM_8B(cmd->mem_type.bin.s); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_32B(cmd->addr_begin.bin.l); 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->mem_type.bin.l); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (cmd->hdr.addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* num */ 
            ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
            /* data */ 
            ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_device_write_block_ext_bit_block( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_device_write_block_ext_bit_block_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 8, 12, 16); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_device_write_block_ext_bit_block_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_device_write_block_ext_bit_block_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_24B(&(cmd->addr_begin.bin.s)); 
            DECODE_AND_ADVANCE_STREAM_8B(&(cmd->mem_type.bin.s)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_32B(&(cmd->addr_begin.bin.l)); 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->mem_type.bin.l)); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        switch (addr_width) { 
        case SLMP_ADDRESS_16BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.s), 2); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.s), 6); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        case SLMP_ADDRESS_32BIT: 
            /* typeBtDevice */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->mem_type.ascii.l), 4); 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->addr_begin.ascii.l), 8); 
            /* num */ 
            DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
            /* data */ 
            DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
            break;
        default: 
            break; 
        } 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_read(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_read_t, 1); 

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
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_read( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_read_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_read_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_read_label(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_label_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_read_label_t, 0); 

    var_part_size += (size_t)(cmd->label_len); 
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
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* read_unit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->read_unit); 
        /* reserved1 */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->reserved1); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* read_unit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->read_unit); 
        /* reserved1 */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->reserved1); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_read_label( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_label_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 6, 12, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_read_label_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_read_label_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* read_unit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->read_unit)); 
        /* reserved1 */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->reserved1)); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* read_unit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->read_unit)); 
        /* reserved1 */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->reserved1)); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_read_ext(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_ext_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_read_ext_t, 1); 

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
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* num_ext */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_ext); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* num_ext */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_ext); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_read_ext( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_ext_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_read_ext_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_read_ext_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* num_ext */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_ext)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* num_ext */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_ext)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_read_ext_label_ext(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_ext_label_ext_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_read_ext_label_ext_t, 0); 

    var_part_size += (size_t)(cmd->label_ext_len); 
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
        /* label_ext_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_ext_len); 
        /* label_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_ext_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_ext_len); 
        /* label_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_read_ext_label_ext( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_ext_label_ext_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_read_ext_label_ext_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_read_ext_label_ext_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* label_ext_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_ext_len)); 
        /* label_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_ext_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_ext_len)); 
        /* label_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_read_ext_label(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_ext_label_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_read_ext_label_t, 0); 

    var_part_size += (size_t)(cmd->label_len); 
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
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* read_unit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->read_unit); 
        /* reserved1 */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->reserved1); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* read_unit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->read_unit); 
        /* reserved1 */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->reserved1); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_read_ext_label( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_ext_label_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 6, 12, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_read_ext_label_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_read_ext_label_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* read_unit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->read_unit)); 
        /* reserved1 */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->reserved1)); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* read_unit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->read_unit)); 
        /* reserved1 */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->reserved1)); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_label_read(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_label_read_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_label_read_t, 1); 

    ENCODE_COMMAND_SET_MIN_BUF_SIZE( 
        1 + var_part_size, 
        1 + var_part_size, 
        2 + var_part_size, 
        2 + var_part_size 
    ); 
    
    if (stream == NULL) { 
        return min_buf_size; 
    } 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->num); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_label_read( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_label_read_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(1, 1, 2, 2); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_label_read_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_label_read_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->num)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_label_read_label(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_label_read_label_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_label_read_label_t, 0); 

    var_part_size += (size_t)(cmd->data_len); 
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
        /* type_id */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->type_id); 
        /* read_unit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->read_unit); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* type_id */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->type_id); 
        /* read_unit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->read_unit); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_label_read_label( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_label_read_label_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_label_read_label_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_label_read_label_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* type_id */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->type_id)); 
        /* read_unit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->read_unit)); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* type_id */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->type_id)); 
        /* read_unit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->read_unit)); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_write(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_write_t, 1); 

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
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_write( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_write_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_write_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_write_label(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_label_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_write_label_t, 0); 

    var_part_size += (size_t)(cmd->label_len); 
    var_part_size += (size_t)(cmd->data_len); 
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
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* write_unit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->write_unit); 
        /* reserved1 */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->reserved1); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* write_unit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->write_unit); 
        /* reserved1 */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->reserved1); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_write_label( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_label_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 6, 12, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_write_label_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_write_label_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* write_unit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->write_unit)); 
        /* reserved1 */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->reserved1)); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* write_unit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->write_unit)); 
        /* reserved1 */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->reserved1)); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_write_ext(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_ext_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_write_ext_t, 1); 

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
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* num_ext */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_ext); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* num_ext */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_ext); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_write_ext( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_ext_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_write_ext_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_write_ext_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* num_ext */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_ext)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* num_ext */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_ext)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_write_ext_label_ext(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_ext_label_ext_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_write_ext_label_ext_t, 0); 

    var_part_size += (size_t)(cmd->label_ext_len); 
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
        /* label_ext_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_ext_len); 
        /* label_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_ext_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_ext_len); 
        /* label_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_write_ext_label_ext( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_ext_label_ext_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_write_ext_label_ext_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_write_ext_label_ext_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* label_ext_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_ext_len)); 
        /* label_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_ext_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_ext_len)); 
        /* label_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_write_ext_label(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_ext_label_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_write_ext_label_t, 0); 

    var_part_size += (size_t)(cmd->label_len); 
    var_part_size += (size_t)(cmd->data_len); 
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
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* write_unit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->write_unit); 
        /* reserved1 */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->reserved1); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* write_unit */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->write_unit); 
        /* reserved1 */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->reserved1); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_write_ext_label( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_ext_label_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(6, 6, 12, 12); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_write_ext_label_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_write_ext_label_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* write_unit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->write_unit)); 
        /* reserved1 */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->reserved1)); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* write_unit */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->write_unit)); 
        /* reserved1 */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->reserved1)); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_read_random(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_random_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_read_random_t, 1); 

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
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_read_random( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_random_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_read_random_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_read_random_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_read_random_label(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_random_label_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_read_random_label_t, 0); 

    var_part_size += (size_t)(cmd->label_len); 
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
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_read_random_label( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_random_label_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_read_random_label_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_read_random_label_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_read_random_ext(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_random_ext_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_read_random_ext_t, 1); 

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
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* num_ext */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_ext); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* num_ext */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_ext); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_read_random_ext( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_random_ext_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_read_random_ext_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_read_random_ext_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* num_ext */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_ext)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* num_ext */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_ext)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_read_random_ext_label_ext(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_random_ext_label_ext_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_read_random_ext_label_ext_t, 0); 

    var_part_size += (size_t)(cmd->label_ext_len); 
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
        /* label_ext_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_ext_len); 
        /* label_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_ext_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_ext_len); 
        /* label_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_read_random_ext_label_ext( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_random_ext_label_ext_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_read_random_ext_label_ext_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_read_random_ext_label_ext_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* label_ext_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_ext_len)); 
        /* label_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_ext_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_ext_len)); 
        /* label_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_read_random_ext_label(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_random_ext_label_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_read_random_ext_label_t, 0); 

    var_part_size += (size_t)(cmd->label_len); 
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
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_read_random_ext_label( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_read_random_ext_label_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_read_random_ext_label_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_read_random_ext_label_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_label_read_random(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_label_read_random_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_label_read_random_t, 1); 

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
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_label_read_random( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_label_read_random_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_label_read_random_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_label_read_random_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_res_label_read_random_label(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_label_read_random_label_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_res_label_read_random_label_t, 0); 

    var_part_size += (size_t)(cmd->data_len); 
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
        /* type_id */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->type_id); 
        /* reserved1 */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->reserved1); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* type_id */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->type_id); 
        /* reserved1 */ 
        ENCODE_AND_ADVANCE_STREAM_8B(cmd->reserved1); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_res_label_read_random_label( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_res_label_read_random_label_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_res_label_read_random_label_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_res_label_read_random_label_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* type_id */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->type_id)); 
        /* reserved1 */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->reserved1)); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* type_id */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->type_id)); 
        /* reserved1 */ 
        DECODE_AND_ADVANCE_STREAM_8B(&(cmd->reserved1)); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_write_random(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_random_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_write_random_t, 1); 

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
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* reserved2 */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->reserved2); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_write_random( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_random_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_write_random_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_write_random_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* reserved2 */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->reserved2)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_write_random_label(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_random_label_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_write_random_label_t, 0); 

    var_part_size += (size_t)(cmd->label_len); 
    var_part_size += (size_t)(cmd->data_len); 
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
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_write_random_label( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_random_label_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_write_random_label_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_write_random_label_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_write_random_ext(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_random_ext_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_write_random_ext_t, 1); 

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
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* num_ext */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_ext); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num); 
        /* num_ext */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->num_ext); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_write_random_ext( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_random_ext_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_write_random_ext_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_write_random_ext_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* num_ext */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_ext)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* num */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num)); 
        /* num_ext */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->num_ext)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY(&(cmd->data), var_part_size); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_write_random_ext_label_ext(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_random_ext_label_ext_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_write_random_ext_label_ext_t, 0); 

    var_part_size += (size_t)(cmd->label_ext_len); 
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
        /* label_ext_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_ext_len); 
        /* label_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_ext_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_ext_len); 
        /* label_ext */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_write_random_ext_label_ext( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_random_ext_label_ext_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(2, 2, 4, 4); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_write_random_ext_label_ext_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_write_random_ext_label_ext_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* label_ext_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_ext_len)); 
        /* label_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_ext_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_ext_len)); 
        /* label_ext */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label_ext, cmd->label_ext_len); 
    } 

    return &(cmd->hdr); 
}

SLMPAPI size_t SLMPCALL slmp_encode_req_label_write_random_ext_label(
    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)
{ 
    ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_random_ext_label_t); 
    ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(slmp_req_label_write_random_ext_label_t, 0); 

    var_part_size += (size_t)(cmd->label_len); 
    var_part_size += (size_t)(cmd->data_len); 
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
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->label_len); 
        /* label */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* data_len */ 
        ENCODE_AND_ADVANCE_STREAM_16B(cmd->data_len); 
        /* data */ 
        ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 

    return min_buf_size; 
}

SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_req_label_write_random_ext_label( 
    uint8_t *stream, size_t len, int type, int addr_width) 
{ 
    DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(slmp_req_label_write_random_ext_label_t); 
    DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); 
    DECODE_COMMAND_CHECK_STREAM_LENGTH(4, 4, 8, 8); 
    DECODE_COMMAND_ALLOC_MEMORY(slmp_req_label_write_random_ext_label_t); 
    DECODE_COMMAND_FILL_COMMAND_HEADER(slmp_req_label_write_random_ext_label_t); 
    
    if (type == SLMP_BINARY_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 
    else if (type == SLMP_ASCII_STREAM) { 
        /* label_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->label_len)); 
        /* label */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->label, cmd->label_len); 
        /* data_len */ 
        DECODE_AND_ADVANCE_STREAM_16B(&(cmd->data_len)); 
        /* data */ 
        DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(cmd->data, cmd->data_len); 
    } 

    return &(cmd->hdr); 
}

