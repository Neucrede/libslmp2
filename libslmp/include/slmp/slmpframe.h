/**
 * \file slmpframe.h
 *
 * \brief Data structures describing SLMP frames.
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 */

#ifndef __SLMPFRAME_H__
#define __SLMPFRAME_H__

#include <stdint.h>
#include <limits.h>
#include <sys/types.h>

#include "_pushpack4.h"

#define SLMP_MAX_DATA_LEN           UINT16_MAX

/** \brief SLMP frame header. */
typedef struct slmp_hdr {
    /** Frame type */
    uint16_t ftype;
    /** Serial number, not used if this is an ST type frame. */
    uint16_t serial;
} slmp_hdr_t;

/** \brief SLMP frame sub-header. */
typedef struct slmp_sub_hdr {
    /** Network number of request destination station. */
    uint8_t net_no;
    /** Node number of request destination station. */
    uint8_t node_no;
    /** Processor number of request destination station. */
    uint16_t dst_proc_no;
    /** Data length. */
    uint16_t data_len;

    /** Not used if this is an OD frame. */
    union {
        /** Timer (used in request frame). */
        uint16_t timer;
        /** End code (used in response frame). */
        uint16_t end_code;
        /** Reserved. */
        uint16_t reserved;
    } un;
} slmp_sub_hdr_t, slmp_sub_hdr_st_t, slmp_sub_hdr_mt_t;

/** \brief Sub-header of an extended MT type SLMP frame. */
typedef struct slmp_sub_hdr_emt {
    /** Network number of request destination station. */
    uint8_t dst_net_no;
    /** Node number of request destination station. */
    uint8_t dst_node_no;
    /** Processor number of request destination station. */
    uint16_t dst_proc_no;
    /** Network number of request source station. */
    uint8_t src_net_no;
    /** Node number of request source station. */
    uint8_t src_node_no;
    /** Processor number of request source station. */
    uint16_t src_proc_no;
    /** Packet type. */
    uint8_t pkt_type;
    /**
     * Division info. The frame will carry the last data if MSB of flgm is not
     * set, otherwise it will not. Bits 14..0 indicates the division number. 
     */
    uint16_t flgm;
    /** Data length. */
    uint16_t data_len;
} slmp_sub_hdr_emt_t;

/** \brief Sub-header of an station-number-extended-MT type SLMP frame. */
typedef struct slmp_sub_hdr_lmt {
    /** Network number of request destination station. */
    uint8_t net_no;
    /** Node number of request destination station. */
    uint8_t node_no;
    /** Processor number of request destination station. */
    uint16_t dst_proc_no;
    /** Processor sub-number of request destination station. */
    uint8_t dst_proc_sub_no;
    /** Large node number. */
    uint16_t large_node_no;
    /** Data length. */
    uint16_t data_len;

    union {
        /** Timer (used in request frame). */
        uint16_t timer;
        /** End code (used in response frame). */
        uint16_t end_code;
        /** Reserved. */
        uint16_t reserved;
    } un;
} slmp_sub_hdr_lmt_t;

/** \brief Command data for ST, MT and EMT type frames. */
typedef struct slmp_cmd_data {
    /** Command. */
    uint16_t cmd;
    /** Sub command. */
    uint16_t sub_cmd;
    /** End code (used only by EMT response). */
    uint16_t end_code;
} slmp_cmd_data_t, slmp_cmd_data_st_t, slmp_cmd_data_mt_t, slmp_cmd_data_emt_t;

/** \brief Command data for LMT type frames. */
typedef struct slmp_cmd_data_lmt {
    /** Command. */
    uint16_t cmd;
    /** Sub command. */
    uint16_t sub_cmd;
    /** Message identification value. */
    uint8_t data_id;
    /** Total number of frames to which the data is divided. */
    uint16_t data_div_total;
    /** Current frame number. */
    uint16_t div_no;
} slmp_cmd_data_lmt_t;

/** \brief Error information structure for ST, MT and EMT type frames. */
typedef struct slmp_err_info {
    /** Network number of request source station. */
    uint8_t net_no;
    /** Node number of request source station. */
    uint8_t node_no;
    /** Processor number of request source station. */
    uint16_t dst_proc_no;
    /** Command. */
    uint16_t cmd;
    /** Sub-command. */
    uint16_t sub_cmd;
} slmp_err_info_t, slmp_err_info_st_t, slmp_err_info_mt_t, slmp_err_info_emt_t;

/** \brief Error information structure for LMT type frames. */
typedef struct slmp_err_info_lmt {
    /** Network number of request source station. */
    uint8_t net_no;
    /** Node number of request source station. */
    uint8_t node_no;
    /** Processor number of request source station. */
    uint16_t dst_proc_no;
    /** Processor sub_number of request source station. */
    uint8_t dst_proc_sub_no;
    /** Large node number. */
    uint16_t large_node_no;
} slmp_err_info_lmt_t;

/** \brief SLMP frame. */
typedef struct slmp_frame {
    /** 
     * Size of the structure.
     *
     * Note that `raw_data` member is been declared as an array of 
     * one `uint8_t` for convenience hence that the value of
     * `size` member should be calculated as follows: 
     *      <code>size = raw_data_length + sizeof(slmp_frame_t) - 1</code>,
     * where `raw_data_length` may be zero.
     *
     * It is encouraged to use macro `SLMP_FRAME_STRUCT_SIZE()`
     * to calculate this value.
     */
    size_t size;
    
    /** timestamp when the frame was received. */
    uint64_t timestamp;

    /** Header. */
    slmp_hdr_t hdr;
    
    /** Sub header. */
    union {
        slmp_sub_hdr_st_t st;
        slmp_sub_hdr_mt_t mt;
        slmp_sub_hdr_emt_t emt;
        slmp_sub_hdr_lmt_t lmt;
    } sub_hdr;
    
    /** Command data. */
    union {
        slmp_cmd_data_st_t st;
        slmp_cmd_data_mt_t mt;
        slmp_cmd_data_emt_t emt;
        slmp_cmd_data_lmt_t lmt;
    } cmd_data;
    
    /** 
     * Error information. Not used if this is not an error information frame. 
     */
    union {
        slmp_err_info_st_t st;
        slmp_err_info_mt_t mt;
        slmp_err_info_emt_t emt;
        slmp_err_info_lmt_t lmt;
    } err_info;
    
    /** Variable length binary raw data. */
    uint8_t raw_data[1];
} slmp_frame_t;


/**
 * Compute the value of `size` field of an
 * `slmp_frame_t` struct.
 */
#define SLMP_FRAME_STRUCT_SIZE(raw_data_len)                                \
    (raw_data_len + sizeof(slmp_frame_t) - 1)                               \


/**
 * Compute the size of raw data of an `slmp_frame_t` struct.
 */
#define SLMP_FRAME_RAW_DATA_SIZE(pframe)                                    \
    (pframe->size - sizeof(slmp_frame_t) + 1)                               \
    
    
#include "_poppack.h"

#endif /* __SLMPFRAME_H__ */
