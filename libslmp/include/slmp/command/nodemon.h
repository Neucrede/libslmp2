/**
 * \file nodemon.h
 * 
 * \brief Monitoring Devices (Node Monitoring)
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\NodeMonitoring.cge by CCGEN program.
 */

#ifndef NODEMON_H
#define NODEMON_H

#include "slmp/command/cmdhdr.h" 
#include "slmp/_pushpack4.h" 


/**
 * \brief Acquire the operating status of a server.
 */
typedef struct slmp_req_status_read {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

} slmp_req_status_read_t;

/**
 * \brief Response to ReqStatusRead.
 */
typedef struct slmp_res_status_read {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Reserved
     */
    uint16_t reserved2;
    /**
     * Status code
     */
    uint16_t status;
} slmp_res_status_read_t;

/**
 * \brief This function acquires the operating statuses of multiple nodes.
 */
typedef struct slmp_req_status_read_multi {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

} slmp_req_status_read_multi_t;

/**
 * \brief Response to ReqStatusReadMulti.
 */
typedef struct slmp_res_status_read_multi {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Size of IP address fields.
     */
    uint8_t ip_addr_size;
    /**
     * Server IP address
     */
    uint8_t *svr_ip_addr; /* (size = 'ip_addr_size') */
    /**
     * Target IP address
     */
    uint8_t *tgt_ip_addr; /* (size = 'ip_addr_size') */
    /**
     * Operating state
     */
    uint8_t svr_state;
    /**
     * Status code
     */
    uint16_t status;
    /**
     * Reserved
     */
    uint16_t reserved2;
} slmp_res_status_read_multi_t;

/**
 * \brief This function acquires the communication settings (communication port number and 
 * timeout value) from the server.
 */
typedef struct slmp_req_get_comm_settings {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Acquisition target
     */
    uint16_t target;
} slmp_req_get_comm_settings_t;

/**
 * \brief Response to ReqGetCommSettings command.
 */
typedef struct slmp_res_get_comm_settings {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Acquisition target
     */
    uint16_t target;
    /**
     * Port number
     */
    uint16_t port_num;
    /**
     * Timeout value
     */
    uint32_t timeout; /* 32b */
} slmp_res_get_comm_settings_t;


#include "slmp/_poppack.h" 

#endif /* NODEMON_H */
