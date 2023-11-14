#ifndef __TSD_H__
#define __TSD_H__

#include "config.h"

#if defined(ENABLE_TSD) && defined(_WIN32)

/* Use TLS functions shipped with Win32 API. */
#include <windows.h>
typedef DWORD tsd_key_t;

#elif defined(ENABLE_TSD) && defined(HAVE_PTHREADS)

/* Use POSIX threading library. */
#include <pthread.h>
typedef pthread_key_t tsd_key_t;

#else

/* No TSD support at all. */
#include <stdlib.h>
#include <string.h>
typedef void** tsd_key_t;

#endif


int tsd_alloc(tsd_key_t* key);
int tsd_set(tsd_key_t key, void *value);
void* tsd_get(tsd_key_t key);
int tsd_free(tsd_key_t key);


#endif /* __TSD_H__ */
