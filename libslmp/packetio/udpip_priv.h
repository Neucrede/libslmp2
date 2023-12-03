/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#ifndef __UDPIP_PRIV_H__
#define __UDPIP_PRIV_H__


#include "pktio_priv.h"

typedef struct _ctx {
    int conn_timeout;               /* connection timeout */
    int recv_timeout;               /* default recv timeout */

    struct sockaddr_in sa_bind;     /* local */
    struct sockaddr_in sa_peer;     /* remote */
} _ctx_t;


#endif /* __UDPIP_PRIV_H__ */
