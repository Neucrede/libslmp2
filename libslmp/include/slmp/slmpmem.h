/**
 * \file slmpmem.h
 *
 * \brief Memory management functions.
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 */

#ifndef __SLMPMEM_H__
#define __SLMPMEM_H__

#include <stdint.h>
#include <sys/types.h>

#include "slmpapi.h"

/** Memory allocator function prototype. */
typedef void* (CDECLCALL *pfn_slmp_malloc_t)(size_t /* size */);

/** Array memory allocator function prototype. */
typedef void* (CDECLCALL *pfn_slmp_calloc_t)(size_t /* num */, size_t /* size */);

/** Memory deallocator function prototype. */
typedef void (CDECLCALL *pfn_slmp_free_t)(void* /* ptr */);

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Allocate `size` bytes of memory.
 */
SLMPAPI void* SLMPCALL slmp_malloc(size_t size);

/**
 * \brief Allocate memory for an array of `num` objects of
 * size `size` and initialize all bytes to zero. 
 */
SLMPAPI void* SLMPCALL slmp_calloc(size_t num, size_t size);

/**
 * \brief Deallocate the space pointed by `p`.
 */
SLMPAPI void SLMPCALL slmp_free(void* p);

/**
 * \brief Register a new `slmp_malloc` implementation.
 *
 * \param[in] pfn Pointer to the new function. If NULL, use the default
 * implementation provided by C standard library.
 *
 * \return Previous `slmp_malloc` function.
 */
SLMPAPI pfn_slmp_malloc_t SLMPCALL slmp_register_malloc_function(
    pfn_slmp_malloc_t pfn);

/**
 * \brief Register a new `slmp_calloc` implementation.
 *
 * \param[in] pfn Pointer to the new function. If NULL, use the default
 * implementation provided by C standard library.
 *
 * \return Previous `slmp_calloc` function.
 */
SLMPAPI pfn_slmp_calloc_t SLMPCALL slmp_register_calloc_function(
    pfn_slmp_calloc_t pfn);

/**
 * \brief Register a new `slmp_free` implementation.
 *
 * \param[in] pfn Pointer to the new function. If NULL, use the default
 * implementation provided by C standard library.
 *
 * \return Previous `slmp_free` function.
 */
SLMPAPI pfn_slmp_free_t SLMPCALL slmp_register_free_function(
    pfn_slmp_free_t pfn);

#ifdef __cplusplus
}
#endif

#endif /* __SLMPMEM_H__ */
