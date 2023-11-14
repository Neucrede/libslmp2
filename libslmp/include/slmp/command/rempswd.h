/**
 * \file rempswd.h
 * 
 * \brief Remote Password Commands
 * 
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\RemotePassword.cge by CCGEN program.
 */

#ifndef REMPSWD_H
#define REMPSWD_H

#include "slmp/command/cmdhdr.h" 
#include "slmp/_pushpack4.h" 


/**
 * \brief Set remote password.
 */
typedef struct slmp_req_password_lock {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Password length
     */
    uint16_t len;
    /**
     * Password
     */
    uint8_t *pwd; /* (size = 'len') */
} slmp_req_password_lock_t;

/**
 * \brief Cancel remote password.
 */
typedef struct slmp_req_password_unlock {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Password length
     */
    uint16_t len;
    /**
     * Password
     */
    uint8_t *pwd; /* (size = 'len') */
} slmp_req_password_unlock_t;


#include "slmp/_poppack.h" 

#endif /* REMPSWD_H */
