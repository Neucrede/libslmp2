/**
 * \file slmperr.h
 *
 * \brief Error number support.
 *
 * Most functions exported by this library set thread specific error
 * number if they fails. Call slmp_get_errno() right after these function
 * returns to get the error number. Pass the error number to
 * slmp_get_err_msg() to lookup description message.
 *
 * \code
 *  int res = slmp_xxxxxxxx(...);
 *  if (res < 0) {
 *      int err = slmp_get_errno();
 *      const char* msg = slmp_get_err_msg(err);
 *      fprintf(stderr, "[ERROR] %d : %s\n", err, msg);
 *  }
 * \endcode
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 */

#ifndef __SLMPERR_H__
#define __SLMPERR_H__

#include "slmpapi.h"

/**
 * \name Error Code
 * @{
 */
#define SLMP_ERROR_SUCCESS                              0

#define SLMP_ERROR_OUT_OF_MEMORY                        -1
#define SLMP_ERROR_INVALID_ARGUMENTS                    -2
#define SLMP_ERROR_BUFFER_TOO_SHORT                     -3
#define SLMP_ERROR_MODULE_INIT_FAILED                   -4
#define SLMP_ERROR_NOT_INITIALIZED                      -5
#define SLMP_ERROR_PKTIO_CONTEXT_CORRUPTED              -6
#define SLMP_ERROR_OPERATION_FAILED                     -7
#define SLMP_ERROR_TIMEOUT                              -8
#define SLMP_ERROR_BAD_FTYPE                            -9
#define SLMP_ERROR_BAD_STREAM_TYPE                      -10
#define SLMP_ERROR_BAD_FRAME_PACKET                     -11
#define SLMP_ERROR_RESOURCE_IS_BUSY                     -12
#define SLMP_ERROR_DATA_NOT_YET_AVAILABLE               -13
#define SLMP_ERROR_OPERATION_NOT_SUPPORTED              -14
#define SLMP_ERROR_BAD_ADDRESS_WIDTH                    -15
#define SLMP_ERROR_INCORRECT_SIZE                       -16
#define SLMP_ERROR_INVALID_POINTER                      -17
#define SLMP_ERROR_INCONSISTENT_FRAME_TYPES             -18
#define SLMP_ERROR_RUN_OUT_OF_INTERNAL_BUFFER           -19
#define SLMP_ERROR_DATA_TOO_LARGE                       -20

#define SLMP_ERROR_SOCKET_CREATION_FAILED               -100
#define SLMP_ERROR_SET_OPTIONS_FAILED                   -101
#define SLMP_ERROR_BIND_FAILED                          -102
#define SLMP_ERROR_LISTEN_FAILED                        -103
#define SLMP_ERROR_ADDRESS_NOT_AVAILABLE                -104
#define SLMP_ERROR_NO_CONNECTION                        -105
#define SLMP_ERROR_CONNECT_FAILED                       -106
#define SLMP_ERROR_SOCKET_ERROR                         -107
#define SLMP_ERROR_STILL_CONNECTED                      -108
#define SLMP_ERROR_NOT_OPENED                           -109
#define SLMP_ERROR_ACCEPT_FAILED                        -110
#define SLMP_ERROR_ALREADY_OPEN                         -111
#define SLMP_ERROR_CONNECTION_CLOSED                    -112

#define SLMP_ERROR_STILL_RUNNING                        -200
#define SLMP_ERROR_NOT_RUNNING                          -201
#define SLMP_ERROR_INITIALIZATION_FAILED                -202

#define SLMP_ERROR_INVALID_POINTERS     SLMP_ERROR_INVALID_POINTER

/** @} */


#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Get error number dedicated for the caller thread.
 *
 * \return Error number.
 */
SLMPAPI int SLMPCALL slmp_get_errno();

/**
 * \brief Get error number dedicated for the caller thread.
 *
 * This function is used internally at most of the time.
 *
 * \param[in] err Error number.
 */
SLMPAPI void SLMPCALL slmp_set_errno(int err);

/**
 * \brief Get description of the error number.
 *
 * \param[in] err Error number.
 *
 * \return Description of error number `err`.
 */
SLMPAPI const char* SLMPCALL slmp_get_err_msg(int err);

/**
 * \brief Get description of an SLMP end-code.
 *
 * \param[in] endcode End code.
 *
 * \return Description of the specified SLMP end-code.
 */
SLMPAPI const char* SLMPCALL slmp_get_endcode_msg(int endcode);

#ifdef __cplusplus
}
#endif

#endif /* __SLMPERR_H__ */
