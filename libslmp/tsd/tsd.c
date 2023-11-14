#include "tsd.h"


#if defined(ENABLE_TSD) && defined(_WIN32)

int tsd_alloc(tsd_key_t* key)
{
    *key = TlsAlloc();
    return (*key ? 0 : -1);
}

int tsd_set(tsd_key_t key, void *value)
{
    BOOL bOk = TlsSetValue(key, value);
    return (bOk ? 0 : -1);
}

void* tsd_get(tsd_key_t key)
{
    return TlsGetValue(key);
}

int tsd_free(tsd_key_t key)
{
    BOOL bOk = TlsFree(key);
    return (bOk ? 0 : -1);
}

#elif defined(ENABLE_TSD) && defined(HAVE_PTHREADS)

int tsd_alloc(tsd_key_t* key)
{
    return pthread_key_create(key, NULL);
}

int tsd_set(tsd_key_t key, void *value)
{
    return pthread_setspecific(key, value);
}

void* tsd_get(tsd_key_t key)
{
    return pthread_getspecific(key);
}

int tsd_free(tsd_key_t key)
{
    return pthread_key_delete(key);
}

#else

#if defined(ENABLE_TSD)
    #pragma message("WARNING: TSD is not supported.")
#endif

int tsd_alloc(tsd_key_t* key)
{
    *key = (tsd_key_t)malloc(sizeof(void*));
    memset(*key, 0, sizeof(tsd_key_t));

    return (*key ? 0 : -1);
}

int tsd_set(tsd_key_t key, void *value)
{
    if (key == NULL) {
        return -1;
    }

    *key = value;
    return 0;
}

void* tsd_get(tsd_key_t key)
{
    if (key == NULL) {
        return NULL;
    }

    return *key;
}

int tsd_free(tsd_key_t key)
{
    if (key == NULL) {
        return -1;
    }

    free(key);
    return 0;
}

#endif

