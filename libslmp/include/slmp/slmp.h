/**
 * \file slmp.h
 *
 * \brief C/C++ Library for SLMP (Seamless Message Protocol)
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 */

#ifndef __SLMP_H__
#define __SLMP_H__

#include "config.h"

#include "slmpdef.h"
#include "slmpinit.h"
#include "slmperr.h"
#include "slmpmem.h"
#include "slmpframe.h"
#include "slmpcodec.h"
#include "slmppktio.h"
#include "slmpfrmio.h"
#include "slmpserver.h"

#include "command/cmdcode.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief This function returns current timestamp.
 *
 * \return Current timestamp.
 */
SLMPAPI uint64_t SLMPCALL slmp_get_current_timestamp();

/**
 * \brief Wait for specified interval.
 *
 * \param[in] ms Interval, in milliseconds.
 */
SLMPAPI void SLMPCALL slmp_milli_sleep(int ms);

#ifdef __cplusplus
}
#endif


#endif /* __SLMP_H__ */
