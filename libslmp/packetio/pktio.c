/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include <stdio.h>
#include <assert.h>

#include "slmp/slmpdef.h"
#include "slmp/slmperr.h"
#include "slmp/slmppktio.h"
#include "slmp/packetio/tcpip.h"
#include "slmp/packetio/udpip.h"

#include "pktio_priv.h"

static void hex_print(const char* buf, size_t len)
{
    size_t i;

    for (i = 0; i < len; ++i) {
        printf("%02X ", buf[i] & 0xFF);
    }
    
    fputs("\n", stdout);
}

SLMPAPI void SLMPCALL slmp_pktio_free(slmp_pktio_t *pktio)
{
    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return;
    }

    pktio->backend->pfn_free(pktio);

    if (pktio->pre_recv_data != NULL) {
        free(pktio->pre_recv_data);
        pktio->pre_recv_data = NULL;
    }
}

SLMPAPI int SLMPCALL slmp_pktio_init(slmp_pktio_t *pktio)
{
    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }

    return pktio->backend->pfn_init(pktio);
}

SLMPAPI int SLMPCALL slmp_pktio_open(slmp_pktio_t *pktio)
{
    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }

    return pktio->backend->pfn_open(pktio);
}

SLMPAPI int SLMPCALL slmp_pktio_close(slmp_pktio_t *pktio)
{
    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }

    return pktio->backend->pfn_close(pktio);
}

SLMPAPI int SLMPCALL slmp_pktio_disconnect(slmp_pktio_t *pktio)
{
    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }

    return pktio->backend->pfn_disconnect(pktio);
}

SLMPAPI int SLMPCALL slmp_pktio_accept(slmp_pktio_t *pktio)
{
    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }

    return pktio->backend->pfn_accept(pktio);
}

SLMPAPI size_t SLMPCALL slmp_pktio_send(slmp_pktio_t *pktio, void *buf, 
    size_t len)
{
#ifdef __NATIVE_FUNCTION_MACRO_NOT_DEFINED__
#   ifdef __FUNCTION__
#       undef __FUNCTION__
#   endif
#   define __FUNCTION__ "slmp_pktio_send"
#endif

    size_t bytes_sent;

    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    bytes_sent = pktio->backend->pfn_send(pktio, buf, len);

    if (pktio->echo && (bytes_sent > 0)) {
        __DBGPRINT1("Sent %d bytes.", bytes_sent);
        hex_print((const char*)buf, bytes_sent);
    }

    return bytes_sent;
}

SLMPAPI size_t SLMPCALL slmp_pktio_recv(slmp_pktio_t *pktio, void *buf, size_t len, int timeout)
{
#ifdef __NATIVE_FUNCTION_MACRO_NOT_DEFINED__
#   ifdef __FUNCTION__
#       undef __FUNCTION__
#   endif
#   define __FUNCTION__ "slmp_pktio_recv"
#endif

    size_t bytes_recv;

    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    if (pktio->pre_recv_data_len > 0) {
        if (pktio->pre_recv_data_len >= len) {
            memcpy(buf, pktio->pre_recv_data, len);
            bytes_recv = len;
            
            if (pktio->pre_recv_data_len > len) {
                memmove(pktio->pre_recv_data, pktio->pre_recv_data + len,
                    pktio->pre_recv_data_len - len);
            }

            pktio->pre_recv_data_len -= len;
        }
        else {
            memcpy(buf, pktio->pre_recv_data, pktio->pre_recv_data_len);
            bytes_recv = pktio->backend->pfn_recv(
                pktio, 
                (char*)(buf) + pktio->pre_recv_data_len, 
                len - pktio->pre_recv_data_len, 
                timeout);
            
            if (bytes_recv > 0) {
                bytes_recv += pktio->pre_recv_data_len;
                pktio->pre_recv_data_len = 0;
            }
        }
    }
    else {
        bytes_recv = pktio->backend->pfn_recv(pktio, buf, len, timeout);
    }

    if (pktio->echo && (bytes_recv > 0)) {
        __DBGPRINT1("Received %d bytes.", bytes_recv);
        hex_print((const char*)buf, bytes_recv);
    }

    return bytes_recv;
}

SLMPAPI void SLMPCALL slmp_pktio_discard(slmp_pktio_t *pktio)
{
    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return;
    }

    pktio->pre_recv_data_len = 0;

    pktio->backend->pfn_discard(pktio);
}

SLMPAPI int SLMPCALL slmp_pktio_set_recv_data_preamble(slmp_pktio_t *pktio, void *data, size_t n)
{
    if ((pktio == NULL) || (data == NULL) || (n == 0)) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }

    if (pktio->pre_recv_data == NULL) {
        size_t n0 = n;
        if (n0 < 4096) {
            n0 = 4096;
        }

        if ((pktio->pre_recv_data = malloc(n0)) == NULL) {
            pktio->pre_recv_data_len = 0;
            slmp_set_errno(SLMP_ERROR_OUT_OF_MEMORY);
            return -1;
        }
    }
    else if (n > pktio->pre_recv_data_len) {
        if ((pktio->pre_recv_data = realloc(pktio->pre_recv_data, n)) == NULL) {
            pktio->pre_recv_data_len = 0;
            slmp_set_errno(SLMP_ERROR_OUT_OF_MEMORY);
            return -1;
        }
    }

    pktio->pre_recv_data_len = n;
    memcpy(pktio->pre_recv_data, data, n);

    if (pktio->echo) {
        __DBGPRINT1("Put back %u bytes.", n);
        hex_print((const char*)data, n);
    }

    slmp_set_errno(SLMP_ERROR_SUCCESS);
    return 0;
}

SLMPAPI const char* SLMPCALL slmp_pktio_get_peer_ipaddr(slmp_pktio_t *pktio)
{
    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return NULL;
    }

    return pktio->peer_ipaddr;
}

SLMPAPI void SLMPCALL slmp_pktio_set_echo(slmp_pktio_t *pktio, int echo)
{
    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return;
    }

    pktio->echo = echo;
}

SLMPAPI int SLMPCALL slmp_pktio_set_timeout(slmp_pktio_t *pktio, int type, 
    int timeout)
{
    int pktio_type;

    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }

    pktio_type = pktio->type;
    if (pktio_type == SLMP_PKTIO_TCPIP) {
        switch (type) {
            case SLMP_PKTIO_CONN_TIMEOUT:
                return slmp_pktio_tcpip_set_conn_timeout(pktio, timeout);
            case SLMP_PKTIO_RECV_TIMEOUT:
                return slmp_pktio_tcpip_set_recv_timeout(pktio, timeout);
            case SLMP_PKTIO_ACCEPT_TIMEOUT:
                return slmp_pktio_tcpip_set_accept_timeout(pktio, timeout);
            default:
                return -1;
        }
    }
    else if (pktio_type == SLMP_PKTIO_UDPIP) {
        switch (type) {
            case SLMP_PKTIO_CONN_TIMEOUT:
                return slmp_pktio_udpip_set_conn_timeout(pktio, timeout);
            case SLMP_PKTIO_RECV_TIMEOUT:
                return slmp_pktio_udpip_set_recv_timeout(pktio, timeout);
            default:
                return -1;
        }
    }
    else {
        return -1;
    }

    return 0;
}

SLMPAPI int SLMPCALL slmp_pktio_set_dbgprint_fcn(
    slmp_pktio_t *pktio, int (CDECLCALL* pfn)(const char*, ...))
{
    assert(pktio != NULL);
    if (pktio == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return -1;
    }

    if (pfn) {
        pktio->dbgprint = pfn;
    }
    else {
        pktio->dbgprint = &printf;
    }
    
    return 0;
}

