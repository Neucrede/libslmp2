/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */


#ifndef __SLMPAPI_H__
#define __SLMPAPI_H__

#ifndef SLMPAPI
    #if defined(_WIN32) /* && defined(MSVC) */
        #ifdef LIBSLMP_EXPORTS
            #define SLMPAPI __declspec(dllexport)
        #else
            #define SLMPAPI __declspec(dllimport)
        #endif
    #else
        #ifndef __stdcall
            #define __stdcall
        #endif

        #define SLMPAPI
        #define SLMPCALL
        #define CDECLCALL
    #endif
#endif


#if defined(_WIN32)
    #if defined(_MSC_VER)
        #define SLMPCALL __stdcall
        #define CDECLCALL __cdecl
    #elif defined(__MINGW32__)
        #define SLMPCALL __attribute__ ((__stdcall__))
        #define CDECLCALL __attribute__ ((__cdecl__))
    #else
        #define SLMPCALL
        #define CDECLCALL
    #endif
#endif


#endif /* __SLMPAPI_H__ */
