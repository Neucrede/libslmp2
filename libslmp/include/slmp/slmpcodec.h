/**
 * \file slmpcodec.h
 *
 * \brief Frame and command encoding / decoding functions.
 *
 * For general description about command codec functions, refer to 
 * \ref cmdcodec.h "command codec" .
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 */

#ifndef __SLMPCODEC_H__
#define __SLMPCODEC_H__

#include <stdint.h>
#include <sys/types.h>
#include "slmpapi.h"
#include "slmpframe.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Encode a frame into a stream.
 *
 * \param[in] frame Pointer to an `slmp_frame_t` struct.
 * \param[in] stream Pointer to the stream buffer. If it is setted to NULL,
 * no actual encoding will be performed except for returning the minimum byte
 * length required for the stream buffer.
 * \param[in] type Type of the stream. `SLMP_BINARY_STREAM`
 * for binary stream or `SLMP_ASCII_STREAM` for ASCII stream.
 *
 * \return If the function succeeds, it returns the length of the stream. 
 * If the function fails, the function returns a value of zero. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI size_t SLMPCALL slmp_encode_frame(
    slmp_frame_t *frame, uint8_t *stream, int type);

/**
 * \brief Decode a stream to build a frame.
 *
 * \param[in] stream Packet stream.
 * \param[in] len Length of the stream.
 * \param[in] type Type of the stream. `SLMP_BINARY_STREAM`
 * for binary stream or `SLMP_ASCII_STREAM` for ASCII stream.
 * \param[out] len_remains Optional. Indicates number of bytes left unprocessed
 * in last function call.
 *
 * \return If the function succeeds, it returns the pointer to the decoded frame. 
 * If the function fails, the function returns a value of NULL. Call
 * slmp_get_errno() to get the error number.
 *
 * \remarks Free returned frame pointer by calling slmp_free()
 * after use.
 *
 */
SLMPAPI slmp_frame_t* SLMPCALL slmp_decode_frame(
    uint8_t *stream, size_t len, int type, size_t *len_remains);

#ifdef __cplusplus
}
#endif

#include "codec/cmdcodec.h"

#endif /* __SLMPCODEC_H__ */

