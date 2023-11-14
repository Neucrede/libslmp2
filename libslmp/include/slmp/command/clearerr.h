/**
 * \file clearerr.h
 * 
 * \brief Clear Error.
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\ClearError.cge by CCGEN program.
 */

#ifndef CLEARERR_H
#define CLEARERR_H

#include "slmp/command/cmdhdr.h" 
#include "slmp/_pushpack4.h" 


/**
 * \brief Clear error code.
 */
typedef struct slmp_req_clear_error_code {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

} slmp_req_clear_error_code_t;

/**
 * \brief Clear error history.
 */
typedef struct slmp_req_clear_error_history {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

} slmp_req_clear_error_history_t;


#include "slmp/_poppack.h" 

#endif /* CLEARERR_H */
