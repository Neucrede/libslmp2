/**
 * \file dpmem.h
 * 
 * \brief Dual Port Memory (Memory) Commands
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\DualPortMemory.cge by CCGEN program.
 */

#ifndef DPMEM_H
#define DPMEM_H

#include "slmp/command/cmdhdr.h" 
#include "slmp/_pushpack4.h" 


/**
 * \brief Read data from the network module memory (dual port memory).
 */
typedef struct slmp_req_memory_read {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Starting address
     */
    uint32_t addr_begin; /* 32b */
    /**
     * Word length
     */
    uint16_t len;
} slmp_req_memory_read_t;

/**
 * \brief Write data to network module memory (dual port memory).
 */
typedef struct slmp_req_memory_write {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Starting address
     */
    uint32_t addr_begin; /* 32b */
    /**
     * Word length
     */
    uint16_t len;
    /**
     * Data (word unit)
     */
    uint8_t data[1]; /* variable size */
} slmp_req_memory_write_t;


#include "slmp/_poppack.h" 

#endif /* DPMEM_H */
