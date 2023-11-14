/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#ifndef __SLMP_INTL_H__
#define __SLMP_INTL_H__

#include <stdint.h>
#include <sys/types.h>

#include "config.h"

#ifndef HAVE_STRLCPY
size_t strlcpy(char *dest, const char *src, size_t dest_size);
#else
#include <string.h>
#endif

typedef struct err_msg_desc {
    int err;
    const char *msg;
} err_msg_desc_t;

uint64_t get_current_timestamp();
void milli_sleep(int millis);

#endif /* __SLMP_INTL_H__ */
