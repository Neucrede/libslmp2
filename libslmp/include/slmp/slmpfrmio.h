/**
 * \file slmpfrmio.h
 *
 * \brief Helper routines for sending and receiving frames.
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 */

#ifndef __SLMPFRMIO_H__
#define __SLMPFRMIO_H__

#include <stdint.h>
#include <sys/types.h>
#include "slmpapi.h"
#include "slmpframe.h"
#include "slmppktio.h"

#define SLMP_FRAMEIO_MAX_RAW_DATA_LEN           1024

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Send multiple frames.
 *
 * \param[in] pktio Pointer to the packet IO object to which frames are sent.
 * \param[in] frames Array of pointers to frames to be sent.
 * \param[in] n Number of frames to send.
 * \param[in] type Stream type.
 * \param[in] interval Time interval between adjacent frames (msec).
 *
 * \return If the function succeeds, it returns the number of frames sent. 
 * If the function fails, the function returns a value of zero. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI size_t SLMPCALL slmp_send_frames(
    slmp_pktio_t *pktio, slmp_frame_t **frames, size_t n, int type, int interval);

/**
 * \brief Receive multiple frames.
 *
 * \param[in] pktio Pointer to the packet IO object from which frames are received.
 * \param[in,out] frames Array consists of pointers to frames received. The size
 * of the array should be at least `n`. 
 * \param[in] n Maximum number of frames to receive.
 * \param[out] type Stream type.
 * \param[in] timeout Timeout value in milliseconds. A value of zero indicates
 * infinite waiting.
 * 
 * \return If the function succeeds, it returns the number of frames received. 
 * If the function fails, the function returns a value of zero. Call
 * slmp_get_errno() to get the error number.
 *
 * \remarks Free each frame pointer by calling slmp_free() after use.
 */
SLMPAPI size_t SLMPCALL slmp_receive_frames(
    slmp_pktio_t *pktio, slmp_frame_t **frames, size_t n, int *type, 
    int timeout);

#ifdef __cplusplus
}
#endif

#endif /* __SLMPFRMIO_H__ */
