/**
 * \file slmpinit.h
 *
 * \brief Library startup and cleanup functions.
 *
 * On Win32 platform, both startup and cleanup functions will be
 * automatically called by the operating system at approriate time.
 * The user need not have to call these functions explicitly.
 *
 * On other platforms, both startup and cleanup functions are
 * called by C runtime library only in the context of the thread
 * that loads the library. When using libslmp function in threads 
 * other than the thread that loads the library, function 
 * slmp_init() should be called before other libslmp supplied 
 * functions can be called. To prevent memory leaks, function 
 * slmp_uninit() should also be called before the thread entry 
 * function returns.
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 */

#ifndef __SLMPINIT_H__
#define __SLMPINIT_H__

#include "slmpapi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Initialize.
 *
 * \return 0 for success, -1 for failure.
 */
SLMPAPI int SLMPCALL slmp_init();

/**
 * \brief Uninitialize.
 *
 * \return 0 for success, -1 for failure.
 */
SLMPAPI int SLMPCALL slmp_uninit(); 

#ifdef __cplusplus
}
#endif

#endif /* __SLMPINIT_H__ */
