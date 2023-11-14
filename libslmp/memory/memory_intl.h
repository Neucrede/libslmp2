/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#ifndef __MEMORY_INTL_H__
#define __MEMORY_INTL_H__

#include "slmp/slmpmem.h"

typedef struct mem_fcn_table
{
    pfn_slmp_malloc_t pfn_malloc;
    pfn_slmp_calloc_t pfn_calloc;
    pfn_slmp_free_t pfn_free;
} mem_fcn_table_t;


int mem_init();
int mem_uninit();
int mem_init_per_thread();
int mem_uninit_per_thread();

#endif /* __MEMORY_INTL_H__ */
