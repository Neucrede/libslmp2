/**
 * \file slmppktio.h
 *
 * \brief Packet IO
 *
 * PktIO provides a unified interface for accessing different underlying 
 * networking facilities.
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 */

#ifndef __SLMPPKTIO_H__
#define __SLMPPKTIO_H__

#include <stdint.h>
#include <sys/types.h>

/**
 * \name Packet IO timeout type
 * @{
 */
#define SLMP_PKTIO_CONN_TIMEOUT                 1
#define SLMP_PKTIO_RECV_TIMEOUT                 2
#define SLMP_PKTIO_ACCEPT_TIMEOUT               3
/** @} */

#ifdef __cplusplus
extern "C" {
#endif

/** \brief Packet IO object type. */
typedef struct slmp_pktio slmp_pktio_t;

/** 
 * \brief Free a packet IO object.
 *
 * \param[in] pktio Pointer to packet IO object.
 */
SLMPAPI void SLMPCALL slmp_pktio_free(slmp_pktio_t *pktio);

/** 
 * \brief Initialize a packet IO object.
 *
 * \param[in] pktio Pointer to packet IO object.
 *
 * \return If the function succeeds, it returns the value of 0. 
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_pktio_init(slmp_pktio_t *pktio);

/** 
 * \brief Open a connection associated with a packet IO object.
 * 
 * \param[in] pktio Pointer to packet IO object.
 *
 * \return If the function succeeds, it returns the value of 0. 
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_pktio_open(slmp_pktio_t *pktio);

/** 
 * \brief Close all connections.
 * 
 * \param[in] pktio Pointer to packet IO object.
 *
 * \return If the function succeeds, it returns the value of 0. 
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_pktio_close(slmp_pktio_t *pktio);

/**
 * \brief Close the accepted connection.
 *
 * \param[in] pktio Pointer to packet IO object.
 *
 * \return If the function succeeds, it returns the value of 0. 
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_pktio_disconnect(slmp_pktio_t *pktio);

/** 
 * \brief Accept a pending connection request.
 * 
 * \param[in] pktio Pointer to packet IO object.
 *
 * \return If the function succeeds, it returns the value of 0. 
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_pktio_accept(slmp_pktio_t *pktio);

/** 
 * \brief Send data.
 * 
 * \param[in] pktio Pointer to packet IO object.
 * \param[in] buf Pointer to the data to be sent.
 * \param[in] len Byte length of the data.
 *
 * \return If the function succeeds, it returns the value of 0. 
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI size_t SLMPCALL slmp_pktio_send(slmp_pktio_t *pktio, void *buf, size_t len);

/** 
 * \brief Receive data.
 * 
 * \param[in] pktio Pointer to packet IO object.
 * \param[in] buf Pointer to a pre-allocated buffer of size `len`.
 * \param[in] len Buffer size.
 * \param[in] timeout This value specifies the maximum time 
 * in milliseconds allowed to elapse while waiting for data
 * to become available for reading. If this value is smaller
 * or equal to zero, the default timeout value associated with 
 * the specified packet IO object will be used.
 *
 * \return If the function succeeds, it returns the value of 0. 
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI size_t SLMPCALL slmp_pktio_recv(slmp_pktio_t *pktio, void *buf, size_t len, 
    int timeout);

/** 
 * \brief Remove all data from input buffer.
 *
 * \param[in] pktio Pointer to packet IO object.
 */
SLMPAPI void SLMPCALL slmp_pktio_discard(slmp_pktio_t *pktio);

/**
 * \brief For TCP/IP, this function returns the IP address of the station
 * that `pktio` is connected to. For UDP/IP, this function returns the IP
 * address of the last station that sends data to `pktio` after data is
 * received.
 *
 * \param[in] pktio Pointer to packet IO object.
 *
 * \return Pointer to the IP address string.
 *
 * \remark The returned pointer is to the internal buffer and does **NOT**
 * need to be free()-ed after use.
 */
SLMPAPI const char* SLMPCALL slmp_pktio_get_peer_ipaddr(slmp_pktio_t *pktio);

/** 
 * \brief Toggle echo mode. If echo mode is enabled, data sent / received
 * will be dumped to `stdout` in hexadecimal form.
 *
 * \param[in] pktio Pointer to packet IO object.
 * \param[in] echo Specifies whether echo mode is enabled. A value of 1 indicates
 * enable. A value of 0 indicates disable.
 */
SLMPAPI void SLMPCALL slmp_pktio_set_echo(slmp_pktio_t *pktio, int echo);

/**
 * \brief Configure timeout value.
 *
 * \param[in] pktio Pointer to packet IO object.
 * \param[in] type Timeout type.
 * \param[in] timeout Timeout value.
 * 
 * \return If the function succeeds, it returns the value of 0. 
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_pktio_set_timeout(slmp_pktio_t *pktio, int type, int timeout);

/**
 * \brief Setup debug print function.
 *
 * \param[in] pktio Pointer to packet IO object.
 * \param[in] pfn Pointer to a function that performs formatted output like
 * `printf()` does.
 */
SLMPAPI int SLMPCALL slmp_pktio_set_dbgprint_fcn(
    slmp_pktio_t *pktio, int (CDECLCALL* pfn)(const char*, ...));

#ifdef __cplusplus
}
#endif

#include "packetio/tcpip.h"
#include "packetio/udpip.h"

#endif /* __SLMPPKTIO_H__ */
