/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <assert.h>

#include "slmp/slmpdef.h"
#include "slmp/slmperr.h"
#include "slmp/packetio/udpip.h"

#include "../slmp_intl.h"
#include "udpip_priv.h"

static int _init(pktio_t *pktio);
static int _open(pktio_t *pktio);
static int _close(pktio_t *pktio);
static int _accept(pktio_t *pktio);
static size_t _send(pktio_t *pktio, void* buf, size_t len);
static size_t _recv(pktio_t *pktio, void* buf, size_t len, int timeout);
static void _discard(pktio_t *pktio);
static void _free(pktio_t *pktio);

static pktio_backend_t backend = {
    _init,
    _open,
    _close,
    _accept,
    _send,
    _recv,
    _discard,
    _free
};

/* **************************************************************************/

SLMPAPI slmp_pktio_t* SLMPCALL slmp_pktio_new_udpip(
    const char *ipaddr_bind, int port_bind, 
    const char *ipaddr_peer, int port_peer)
{
    slmp_pktio_t *pktio = NULL;
    _ctx_t *ctx = NULL;

    assert(ipaddr_peer != NULL);
    if (ipaddr_peer == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return NULL;
    }

    assert((port_bind >= 0) && (port_bind <= 65535)
        && (port_peer > 0) && (port_peer <= 65535));
    if ((port_bind < 0) || (port_bind > 65535)
        || (port_peer < 0) || (port_peer > 65535)) {
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

    ctx->sa_bind.sin_family = AF_INET;
    ctx->sa_bind.sin_port = htons((u_short)port_bind);
    if (ipaddr_bind != NULL) {
        if (ipaddr_bind[0] == '0') {
            ctx->sa_bind.sin_addr.s_addr = htonl(INADDR_ANY);
        }
        else {
            ctx->sa_bind.sin_addr.s_addr = inet_addr(ipaddr_bind);
        }
    }
    else {
        ctx->sa_bind.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    ctx->sa_peer.sin_family = AF_INET;
    ctx->sa_peer.sin_port = htons((u_short)port_peer);
    if (ipaddr_peer[0] == '0') {
        free(pktio);
        slmp_set_errno(SLMP_ERROR_ADDRESS_NOT_AVAILABLE);
        return NULL;
    }
    else {
        ctx->sa_peer.sin_addr.s_addr = inet_addr(ipaddr_peer);
    }


    ctx->conn_timeout = UDPIP_PKTIO_DEFAULT_CONN_TIMEOUT;
    ctx->recv_timeout = UDPIP_PKTIO_DEFAULT_RECV_TIMEOUT;
    
    pktio->fd = -1;
    pktio->fd2 = -1;
    pktio->echo = 0;
    pktio->type = SLMP_PKTIO_UDPIP;
    pktio->backend = &backend;
    pktio->backend_ctx = ctx;

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
    
    assert(pktio->type == SLMP_PKTIO_UDPIP);
    if (pktio->type != SLMP_PKTIO_UDPIP) {
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

SLMPAPI int SLMPCALL slmp_pktio_udpip_set_conn_timeout(
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

SLMPAPI int SLMPCALL slmp_pktio_udpip_set_recv_timeout(
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

SLMPAPI int SLMPCALL slmp_pktio_udpip_set_broadcast(
    slmp_pktio_t *pktio, int enable)
{
    _ctx_t *ctx;
    int ret;
    int opt = (enable != 0) ? 1 : 0;

    ret = get_ctx(pktio, &ctx);
    if (ret != 0) {
        return ret;
    }

    if (pktio->fd < 0) {
        slmp_set_errno(SLMP_ERROR_NOT_OPENED);
        return -1;
    }

    if (setsockopt(pktio->fd, SOL_SOCKET, SO_BROADCAST, (const char*)(&opt), 
        sizeof(int)) != 0)
    {
        slmp_set_errno(SLMP_ERROR_SET_OPTIONS_FAILED);
        return -1;
    }

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
    int flags = SOCK_DGRAM;
    int opt;
    int ret;
#ifdef _WIN32
    int wsa_err;
#endif

    assert(pktio->type == SLMP_PKTIO_UDPIP);
    if (pktio->type != SLMP_PKTIO_UDPIP) {
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

    /* Create a UDP socket. */
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

    pktio->fd = (int)socket(PF_INET, flags, IPPROTO_UDP);
    if (pktio->fd < 0) {
        slmp_set_errno(SLMP_ERROR_SOCKET_CREATION_FAILED);
        return -1;
    }

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

    if (bind(pktio->fd, (struct sockaddr*)(&ctx->sa_bind), 
        sizeof(struct sockaddr_in)) < 0) 
    {
        close(pktio->fd);
        pktio->fd = -1;
        slmp_set_errno(SLMP_ERROR_BIND_FAILED);
        return -1;
    }

    /* Setup default destination address. */
    ret = connect(pktio->fd, (struct sockaddr*)&(ctx->sa_peer), 
        sizeof(struct sockaddr_in));
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
        int opt;
        int optlen = sizeof(opt);
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

        ret = getsockopt(pktio->fd, SOL_SOCKET, SO_ERROR, (char*)(&opt), 
            &optlen);
        if (!((ret == 0) && (opt == 0))) {
            close(pktio->fd);
            pktio->fd = -1;
            slmp_set_errno(SLMP_ERROR_CONNECT_FAILED);
            return -1;
        }
    }

    return 0;
}

static int _close(pktio_t *pktio)
{
    assert(pktio->type == SLMP_PKTIO_UDPIP);
    if (pktio->type != SLMP_PKTIO_UDPIP) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }

    close(pktio->fd);
    pktio->fd = -1;

    return 0;
}

static int _accept(pktio_t *pktio)
{
    slmp_set_errno(SLMP_ERROR_OPERATION_NOT_SUPPORTED);
    return -1;
}

static size_t _send(pktio_t *pktio, void* buf, size_t len)
{
    int fd = pktio->fd;
    _ctx_t *ctx;
    int ret;
#ifdef _WIN32
    int wsa_err;
#endif

    assert(pktio->type == SLMP_PKTIO_UDPIP);
    if (pktio->type != SLMP_PKTIO_UDPIP) {
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

    if (fd < 0) {
        slmp_set_errno(SLMP_ERROR_NO_CONNECTION);
        return 0;
    }

    ret = send(fd, (const char*)buf, (int)len, MSG_NOSIGNAL);
    if (ret >= 0) {
        slmp_set_errno(SLMP_ERROR_SUCCESS);
        return (size_t)(ret);
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
    int fd = pktio->fd;
    _ctx_t *ctx;
    int ret;
    fd_set rfds;
#ifdef _WIN32
    int wsa_err;
#endif

    assert(pktio->type == SLMP_PKTIO_UDPIP);
    if (pktio->type != SLMP_PKTIO_UDPIP) {
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

    if (fd < 0) {
        slmp_set_errno(SLMP_ERROR_NO_CONNECTION);
        return 0;
    }

    FD_ZERO(&rfds);
#if defined(_WIN32) && defined(_MSC_VER)
    FD_SET((SOCKET)(fd), &rfds);
#else
    FD_SET(fd, &rfds);
#endif

    if ((ctx->recv_timeout > 0) || (timeout > 0)) {
        struct timeval tv;
        tv.tv_sec = ___max(ctx->recv_timeout, timeout);
        tv.tv_usec = 0;
        ret = select(fd + 1, &rfds, NULL, NULL, &tv);  
    }
    else {
        ret = select(fd + 1, &rfds, NULL, NULL, NULL);
    }

    if (ret == 0) {
        slmp_set_errno(SLMP_ERROR_TIMEOUT);
        return 0;
    }
    else if (ret < 0) {
        slmp_set_errno(SLMP_ERROR_SOCKET_ERROR);
        return 0;
    }

    ret = recv(fd, (char*)(buf), (int)len, 0);
    if (ret > 0) {
        slmp_set_errno(SLMP_ERROR_SUCCESS);
        return (size_t)(ret);
    }
    else if (ret == 0) {
        close(fd);
        pktio->fd = -1;
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
#if defined(_WIN32)
    else if (wsa_err == WSAEMSGSIZE) 
#else
    else if (errno == EMSGSIZE)
#endif
    {
        slmp_set_errno(SLMP_ERROR_BUFFER_TOO_SHORT);
        return len;
    }

    slmp_set_errno(SLMP_ERROR_SOCKET_ERROR);
    return 0;
}

static void _discard(pktio_t *pktio)
{
    _ctx_t *ctx;
    int fd = pktio->fd;
    int ret;
    char buf[512];

    assert(pktio->type == SLMP_PKTIO_UDPIP);
    if (pktio->type != SLMP_PKTIO_UDPIP) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return;
    }

    ctx = (_ctx_t*)(pktio->backend_ctx);
    assert(ctx != NULL);
    if (ctx == NULL) {
        slmp_set_errno(SLMP_ERROR_NOT_INITIALIZED);
        return;
    }

    if (fd < 0) {
        slmp_set_errno(SLMP_ERROR_NO_CONNECTION);
        return;
    }

    /* Remove all data from the input queue. */
    do {
        ret = recvfrom(fd, (char*)(buf), sizeof(buf), 0, NULL, NULL);
    } while (ret > 0);
}

static void _free(pktio_t *pktio)
{
    _ctx_t *ctx;

    assert(pktio->type == SLMP_PKTIO_UDPIP);
    if (pktio->type != SLMP_PKTIO_UDPIP) {
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
