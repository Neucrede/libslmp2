/**
 * \file udpip.h
 *
 * \brief UDP/IP packet IO object.
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 *
 */
 
#ifndef __UDPIP_PACKETIO_H__
#define __UDPIP_PACKETIO_H__

#include "slmp/slmpapi.h"

/** Default connection timeout (sec). */
#define UDPIP_PKTIO_DEFAULT_CONN_TIMEOUT       2
/** Default receive timeout (sec). */
#define UDPIP_PKTIO_DEFAULT_RECV_TIMEOUT       2


#ifdef __cplusplus
extern "C" {
#endif

typedef struct slmp_pktio slmp_pktio_t;

/**
 * \brief Create a UDP/IP packet IO object.
 *
 * \param[in] ipaddr_bind Local IP address to which the socket is bound.
 * \param[in] port_bind Local port.
 * \param[in] ipaddr_peer Peer IP address.
 * \param[in] port_peer Peer port.
 *
 * \return If the function succeeds, it returns the pointer to the packet IO
 * object. If the function fails, the function returns a value of NULL. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI slmp_pktio_t* SLMPCALL slmp_pktio_new_udpip(
    const char *ipaddr_bind, int port_bind, 
    const char *ipaddr_peer, int port_peer);

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
SLMPAPI int SLMPCALL slmp_pktio_udpip_set_conn_timeout(
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
SLMPAPI int SLMPCALL slmp_pktio_udpip_set_recv_timeout(
    slmp_pktio_t *pktio, int sec);

/** 
 * \brief Enable or disable transmission and receipt of broadcast packets
 * on the underlying UDP/IP socket.
 *
 * \param[in] pktio Pointer to a packet IO object.
 * \param[in] enable 0 means 'no', a non-zero value means 'yes'.
 *
 * \return If the function succeeds, it returns a value of 0.
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_pktio_udpip_set_broadcast(
    slmp_pktio_t *pktio, int enable);

#ifdef __cplusplus
}
#endif

#endif /* __UDPIP_PACKETIO_H__ */
