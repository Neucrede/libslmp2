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
    int role;               /* client / server */

    int backlog;            /* server socket backlog */

    int conn_timeout;       /* connection timeout */
    int accept_timeout;     /* accept timeout */
    int recv_timeout;       /* default recv timeout */

    char ipaddr[24];        /* client: remote ipaddr, server: bind ipaddr */
    unsigned short port;    /* port */
    
    char client_addr[24];   /* client: address to which socket binds */
} _ctx_t;


#endif /* __TCPIP_PRIV_H__ */
