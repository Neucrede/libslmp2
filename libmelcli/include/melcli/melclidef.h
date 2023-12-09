/**
 * \file melclidef.h
 * 
 * \brief Constant definitions.
 *
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 *
 */


#ifndef __MELCLIDEF_H__
#define __MELCLIDEF_H__

/**
 * \name Error codes
 * @{
 */
#define MELCLI_ERROR_SUCCESS                            0
#define MELCLI_ERROR_INVALID_POINTER                    -1
#define MELCLI_ERROR_INVALID_ARGUMENTS                  -2
#define MELCLI_ERROR_INVALID_ADDRESS                    -3
#define MELCLI_ERROR_UNIT_TYPE_NOT_SUPPORTED            -4
#define MELCLI_ERROR_BUILD_REQUEST_FRAME                -5
#define MELCLI_ERROR_OUT_OF_MEMORY                      -6
#define MELCLI_ERROR_DECODE_FRAME                       -7
#define MELCLI_ERROR_ENCODE_COMMAND                     -8
#define MELCLI_ERROR_INCONSISTENT_ADDRESS_WIDTH         -9
#define MELCLI_ERROR_CONNECT_FAILED                     -10
#define MELCLI_ERROR_SEND_FRAMES                        -11
#define MELCLI_ERROR_RECEIVE_FRAMES                     -12
#define MELCLI_ERROR_OPERATION_FAILED                   -13
#define MELCLI_ERROR_FRAME_SERIAL_MISMATCH              -14
#define MELCLI_ERROR_SELF_TEST_FAILED                   -15
/** @} */

/**
 * \name Communication types
 * @{
 */
/** TCP/IP */
#define MELCLI_TYPE_TCPIP                               1
/** UDP/IP */
#define MELCLI_TYPE_UDPIP                               2
/** @} */

/**
 * \name Remote control codes
 * @{
 */
/** Issue a remote RUN request. */
#define MELCLI_REMOTE_RUN                               1
/** Issue a remote STOP request. */
#define MELCLI_REMOTE_STOP                              2
/** Issue a remote RESET request. */
#define MELCLI_REMOTE_RESET                             3
/** Issue a remote PAUSE request. */
#define MELCLI_REMOTE_PAUSE                             4
/** 
 * Issue a remote latch clear request when the target device is in the 
 * STOP state. 
 * */
#define MELCLI_REMOTE_LATCH_CLEAR                       5
/** Read the processor model code of the target deivce. */
#define MELCLI_REMOTE_READ_TYPE_NAME                    6
/** @} */

/**
 * \name Mode flags
 *
 * Used when `ctl_code` is `MELCLI_REMOTE_RUN` or 
 * `MELCLI_REMOTE_PAUSE`.
 *
 * @{
 */
/** 
 * Forced execution allowed. Remote RUN can be executed even when other device
 * is performing the remote STOP or remote PAUSE.
 */
#define MELCLI_FORCE_MODE                               (1 << 0)
/** Do not clear the device. */
#define MELCLI_CLEAR_NONE                               (1 << 5)
/** Clear all devices except those in the latch range. */
#define MELCLI_CLEAR_EXCLUDE_LATCHED                    (1 << 6)
/** Clear all devices. */
#define MELCLI_CLEAR_ALL                                (1 << 7)
/** @} */

/** Initializer for connected station. */
#define MELCLI_CONNECTED_STATION    { 0x00, 0xFF, 0x03FF, 0x00, 0x00 }

/** Initializer for default timeout values. */
#define MELCLI_TIMEOUT_DEFAULT      { 1, 1, 500, 5 }


#endif /* __MELCLIDEF_H__ */
