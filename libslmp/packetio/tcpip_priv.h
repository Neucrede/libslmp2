/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#ifndef __TCPIP_PRIV_H__
#define __TCPIP_PRIV_H__


#include "pktio_priv.h"


#define TCPIP_PKTIO_DEFAULT_BACKLOG            3

typedef struct _ctx {
    int role;

    int backlog;

    int conn_timeout;
    int accept_timeout;
    int recv_timeout;

    char ipaddr[16];
    unsigned short port;
    
    char client_addr[16];
} _ctx_t;


#endif /* __TCPIP_PRIV_H__ */
