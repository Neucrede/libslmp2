/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#ifndef __MELCLI_PRIV_H__
#define __MELCLI_PRIV_H__

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <ctype.h>
#include "melcli/melcli.h"
#include "slmp/slmp.h"
#include "slmp/command/cmdcode.h"
#include "slmp/command/intmem.h"
#include "slmp/command/remctrl.h"
#include "slmp/command/rempswd.h"
#include "slmp/command/selftest.h"
#include "slmp/command/dpmem.h"
#include "slmp/command/clearerr.h"
#include "slmp/codec/cmdcodec.h"

#include "config.h"

#ifndef HAVE_STRLCPY
size_t strlcpy(char *dest, const char *src, size_t dest_size);
#endif

#define DEVICE_SM                   0x91
#define DEVICE_SD                   0xA9
#define DEVICE_X                    0x9C
#define DEVICE_Y                    0x9D
#define DEVICE_M                    0x90
#define DEVICE_L                    0x92
#define DEVICE_F                    0x93
#define DEVICE_V                    0x94
#define DEVICE_B                    0xA0
#define DEVICE_D                    0xA8
#define DEVICE_W                    0xB4
#define DEVICE_TS                   0xC1
#define DEVICE_TC                   0xC0
#define DEVICE_TN                   0xC2
#define DEVICE_LTS                  0x51
#define DEVICE_LTC                  0x50
#define DEVICE_LTN                  0x52
#define DEVICE_STS                  0xC7
#define DEVICE_STC                  0xC6
#define DEVICE_STN                  0xC8
#define DEVICE_LSTS                 0x59
#define DEVICE_LSTC                 0x58
#define DEVICE_LSTN                 0x5A
#define DEVICE_CS                   0xC4
#define DEVICE_CC                   0xC3
#define DEVICE_CN                   0xC5
#define DEVICE_LCS                  0x55
#define DEVICE_LCC                  0x54
#define DEVICE_LCN                  0x56
#define DEVICE_SB                   0xA1
#define DEVICE_SW                   0xB5
#define DEVICE_DX                   0xA2
#define DEVICE_DY                   0xA3
#define DEVICE_Z                    0xCC
#define DEVICE_LZ                   0x62
#define DEVICE_R                    0xAF
#define DEVICE_ZR                   0xB0
#define DEVICE_RD                    0x2C

#define UNIT_BIT                    1
#define UNIT_WORD                   2
#define UNIT_DWORD                  3


typedef struct melcli_ctx {
    slmp_pktio_t* pktio;
    melcli_station_t station;
    melcli_timeout_t timeout;
    int (CDECLCALL *dbgprint)(const char*, ...);
    int debug;
    uint16_t serial;
} melcli_ctx_t;

#endif /* __MELCLI_PRIV_H__ */

