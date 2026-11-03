/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include "melcli/melcli.h"

static const char version[] = LIBMELCLI_VERSION;

#if defined(_WIN32)

#include <windows.h>

#ifdef __WATCOMC__
BOOL WINAPI LibMain(HINSTANCE hInstDll, DWORD dwReason, LPVOID lpvReserved)
#else
BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD dwReason, LPVOID lpvReserved)
#endif
{
    BOOL bRet = TRUE;

    UNREFERENCED_PARAMETER(hInstDll);
    UNREFERENCED_PARAMETER(lpvReserved);

    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;    
    default:
        break;
    }

    return bRet;
}

#elif defined(__GNUC__)

#include <signal.h>

void __attribute__ ((constructor)) libmelcli_load()
{
    if (melcli_init() != 0) {
        raise(SIGABRT);
    }
}

void __attribute__ ((destructor)) libmelcli_unload()
{
    if (melcli_uninit() != 0) {
        raise(SIGABRT);
    }
}

#endif
