/**
 * \file paramset.h
 * 
 * \brief Setting Parameters (ParameterSetting)
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\ParameterSetting.cge by CCGEN program.
 */

#ifndef PARAMSET_H
#define PARAMSET_H

#include "slmp/command/cmdhdr.h" 
#include "slmp/_pushpack4.h" 


/**
 * \brief Compares the device information values of a server.
 */
typedef struct slmp_req_device_info_compare {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Comparison target
     */
    uint16_t target;
    /**
     * Vendor code
     */
    uint16_t vendor_code;
    /**
     * Model code
     */
    uint32_t model_code; /* 32b */
    /**
     * Machine version
     */
    uint16_t machine_version;
} slmp_req_device_info_compare_t;

/**
 * \brief Response to ReqDeviceInfoCompare command.
 */
typedef struct slmp_res_device_info_compare {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Comparison target
     */
    uint16_t target;
    /**
     * Comparison result
     */
    uint16_t result;
} slmp_res_device_info_compare_t;

/**
 * \brief Acquire parameter values from the server.
 */
typedef struct slmp_req_get_param {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of parameters to acquire
     */
    uint16_t num;
    /**
     * Parameter ID
     */
    uint16_t id;
} slmp_req_get_param_t;

/**
 * \brief Response to ReqGetParam command.
 */
typedef struct slmp_res_get_param {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of parameters
     */
    uint16_t num;
    /**
     * Parameter ID
     */
    uint16_t id;
    /**
     * Size of parameter value
     */
    uint16_t size;
    /**
     * Value
     */
    uint8_t value[1]; /* variable size */
} slmp_res_get_param_t;

/**
 * \brief Update parameter values of a server.
 */
typedef struct slmp_req_set_param {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of parameters to set
     */
    uint16_t num;
    /**
     * Parameter ID
     */
    uint16_t id;
    /**
     * Size of parameter value
     */
    uint16_t size;
    /**
     * Value
     */
    uint8_t value[1]; /* variable size */
} slmp_req_set_param_t;

/**
 * \brief This function notifies a server of the start of the device parameter value update.
 */
typedef struct slmp_req_param_set_start {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

} slmp_req_param_set_start_t;

/**
 * \brief This function notifies a server of the end of the device parameter value update.
 */
typedef struct slmp_req_param_set_end {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

} slmp_req_param_set_end_t;

/**
 * \brief This function notifies a server of the cancellation of the device parameter value update.
 */
typedef struct slmp_req_param_set_cancel {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

} slmp_req_param_set_cancel_t;


#include "slmp/_poppack.h" 

#endif /* PARAMSET_H */
