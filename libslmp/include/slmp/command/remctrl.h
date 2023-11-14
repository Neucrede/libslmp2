/**
 * \file remctrl.h
 * 
 * \brief Remote Control Commands
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\RemoteControl.cge by CCGEN program.
 */

#ifndef REMCTRL_H
#define REMCTRL_H

#include "slmp/command/cmdhdr.h" 
#include "slmp/_pushpack4.h" 


/**
 * \brief Issue a remote RUN request to the target device.
 */
typedef struct slmp_req_remote_run {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Mode
     */
    uint16_t mode;
    /**
     * Clear mode
     */
    uint8_t clear_mode;
    /**
     * Reserved
     */
    uint8_t reserved1;
} slmp_req_remote_run_t;

/**
 * \brief Issue a remote STOP request to the target device.
 */
typedef struct slmp_req_remote_stop {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Mode
     */
    uint16_t mode;
} slmp_req_remote_stop_t;

/**
 * \brief Issue a remote PAUSE request to the target device.
 */
typedef struct slmp_req_remote_pause {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Mode
     */
    uint16_t mode;
} slmp_req_remote_pause_t;

/**
 * \brief Send a remote latch clear request to a device that is in the STOP state.
 */
typedef struct slmp_req_remote_latch_clear {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Mode
     */
    uint16_t mode;
} slmp_req_remote_latch_clear_t;

/**
 * \brief Issue a remote reset request to cancel the error stop state of the target device.
 */
typedef struct slmp_req_remote_reset {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 


    uint16_t mode;
} slmp_req_remote_reset_t;

/**
 * \brief Read the processor model code of the target device
 */
typedef struct slmp_req_read_type_name {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

} slmp_req_read_type_name_t;

/**
 * \brief Response of ReqReadTypeName.
 */
typedef struct slmp_res_read_type_name {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Processor module type name
     */
    uint8_t type[16]; /* string */
    /**
     * Processor type code
     */
    uint16_t type_code;
} slmp_res_read_type_name_t;

/**
 * \brief Start / stop the indicator display of the device with the specified MAC address.
 * !!! Use reqLMT-PDU to carry this request.
 */
typedef struct slmp_req_node_indication {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Target MAC address
     */
    uint8_t mac_addr[6];
    /**
     * Start / stop indicator display
     */
    uint16_t start_stop;
} slmp_req_node_indication_t;

/**
 * \brief Response of ReqNodeIndication.
 */
typedef struct slmp_res_node_indication {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * MAC address
     */
    uint8_t mac_addr[6];
} slmp_res_node_indication_t;


#include "slmp/_poppack.h" 

#endif /* REMCTRL_H */
