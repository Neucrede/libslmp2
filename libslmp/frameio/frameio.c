/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "slmp/slmpdef.h"
#include "slmp/slmperr.h"
#include "slmp/slmpfrmio.h"
#include "slmp/slmpcodec.h"
#include "../slmp_intl.h"


#define SEND_FRAME_MIN_INTERVAL_MILLIS      0


typedef enum {
    FTYPE_ST        = 1,
    FTYPE_MT        = 2,
    FTYPE_EMT       = 3, 
    FTYPE_LMT       = 4, 
    FTYPE_UNKNOWN   = -1
} frame_type_t;


static frame_type_t get_frame_type(slmp_frame_t *frame);
static size_t send_frames_st_mt_emt(slmp_pktio_t *pktio, slmp_frame_t **frames, 
    size_t n, int type, int interval);
static size_t segm_and_send_lmt_frame(slmp_pktio_t *pktio, slmp_frame_t *frame,
    int type, int interval);
static size_t receive_frames(slmp_pktio_t *pktio, slmp_frame_t **frames, 
    size_t n, int *type, int timeout);
static int identify_stream_type(uint8_t *buf, size_t n);

SLMPAPI size_t SLMPCALL slmp_send_frames(
    slmp_pktio_t *pktio, slmp_frame_t **frames, size_t n, int type, int interval)
{
    int ftype0;
    frame_type_t frmtype0;
    size_t i;

    assert(pktio != NULL);
    assert(frames != NULL);
    assert(n != 0);
    assert((type == SLMP_BINARY_STREAM) || (type == SLMP_ASCII_STREAM));

    if ((pktio == NULL) || (frames == NULL) || (n == 0)
        || !((type == SLMP_BINARY_STREAM) || (type == SLMP_ASCII_STREAM))) 
    {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    if (frames[0] == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_POINTER);
        return 0;
    }
    else {
        ftype0 = frames[0]->hdr.ftype;
        frmtype0 = get_frame_type(frames[0]);
    }
    
    if (frmtype0 == FTYPE_UNKNOWN) {
        slmp_set_errno(SLMP_ERROR_BAD_FTYPE);
        return 0;
    }

    for (i = 1; i != n; ++i) {
        int ftype;
        frame_type_t frmtype;
        slmp_frame_t *frame = frames[i];
        assert(frame != NULL);
        if (frame == NULL) {
            slmp_set_errno(SLMP_ERROR_INVALID_POINTER);
            return 0;
        }

        ftype = frame->hdr.ftype;
        frmtype = get_frame_type(frame);
        if (frmtype == FTYPE_UNKNOWN) {
            slmp_set_errno(SLMP_ERROR_BAD_FTYPE);
            return 0;
        }
        else if (ftype != ftype0) {
            slmp_set_errno(SLMP_ERROR_INCONSISTENT_FRAME_TYPES);
            return 0;
        }
    }

    /* Note: 
     *
     * Some SLMP host devices (e.g. Mitsubishi FX5U PLCs) do not
     * not response to xMT frames that are sent continuously too fast.
     */
    if (interval < SEND_FRAME_MIN_INTERVAL_MILLIS) {
        interval = SEND_FRAME_MIN_INTERVAL_MILLIS;
    }

    switch (frmtype0) {
    case FTYPE_ST:
        return send_frames_st_mt_emt(pktio, frames, 1, type, interval);
    case FTYPE_MT:
    case FTYPE_EMT:
        return send_frames_st_mt_emt(pktio, frames, n, type, interval);
    case FTYPE_LMT:
        return segm_and_send_lmt_frame(pktio, frames[0], type, interval);
    default:
        break;
    }

    return 0;
}

SLMPAPI size_t SLMPCALL slmp_receive_frames(
    slmp_pktio_t *pktio, slmp_frame_t **frames, size_t n, int *type, int timeout)
{
    assert(pktio != NULL);
    assert(frames != NULL);
    assert(n != 0);
    assert(timeout >= 0);
    assert(type != NULL);

    if ((pktio == NULL) || (frames == NULL) || (n == 0) || (timeout < 0)
        || (type == NULL)) 
    {
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        return 0;
    }

    return receive_frames(pktio, frames, n, type, timeout);
}

static frame_type_t get_frame_type(slmp_frame_t *frame)
{
    int ftype = frame->hdr.ftype;

    switch (ftype) {
    case SLMP_FTYPE_REQ_ST:
    case SLMP_FTYPE_RES_ST:
    case SLMP_FTYPE_ERR_ST:
        return FTYPE_ST;
    case SLMP_FTYPE_REQ_MT:
    case SLMP_FTYPE_RES_MT:
    case SLMP_FTYPE_ERR_MT:
        return FTYPE_MT;
    case SLMP_FTYPE_REQ_EMT:
    case SLMP_FTYPE_PUSH_EMT:
    case SLMP_FTYPE_RES_EMT:
        return FTYPE_EMT;
    case SLMP_FTYPE_REQ_LMT:
    case SLMP_FTYPE_RES_LMT:
    case SLMP_FTYPE_ERR_LMT:
        return FTYPE_LMT;
    default:
        break;
    }

    return FTYPE_UNKNOWN;
}

static size_t send_frames_st_mt_emt(slmp_pktio_t *pktio, slmp_frame_t **frames, 
    size_t n, int type, int interval)
{
    size_t i;
    uint8_t *buf = NULL;
    size_t buf_len = 0;
    size_t len;
    size_t num_frames_sent = 0;

    for (i = 0; i != n; ++i) {
        slmp_frame_t *frame = frames[i];
        len = slmp_encode_frame(frame, NULL, type);
        if (len == 0) {
            /* An error occured... */
            goto __cleanup;
        }

        if (len > buf_len) {
            if (buf != NULL) {
                free(buf);
            }

            buf_len = 2 * len;
            if ((buf = malloc(buf_len)) == NULL) {
                slmp_set_errno(SLMP_ERROR_OUT_OF_MEMORY);
                goto __cleanup;
            }
        }

        len = slmp_encode_frame(frame, buf, type);
        if (len > 0) {
            if (slmp_pktio_send(pktio, buf, len) == len) {
                ++num_frames_sent;
            }
            else {
                goto __cleanup;
            }
        }
        else {
            goto __cleanup;
        }

        milli_sleep(interval);
    }

    slmp_set_errno(SLMP_ERROR_SUCCESS);

__cleanup:
    if (buf != NULL) {
        free(buf);
    }
    return num_frames_sent;
}

static size_t segm_and_send_lmt_frame(slmp_pktio_t *pktio, slmp_frame_t *frame,
    int type, int interval)
{
    size_t num_segm;
    size_t raw_data_len;
    slmp_frame_t *cur_frame = NULL;
    size_t i;
    size_t cur_raw_data_len;
    uint8_t *buf = NULL;
    size_t buf_len = 0;
    size_t len;
    size_t num_frames_sent = 0;
    
    assert(frame->size >= sizeof(slmp_frame_t) - 1);
    if (frame->size < sizeof(slmp_frame_t) - 1) {
        slmp_set_errno(SLMP_ERROR_INCORRECT_SIZE);
        return 0;
    }

    raw_data_len = frame->size - sizeof(slmp_frame_t) + 1;
    num_segm = raw_data_len / SLMP_FRAMEIO_MAX_RAW_DATA_LEN + 1;
    if (num_segm > UINT16_MAX - 1) {
        slmp_set_errno(SLMP_ERROR_DATA_TOO_LARGE);
        return 0;
    }

    if (num_segm == 1) {
        cur_frame = frame;
    }
    else {
        if ((cur_frame = (slmp_frame_t*)malloc(
                SLMP_FRAME_STRUCT_SIZE(SLMP_FRAMEIO_MAX_RAW_DATA_LEN + 1))) 
            == NULL) 
        {
            slmp_set_errno(SLMP_ERROR_OUT_OF_MEMORY);
            goto __cleanup;
        }

        memcpy(cur_frame, frame, sizeof(slmp_frame_t) - 1);
        cur_frame->cmd_data.lmt.data_div_total = (uint16_t)num_segm;
        cur_frame->cmd_data.lmt.div_no = 0;
    }

    for (i = 0; i != num_segm; ++i) {
        cur_raw_data_len = (
            (i != num_segm - 1)
            ?   SLMP_FRAMEIO_MAX_RAW_DATA_LEN
            :   raw_data_len - (num_segm - 1) * SLMP_FRAMEIO_MAX_RAW_DATA_LEN
        );

        memcpy(
            cur_frame->raw_data, 
            &(frame->raw_data[i * SLMP_FRAMEIO_MAX_RAW_DATA_LEN]),
            cur_raw_data_len
        );

        cur_frame->size = SLMP_FRAME_STRUCT_SIZE(cur_raw_data_len);

        len = slmp_encode_frame(cur_frame, NULL, type);
        if (len == 0) {
            /* An error occured... */
            goto __cleanup;
        }

        if (len > buf_len) {
            if (buf != NULL) {
                free(buf);
            }

            buf_len = 2 * len;
            if ((buf = malloc(buf_len)) == NULL) {
                slmp_set_errno(SLMP_ERROR_OUT_OF_MEMORY);
                goto __cleanup;
            }
        }

        len = slmp_encode_frame(cur_frame, buf, type);
        if (len > 0) {
            if (slmp_pktio_send(pktio, buf, len) == len) {
                ++num_frames_sent;
            }
            else {
                goto __cleanup;
            }
        }
        else {
            goto __cleanup;
        }

        ++cur_frame->cmd_data.lmt.div_no;

        if (interval > 0) {
            milli_sleep(interval);
        }
    }

    slmp_set_errno(SLMP_ERROR_SUCCESS);

__cleanup:
    if ((cur_frame != NULL) && (cur_frame != frame)) {
        free(cur_frame);
    }

    if (buf != NULL) {
        free(buf);
    }

    return num_frames_sent;
}

static size_t receive_frames(slmp_pktio_t *pktio, slmp_frame_t **frames, size_t n,
    int *type, int timeout)
{
    const size_t buf_len = 4096;
    uint8_t *buf;
    size_t idx_frm = 0;
    size_t len_recv;
    int err;
    size_t offset = 0;
    size_t len_remains = 0;
    slmp_frame_t *frame;
    uint64_t t0 = get_current_timestamp();
    uint64_t t;
    int cur_type, prev_type = SLMP_BINARY_STREAM;

    if ((buf = (uint8_t*)malloc(buf_len)) == NULL) {
        slmp_set_errno(SLMP_ERROR_OUT_OF_MEMORY);
        goto __cleanup;
    }

    memset(frames, 0, n * sizeof(slmp_frame_t*));

    for (idx_frm = 0; idx_frm != n; ) {
__outer_for_loop:
        if (buf_len <= offset) {
            slmp_set_errno(SLMP_ERROR_RUN_OUT_OF_INTERNAL_BUFFER);
            goto __cleanup;
        }

        t = get_current_timestamp();
        if ((timeout > 0) && (t0 + timeout < t)) {
            goto __cleanup;
        }

        len_recv = slmp_pktio_recv(pktio, &(buf[offset]), buf_len - offset, 
            (int)(t - t0));

        if (len_recv == 0) {
            err = slmp_get_errno();
            if (    (err == SLMP_ERROR_DATA_NOT_YET_AVAILABLE)
                ||  (err == SLMP_ERROR_TIMEOUT) ) 
            {
                continue;
            }
            else {
                goto __cleanup;
            }
        }

        t = get_current_timestamp();
        while ((idx_frm != n) && (offset + len_recv > 0)) {
            cur_type = identify_stream_type(buf, offset + len_recv);
            if (cur_type != -1) {
                prev_type = cur_type;
            }
            
            frame = slmp_decode_frame(buf, offset + len_recv, 
                cur_type != -1 ? cur_type : prev_type, &len_remains);

            if (frame == NULL) {
                err = slmp_get_errno();
                if (err == SLMP_ERROR_BUFFER_TOO_SHORT) {
                    offset += len_recv;
                    goto __outer_for_loop;
                }
                else {
                    goto __cleanup;
                }
            }

            frame->timestamp = t;
            frames[idx_frm] = frame;
            ++idx_frm;

            if (len_remains != 0) {
                memmove(buf, &(buf[offset + len_recv - len_remains]), len_remains);
            }

            offset = len_remains;
            len_recv = 0;
        }
    }

    *type = cur_type;
    slmp_set_errno(SLMP_ERROR_SUCCESS);

__cleanup:
    free(buf);
    return idx_frm;
}

static int identify_stream_type(uint8_t *buf, size_t n)
{
    uint32_t x;
    uint8_t y[5];

    if (n < 4) {
        return -1;
    }

    /* Try binary */
    x = buf[0] | ((uint32_t)(buf[1]) << 8);
    switch (x) {
    case SLMP_FTYPE_REQ_ST:
    case SLMP_FTYPE_RES_ST:
    case SLMP_FTYPE_REQ_MT:
    case SLMP_FTYPE_RES_MT:
    case SLMP_FTYPE_REQ_EMT:
    case SLMP_FTYPE_PUSH_EMT:
    case SLMP_FTYPE_RES_EMT:
    case SLMP_FTYPE_REQ_LMT:
    case SLMP_FTYPE_RES_LMT:
        return SLMP_BINARY_STREAM;
    default:
        break;
    }
    
    /* Try ASCII */
    strlcpy(y, buf, 5);
    if (
            strcmp(y, "5000") == 0        /* req_st */
        ||  strcmp(y, "D000") == 0        /* res_st, err_st */
        ||  strcmp(y, "5400") == 0        /* req_mt */
        ||  strcmp(y, "D400") == 0        /* res_mt, err_mt */
        ||  strcmp(y, "5D00") == 0        /* req_emt */
        ||  strcmp(y, "9D00") == 0        /* push_emt */
        ||  strcmp(y, "DD00") == 0        /* res_emt */
    )
    {
        return SLMP_ASCII_STREAM;
    }

    return -1;
}
