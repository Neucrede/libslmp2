/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include <stdlib.h>
#include <assert.h>

#include "memory_intl.h"
#include "../tsd/tsd.h"


static tsd_key_t fcn_table_key;


int mem_init()
{
    return tsd_alloc(&fcn_table_key);
}

int mem_uninit()
{
    return tsd_free(fcn_table_key);
}

int mem_init_per_thread()
{
    mem_fcn_table_t *fcntab = tsd_get(fcn_table_key);
    if (fcntab != NULL) {
        /* Already initialized by the caller thread. */
        return 0;
    }

    fcntab = calloc(1, sizeof(mem_fcn_table_t));
    assert(fcntab != NULL);
    
    if (fcntab == NULL) {
        return -1;
    }

    /* Initialize with C standard library implementations. */
    fcntab->pfn_calloc = &calloc;
    fcntab->pfn_malloc = &malloc;
    fcntab->pfn_free = &free;

    return tsd_set(fcn_table_key, fcntab);
}

int mem_uninit_per_thread()
{
    mem_fcn_table_t *fcntab = tsd_get(fcn_table_key);
    if (fcntab == NULL) {
        /* Not initialized or already uninitialized. */
        return 0;
    }

    free(fcntab);
    return tsd_set(fcn_table_key, NULL);
}

SLMPAPI void* SLMPCALL slmp_malloc(size_t size)
{
    mem_fcn_table_t *fcntab = tsd_get(fcn_table_key);
    assert(fcntab != NULL);
    if (fcntab == NULL) {
        return NULL;
    }

    return fcntab->pfn_malloc(size);
}

SLMPAPI void* SLMPCALL slmp_calloc(size_t num, size_t size)
{
    mem_fcn_table_t *fcntab = tsd_get(fcn_table_key);
    assert(fcntab != NULL);
    if (fcntab == NULL) {
        return NULL;
    }

    return fcntab->pfn_calloc(num, size);
}

SLMPAPI void SLMPCALL slmp_free(void* p)
{
    mem_fcn_table_t *fcntab = tsd_get(fcn_table_key);
    assert(fcntab != NULL);
    if (fcntab == NULL) {
        return;
    }

    fcntab->pfn_free(p);
}


#define REGISTER_FUNCTION(_name, _pfn)                                      \
    pfn_slmp_##_name##_t oldpfn;                                            \
    mem_fcn_table_t *fcntab = tsd_get(fcn_table_key);                       \
    assert(fcntab != NULL);                                                 \
    if (fcntab == NULL) {                                                   \
        return NULL;                                                        \
    }                                                                       \
    oldpfn = fcntab->pfn_##_name ;                                          \
    if (_pfn != NULL) {                                                     \
        fcntab->pfn_##_name = _pfn;                                         \
    }                                                                       \
    else {                                                                  \
        fcntab->pfn_##_name = _name;                                        \
    }                                                                       \
    return oldpfn;                                                          \


SLMPAPI pfn_slmp_malloc_t SLMPCALL
slmp_register_malloc_function(pfn_slmp_malloc_t pfn)
{
    REGISTER_FUNCTION(malloc, pfn);
}

SLMPAPI pfn_slmp_calloc_t SLMPCALL
slmp_register_calloc_function(pfn_slmp_calloc_t pfn)
{
    REGISTER_FUNCTION(calloc, pfn);
}

SLMPAPI pfn_slmp_free_t SLMPCALL
slmp_register_free_function(pfn_slmp_free_t pfn)
{
    REGISTER_FUNCTION(free, pfn);
}
