/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#ifndef __PKTIO_PRIV_H__
#define __PKTIO_PRIV_H__

#include <stdint.h>

#if defined(_WIN32)
    #define _WINSOCK_DEPRECATED_NO_WARNINGS
    #include <winsock2.h>
    
    #if !defined(ECONNRESET)
        #define ECONNRESET   WSAECONNRESET
    #endif
    #if !defined(ECONNREFUSED)
        #define ECONNREFUSED WSAECONNREFUSED
    #endif
    #if !defined(ETIMEDOUT)
        #define ETIMEDOUT    WSAETIMEDOUT
    #endif
    #if !defined(ENOPROTOOPT)
        #define ENOPROTOOPT  WSAENOPROTOOPT
    #endif
    #if !defined(EINPROGRESS)
        #define EINPROGRESS  WSAEINPROGRESS
    #endif
    #define close closesocket
    #define SD_RDWR SD_BOTH
#else
    #include <unistd.h>
    #include <sys/socket.h>
    #include <sys/ioctl.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <netinet/tcp.h>
    #include <arpa/inet.h>

    #ifndef SD_RDWR
        #define SD_RDWR 2
    #endif
#endif

#ifndef MSG_NOSIGNAL
    #define MSG_NOSIGNAL 0
#endif

#ifndef ___max
#define ___max(a, b)    (((a) > (b)) ? (a) : (b))
#endif

#define __DBGPRINT_FMT_STR(s)       "[DEBUG] %s(): "s"\n",__FUNCTION__

#define __DBGPRINT0(s)   \
    if (pktio->echo) { pktio->dbgprint(__DBGPRINT_FMT_STR(s)); }
    
#define __DBGPRINT1(s, x1)   \
    if (pktio->echo) { pktio->dbgprint(__DBGPRINT_FMT_STR(s), x1); }
    
#define __DBGPRINT2(s, x1, x2)   \
    if (pktio->echo) { pktio->dbgprint(__DBGPRINT_FMT_STR(s), x1, x2); }
    
#define __DBGPRINT3(s, x1, x2, x3)   \
    if (pktio->echo) { pktio->dbgprint(__DBGPRINT_FMT_STR(s), x1, x2, x3); }
    
#define __DBGPRINT4(t, s, x1, x2, x3, x4)   \
    if (pktio->echo) { pktio->dbgprint(__DBGPRINT_FMT_STR(s), x1, x2, x3, x4); }

typedef struct pktio_backend pktio_backend_t;
typedef struct slmp_pktio pktio_t;


typedef pktio_t* (*pfn_pktio_new_t)(int /* type */);
typedef int (*pfn_pktio_init_t)(pktio_t* /* pktio */);
typedef int (*pfn_pktio_open_t)(pktio_t* /* pktio */);
typedef int (*pfn_pktio_close_t)(pktio_t* /* pktio */);
typedef int (*pfn_pktio_disconnect_t)(pktio_t* /* pktio */);
typedef int (*pfn_pktio_accept_t)(pktio_t* /* pktio */);
typedef size_t (*pfn_pktio_send_t)(pktio_t* /* pktio */, void* /* buf */,
    size_t /* len */);
typedef size_t (*pfn_pktio_recv_t)(pktio_t* /* pktio */, void* /* buf */,
    size_t /* len */, int /* timeout */);
typedef void (*pfn_pktio_discard_t)(pktio_t* /* pktio */);
typedef void (*pfn_pktio_free_t)(pktio_t* /* pktio */);


struct pktio_backend {
    pfn_pktio_init_t pfn_init;
    pfn_pktio_open_t pfn_open;
    pfn_pktio_close_t pfn_close;
    pfn_pktio_disconnect_t pfn_disconnect;
    pfn_pktio_accept_t pfn_accept;
    pfn_pktio_send_t pfn_send;
    pfn_pktio_recv_t pfn_recv;
    pfn_pktio_discard_t pfn_discard;
    pfn_pktio_free_t pfn_free;
};

struct slmp_pktio {
    int type;                                       /* Implementation type */
    
    int fd;                                         /* Client / server socket */
    int fd2;                                        /* Accepted socket */
    char peer_ipaddr[24];                           /* Peer IP address */

    int echo;                               /* Whether to dump traffic data */
    int (CDECLCALL *dbgprint)(const char*, ...);    /* Debug print function */
    
    pktio_backend_t* backend;                       /* Function table */
    void* backend_ctx;                              /* Impl specific context */
};


#endif /* __PKTIO_PRIV_H__ */
