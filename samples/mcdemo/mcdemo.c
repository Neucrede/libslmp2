/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "melcli/melcli.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


/* ****************************************************************************
 * It may be needed to modify these values according to actual hardware 
 * configuration.
 */
#if 0   /* 1: UDP/IP, 0: TCP/IP */
    const int ctxtype = MELCLI_TYPE_UDPIP;
    const char *target_ip_addr = "192.168.128.200";
    const int target_port = 8889;
    const char *local_ip_addr = "192.168.128.1";
    const int local_port = 0;
#else
    const int ctxtype = MELCLI_TYPE_TCPIP;
    const char *target_ip_addr = "192.168.128.200";
    const int target_port = 8888;
    const char *local_ip_addr = "0.0.0.0";
    const int local_port = 0;
#endif
const melcli_station_t target_station = MELCLI_CONNECTED_STATION;
const melcli_timeout_t timeout = MELCLI_TIMEOUT_DEFAULT;
/* ****************************************************************************/

melcli_ctx_t *g_ctx = NULL;

static int init();
static void demo_batch_read_write();
static void demo_random_read_write();
static void demo_buffer_read_write();
static void demo_self_test();
static void demo_remote_control();
static void demo_clear_error();
static void nap(int duration);

/* Pause for a while after end of each command execution. */
#define NAP_DURATION_SECONDS    1
#define NAP()                   nap(NAP_DURATION_SECONDS)

int main(int argc, char *argv[])
{
    printf(
        "*************************************** \n"
        "  MELSEC Client Library Demonstration   \n"
        "*************************************** \n\n"
    );
    
    if (init() != 0) {
        return 1;
    }
    
    demo_batch_read_write();
    NAP();

    demo_random_read_write();
    NAP();

    demo_buffer_read_write();
    NAP();
    
    demo_self_test();
    NAP();

    demo_remote_control();
    NAP();
    
    demo_clear_error();
    NAP();
    
    printf("\nDisconnecting.\n");
    melcli_disconnect(g_ctx);
    melcli_free_context(g_ctx);
    NAP();
    
    return 0;
}

static int init()
{
    srand((unsigned int)time(NULL));
    
    /* Create a connection context and store it into `g_ctx`. */
    g_ctx = melcli_new_context(ctxtype, target_ip_addr, target_port,
        local_ip_addr, local_port, &target_station, &timeout);
    if (g_ctx == NULL) {
        printf("Failed to create connection context. \n");
        return -1;
    }
    
    /* Enable debug information printout. */
    melcli_set_debug(g_ctx, 1);
    
    printf("Connecting to %s:%d \n", target_ip_addr, target_port);
    if (melcli_connect(g_ctx) != 0) {
        printf("Failed to connect. \n");
        return -1;
    }
    
    printf("Connected. \n");
    
    return 0;
}

static void demo_batch_read_write()
{
    uint8_t *rd_bits;
    uint8_t wr_bits[4] = { 1, 0, 1, 0 };
    uint16_t *rd_words;
    uint16_t wr_words[4] = { 0x1234, 0x5678, 0x90AB, 0xCDEF };
    int i;
    
    printf(
        "\n"
        "Batch Read / Write on Internal Memory      \n"
        "---------------------------------------    \n"
    );
    
    for (i = 0;; ++i) {
        printf("Reading M1000 till M1003. \n");
        if (melcli_batch_read(g_ctx, NULL, "M1000", 4, (char**)(&rd_bits), NULL) != 0) 
        {
            printf("Failed.\n");
            return;
        }
        else {
            printf("M1000 = %d, M1001 = %d, M1002 = %d, M1003 = %d \n",
                rd_bits[0], rd_bits[1], rd_bits[2], rd_bits[3]);
            melcli_free(rd_bits);
        }
        
        if (i > 0) {
            break;
        }

        NAP();
        
        printf("Writing M1000 := 1, M1001 := 0, M1002 := 1, M1003 := 0. \n");
        if (melcli_batch_write(g_ctx, NULL, "M1000", 4, (char*)(wr_bits)) != 0)
        {
            printf("Failed.\n");
            return;
        }

        NAP();
    }

    NAP();
    
    for (i = 0;; ++i) {
        printf("Reading D100 till D103. \n");
        if (melcli_batch_read(g_ctx, NULL, "D100", 4, (char**)(&rd_words), NULL) != 0) 
        {
            printf("Failed.\n");
            return;
        }
        else {
            printf(
                "D100 = 0x%04X, D100 = 0x%04X, D100 = 0x%04X, D100 = 0x%04X \n",
                rd_words[0], rd_words[1], rd_words[2], rd_words[3]);
            melcli_free(rd_words);
        }
        
        if (i > 0) {
            break;
        }

        NAP();

        printf(
            "Writing D100 := 0x1234, D101 := 0x5678, "
            "D102 := 0x90AB, D103 := 0xCDEF \n");
        if (melcli_batch_write(g_ctx, NULL, "D100", 4, (char*)(wr_words)) != 0)
        {
            printf("Failed.\n");
            return;
        }

        NAP();
    }
}

static void demo_random_read_write()
{
    const char *word_addrs[] = { "D107", "D105", "D104", "D108", NULL };
    uint16_t *data = NULL;
    int i, j;
    
    printf(
        "\n"
        "Random Read / Write on Internal Memory     \n"
        "----------------------------------------   \n"
    );
    
    for (i = 0;; ++i) {
        printf("Reading D107, D105, D104 and D108. \n");
        if (melcli_random_read_word(g_ctx, NULL, word_addrs, &data, NULL) != 0) {
            printf("Failed.\n");
            goto __done;
        }
        else {
            printf(
                "D107 = 0x%04X, D105 = 0x%04X, D104 = 0x%04X, D108 = 0x%04X \n",
                data[0], data[1], data[2], data[3]);
        }
        
        if (i > 0) {
            break;
        }

        NAP();
        
        for (j = 0; j != 4; ++j) {
            data[j] = (uint16_t)rand();
        }
        
        printf(
            "Writing D107 := 0x%04X, D105 := 0x%04X, "
            "D104 := 0x%04X, D108 := 0x%04X \n",
            data[0], data[1], data[2], data[3]);
        if (melcli_random_write_word(g_ctx, NULL, word_addrs, data) != 0) {
            printf("Failed.\n");
            goto __done;
        }

        NAP();
    }
    
__done:
    melcli_free(data);
}

static void demo_buffer_read_write()
{
    const uint32_t addr = 0x00000010;
    const int n = 64;
    uint16_t *data = NULL;
    int i, j;

    printf(
        "\n"
        "Batch Read / Write on Buffer Memory (Dual Port Memory)   \n"
        "-------------------------------------------------------- \n"
    );

    for (i = 0;; ++i) {
        printf("Reading %d word units starting from 0x%08X. \n", n, addr);
        if (melcli_buffer_read(g_ctx, NULL, addr, n, &data, NULL) != 0) {
            printf("Failed.\n");
            goto __done;
        }

        if (i > 0) {
            break;
        }

        NAP();

        for (j = 0; j != n; ++j) {
            data[j] = (uint16_t)rand();
        }

        printf(
            "Writing %d word units starting from 0x%08X with random values. \n",
            n, addr);
        if (melcli_buffer_write(g_ctx, NULL, addr, n, data) != 0) {
            printf("Failed.\n");
            goto __done;
        }

        NAP();
    }

__done:
    melcli_free(data);
}

static void demo_self_test()
{
    printf(
        "\n"
        "Self Test      \n"
        "-----------    \n"
    );

    if (melcli_self_test(g_ctx, NULL) != 0) {
        printf("Failed.\n");
        return;
    }
}

static void demo_remote_control()
{
    char *type_name = NULL;
    int type_code;

    printf(
        "\n"
        "Remote Control     \n"
        "----------------   \n"
    );

    printf("Reading processor type\n");
    if (melcli_remote_read_type_name(g_ctx, NULL, &type_name, &type_code) != 0)
    {
        printf("Failed.\n");
    }
    else {
        printf(
            "Processor type code: %d \n"
            "Processor type name: %s \n",
            type_code, type_name);
        melcli_free(type_name);
    }

    NAP();

    printf("Request remote PAUSE\n");
    if (melcli_remote_pause(g_ctx, NULL, 0) != 0) {
        printf("Failed.\n");
        return;
    }

    NAP();

    printf("Request remote RUN\n");
    if (melcli_remote_run(g_ctx, NULL, 0) != 0)
    {
        printf("Failed.\n");
        return;
    }

    NAP();

    printf("Request remote STOP\n");
    if (melcli_remote_stop(g_ctx, NULL) != 0) {
        printf("Failed.\n");
        return;
    }

    NAP();

    printf("Request remote RUN\n");
    if (melcli_remote_run(g_ctx, NULL, 0) != 0)
    {
        printf("Failed.\n");
        return;
    }

    NAP();

    if (ctxtype == MELCLI_TYPE_UDPIP) {
        printf("Request remote RESET\n");
        if (melcli_remote_reset(g_ctx, NULL) != 0) {
            printf("Failed.\n");
            return;
        }

        NAP();

        printf("Request remote RUN\n");
        if (melcli_remote_run(g_ctx, NULL, 0) != 0)
        {
            printf("Failed.\n");
            return;
        }
    }
}

static void demo_clear_error()
{
    printf(
        "\n"
        "Clear error    \n"
        "-------------  \n"
    );

    printf("Clear error history. \n");
    if (melcli_clear_error_history(g_ctx, NULL) != 0) {
        printf("Failed.\n");
    }

    NAP();

    printf("Clear error code. \n");
    if (melcli_clear_error_code(g_ctx, NULL) != 0) {
        printf("Failed.\n");
    }
}

static void nap(int duration)
{
    int i;

    for (i = 0; i != duration; ++i) {
        putc('.', stdout);
#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
    }

    putc('\n', stdout);
}
