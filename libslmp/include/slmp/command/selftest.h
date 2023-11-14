/**
 * \file selftest.h
 * 
 * \brief Loopback Test.
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\SelfTest.cge by CCGEN program.
 */

#ifndef SELFTEST_H
#define SELFTEST_H

#include "slmp/command/cmdhdr.h" 
#include "slmp/_pushpack4.h" 


/**
 * \brief Performs test  on the communication with target device.
 */
typedef struct slmp_req_self_test {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Length of data
     */
    uint16_t len;
    /**
     * Loopback data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_self_test_t;

/**
 * \brief Response of ReqSelfTest.
 */
typedef struct slmp_res_self_test {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Length of data
     */
    uint16_t len;
    /**
     * Loopback data
     */
    uint8_t data[1]; /* variable size */
} slmp_res_self_test_t;


#include "slmp/_poppack.h" 

#endif /* SELFTEST_H */
