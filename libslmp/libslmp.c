/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include "slmp/slmpinit.h"
#include "slmp/slmperr.h"

#include "slmp_intl.h"
#include "glthread/lock.h"
#include "tsd/tsd.h"
#include "memory/memory_intl.h"

static const char version[] = LIBSLMP_VERSION;

gl_lock_define_initialized(static, init_lock);
static unsigned int init_count = 0;
static int global_init_ok = 0;
static tsd_key_t errno_key;


SLMPAPI int SLMPCALL slmp_init()
{
    int ret = 0;

    gl_lock_lock(init_lock);

    if (!global_init_ok) {
        if (tsd_alloc(&errno_key) != 0) {
            ret = -1;
            goto _quit;
        }

        if (mem_init() != 0) {
            ret = -1;
            goto _quit;
        }

        global_init_ok = 1;
    }

    if (global_init_ok) {
        if (mem_init_per_thread() != 0) {
            ret = -1;
            goto _quit;
        }

        ++init_count;
    }

_quit:
    gl_lock_unlock(init_lock);
    return ret;
}

SLMPAPI int SLMPCALL slmp_uninit()
{
    gl_lock_lock(init_lock);

    if (!global_init_ok) {
        goto _quit;
    }
    else {
        if (init_count == 0) {
            goto _quit;
        }
        else {
            --init_count;

            if (init_count != 0) {
                mem_uninit_per_thread();
            }
            else {
                mem_uninit_per_thread();
                mem_uninit();
                tsd_free(errno_key);
                global_init_ok = 0;
            }
        }
    }

_quit:
    gl_lock_unlock(init_lock);
    return 0;
}

SLMPAPI int SLMPCALL slmp_get_errno()
{
    return (int)((intptr_t)tsd_get(errno_key));
}

SLMPAPI void SLMPCALL slmp_set_errno(int err)
{
    tsd_set(errno_key, (void*)((intptr_t)err));
}

SLMPAPI const char* SLMPCALL slmp_get_err_msg(int err)
{
    extern const err_msg_desc_t err_msg[];
    err_msg_desc_t const *desc = &err_msg[0];
    
    do {
        if (desc->err == err) {
            return desc->msg;
        }

        ++desc;
    } while (desc->msg != NULL);

    return "Unknown error.";
}

SLMPAPI const char* SLMPCALL slmp_get_endcode_msg(int endcode)
{
    extern const err_msg_desc_t endcode_msg[];
    err_msg_desc_t const *desc = &endcode_msg[0];
    
    do {
        if (desc->err == endcode) {
            return desc->msg;
        }

        ++desc;
    } while (desc->msg != NULL);

    return "Unknown error.";
}

#if defined(_WIN32)

#include <windows.h>

BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD dwReason, LPVOID lpvReserved)
{
    BOOL bRet = TRUE;

    UNREFERENCED_PARAMETER(hInstDll);
    UNREFERENCED_PARAMETER(lpvReserved);

    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
        if (slmp_init() != 0) {
            bRet = FALSE;
        }
        break;
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        slmp_uninit();
        break;    
    default:
        break;
    }

    return bRet;
}

uint64_t get_current_timestamp()
{
    FILETIME ft;
    uint64_t t;
    const uint64_t delta = 11644473600000;

    /* ft contains a 64-bit value representing the number of
     * 100-nanosecond intervals since January 1, 1601 (UTC).
     */
    GetSystemTimeAsFileTime(&ft);

    t = ft.dwHighDateTime;
    t = t << 32;
    t |= ft.dwLowDateTime;
    
    t /= 10000;            
    t -= delta; 

    return t;
}

void milli_sleep(int millis)
{
    Sleep((DWORD)millis);
}

#elif defined(__GNUC__)

#include <signal.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

void __attribute__ ((constructor)) libslmp_load()
{
    if (slmp_init() != 0) {
        raise(SIGABRT);
    }
}

void __attribute__ ((destructor)) libslmp_unload()
{
    if (slmp_uninit() != 0) {
        raise(SIGABRT);
    }
}

uint64_t get_current_timestamp()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)(tv.tv_sec * 1000) + (uint64_t)(tv.tv_usec / 1000);
}

void milli_sleep(int millis)
{
    struct timespec req_time, remaining;
    int res;

    req_time.tv_sec = millis / 1000;
    req_time.tv_nsec = (millis - 1000 * req_time.tv_sec) * 1000000;
    for (;;) {
        res = nanosleep(&req_time, &remaining);
        if (res == 0) {
            break;
        }

        if (errno == EINTR) {
            memcpy(&req_time, &remaining, sizeof(struct timespec));
        }
        else {
            break;
        }
    }
}

#endif
