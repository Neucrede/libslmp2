/**
 * \file extunit.h
 * 
 * \brief Extension Module (ExtendUnit) Commands
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\ExtensionModule.cge by CCGEN program.
 */

#ifndef EXTUNIT_H
#define EXTUNIT_H

#include "slmp/command/cmdhdr.h" 
#include "slmp/_pushpack4.h" 


/**
 * \brief Read data from extension module memory.
 */
typedef struct slmp_req_extend_unit_read {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Starting address
     */
    uint32_t addr_begin; /* 32b */
    /**
     * Number of bytes
     */
    uint16_t num;
    /**
     * Module number
     */
    uint16_t unit;
} slmp_req_extend_unit_read_t;

/**
 * \brief Write data to extension memory.
 */
typedef struct slmp_req_extend_unit_write {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Starting address
     */
    uint32_t addr_begin; /* 32b */
    /**
     * Number of bytes
     */
    uint16_t num;
    /**
     * Module number
     */
    uint16_t unit;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_extend_unit_write_t;


#include "slmp/_poppack.h" 

#endif /* EXTUNIT_H */
