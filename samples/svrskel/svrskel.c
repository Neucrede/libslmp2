/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "slmp/slmp.h"
#include "slmp/command/cmdcode.h"
#include "slmp/command/selftest.h"

/* Declaration of command handlers *******************************************/
SLMP_SERVER_DECLARE_COMMAND_HANDLER(static, on_loopback_test);
/* ***************************************************************************/

/* Command dispatch table ****************************************************/
SLMP_SERVER_BEGIN_COMMAND_DISPATCH_TABLE(const static, disp_tbl)
    SLMP_SERVER_COMMAND_DISPATCH(
        SLMP_CMD_LOOPBACK_TEST, 0x0000, 
        SLMP_ADDRESS_WIDTH_DONT_CARE, 
        slmp_decode_req_self_test, on_loopback_test)
SLMP_SERVER_END_COMMAND_DISPATCH_TABLE()
/* ***************************************************************************/

int main(int argc, char *argv[])
{
    slmp_server_config_t config;
    slmp_server_t *server = NULL;
    
    printf(
        "************************************ \n"
        "  SLMP Server Application Skeleton   \n"
        "************************************ \n\n"
    );
    
    memset(&config, 0, sizeof(slmp_server_config_t));
    strcpy(config.ipaddr, "0.0.0.0");
    config.port = 8888;
    config.pktio_type = SLMP_PKTIO_TCPIP;
    config.debug = 1;
    config.logging = 1;
    config.disp_tbl = disp_tbl;
    
    server = slmp_server_new(&config);
    slmp_server_init(server);
    
    return slmp_server_mainloop(server);
}

/* Implementation of command handlers ****************************************/
static int on_loopback_test(slmp_server_trx_info_t* info, void* userptr)
{
    int hint = SLMP_SERVER_HINT_SKIP;
    slmp_req_self_test_t *req = (slmp_req_self_test_t*)(info->req_cmd);
    size_t res_size;
    slmp_res_self_test_t *res = NULL;
    slmp_frame_t *resp_frame = NULL;
    size_t data_len;

    if (req == NULL) {
        goto __done;
    }

    res_size = sizeof(slmp_res_self_test_t) + req->len - 1;
    res = (slmp_res_self_test_t*)calloc(1, res_size);
    if (res == NULL) {
        goto __done;
    }

    res->hdr.addr_width = SLMP_ADDRESS_WIDTH_DONT_CARE;
    res->hdr.size = res_size;
    res->len = req->len;
    memcpy(res->data, req->data, req->len);

    data_len = slmp_encode_res_self_test((slmp_cmd_hdr_t*)res, NULL,
        info->strm_type);
    resp_frame = slmp_calloc(1, SLMP_FRAME_STRUCT_SIZE(data_len));
    if (resp_frame == NULL) {
        goto __done;
    }

    switch (info->cat) {
    case SLMP_FRAME_CATEGORY_ST:
        resp_frame->hdr.ftype = SLMP_FTYPE_RES_ST;
        resp_frame->cmd_data.st.cmd = SLMP_CMD_LOOPBACK_TEST;
        resp_frame->sub_hdr.st.net_no = info->req_frame->sub_hdr.st.net_no;
        resp_frame->sub_hdr.st.node_no = info->req_frame->sub_hdr.st.node_no;
        resp_frame->sub_hdr.st.dst_proc_no = info->req_frame->sub_hdr.st.dst_proc_no;
        resp_frame->sub_hdr.st.data_len = (uint16_t)data_len;
        break;
    case SLMP_FRAME_CATEGORY_MT:
        resp_frame->hdr.ftype = SLMP_FTYPE_RES_MT;
        resp_frame->cmd_data.mt.cmd = SLMP_CMD_LOOPBACK_TEST;
        resp_frame->sub_hdr.mt.net_no = info->req_frame->sub_hdr.mt.net_no;
        resp_frame->sub_hdr.mt.node_no = info->req_frame->sub_hdr.mt.node_no;
        resp_frame->sub_hdr.mt.dst_proc_no = info->req_frame->sub_hdr.mt.dst_proc_no;
        resp_frame->sub_hdr.mt.data_len = (uint16_t)data_len;
        break;
    default:
        goto __done;
    }

    resp_frame->size = SLMP_FRAME_STRUCT_SIZE(data_len);

    if (slmp_encode_res_self_test((slmp_cmd_hdr_t*)res, resp_frame->raw_data, 
        info->strm_type) != data_len)
    {
        goto __done;
    }

    info->resp_frame = resp_frame;
    hint = SLMP_SERVER_HINT_CONTINUE;

__done:
    free(res);
    return hint;
}
/* ***************************************************************************/
