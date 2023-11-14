/**
 * \file slmpdef.h
 *
 * \brief Constant definitions
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 */

#ifndef __SLMPDEF_H__
#define __SLMPDEF_H__

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#ifndef NULL
    #define NULL 0
#endif

/**
 * \name Type of packet IO objects
 * @{
 */
#define SLMP_PKTIO_TCPIP              1
#define SLMP_PKTIO_UDPIP              2
/** @} */

/**
 * \name Role of packet IO objects
 * @{
 */
/** Client */
#define SLMP_PKTIO_CLIENT             1
/** Server */
#define SLMP_PKTIO_SERVER             2
/** Synonym of SLMP_PKTIO_CLIENT */
#define SLMP_PKTIO_ACTIVE             SLMP_PKTIO_CLIENT
/** Synonym of SLMP_PKTIO_SERVER */
#define SLMP_PKTIO_PASSIVE            SLMP_PKTIO_SERVER
/** @} */

/** 
 * \name Stream Type
 * @{
 */
/** Binary encoded stream */
#define SLMP_BINARY_STREAM                              1
/** ASCII encoded stream (human readable but less cost effective) */
#define SLMP_ASCII_STREAM                               2
/** @} */

/**
 * \name Address Width 
 * @{
 */
/** 
 * Indicates that 16bit address values are specified in the command.
 */
#define SLMP_ADDRESS_16BIT                              16
/** 
 * Indicates that 32bit address values are specified in the command.
 */
#define SLMP_ADDRESS_32BIT                              32
/**
 * Indicates that either the command doesn't care about address width,
 * or it doesn't contain any address field.
 */
#define SLMP_ADDRESS_WIDTH_DONT_CARE                    SLMP_ADDRESS_16BIT
/** @} */

/**
 * \name Network Number
 * @{
 */
#define SLMP_NETWORK_CONNECTED                          0x00
#define SLMP_NETWORK_NONDIRECT_MIN                      0x01
#define SLMP_NETWORK_NONDIRECT_MAX                      0xEF
/** @} */

/**
 * \name Timer
 * @{
 */
#define SLMP_TIMER_WAIT_INFINITE                        0x0000
/** @} */

/**
 * \name Packet Type (EMT Only)
 * @{
 */
#define SLMP_STATION_CONNECTED                          0xFF
#define SLMP_STATION_SPECIFIED_MANAGEMENT               0x7D
#define SLMP_STATION_CURRENT_MANAGEMENT                 0x7E
#define SLMP_STATION_OTHER_MIN                          0x01
#define SLMP_STATION_OTHER_MAX                          0x78
/** @} */

/**
 * \name Processor Number
 * @{
 */
#define SLMP_PROC_CONTROL_SYSTEM                        0x03D0
#define SLMP_PROC_STANDBY_SYSTEM                        0x03D1
#define SLMP_PROC_A_SYSTEM                              0x03D2
#define SLMP_PROC_B_SYSTEM                              0x03D3
#define SLMP_PROC_MULTI_UNIT_1                          0x03E0
#define SLMP_PROC_MULTI_UNIT_2                          0x03E1
#define SLMP_PROC_MULTI_UNIT_3                          0x03E2
#define SLMP_PROC_MULTI_UNIT_4                          0x03E3
#define SLMP_PROC_DEFAULT                               0x03FF
/** @} */

/**
 * \name Packet Type (EMT Only)
 * @{
 */
#define SLMP_PKT_CONNECT                                0x00
#define SLMP_PKT_VERIFY                                 0x10
#define SLMP_PKT_NORMAL                                 0x40
#define SLMP_PKT_PERMIT_FRAGMENT_TRANSFER               0x41
#define SLMP_PKT_CANCEL_FRAGMENT_TRANSFER               0x43
/** @} */

/**
 * \name Division Information (EMT Only)
 * @{
 */
#define SLMP_FLGM_LAST_DATA_MASK                        0x8000
/** @} */

/**
 * \name SLMP frame type
 * @{
 *
 * To tell ERR frames and RES frames apart, the most significant bit is used as
 * a flag to indicate the ERR frame. Clear this bit during packet stream
 * encoding by performing AND operations on FTYPE values provided here with 
 * `SLMP_FTYPE_MASK`.
 */
#define SLMP_FTYPE_REQ_ST           0x0050
#define SLMP_FTYPE_RES_ST           0x00D0
#define SLMP_FTYPE_ERR_ST           0x80D0
#define SLMP_FTYPE_REQ_MT           0x0054
#define SLMP_FTYPE_RES_MT           0x00D4
#define SLMP_FTYPE_ERR_MT           0x80D4
#define SLMP_FTYPE_REQ_EMT          0x005D
#define SLMP_FTYPE_PUSH_EMT         0x009D
#define SLMP_FTYPE_RES_EMT          0x00DD
#define SLMP_FTYPE_REQ_LMT          0x0068
#define SLMP_FTYPE_RES_LMT          0x00E8
#define SLMP_FTYPE_ERR_LMT          0x80E8
#define SLMP_FTYPE_MASK             0x7FFF
#define SLMP_FTYPE_ERR_MASK         0x8000
/** @} */

/**
 * \name End code
 * @{
 */
#define SLMP_ENDCODE_SUCCESS                            0x0000
#define SLMP_ENDCODE_BAD_COMMAND                        0xC059
#define SLMP_ENDCODE_BAD_REQUEST_CONTENT                0xC05C
#define SLMP_ENDCODE_REQUEST_DATA_LENGTH_MISMATCH       0xC061
#define SLMP_ENDCODE_RESOURCE_BUSY                      0xCEE0
#define SLMP_ENDCODE_REQUEST_MESSAGE_TOO_LARGE          0xCEE1
#define SLMP_ENDCODE_RESPONSE_MESSAGE_TOO_LARGE         0xCEE2
#define SLMP_ENDCODE_SERVER_INFO_NOT_EXIST              0xCF10
#define SLMP_ENDCODE_PARAM_ID_NOT_EXIST                 0xCF30
#define SLMP_ENDCODE_WRITE_MUTEX_START_NOT_PERFORMED    0xCF31
#define SLMP_ENDCODE_DIVIDED_MESSAGE_RECEIVE_TIMEOUT    0xCF40
#define SLMP_ENDCODE_DUPLICATED_DIVIDED_MESSAGE         0xCF41
#define SLMP_ENDCODE_DIVIDED_MESSAGE_DATA_ERROR         0xCF42
#define SLMP_ENDCODE_DIVIDED_MESSAGE_LOST               0xCF43
#define SLMP_ENDCODE_DIVISON_NOT_SUPPORTED_BY_TARGET    0xCF44
/** @} */


#endif /* __SLMPDEF_H__ */
