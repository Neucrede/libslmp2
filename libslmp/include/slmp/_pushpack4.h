/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#ifndef __PUSHPACK4__
#define __PUSHPACK4__


#pragma pack(push)

#if defined(_MSC_VER)
    #pragma warning(disable:4103)

    #if defined(_M_AMD64) || defined(_M_X64) || defined(_M_IX64)
        #pragma pack(8)
    #elif defined(_M_IX86)
        #pragma pack(4)
    #else
        #pragma message("WARNING: Address width is unknown for target platform. Assuming 32 bit.")
        #pragma pack(4)
    #endif
#elif defined(__GNUC__)
    #if defined(__amd64__) || defined(__x86_64__) || defined(__ia64__)
        #pragma pack(8)
    #elif defined(__i386__)
        #pragma pack(4)
    #else
        #pragma message("WARNING: Address width is unknown for target platform. Assuming 32 bit.")
        #pragma pack(4)
    #endif
#else
    #pragma message("WARNING: Address width is unknown for target platform. Assuming 32 bit.")
    #pragma pack(4)
#endif

#endif /* __PUSHPACK4__ */