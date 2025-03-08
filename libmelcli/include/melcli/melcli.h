/**
 * \file melcli.h
 * 
 * \brief SLMP client library for Mitsubishi(R) MELSEC(R) series PLCs.
 *
 * This library also serves as a demonstration on typical usage of libslmp.
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 *
 */

#ifndef __MELCLI_H__
#define __MELCLI_H__

#include "config.h"

#include <stdint.h>
#include "melcliapi.h"
#include "melclidef.h"


/**
 * \brief Data structure that describes an request destination.
 */
typedef struct melcli_station {
    /** Network number */
    uint8_t net_num;
    /** Node number */
    uint8_t node_num;
    /** Destination processor number */
    uint16_t dst_proc_num;
    /** Destination processor sub-number (currently not used) */
    uint8_t dst_proc_sub_num;
    /** Large node number (currently not used) */
    uint16_t large_node_num;
} melcli_station_t;

/**
 * \brief Timeout values.
 */
typedef struct melcli_timeout {
    /** Connection timeout (sec) */
    int conn_timeout;
    /** Receive timeout (sec) */
    int recv_timeout;
    /** Frame receive timeout (msec) */
    int frame_timeout;
    /** 
     * Frame monitoring timer which indicates the time to wait from when
     * a request is received in the network module to when a response is
     * returned from the processor module. The wait time (in msecs) is 
     * calculated by multipling the monitoring timer value by 250. 
     * A value of zero indicates infinite waiting.
     */
    int frame_timer;
} melcli_timeout_t;

/** Context struct */
typedef struct melcli_ctx melcli_ctx_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Initialize the library.
 *
 * This function initializes libslmp internally. Call this function before 
 * calling other libmelcli functions. Need not be called on Win32 platform.
 *
 * \return If the function succeeds, the return value is 0, otherwise
 * returns -1.
 */
MELCLIAPI int MELCLICALL melcli_init();

/**
 * \brief Uninitialize the library. 
 *
 * This function uninitializes libslmp internally. Call this function before 
 * thread entry function returns. Need not be called on Win32 platform.
 *
 * \return If the function succeeds, the return value is 0, otherwise
 * returns -1.
 */
MELCLIAPI int MELCLICALL melcli_uninit();

/**
 * \brief Get description of the error number.
 *
 * \param[in] err Error number.
 *
 * \return Description of error number `err`.
 */
MELCLIAPI const char* MELCLICALL melcli_get_err_msg(int err);

/**
 * \brief Create a new connection context.
 *
 * \param[in] type Context type.
 * \param[in] remote_ipaddr IP address of the connection target.
 * \param[in] remote_port Port number of the connection target.
 * \param[in] local_ipaddr Local IP address. This is an optional parameter.
 * If its not NULL, the client socket will be bound to the given address. 
 * \param[in] local_port Local port number (UDP only).
 * \param[in] station Default destination station. This is an optional
 * parameter, values of `MELCLI_CONNECTED_STATION` will be 
 * used as default if a NULL argument is given.
 * \param[in] timeout Default timeout settings. This is an optional parameter.
 * Values of `MELCLI_TIMEOUT_DEFAULT` will be used as default 
 * values if given a NULL argument.
 *
 * \return If the function succeeds, it returns a pointer to the context 
 * created. Otherwise a NULL pointer is returned.
 */
MELCLIAPI melcli_ctx_t* MELCLICALL melcli_new_context(
    int type, const char* remote_ipaddr, int remote_port,
    const char* local_ipaddr, int local_port,
    const melcli_station_t* station, const melcli_timeout_t* timeout);

/**
 * \brief Free a connection context. If the connection is still alive,
 * it will be shutdown forcifully.
 *
 * \param[in] ctx Connection context.
 */
MELCLIAPI void MELCLICALL melcli_free_context(
    melcli_ctx_t* ctx);

/**
 * \brief Setup debug print function.
 *
 * \param[in] ctx Connection context.
 * \param[in] pfn Pointer to a function that performs formatted output like
 * `printf()` does.
 */
MELCLIAPI void MELCLICALL melcli_set_dbgprint_fcn(
    melcli_ctx_t* ctx, int (CDECLCALL* pfn)(const char*, ...));

/**
 * \brief Connect to the target.
 *
 * \param[in] ctx Connection context.
 *
 * \return If the function succeeds, the return value is 0. If the function fails,
 * the return value is one of the following error codes.
 *
 * - MELCLI_ERROR_INVALID_POINTER
 *
 *   Argument `ctx` is a null pointer.
 *
 * - MELCLI_ERROR_CONNECT_FAILED
 *
 *   Failed to establish a connection.
 */
MELCLIAPI int MELCLICALL melcli_connect(
    melcli_ctx_t* ctx);

/** 
 * \brief Disconnect from a connected target.
 *
 * \param[in] ctx Connection context.
 */
MELCLIAPI void MELCLICALL melcli_disconnect(
    melcli_ctx_t* ctx);

/**
 * \brief Set whether to dump debug info.
 *
 * \param[in] ctx Connection context.
 * \param[in] debug If the argument is 1, debug mode is enabled.
 * If the argument is 0, debug mode is disabled.
 *
 */
MELCLIAPI void MELCLICALL melcli_set_debug(
    melcli_ctx_t* ctx, int debug);

/**
 * \brief Free any pointer returned by libmelcli except pointers
 * of type `melcli_ctx_t*`.
 *
 * \param[in] p Pointer to release.
 */
MELCLIAPI void MELCLICALL melcli_free(
    void* p);

/**
 * \brief Perform sequential read on internal memory (device) units.
 *
 * \param[in] ctx Connection context.
 * \param[in] station Optional destination station. If the argument is NULL,
 * default destination station is used.
 * \param[in] addr Address string of the starting unit.
 * \param[in] n Number of units to access.
 * \param[out] data Pointer to the data buffer pointer.
 *
 * \return If the function succeeds, the return value is 0. If the function fails,
 * the return value is one of the following error codes.
 *
 * - MELCLI_ERROR_INVALID_POINTER
 *
 *   Value of one or more of `ctx`, `addr` and
 *   `data` is NULL.
 *
 * - MELCLI_ERROR_INVALID_ARGUMENTS
 *   
 *   Number of units to read is either smaller or equal to zero, or 
 *   larger or equal to 65536.
 *
 * - MELCLI_ERROR_INVALID_ADDRESS
 *   
 *   Address string given in `addr` is invalid.
 *
 * - MELCLI_ERROR_BUILD_REQUEST_FRAME
 *
 *   Failed to build a request frame.
 *
 * - MELCLI_ERROR_SEND_FRAMES
 *
 *   Failed to send request frames, possible due to networking errors.
 *
 * - MELCLI_ERROR_RECEIVE_FRAMES
 *
 *   Failed to receive response frames, possible due to networking errors
 *   or read operation timeout.
 *
 * - MELCLI_ERROR_FRAME_SERIAL_MISMATCH
 *
 *   The serial of the received frame doesn't match that of the one just
 *   sent before.
 *
 * - MELCLI_ERROR_OPERATION_FAILED
 *
 *   The response frame indicates that an error has happened.
 *
 * - MELCLI_ERROR_DECODE_FRAME
 *
 *   Unable to decode the data carried by the frame.
 *
 * - MELCLI_ERROR_OUT_OF_MEMORY
 *
 *   Memory allocation has failed. 
 *
 * \remark If the function succeeds, it sets `*data` be the pointer 
 * to an array containing data read from specified internal memory (or device,
 * if you like) units. The array will contain `n` char elements if
 * bit units are being read, while each element will be 1 if the bit is set and
 * will be 0 if the bit is cleared. If word or double-word units are being read,
 * the array will contain `n` `uint16_t` or 
 * `uint32_t` elements respectively. Remember to free the array
 * pointer after use, by calling melcli_free() and passing the array pointer to
 * it.
 */
MELCLIAPI int MELCLICALL melcli_batch_read(
    melcli_ctx_t* ctx, const melcli_station_t* station, const char* addr,
    int n, char** data, int* datalen);

/**
 * \brief Perform sequential write on internal memory (device) units.
 *
 * \param[in] ctx Connection context.
 * \param[in] station Optional destination station. If the argument is NULL,
 * default destination station is used.
 * \param[in] addr Address string of the starting unit.
 * \param[in] n Number of units to access.
 * \param[in] data Pointer to data to be written into target units.
 * \param[out] data_len Optional output parameter that stores the byte length
 * of `data`.
 *
 * \return If the function succeeds, the return value is 0. If the function fails,
 * the return value is one of the following error codes.
 *
 * - MELCLI_ERROR_INVALID_POINTER
 *
 *   Value of one or more of `ctx`, `addr` and
 *   `data` is NULL.
 *
 * - MELCLI_ERROR_INVALID_ARGUMENTS
 *   
 *   Number of units to write is either smaller or equal to zero, or 
 *   larger or equal to 65536.
 *
 * - MELCLI_ERROR_INVALID_ADDRESS
 *   
 *   Address string given in `addr` is invalid.
 *
 * - MELCLI_ERROR_BUILD_REQUEST_FRAME
 *
 *   Failed to build a request frame.
 *
 * - MELCLI_ERROR_SEND_FRAMES
 *
 *   Failed to send request frames, possible due to networking errors.
 *
 * - MELCLI_ERROR_RECEIVE_FRAMES
 *
 *   Failed to receive response frames, possible due to networking errors
 *   or read operation timeout.
 *
 * - MELCLI_ERROR_FRAME_SERIAL_MISMATCH
 *
 *   The serial of the received frame doesn't match that of the one just
 *   sent before.
 *
 * - MELCLI_ERROR_OPERATION_FAILED
 *
 *   The response frame indicates that an error has happened.
 *
 * - MELCLI_ERROR_OUT_OF_MEMORY
 *
 *   Memory allocation has failed. 
 *
 * \remark The data array shall contain `n` char elements if bit 
 * units are being written, while each element be 1 if the bit is to be set
 * and be 0 if the bit is to be cleared. If word or double-word units are 
 * being written, the data array shall contain `n` 
 * `uint16_t` or `uint32_t` elements respectively.
 * Incorrect data array size might cause unpredictable application crashes.
 *
 */
MELCLIAPI int MELCLICALL melcli_batch_write(
    melcli_ctx_t* ctx, const melcli_station_t* station, const char* addr,
    int n, const char* data);

/**
 * \brief Perform random read on internal memory (device) units.
 *
 * \param[in] ctx Connection context.
 * \param[in] station Optional destination station. If the argument is NULL,
 * default destination station is used.
 * \param[in] word_unit_addrs Array of address strings of word units to be read 
 * from. The array must terminate by a NULL pointer which indicates the
 * end of array elements.
 * \param[in] dword_unit_addrs Array of address of double-word units to be 
 * read from. The array must terminate by a NULL pointer which indicates the
 * end of array elements.
 * \param[out] word_data Pointer to the word data buffer pointer.
 * \param[out] word_data_len Optional output parameter that stores the byte length
 * of `word_data`.
 * \param[out] dword_data Pointer to the double-word data buffer pointer.
 * \param[out] dword_data_len Optional output parameter that stores the byte length
 * of `dword_data`.
 *
 * \return If the function succeeds, the return value is 0. If the function fails,
 * the return value is one of the following error codes.
 *
 * - MELCLI_ERROR_INVALID_POINTER
 *
 *   Possible causes are:
 *   - `ctx` is a NULL pointer.
 *   - No address string is given.
 *   - There exists some units to read but corresponding data pointer is NULL.
 *
 * - MELCLI_ERROR_INVALID_ARGUMENTS
 *
 *   Possible causes are:
 *   - Total number of units to read is zero.
 *   - The number of one or more types of units to read exceeds 255.
 *
 * - MELCLI_ERROR_INVALID_ADDRESS
 *   
 *   One or more address strings are invalid.
 *
 * - MELCLI_ERROR_INCONSISTENT_ADDRESS_WIDTH
 *
 *   The address width of given units are inconsistent.
 *
 * - MELCLI_ERROR_BUILD_REQUEST_FRAME
 *
 *   Failed to build a request frame.
 *
 * - MELCLI_ERROR_ENCODE_COMMAND
 *
 *   Failed to encode the request command.
 *
 * - MELCLI_ERROR_SEND_FRAMES
 *
 *   Failed to send request frames, possible due to networking errors.
 *
 * - MELCLI_ERROR_RECEIVE_FRAMES
 *
 *   Failed to receive response frames, possible due to networking errors
 *   or read operation timeout.
 *
 * - MELCLI_ERROR_FRAME_SERIAL_MISMATCH
 *
 *   The serial of the received frame doesn't match that of the one just
 *   sent before.
 *
 * - MELCLI_ERROR_OPERATION_FAILED
 *
 *   The response frame indicates that an error has happened.
 *
 * - MELCLI_ERROR_DECODE_FRAME
 *
 *   Unable to decode the data carried by the frame.
 *
 * - MELCLI_ERROR_OUT_OF_MEMORY
 *
 *   Memory allocation has failed. 
 *
 * \remark Remember to free the data array pointers using melcli_free() after
 * they are no longer to be used.
 *
 * \sa melcli_random_read_word(), melcli_random_read_dword()
 */
MELCLIAPI int MELCLICALL melcli_random_read(
    melcli_ctx_t* ctx, const melcli_station_t* station, 
    const char** word_unit_addrs, const char** dword_unit_addrs, 
    uint16_t** word_data, int* word_data_len, 
    uint32_t** dword_data, int* dword_data_len);

/**
 * Provided for convenience. 
 * \sa melcli_random_read()
 */
MELCLIAPI int MELCLICALL melcli_random_read_word(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char** addrs, uint16_t** data, int* data_len);

/** 
 * Provided for convenience.
 * \sa melcli_random_read()
 */
MELCLIAPI int MELCLICALL melcli_random_read_dword(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char** addrs, uint32_t** data, int* data_len);

/**
 * \brief Perform random write on internal memory (device) units.
 *
 * \param[in] ctx Connection context.
 * \param[in] station Optional destination station. If the argument is NULL,
 * default destination station is used.
 * \param[in] bit_unit_addrs Array of address strings of bit units to be read 
 * from. The array must terminate by a NULL pointer which indicates the
 * end of array elements.
 * \param[in] word_unit_addrs Array of address strings of word units to be read 
 * from. The array must terminate by a NULL pointer which indicates the
 * end of array elements.
 * \param[in] dword_unit_addrs Array of address of double-word units to be 
 * read from. The array must terminate by a NULL pointer which indicates the
 * end of array elements.
 * \param[in] bit_data Pointer to data to be written into target bit units.
 * \param[in] word_data Pointer to data to be written into target word units.
 * \param[in] dword_data Pointer to data to be written into target double-word
 * units.
 *
 * \return If the function succeeds, the return value is 0. If the function fails,
 * the return value is one of the following error codes.
 *
 * - MELCLI_ERROR_INVALID_POINTER
 *
 *   Possible causes are:
 *   - `ctx` is a NULL pointer.
 *   - No address string is given.
 *   - There exists some units to write but corresponding data pointer is NULL.
 *
 * - MELCLI_ERROR_INVALID_ARGUMENTS
 *   
 *   Possible causes are:
 *   - Total number of units to read is zero.
 *   - The number of one or more types of units to read exceeds 255.
 *
 * - MELCLI_ERROR_INVALID_ADDRESS
 *   
 *   One or more address strings are invalid.
 *
 * - MELCLI_ERROR_INCONSISTENT_ADDRESS_WIDTH
 *
 *   Possible causes are:
 *   - The address width of given bit units are inconsistent.
 *   - The address width of given multi-byte units are inconsistent.
 *
 * - MELCLI_ERROR_BUILD_REQUEST_FRAME
 *
 *   Failed to build a request frame.
 *
 * - MELCLI_ERROR_ENCODE_COMMAND
 *
 *   Failed to encode the request command.
 *
 * - MELCLI_ERROR_SEND_FRAMES
 *
 *   Failed to send request frames, possible due to networking errors.
 *
 * - MELCLI_ERROR_RECEIVE_FRAMES
 *
 *   Failed to receive response frames, possible due to networking errors
 *   or read operation timeout.
 *
 * - MELCLI_ERROR_FRAME_SERIAL_MISMATCH
 *
 *   The serial of the received frame doesn't match that of the one just
 *   sent before.
 *
 * - MELCLI_ERROR_OPERATION_FAILED
 *
 *   The response frame indicates that an error has happened.
 *
 * - MELCLI_ERROR_OUT_OF_MEMORY
 *
 *   Memory allocation has failed. 
 *
 * \remark The data array shall contain `n` char elements if bit 
 * units are being written, while each element be 1 if the bit is to be set
 * and be 0 if the bit is to be cleared. If word or double-word units are 
 * being written, the data array shall contain `n` 
 * `uint16_t` or `uint32_t` elements respectively.
 * Incorrect data array size might cause unpredictable application crashes.
 *
 * \sa melcli_random_write_bit(), melcli_random_write_word(),
 * melcli_random_write_dword()
 */
MELCLIAPI int MELCLICALL melcli_random_write(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char** bit_unit_addrs, const char** word_unit_addrs, 
    const char** dword_unit_addrs, const uint8_t* bit_data, 
    const uint16_t* word_data, const uint32_t* dword_data);

/**
 * Provided for convenience.
 * \sa melcli_random_write()
 */
MELCLIAPI int MELCLICALL melcli_random_write_bit(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char** addrs, const uint8_t* data);

/**
 * Provided for convenience.
 * \sa melcli_random_write()
 */
MELCLIAPI int MELCLICALL melcli_random_write_word(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char** addrs, const uint16_t* data);

/**
 * Provided for convenience.
 * \sa melcli_random_write()
 */
MELCLIAPI int MELCLICALL melcli_random_write_dword(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char** addrs, const uint32_t* data);
    
/**
 * \brief Perform sequential read on buffer (dual port memory) units.
 *
 * \param[in] ctx Connection context.
 * \param[in] station Optional destination station. If the argument is NULL,
 * default destination station is used.
 * \param[in] addr Address of the starting unit.
 * \param[in] n Number of word units to access.
 * \param[out] data Pointer to the data buffer pointer.
 * \param[out] data_len Optional output parameter that stores the byte length
 * of `data`.
 *
 * \return If the function succeeds, the return value is 0. If the function fails,
 * the return value is one of the following error codes.
 *
 * - MELCLI_ERROR_INVALID_POINTER
 *
 *   Value of one or more of `ctx` and `data` is NULL.
 *
 * - MELCLI_ERROR_INVALID_ARGUMENTS
 *   
 *   Number of units to read is either smaller or equal to zero, or 
 *   larger or equal to 65536.
 *
 * - MELCLI_ERROR_BUILD_REQUEST_FRAME
 *
 *   Failed to build a request frame.
 *
 * - MELCLI_ERROR_SEND_FRAMES
 *
 *   Failed to send request frames, possible due to networking errors.
 *
 * - MELCLI_ERROR_RECEIVE_FRAMES
 *
 *   Failed to receive response frames, possible due to networking errors
 *   or read operation timeout.
 *
 * - MELCLI_ERROR_FRAME_SERIAL_MISMATCH
 *
 *   The serial of the received frame doesn't match that of the one just
 *   sent before.
 *
 * - MELCLI_ERROR_OPERATION_FAILED
 *
 *   The response frame indicates that an error has happened.
 *
 * - MELCLI_ERROR_DECODE_FRAME
 *
 *   Unable to decode the data carried by the frame.
 *
 * - MELCLI_ERROR_OUT_OF_MEMORY
 *
 *   Memory allocation has failed. 
 *
 * \remark If the function succeeds, it sets `*data` be the pointer 
 * to an array containing word data read from specified buffer (dual port 
 * memory). 
 * Remember to free the array pointer `data` after use, by calling 
 * melcli_free() and passing the array pointer to it.
 */
MELCLIAPI int MELCLICALL melcli_buffer_read(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    uint32_t addr, int n, uint16_t** data, int* data_len);

/**
 * \brief Perform sequential write on buffer (dual port memory) units.
 *
 * \param[in] ctx Connection context.
 * \param[in] station Optional destination station. If the argument is NULL,
 * default destination station is used.
 * \param[in] addr Address of the starting unit.
 * \param[in] n Number of word units to access.
 * \param[in] data Pointer to word data to be written into target units.
 *
 * \return If the function succeeds, the return value is 0. If the function fails,
 * the return value is one of the following error codes.
 *
 * - MELCLI_ERROR_INVALID_POINTER
 *
 *   Value of one or more of `ctx` and `data` is NULL.
 *
 * - MELCLI_ERROR_INVALID_ARGUMENTS
 *   
 *   Number of units to write is either smaller or equal to zero, or 
 *   larger or equal to 65536.
 *
 * - MELCLI_ERROR_BUILD_REQUEST_FRAME
 *
 *   Failed to build a request frame.
 *
 * - MELCLI_ERROR_SEND_FRAMES
 *
 *   Failed to send request frames, possible due to networking errors.
 *
 * - MELCLI_ERROR_RECEIVE_FRAMES
 *
 *   Failed to receive response frames, possible due to networking errors
 *   or read operation timeout.
 *
 * - MELCLI_ERROR_FRAME_SERIAL_MISMATCH
 *
 *   The serial of the received frame doesn't match that of the one just
 *   sent before.
 *
 * - MELCLI_ERROR_OPERATION_FAILED
 *
 *   The response frame indicates that an error has happened.
 *
 * - MELCLI_ERROR_OUT_OF_MEMORY
 *
 *   Memory allocation has failed. 
 *
 * \remark The data array shall contain `n` `uint16_t` elements.
 * Incorrect data array size might cause unpredictable application crashes.
 *
 */
MELCLIAPI int MELCLICALL melcli_buffer_write(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    uint32_t addr, int n, const uint16_t* data);

/**
 * \brief Issue a remote control command to specified destination station.
 *
 * \param[in] ctx Connection context.
 * \param[in] station Optional destination station. If the argument is NULL,
 * default destination station is used.
 * \param[in] ctl_code Control code.
 * \param[in] flag Dedicated subcommand flags.
 * \param[out] type_name Receives the buffer to a string containing type name
 * of the destination station CPU when specifying a control code of value
 * `MELCLI_REMOTE_READ_TYPE_NAME`. Otherwise it's ignored.
 * \param[out] type_code Receives the type code of the destination station
 * CPU when specifying a control code of value
 * `MELCLI_REMOTE_READ_TYPE_NAME`. Otherwise it's ignored.
 *
 * \return If the function succeeds, the return value is 0. If the function fails,
 * the return value is one of the following error codes.
 *
 * - MELCLI_ERROR_INVALID_POINTER
 *
 *   Possible causes are:
 *   - `ctx` is a NULL pointer.
 *   - `type_name` and / or `type_code` are NULL pointers 
 *     when `MELCLI_REMOTE_READ_TYPE_NAME` is given.
 *
 * - MELCLI_ERROR_INVALID_ARGUMENTS
 *   
 *   Invalid control code was given.
 *
 * - MELCLI_ERROR_BUILD_REQUEST_FRAME
 *
 *   Failed to build a request frame.
 *
 * - MELCLI_ERROR_SEND_FRAMES
 *
 *   Failed to send request frames, possible due to networking errors.
 *
 * - MELCLI_ERROR_RECEIVE_FRAMES
 *
 *   Failed to receive response frames, possible due to networking errors
 *   or read operation timeout.
 *
 * - MELCLI_ERROR_FRAME_SERIAL_MISMATCH
 *
 *   The serial of the received frame doesn't match that of the one just
 *   sent before.
 *
 * - MELCLI_ERROR_OPERATION_FAILED
 *
 *   The response frame indicates that an error has happened.
 *
 * - MELCLI_ERROR_DECODE_FRAME
 *
 *   Unable to decode the data carried by the frame.
 *
 * - MELCLI_ERROR_OUT_OF_MEMORY
 *
 *   Memory allocation has failed. 
 *
 * \remark When `MELCLI_REMOTE_READ_TYPE_NAME` control code
 * is specified, free `type_name` after use by calling melcli_free().
 *
 * \sa melcli_remote_run(), melcli_remote_stop(), melcli_remote_reset(),
 * melcli_remote_pause(), melcli_remote_latch_clear(),
 * melcli_remote_read_type_name()
 */
MELCLIAPI int MELCLICALL melcli_remote_control(
    melcli_ctx_t* ctx, const melcli_station_t* station, int ctl_code,
    int flag, char** type_name, int* type_code);

/** 
 * Provided for convenience.
 * \sa melcli_remote_control()
 */
MELCLIAPI int MELCLICALL melcli_remote_run(
    melcli_ctx_t* ctx, const melcli_station_t* station, int flag);
    
/** 
 * Provided for convenience.
 * \sa melcli_remote_control()
 */
MELCLIAPI int MELCLICALL melcli_remote_stop(
    melcli_ctx_t* ctx, const melcli_station_t* station);

/** 
 * Provided for convenience.
 * \sa melcli_remote_control()
 */
MELCLIAPI int MELCLICALL melcli_remote_reset(
    melcli_ctx_t* ctx, const melcli_station_t* station);

/** 
 * Provided for convenience.
 * \sa melcli_remote_control()
 */
MELCLIAPI int MELCLICALL melcli_remote_pause(
    melcli_ctx_t* ctx, const melcli_station_t* station, int flag);

/** 
 * Provided for convenience.
 * \sa melcli_remote_control()
 */
MELCLIAPI int MELCLICALL melcli_remote_latch_clear(
    melcli_ctx_t* ctx, const melcli_station_t* station);

/** 
 * Provided for convenience.
 * \sa melcli_remote_control()
 */
MELCLIAPI int MELCLICALL melcli_remote_read_type_name(
    melcli_ctx_t* ctx, const melcli_station_t* station, char** type_name, 
    int* type_code);
    
/**
 * \brief Enable / disable remote access from SLMP compatible devices.
 *
 * \param[in] ctx Connection context.
 * \param[in] station Optional destination station. If the argument is NULL,
 * default destination station is used.
 * \param[in] lock 1: Lock, 0: Unlock.
 * \param[in] password Password string.
 *
 * \return If the function succeeds, the return value is 0. If the function fails,
 * the return value is one of the following error codes.
 *
 * - MELCLI_ERROR_INVALID_POINTER
 *
 *   Possible causes are:
 *   - `ctx` is a null pointer.
 *   - `password` is a null pointer.
 *
 * - MELCLI_ERROR_INVALID_ARGUMENTS
 *   
 *   Empty password.
 *
 * - MELCLI_ERROR_BUILD_REQUEST_FRAME
 *
 *   Failed to build a request frame.
 *
 * - MELCLI_ERROR_SEND_FRAMES
 *
 *   Failed to send request frames, possible due to networking errors.
 *
 * - MELCLI_ERROR_OUT_OF_MEMORY
 *
 *   Memory allocation has failed. 
 *
 * \sa melcli_remote_lock(), melcli_remote_unlock()
 */
MELCLIAPI int MELCLICALL melcli_remote_password(
    melcli_ctx_t* ctx, const melcli_station_t* station, int lock,
    const char* password);

/** 
 * Provided for convenience.
 * \sa melcli_remote_password()
 */
MELCLIAPI int MELCLICALL melcli_remote_lock(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char* password);

/** 
 * Provided for convenience.
 * \sa melcli_remote_password()
 */
MELCLIAPI int MELCLICALL melcli_remote_unlock(
    melcli_ctx_t* ctx, const melcli_station_t* station,
    const char* password);
    
/**
 * \brief Perform loopback test.
 *
 * \param[in] ctx Connection context.
 * \param[in] station Optional destination station. If the argument is NULL,
 * default destination station is used.
 *
 * \return If the function succeeds, the return value is 0. If the function fails,
 * the return value is one of the following error codes.
 *
 * - MELCLI_ERROR_INVALID_POINTER
 *
 *   `ctx` is a null pointer.
 *
 * - MELCLI_ERROR_BUILD_REQUEST_FRAME
 *
 *   Failed to build a request frame.
 *
 * - MELCLI_ERROR_SEND_FRAMES
 *
 *   Failed to send request frames, possible due to networking errors.
 *
 * - MELCLI_ERROR_RECEIVE_FRAMES
 *
 *   Failed to receive response frames, possible due to networking errors
 *   or read operation timeout.
 *
 * - MELCLI_ERROR_FRAME_SERIAL_MISMATCH
 *
 *   The serial of the received frame doesn't match that of the one just
 *   sent before.
 *
 * - MELCLI_ERROR_OPERATION_FAILED
 *
 *   The response frame indicates that an error has happened.
 *
 * - MELCLI_ERROR_DECODE_FRAME
 *
 *   Unable to decode the data carried by the frame.
 *
 * - MELCLI_ERROR_SELF_TEST_FAILED
 *
 *   Data received from the target doesn't match the test data that was sent
 *   to the target.
 *
 * - MELCLI_ERROR_OUT_OF_MEMORY
 *
 *   Memory allocation has failed. 
 */
MELCLIAPI int MELCLICALL melcli_self_test(
    melcli_ctx_t* ctx, const melcli_station_t* station);

/**
 * \brief Clear error code.
 *
 * \param[in] ctx Connection context.
 * \param[in] station Optional destination station. If the argument is NULL,
 * default destination station is used.
 *
 * \return If the function succeeds, the return value is 0. If the function fails,
 * the return value is one of the following error codes.
 *
 * - MELCLI_ERROR_INVALID_POINTER
 *
 *   `ctx` is a null pointer.
 *
 * - MELCLI_ERROR_BUILD_REQUEST_FRAME
 *
 *   Failed to build a request frame.
 *
 * - MELCLI_ERROR_SEND_FRAMES
 *
 *   Failed to send request frames, possible due to networking errors.
 *
 * - MELCLI_ERROR_OUT_OF_MEMORY
 *
 *   Memory allocation has failed. 
 */
MELCLIAPI int MELCLICALL melcli_clear_error_code(
    melcli_ctx_t* ctx, const melcli_station_t* station);

/**
 * \brief Clear error history.
 *
 * \param[in] ctx Connection context.
 * \param[in] station Optional destination station. If the argument is NULL,
 * default destination station is used.
 *
 * \return If the function succeeds, the return value is 0. If the function fails,
 * the return value is one of the following error codes.
 *
 * - MELCLI_ERROR_INVALID_POINTER
 *
 *   `ctx` is a null pointer.
 *
 * - MELCLI_ERROR_BUILD_REQUEST_FRAME
 *
 *   Failed to build a request frame.
 *
 * - MELCLI_ERROR_SEND_FRAMES
 *
 *   Failed to send request frames, possible due to networking errors.
 *
 * - MELCLI_ERROR_OUT_OF_MEMORY
 *
 *   Memory allocation has failed. 
 */
MELCLIAPI int MELCLICALL melcli_clear_error_history(
    melcli_ctx_t* ctx, const melcli_station_t* station);

#ifdef __cplusplus
}
#endif

#endif /* __MELCLI_H__ */
