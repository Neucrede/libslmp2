/**
 * \file tcpip.h
 *
 * \brief TCP/IP packet IO object.
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 *
 */
 
#ifndef __TCPIP_PACKETIO_H__
#define __TCPIP_PACKETIO_H__

#include "slmp/slmpapi.h"

#define TCPIP_PKTIO_DEFAULT_CONN_TIMEOUT       2
#define TCPIP_PKTIO_DEFAULT_ACCEPT_TIMEOUT     5
#define TCPIP_PKTIO_DEFAULT_RECV_TIMEOUT       2

#ifdef __cplusplus
extern "C" {
#endif

typedef struct slmp_pktio slmp_pktio_t;

/**
 * \brief Create a TCP/IP packet IO object.
 *
 * \param[in] role Specifies the role of the object. A value of 
 * `SLMP_PKTIO_SERVER` indicates a server object. A value of
 * `SLMP_PKTIO_CLIENT` indicates a client object.
 * \param[in] ipaddr If a server object is being created, this parameter is the 
 * address of the server socket. Use a value of "0.0.0.0" if explicit address
 * binding is not required. If a client object is being created, this parameter
 * indicates the address of the server to be connected to.
 * \param[in] port Port number.
 *
 * \return If the function succeeds, it returns the pointer to the packet IO
 * object. If the function fails, the function returns a value of NULL. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI slmp_pktio_t* SLMPCALL slmp_pktio_new_tcpip(
    int role, const char *ipaddr, int port);

/**
 * \brief Configure local bind address fur a client TCP/IP packet IO object.
 *
 * \param[in] pktio Pointer to a packet IO object.
 * \param[in] local_addr Local address to assign. If a NULL value is given,
 * an address of value `0.0.0.0` will be used.
 *
 * \return If the function succeeds, it returns the pointer to the packet IO
 * object. If the function fails, the function returns a value of NULL. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_pktio_tcpip_set_client_addr(
    slmp_pktio_t *pktio, const char *local_addr);

/** 
 * \brief Set connection timeout for specified packet IO object.
 *
 * \param[in] pktio Pointer to a packet IO object.
 * \param[in] sec Timeout value, in seconds. A value of 0 or 
 * negative values indicates infinite waiting until a connection 
 * has established or an error occurs.
 *
 * \return If the function succeeds, it returns a value of 0.
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_pktio_tcpip_set_conn_timeout(
    slmp_pktio_t *pktio, int sec);

/** 
 * \brief Set accept timeout for specified packet IO object.
 *
 * This function works on server objects only.
 *
 * \param[in] pktio Pointer to a packet IO object.
 * \param[in] sec Timeout value, in seconds. A value of 0 or negative
 * indicates infinite waiting until data is ready or an error occurs.
 *
 * \return If the function succeeds, it returns a value of 0.
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_pktio_tcpip_set_accept_timeout(
    slmp_pktio_t *pktio, int sec);

/** 
 * \brief Set default receive timeout for specified packet IO object.
 *
 * \param[in] pktio Pointer to a packet IO object.
 * \param[in] sec Timeout value, in seconds. A value of 0 or negative
 * indicates infinite waiting until data is ready or an error occurs.
 *
 * \return If the function succeeds, it returns a value of 0.
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_pktio_tcpip_set_recv_timeout(
    slmp_pktio_t *pktio, int sec);

#ifdef __cplusplus
}
#endif

#endif /* __TCPIP_PACKETIO_H__ */
