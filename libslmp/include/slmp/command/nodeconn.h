/**
 * \file nodeconn.h
 * 
 * \brief Device Connection (NodeConnect)
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\NodeConnect.cge by CCGEN program.
 */

#ifndef NODECONN_H
#define NODECONN_H

#include "slmp/command/cmdhdr.h" 
#include "slmp/_pushpack4.h" 


/**
 * \brief Detects a server within the network.
 */
typedef struct slmp_req_node_search {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Client MAC address
     */
    uint8_t mac_addr[6];
    /**
     * Client IP address size
     */
    uint8_t ip_addr_size;
    /**
     * Client IP address
     */
    uint8_t ip_addr[1]; /* variable size */
} slmp_req_node_search_t;

/**
 * \brief Response of ReqNodeSearch command.
 */
typedef struct slmp_res_node_search {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Client MAC address
     */
    uint8_t cli_mac[6];
    /**
     * Client IP address size
     */
    uint8_t cli_ip_addr_size;
    /**
     * Client IP address
     */
    uint8_t *cli_ip_addr; /* (size = 'cli_ip_addr_size') */
    /**
     * Server MAC address
     */
    uint8_t svr_mac_addr;
    /**
     * Server IP address size
     */
    uint8_t svr_ip_addr_size;
    /**
     * Server IP address
     */
    uint8_t *svr_ip_addr; /* (size = 'svr_ip_addr_size') */
    /**
     * Server subnet mask
     */
    uint8_t *svr_subnet_mask; /* (size = 'svr_ip_addr_size') */
    /**
     * Server default gateway IP address
     */
    uint8_t *svr_default_gateway; /* (size = 'svr_ip_addr_size') */
    /**
     * Server hostname size
     */
    uint8_t svr_hostname_size;
    /**
     * Server hostname
     */
    uint8_t *svr_hostname; /* (size = 'svr_hostname_size') */
    /**
     * Server vendor code
     */
    uint16_t svr_vendor_code;
    /**
     * Server model code
     */
    uint32_t svr_model_code; /* 32b */
    /**
     * Server machine version
     */
    uint16_t svr_machine_version;
    /**
     * Size of IP address of other communication target unit
     */
    uint8_t tgt_ip_addr_size;
    /**
     * IP address of other communication target unit
     */
    uint8_t *tgt_ip_addr; /* (size = 'tgt_ip_addr_size') */
    /**
     * Port number of other communication target unit
     */
    uint16_t tgt_port_num;
    /**
     * Server status
     */
    uint16_t svr_status;
    /**
     * Server port number
     */
    uint16_t svr_port_num;
    /**
     * Server communication protocol setting
     */
    uint8_t svr_protocol;
} slmp_res_node_search_t;

/**
 * \brief Setting IP address of device to be connected (IPAddressSet)
 * 
 * This function  sets the IP address of the server specified by MAC 
 * address. The server that received the message sets the IP address 
 * only when its own MAC address and the MAC address in the 
 * message match. The server that received the message does not 
 * respond if its own MAC address and the MAC address in the 
 * message differ. 
 */
typedef struct slmp_req_set_ip_address {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Client MAC address
     */
    uint8_t cli_mac_addr[6];
    /**
     * Client IP address size
     */
    uint8_t cli_ip_addr_size;
    /**
     * Client IP address
     */
    uint8_t *cli_ip_addr; /* (size = 'cli_ip_addr_size') */
    /**
     * Server MAC address
     */
    uint8_t svr_mac_addr;
    /**
     * Server IP address size
     */
    uint8_t svr_ip_addr_size;
    /**
     * Server IP address
     */
    uint8_t *svr_ip_addr; /* (size = 'svr_ip_addr_size') */
    /**
     * Server subnet mask
     */
    uint8_t *svr_subnet_mask; /* (size = 'svr_ip_addr_size') */
    /**
     * Server default gateway IP address
     */
    uint8_t *svr_default_gateway; /* (size = 'svr_ip_addr_size') */
    /**
     * Server hostname size
     */
    uint8_t svr_hostname_size;
    /**
     * Server hostname
     */
    uint8_t *svr_hostname; /* (size = 'svr_hostname_size') */
    /**
     * Target IP address size
     */
    uint8_t tgt_ip_addr_size;
    /**
     * Target IP address
     */
    uint8_t *tgt_ip_addr; /* (size = 'tgt_ip_addr_size') */
    /**
     * Target port number
     */
    uint16_t tgt_port_num;
    /**
     * Server protocol setting
     */
    uint8_t svr_protocol;
} slmp_req_set_ip_address_t;

/**
 * \brief Response to ReqSetIPAddress command.
 */
typedef struct slmp_res_set_ip_address {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Client MAC address
     */
    uint8_t cli_mac_addr[6];
} slmp_res_set_ip_address_t;


#include "slmp/_poppack.h" 

#endif /* NODECONN_H */
