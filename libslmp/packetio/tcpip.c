/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <assert.h>

#include "slmp/slmpdef.h"
#include "slmp/slmperr.h"
#include "slmp/packetio/tcpip.h"

#include "../slmp_intl.h"
#include "tcpip_priv.h"


static int _init(pktio_t *pktio);
static int _open(pktio_t *pktio);
static int _close(pktio_t *pktio);
static int _disconnect(pktio_t *pktio);
static int _accept(pktio_t *pktio);
static size_t _send(pktio_t *pktio, void* buf, size_t len);
static size_t _recv(pktio_t *pktio, void* buf, size_t len, int timeout);
static void _discard(pktio_t *pktio);
static void _free(pktio_t *pktio);

static pktio_backend_t backend = {
    _init,
    _open,
    _close,
    _disconnect,
    _accept,
    _send,
    _recv,
    _discard,
    _free
};

/* **************************************************************************/

SLMPAPI slmp_pktio_t* SLMPCALL slmp_pktio_new_tcpip(
    int role, const char *ipaddr, int port)
{
    slmp_pktio_t *pktio = NULL;
    _ctx_t *ctx = NULL;

    assert((role == SLMP_PKTIO_CLIENT) || (role == SLMP_PKTIO_SERVER));
    if (!((role == SLMP_PKTIO_CLIENT) || (role == SLMP_PKTIO_SERVER))) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return NULL;
    }

    assert(ipaddr != NULL);
    if (ipaddr == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return NULL;
    }

    assert((port > 0) && (port <= 65535));
    if ((port < 0) || (port > 65535)) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return NULL;
    }

    pktio = (slmp_pktio_t*)(calloc(1, sizeof(slmp_pktio_t)));
    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    ctx = (_ctx_t*)(calloc(1, sizeof(_ctx_t)));
    assert(ctx != NULL);
    if (ctx == NULL) {
        free(pktio);
        slmp_set_errno(SLMP_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    strlcpy(ctx->ipaddr, ipaddr, sizeof(ctx->ipaddr));
    strlcpy(ctx->client_addr, "0.0.0.0", 15);
    ctx->port = port;
    ctx->role = role;
    ctx->backlog = TCPIP_PKTIO_DEFAULT_BACKLOG;
    ctx->conn_timeout = TCPIP_PKTIO_DEFAULT_CONN_TIMEOUT;
    ctx->accept_timeout = TCPIP_PKTIO_DEFAULT_ACCEPT_TIMEOUT;
    ctx->recv_timeout = TCPIP_PKTIO_DEFAULT_RECV_TIMEOUT;
    
    pktio->fd = -1;
    pktio->fd2 = -1;
    pktio->type = SLMP_PKTIO_TCPIP;
    pktio->echo = 0;
    pktio->backend = &backend;
    pktio->backend_ctx = ctx;
    pktio->dbgprint = &printf;

#if defined(SIGPIPE) && (!defined(MSG_NOSIGNAL) || (MSG_NOSIGNAL == 0))
    /*
     * POSIX
     * 
     * Ignore SIGPIPE caused by trying to write to an TCP socket when
     * the connection is closed by peer.
     */
    signal(SIGPIPE, SIG_IGN);
#endif

    return pktio;
}

static int get_ctx(slmp_pktio_t *pktio, _ctx_t **ppctx)
{
    _ctx_t *pctx;

    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }
    
    assert(pktio->type == SLMP_PKTIO_TCPIP);
    if (pktio->type != SLMP_PKTIO_TCPIP) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }

    pctx = (_ctx_t*)(pktio->backend_ctx);
    assert(pctx != NULL);
    if (pctx == NULL) {
        slmp_set_errno(SLMP_ERROR_NOT_INITIALIZED);
        *ppctx = NULL;
        return -1;
    }

    *ppctx = pctx;
    return 0;
}

SLMPAPI int SLMPCALL slmp_pktio_tcpip_set_client_addr(
    slmp_pktio_t *pktio, const char *client_addr)
{
    _ctx_t *ctx;
    int ret;
    
    ret = get_ctx(pktio, &ctx);
    if (ret != 0) {
        return ret;
    }
    
    strlcpy(
        ctx->client_addr,
        (client_addr != NULL) ? client_addr : "0.0.0.0",
        15
    );
    
    return 0;
}

SLMPAPI int SLMPCALL slmp_pktio_tcpip_set_conn_timeout(
    slmp_pktio_t *pktio, int sec)
{
    _ctx_t *ctx;
    int ret;
    
    ret = get_ctx(pktio, &ctx);
    if (ret != 0) {
        return ret;
    }

    ctx->conn_timeout = sec;
    return 0;
}

SLMPAPI int SLMPCALL slmp_pktio_tcpip_set_accept_timeout(
    slmp_pktio_t *pktio, int sec)
{
    _ctx_t *ctx;
    int ret;
    
    ret = get_ctx(pktio, &ctx);
    if (ret != 0) {
        return ret;
    }

    ctx->accept_timeout = sec;
    return 0;
}

SLMPAPI int SLMPCALL slmp_pktio_tcpip_set_recv_timeout(
    slmp_pktio_t *pktio, int sec)
{
    _ctx_t *ctx;
    int ret;
    
    ret = get_ctx(pktio, &ctx);
    if (ret != 0) {
        return ret;
    }

    ctx->recv_timeout = sec;
    return 0;
}

/* **************************************************************************/

static int _init(pktio_t *pktio)
{
#if defined(_WIN32)
    WSADATA wsaData;    
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        slmp_set_errno(SLMP_ERROR_MODULE_INIT_FAILED);
        return -1;
    }
#endif

    (void)(pktio);

    return 0;
}

static int _open(pktio_t *pktio)
{    
    _ctx_t *ctx;
    int flags = SOCK_STREAM;
    int opt;
    int optlen = sizeof(opt);
    struct sockaddr_in addr, addr_local;
    int ret;
#ifdef _WIN32
    int wsa_err;
#endif

#ifndef _WIN32
    uint64_t ts0 = get_current_timestamp();
    uint64_t ts;
#endif

    assert(pktio->type == SLMP_PKTIO_TCPIP);
    if (pktio->type != SLMP_PKTIO_TCPIP) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }

    ctx = (_ctx_t*)(pktio->backend_ctx);
    assert(ctx != NULL);
    if (ctx == NULL) {
        slmp_set_errno(SLMP_ERROR_NOT_INITIALIZED);
        return -1;
    }

    if (pktio->fd >= 0) {
        slmp_set_errno(SLMP_ERROR_ALREADY_OPEN);
        return -1;
    }

    /* Create a TCP socket. */
#ifdef SOCK_CLOEXEC
    /* 
     * Close socket created by parent process after a forked child calls
     * exec() thus preventing unwanted port occupation.
     */
    flags |= SOCK_CLOEXEC;
#endif

#ifdef SOCK_NONBLOCK
    flags |= SOCK_NONBLOCK;
#endif

#ifndef _WIN32
__try_again:
#endif
    pktio->fd = (int)socket(PF_INET, flags, IPPROTO_TCP);
    if (pktio->fd < 0) {
        slmp_set_errno(SLMP_ERROR_SOCKET_CREATION_FAILED);
        return -1;
    }

    /* Try to disable the Nagle algorithm. */
    opt = 1;
    setsockopt(pktio->fd, IPPROTO_TCP, TCP_NODELAY, (const char*)(&opt),
        sizeof(opt));

    /* Enable non-blocking mode. */
#if !defined(SOCK_NONBLOCK) && defined(FIONBIO)
#if defined(_WIN32)
    {
        u_long ulopt = 1;
        ioctlsocket(pktio->fd, FIONBIO, &ulopt);
    }
#else
    opt = 1;
    ioctl(pktio->fd, FIONBIO, &opt);
#endif
#endif
    
    /* Initialize sockaddr struct. */
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(ctx->port);
    if (ctx->ipaddr[0] == '0') {
        if (ctx->role == SLMP_PKTIO_CLIENT) {
            /* It's not allowed to pass a zero address to connect() . */
            close(pktio->fd);
            pktio->fd = -1;
            slmp_set_errno(SLMP_ERROR_ADDRESS_NOT_AVAILABLE);
            return -1;
        }
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else {
        addr.sin_addr.s_addr = inet_addr(ctx->ipaddr);
    }
    
    switch (ctx->role) {
    case SLMP_PKTIO_CLIENT:
        memset(&addr_local, 0, sizeof(addr));
        addr_local.sin_family = AF_INET;
        addr_local.sin_port = 0;    /* any */
        addr_local.sin_addr.s_addr = inet_addr(ctx->client_addr);
        
        if (bind(pktio->fd, (struct sockaddr*)(&addr_local), sizeof(addr_local))
            < 0) 
        {
            close(pktio->fd);
            pktio->fd = -1;
            slmp_set_errno(SLMP_ERROR_BIND_FAILED);
            return -1;
        }

        ret = connect(pktio->fd, (struct sockaddr*)(&addr), sizeof(addr));
        /* 
         * Wait until the connection request is completed by checking to 
         * see if the socket is writable.
         */
#if defined(_WIN32)
        wsa_err = WSAGetLastError();
        if ((wsa_err == WSAEWOULDBLOCK) || (wsa_err == WSAEINPROGRESS))
#else
        if ((ret < 0) && (errno == EINPROGRESS))
#endif
        {
            fd_set wfds;
            struct timeval tv;
            
            FD_ZERO(&wfds);
#if defined(_WIN32) && defined(_MSC_VER)
            /* MSVC: Avoids unsigned / signed mismatch warning. */
            FD_SET((SOCKET)(pktio->fd), &wfds);
#else
            FD_SET(pktio->fd, &wfds);
#endif
            if (ctx->conn_timeout > 0) 
            {
                tv.tv_sec = ctx->conn_timeout;
                tv.tv_usec = 0;
            }
            else {
                close(pktio->fd);
                pktio->fd = -1;
                assert(0 && "Packet IO context corrupted.");
                slmp_set_errno(SLMP_ERROR_PKTIO_CONTEXT_CORRUPTED);
                return -1;
            }
            
            if (select(pktio->fd + 1, NULL, &wfds, NULL, 
                    (ctx->conn_timeout > 0) ? &tv : NULL) <= 0) 
            {
                /* Timeout or failed to connect. */
                close(pktio->fd);
                pktio->fd = -1;
                slmp_set_errno(SLMP_ERROR_TIMEOUT);
                return -1;
            }

#ifdef WIN32
            if (!FD_ISSET(pktio->fd, &wfds)) {
#else
            ret = getsockopt(pktio->fd, SOL_SOCKET, SO_ERROR, (char*)(&opt), 
                &optlen);
            if ((opt != 0) || !FD_ISSET(pktio->fd, &wfds)) {
                /* 
                 * On some platforms other than Win32, trying to connect to an 
                 * unopened port at localhost will cause `select()` to return
                 * immediately with a value of non-zero and set `wfds`. 
                 * But, fortunately `errno` will be set to ECONNREFUSED. Don't! 
                 */
                ts = get_current_timestamp();
                if ((ctx->conn_timeout > 0) 
                    && (ts < ts0 + 1000 * ctx->conn_timeout))
                {
                    milli_sleep(100);
                    close(pktio->fd);
                    goto __try_again;
                }
                else
#endif
                {
                    close(pktio->fd);
                    pktio->fd = -1;
                    slmp_set_errno(SLMP_ERROR_CONNECT_FAILED);
                    return -1;
                }
            }
        }
        strlcpy(pktio->peer_ipaddr, inet_ntoa(addr.sin_addr), 
            sizeof(pktio->peer_ipaddr));
        break;

    case SLMP_PKTIO_SERVER:
        /* Allow the socket to be bound to an address already in use. */
        opt = 1;
        if (setsockopt(pktio->fd, SOL_SOCKET, SO_REUSEADDR, (const char*)(&opt),
            sizeof(opt)) < 0)
        {
            close(pktio->fd);
            pktio->fd = -1;
            slmp_set_errno(SLMP_ERROR_SET_OPTIONS_FAILED);
            return -1;
        }

        if (bind(pktio->fd, (struct sockaddr*)(&addr), sizeof(addr)) < 0) {
            close(pktio->fd);
            pktio->fd = -1;
            slmp_set_errno(SLMP_ERROR_BIND_FAILED);
            return -1;
        }

        if (listen(pktio->fd, ctx->backlog) < 0) {
            close(pktio->fd);
            pktio->fd = -1;
            slmp_set_errno(SLMP_ERROR_LISTEN_FAILED);
            return -1;
        }
        break;

    default:
        close(pktio->fd);
        pktio->fd = -1;
        assert(0 && "Packet IO context corrupted.");
        slmp_set_errno(SLMP_ERROR_PKTIO_CONTEXT_CORRUPTED);
        return -1;
    }

    return 0;
}

static int _close(pktio_t *pktio)
{
    assert(pktio->type == SLMP_PKTIO_TCPIP);
    if (pktio->type != SLMP_PKTIO_TCPIP) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }

    if (pktio->fd >= 0) {
        close(pktio->fd);
        pktio->fd = -1;
    }

    if (pktio->fd2 >= 0) {
        shutdown(pktio->fd2, SD_RDWR);
        close(pktio->fd2);
        pktio->fd2 = -1;
    }

    pktio->peer_ipaddr[0] = 0x00;

    return 0;
}

static int _disconnect(pktio_t *pktio)
{
    assert(pktio->type == SLMP_PKTIO_TCPIP);
    if (pktio->type != SLMP_PKTIO_TCPIP) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }

    if (pktio->fd2 >= 0) {
        shutdown(pktio->fd2, SD_RDWR);
        close(pktio->fd2);
        pktio->fd2 = -1;
    }

    pktio->peer_ipaddr[0] = 0x00;

    return 0;
}


static int _accept(pktio_t *pktio)
{
    _ctx_t *ctx;
    
    fd_set rfds;
    int ret;

    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    int fd2;
    
    assert(pktio->type == SLMP_PKTIO_TCPIP);
    if (pktio->type != SLMP_PKTIO_TCPIP) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }

    ctx = (_ctx_t*)(pktio->backend_ctx);
    assert(ctx != NULL);
    if (ctx == NULL) {
        slmp_set_errno(SLMP_ERROR_NOT_INITIALIZED);
        return -1;
    }

    if (ctx->role != SLMP_PKTIO_SERVER) {
        slmp_set_errno(SLMP_ERROR_OPERATION_NOT_SUPPORTED);
        return -1;
    }

    if (pktio->fd < 0) {
        slmp_set_errno(SLMP_ERROR_NOT_OPENED);
        return -1;
    }

    FD_ZERO(&rfds);
#if defined(_WIN32) && defined(_MSC_VER)
    FD_SET((SOCKET)(pktio->fd), &rfds);
#else
    FD_SET(pktio->fd, &rfds);
#endif

    if (ctx->accept_timeout > 0) {
        struct timeval tv;
        tv.tv_sec = ctx->accept_timeout;
        tv.tv_usec = 0;
        ret = select(pktio->fd + 1, &rfds, NULL, NULL, &tv);  
    }
    else {
        ret = select(pktio->fd + 1, &rfds, NULL, NULL, NULL);
    }

    if (ret == 0) {
        slmp_set_errno(SLMP_ERROR_TIMEOUT);
        return -1;
    }
    else if (ret < 0) {
        slmp_set_errno(SLMP_ERROR_SOCKET_ERROR);
        return -1;
    }

    fd2 = (int)accept(pktio->fd, (struct sockaddr*)(&addr), &addrlen);
    if (fd2 < 0) {
        slmp_set_errno(SLMP_ERROR_ACCEPT_FAILED);
        return -1;
    }

    if (pktio->fd2 >= 0) {
        /* SLMP: At most one active connection is allowed. */
        close(fd2);
        slmp_set_errno(SLMP_ERROR_STILL_CONNECTED);
        return -1;
    }
    else {
        pktio->fd2 = fd2;
        strlcpy(pktio->peer_ipaddr, inet_ntoa(addr.sin_addr), 
            sizeof(pktio->peer_ipaddr));
    }

    return 0;
}

static size_t _send(pktio_t *pktio, void* buf, size_t len)
{
    int fd;
    _ctx_t *ctx;
    size_t bytes_sent = 0;
    int ret;
#ifdef _WIN32
    int wsa_err;
#endif

    assert(pktio->type == SLMP_PKTIO_TCPIP);
    if (pktio->type != SLMP_PKTIO_TCPIP) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    ctx = (_ctx_t*)(pktio->backend_ctx);
    assert(ctx != NULL);
    if (ctx == NULL) {
        slmp_set_errno(SLMP_ERROR_NOT_INITIALIZED);
        return 0;
    }

    assert(buf != NULL);
    if (buf == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    assert(len != 0);
    if (len == 0) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    switch (ctx->role) {
    case SLMP_PKTIO_CLIENT:
        fd = pktio->fd;
        break;
    case SLMP_PKTIO_SERVER:
        fd = pktio->fd2;
        break;
    default:
        assert(0 && "PktIO context corrupted.");
        slmp_set_errno(SLMP_ERROR_PKTIO_CONTEXT_CORRUPTED);
        return 0; 
    }

    if (fd < 0) {
        slmp_set_errno(SLMP_ERROR_NO_CONNECTION);
        return 0;
    }

    do {
        ret = send(fd, &((const char*)buf)[bytes_sent], (int)(len - bytes_sent), 
            MSG_NOSIGNAL);

        if (ret >= 0) {
            bytes_sent += ret;
        }
    } while ((ret >= 0) && (bytes_sent < len));

    if (ret >= 0) {
        slmp_set_errno(SLMP_ERROR_SUCCESS);
        return bytes_sent;
    }
    
#if defined(_WIN32)
    wsa_err = WSAGetLastError();
    if (wsa_err == WSAEWOULDBLOCK)
#else
    /*
     * Quoted from man page of send() :
     *
     * Return values EAGAIN or EWOULDBLOCK: The socket is marked 
     * nonblocking and the requested operation would block.
     * POSIX.1-2001 allows either error to be returned for this case, 
     * and does not require these constants to have the same value, 
     * so a portable application should check for both possibilities.
     */
    if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
#endif
    {
        slmp_set_errno(SLMP_ERROR_RESOURCE_IS_BUSY);
        return 0;
    }

    slmp_set_errno(SLMP_ERROR_SOCKET_ERROR);
    return 0;
}

static size_t _recv(pktio_t *pktio, void* buf, size_t len, int timeout)
{
    int *fd;
    _ctx_t *ctx;
    int ret;
    fd_set rfds;
#ifdef _WIN32
    int wsa_err = 0;
#endif

    assert(pktio->type == SLMP_PKTIO_TCPIP);
    if (pktio->type != SLMP_PKTIO_TCPIP) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    ctx = (_ctx_t*)(pktio->backend_ctx);
    assert(ctx != NULL);
    if (ctx == NULL) {
        slmp_set_errno(SLMP_ERROR_NOT_INITIALIZED);
        return 0;
    }

    assert(buf != NULL);
    if (buf == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    assert(len != 0);
    if (len == 0) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    switch (ctx->role) {
    case SLMP_PKTIO_CLIENT:
        fd = &(pktio->fd);
        break;
    case SLMP_PKTIO_SERVER:
        fd = &(pktio->fd2);
        break;
    default:
        assert(0 && "Packet IO context corrupted.");
        slmp_set_errno(SLMP_ERROR_PKTIO_CONTEXT_CORRUPTED);
        return 0;
    }

    if (*fd < 0) {
        slmp_set_errno(SLMP_ERROR_NO_CONNECTION);
        return 0;
    }

    FD_ZERO(&rfds);
#if defined(_WIN32) && defined(_MSC_VER)
    FD_SET((SOCKET)(*fd), &rfds);
#else
    FD_SET(*fd, &rfds);
#endif

    if (timeout > 0) {
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = timeout * 1000;
        ret = select(*fd + 1, &rfds, NULL, NULL, &tv);  
    }
    else if (ctx->recv_timeout > 0) {
        struct timeval tv;
        tv.tv_sec = ctx->recv_timeout;
        tv.tv_usec = 0;
        ret = select(*fd + 1, &rfds, NULL, NULL, &tv);  
    }
    else {
        ret = select(*fd + 1, &rfds, NULL, NULL, NULL);
    }

    if (ret == 0) {
        slmp_set_errno(SLMP_ERROR_TIMEOUT);
        return 0;
    }
    else if (ret < 0) {
        slmp_set_errno(SLMP_ERROR_SOCKET_ERROR);
        return 0;
    }

    ret = recv(*fd, (char*)(buf), (int)len, 0);
    if (ret > 0) {
        slmp_set_errno(SLMP_ERROR_SUCCESS);
        return (size_t)(ret);
    }
    else if (ret == 0) {
        close(*fd);
        *fd = -1;
        slmp_set_errno(SLMP_ERROR_CONNECTION_CLOSED);
        return 0;
    }
    
#if defined(_WIN32)
    wsa_err = WSAGetLastError();
    if (wsa_err == WSAEWOULDBLOCK)
#else
    if ((errno == EAGAIN) || (errno == EINPROGRESS))
#endif
    {
        slmp_set_errno(SLMP_ERROR_DATA_NOT_YET_AVAILABLE);
        return 0;
    }

    slmp_set_errno(SLMP_ERROR_SOCKET_ERROR);
    return 0;
}

static void _discard(pktio_t *pktio)
{
    _ctx_t *ctx;
    int fd;
    int ret;
    char buf[512];
    fd_set rfds;
    struct timeval tv;
    
    assert(pktio->type == SLMP_PKTIO_TCPIP);
    if (pktio->type != SLMP_PKTIO_TCPIP) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return;
    }

    ctx = (_ctx_t*)(pktio->backend_ctx);
    assert(ctx != NULL);
    if (ctx == NULL) {
        slmp_set_errno(SLMP_ERROR_NOT_INITIALIZED);
        return;
    }

    switch (ctx->role) {
    case SLMP_PKTIO_CLIENT:
        fd = pktio->fd;
        break;
    case SLMP_PKTIO_SERVER:
        fd = pktio->fd2;
        break;
    default:
        assert(0 && "Packet IO context corrupted.");
        slmp_set_errno(SLMP_ERROR_PKTIO_CONTEXT_CORRUPTED);
        return;
    }

    if (fd < 0) {
        slmp_set_errno(SLMP_ERROR_NO_CONNECTION);
        return;
    }
    
    if (ctx->recv_timeout > 0) {
        tv.tv_sec = ctx->recv_timeout;
        tv.tv_usec = 0;
    }
    else {
        tv.tv_sec = 1;
        tv.tv_usec = 0;
    }

    /* Remove all data from the input queue. */
    do {
        FD_ZERO(&rfds);
        
        #if defined(_WIN32) && defined(_MSC_VER)
            FD_SET((SOCKET)(fd), &rfds);
        #else
            FD_SET(fd, &rfds);
        #endif
        
        ret = select(fd + 1, &rfds, NULL, NULL, &tv); 
        if (ret > 0) {
            ret = recv(fd, buf, sizeof(buf), 0);
        }
        else {
            break;
        }
    } while (ret > 0);
}

static void _free(pktio_t *pktio)
{
    _ctx_t *ctx;

    assert(pktio->type == SLMP_PKTIO_TCPIP);
    if (pktio->type != SLMP_PKTIO_TCPIP) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return;
    }

    _close(pktio);

    ctx = (_ctx_t*)(pktio->backend_ctx);
    if (ctx != NULL) {
        free(ctx);
    }

    memset(pktio, 0, sizeof(pktio_t));
    free(pktio);

#if defined(_WIN32)
    WSACleanup();
#endif
}
