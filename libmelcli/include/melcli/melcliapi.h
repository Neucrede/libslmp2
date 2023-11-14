/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#ifndef __MELCLIAPI_H__
#define __MELCLIAPI_H__

#ifndef MELCLIAPI
    #if defined(_WIN32) /* && defined(MSVC) */
        #ifdef LIBMELCLI_EXPORTS
            #define MELCLIAPI __declspec(dllexport)
        #else
            #define MELCLIAPI __declspec(dllimport)
        #endif
    #else
        #ifndef __stdcall
            #define __stdcall
        #endif

        #define MELCLIAPI
        #define MELCLICALL
        #define CDECLCALL
    #endif
#endif


#if defined(_WIN32)
    #if defined(_MSC_VER)
        #define MELCLICALL __stdcall
        #define CDECLCALL __cdecl
    #elif defined(__MINGW32__)
        #define MELCLICALL __attribute__ ((__stdcall__))
        #define CDECLCALL __attribute__ ((__cdecl__))
    #else
        #define MELCLICALL
        #define CDECLCALL
    #endif
#endif


#endif /* __MELCLIAPI_H__ */
