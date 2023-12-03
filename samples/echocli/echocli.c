/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "slmp/slmp.h"

#define BUFFER_SIZE         1024

static void hex_dump(void* data, int n);
static void print_errmsg();

int main(int argc, char *argv[])
{
    const int port = 8888;
    const char *ipaddr = (argc > 1) ? (argv[1]) : "127.0.0.1";
    
    int ret = 0;
    
    slmp_pktio_t *pktio = NULL;
    uint8_t buf[BUFFER_SIZE] = "Hello, world!";
    
    size_t len;
    int err;
    
    printf(
        "*************** \n"
        "  Echo Client   \n"
        "*************** \n\n"
    );
    
    /* Connect to echo server listening on port 8888. */
    pktio = slmp_pktio_new_tcpip(SLMP_PKTIO_CLIENT, ipaddr, port);
    if (!pktio) {
        printf("Failed to create pktio. ");
        print_errmsg();
        
        ret = 1;
        goto __cleanup;
    }
    
    /* Initialization. Initialize Winsock2 if running on Win32 platform. */
    slmp_pktio_init(pktio);
    
    /* Set connection timeout value to 1 second. */
    slmp_pktio_tcpip_set_conn_timeout(pktio, 1);
    
    /* Try to connect. */
    while (slmp_pktio_open(pktio) != 0) {
        printf("Failed to connect. ");
        print_errmsg();
        continue;
    }
    
    printf("Connected to %s. \n", slmp_pktio_get_peer_ipaddr(pktio));
    
    /* Bang! */
    slmp_pktio_send(pktio, buf, strlen(buf));
        
    do {
        /* Receive data from peer, */
        len = slmp_pktio_recv(pktio, buf, BUFFER_SIZE, 100);
        err = slmp_get_errno();

        if (len > 0) {
            printf("[RECV] ");
            hex_dump(buf, len);
        }
        else if (err != SLMP_ERROR_TIMEOUT) {
            print_errmsg();
            
            ret = 1;
            break;
        }
        else {
            /* No data has been received. */
            continue;
        }
        
        /* then bounce them back. */
        if (len != slmp_pktio_send(pktio, buf, len)) {
            err = slmp_get_errno();
            print_errmsg();
            
            ret = 1;
            break;
        }
        else {
            printf("[SEND] ");
            hex_dump(buf, len);
        }
    } while (   err != SLMP_ERROR_NO_CONNECTION
            &&  err != SLMP_ERROR_CONNECTION_CLOSED );
    
__cleanup:
    /* Close connections and free used resources. */
    slmp_pktio_close(pktio);
    slmp_pktio_free(pktio);
    
    return ret;
}

static void hex_dump(void* data, int n)
{
    int i;
    
    for (i = 0; i != n; ++i) {
        printf("%02X ", ((unsigned char*)(data))[i] & 0xFF);
    }
    printf("\n");
}

static void print_errmsg()
{
    int err = slmp_get_errno();
    const char* errmsg = slmp_get_err_msg(err);
    
    printf("Error (%d): %s\n", err, errmsg);
}

