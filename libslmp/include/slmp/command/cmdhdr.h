/**
 * \file cmdhdr.h
 *
 * \brief Command header.
 *
 * Common header for SLMP command structures.
 */

#ifndef __CMDHDR_H__
#define __CMDHDR_H__

#include <stdint.h>

#include "slmp/_pushpack4.h"

/** \brief Common header for SLMP command structures. */
typedef struct slmp_cmd_hdr {
    /** 
     * Size of the command structure. Note that every SLMP command structure
     * should contain an `slmp_cmd_hdr_t` structure as its first entry.
     */
    size_t size;

    /**
     * Address width. 
     */
    uint8_t addr_width;
} slmp_cmd_hdr_t;

#include "slmp/_poppack.h"

#endif /* __CMDHDR_H__ */
