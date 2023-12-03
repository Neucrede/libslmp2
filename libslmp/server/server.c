/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include "server_priv.h"

SLMPAPI slmp_server_t* SLMPCALL slmp_server_new(
    const slmp_server_config_t* cfg)
{
#ifdef __NATIVE_FUNCTION_MACRO_NOT_DEFINED__
#   ifdef __FUNCTION__
#       undef __FUNCTION__
#   endif
#   define __FUNCTION__ "slmp_server_new"
#endif

    slmp_server_t *svr = NULL;

    assert(cfg != NULL);
    if (cfg == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_POINTER);
        return NULL;
    }

    svr = calloc(1, sizeof(slmp_server_t));
    assert(svr != NULL);
    if (svr == NULL) {
        slmp_set_errno(SLMP_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    memcpy(&(svr->cfg), cfg, sizeof(slmp_server_config_t));
    
    svr->cfg.ipaddr[sizeof(svr->cfg.ipaddr) - 1] = 0x00;
    if (strlen(svr->cfg.ipaddr) < 0) {
        strlcpy(svr->cfg.ipaddr, SLMP_SERVER_IP_ADDRESS_ANY,
            sizeof(svr->cfg.ipaddr));
    }
    
    if (svr->cfg.dbgprint == NULL) {
        svr->cfg.dbgprint = &default_log_printf;
    }
    
    if (svr->cfg.logprint == NULL) {
        svr->cfg.logprint = &default_log_printf;
    }
    
    if (svr->cfg.hook_pre_handle == NULL) {
        svr->cfg.hook_pre_handle = &default_hook_handle;
    }
    
    if (svr->cfg.hook_post_handle == NULL) {
        svr->cfg.hook_post_handle = &default_hook_handle;
    }
    
    if (svr->cfg.hook_pre_loop_iter == NULL) {
        svr->cfg.hook_pre_loop_iter = &default_hook_loop_iter;
    }
    
    if (svr->cfg.hook_post_loop_iter == NULL) {
        svr->cfg.hook_post_loop_iter = &default_hook_loop_iter;
    }
    
    gl_lock_init(svr->lock);
    svr->serial = 0;
    svr->status = SLMP_SERVER_STATUS_NOT_INIT;
    svr->retcode = 0;
    svr->notify = SLMP_SERVER_NOTIFY_NOTHING;
    
    __LOGPRINT0(INFO, "Server instance created.");
    
    return svr;
}

SLMPAPI int SLMPCALL slmp_server_free(slmp_server_t* svr)
{
#ifdef __NATIVE_FUNCTION_MACRO_NOT_DEFINED__
#   ifdef __FUNCTION__
#       undef __FUNCTION__
#   endif
#   define __FUNCTION__ "slmp_server_free"
#endif

    assert(svr != NULL);
    if (svr == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_POINTER);
        return -1;
    }

    if (svr->status == SLMP_SERVER_STATUS_RUNNING) {
        __LOGPRINT0(ERR, "Server is still running.");
        slmp_set_errno(SLMP_ERROR_STILL_RUNNING);
        return -1;
    }

    __LOGPRINT0(INFO, "Server instance released.");
    
    /* Block until lock is released. */
    gl_lock_lock(svr->lock);

    slmp_pktio_free(svr->pktio);
    gl_lock_unlock(svr->lock);
    gl_lock_destroy(svr->lock);
    
    free(svr);
    
    return 0;
}

SLMPAPI int SLMPCALL slmp_server_init(slmp_server_t* svr)
{
#ifdef __NATIVE_FUNCTION_MACRO_NOT_DEFINED__
#   ifdef __FUNCTION__
#       undef __FUNCTION__
#   endif
#   define __FUNCTION__ "slmp_server_init"
#endif

    slmp_pktio_t *pktio = NULL;

    assert(svr != NULL);
    if (svr == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_POINTER);
        return -1;
    }
    
    if (svr->status == SLMP_SERVER_STATUS_RUNNING) {
        __LOGPRINT0(ERR, "Server is still running.");
        slmp_set_errno(SLMP_ERROR_STILL_RUNNING);
        return -1;
    }
    
    gl_lock_lock(svr->lock);
    
    if (svr->pktio != NULL) {
        slmp_pktio_close(svr->pktio);
        slmp_pktio_free(svr->pktio);
        svr->pktio = NULL;
    }
    
    assert((svr->cfg.pktio_type == SLMP_PKTIO_TCPIP)
            || (svr->cfg.pktio_type == SLMP_PKTIO_UDPIP));
    switch (svr->cfg.pktio_type) {
    case SLMP_PKTIO_TCPIP:
        pktio = slmp_pktio_new_tcpip(SLMP_PKTIO_SERVER, svr->cfg.ipaddr,
            svr->cfg.port);
        break;
    case SLMP_PKTIO_UDPIP:
        pktio = slmp_pktio_new_udpip(svr->cfg.ipaddr, svr->cfg.port,
            "0.0.0.0", 0);
        break;
    default:
        __LOGPRINT0(ERR, "Invalid pktio_type value.");
        slmp_set_errno(SLMP_ERROR_INVALID_ARGUMENTS);
        goto __fail;
    }
    
    if (pktio == NULL) {
        goto __fail;
    }
    
    switch (svr->cfg.pktio_type) {
    case SLMP_PKTIO_TCPIP:
        if (svr->cfg.accept_timeout <= 0) {
            svr->cfg.accept_timeout = TCPIP_PKTIO_DEFAULT_ACCEPT_TIMEOUT;
        }
        slmp_pktio_set_timeout(pktio, SLMP_PKTIO_ACCEPT_TIMEOUT,
            svr->cfg.accept_timeout);
        
        if (svr->cfg.recv_timeout <= 0) {
            svr->cfg.recv_timeout = TCPIP_PKTIO_DEFAULT_RECV_TIMEOUT;
        }
        slmp_pktio_set_timeout(pktio, SLMP_PKTIO_RECV_TIMEOUT,
            svr->cfg.recv_timeout);
        break;
    case SLMP_PKTIO_UDPIP:
        if (svr->cfg.recv_timeout <= 0) {
            svr->cfg.recv_timeout = UDPIP_PKTIO_DEFAULT_RECV_TIMEOUT;
        }
        slmp_pktio_set_timeout(pktio, SLMP_PKTIO_RECV_TIMEOUT,
            svr->cfg.recv_timeout);
        break;
    default:
        break;
    }
    
    if (slmp_pktio_init(pktio) != 0) {
        int err = slmp_get_errno();
        __LOGPRINT2(ERR, 
            "slmp_pktio_init() failed. (%d) %s",
            err, slmp_get_err_msg(err));
        goto __fail;
    }
    
    slmp_pktio_set_echo(pktio, svr->cfg.debug);
    slmp_pktio_set_dbgprint_fcn(pktio, svr->cfg.dbgprint);
    
    if (svr->cfg.pktio_type == SLMP_PKTIO_UDPIP) {
        slmp_pktio_udpip_set_broadcast(pktio, svr->cfg.broadcast);
    }
    
    svr->pktio = pktio;
    svr->status = SLMP_SERVER_STATUS_STOPPED;
    __LOGPRINT0(INFO, "Initialization done.");
    gl_lock_unlock(svr->lock);
    return 0;
    
__fail:
    if (pktio != NULL) {
        slmp_pktio_free(pktio);
    }
    svr->status = SLMP_SERVER_STATUS_INIT_FAILED;
    gl_lock_unlock(svr->lock);
    return -1;
}

SLMPAPI int SLMPCALL slmp_server_kill(slmp_server_t* svr, int timeout)
{
#ifdef __NATIVE_FUNCTION_MACRO_NOT_DEFINED__
#   ifdef __FUNCTION__
#       undef __FUNCTION__
#   endif
#   define __FUNCTION__ "slmp_server_kill"
#endif

    uint64_t ts0 = get_current_timestamp();
    uint64_t ts = ts0;
    
    assert(svr != NULL);
    if (svr == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_POINTER);
        return -1;
    }
    
    if (svr->status != SLMP_SERVER_STATUS_RUNNING) {
        __LOGPRINT0(ERR, "Server is not running.");
        slmp_set_errno(SLMP_ERROR_NOT_RUNNING);
        return -1;
    }
    
    ts = get_current_timestamp();
    svr->notify = SLMP_SERVER_NOTIFY_KILL;
    while (     (svr->notify == SLMP_SERVER_NOTIFY_KILL)
            &&  ((timeout <= 0) || (ts < ts0 + timeout)) ) 
    {
        milli_sleep(100);
        
        if (svr->status == SLMP_SERVER_STATUS_RUNNING) {
            ts = get_current_timestamp();
        }
        else {
            return 0;
        }
    }

    __LOGPRINT0(ERR, "Operation timed out.");
    slmp_set_errno(SLMP_ERROR_TIMEOUT);
    return -1;
}

SLMPAPI int SLMPCALL slmp_server_notify(slmp_server_t* svr, int notify)
{
    assert(svr != NULL);
    if (svr == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_POINTER);
        return -1;
    }
    
    svr->notify = notify;
    return 0;
}

SLMPAPI int SLMPCALL slmp_server_mainloop(slmp_server_t* svr)
{
#ifdef __NATIVE_FUNCTION_MACRO_NOT_DEFINED__
#   ifdef __FUNCTION__
#       undef __FUNCTION__
#   endif
#   define __FUNCTION__ "slmp_server_mainloop"
#endif

    slmp_pktio_t *pktio = NULL;
    void *userptr = NULL;
    int err;

    int hint = 0;
    
    int strm_type = SLMP_BINARY_STREAM;
    slmp_frame_t *frame = NULL;
    size_t n;
    
    const slmp_server_cmd_disp_entry_t *cmd_disp = NULL;
    slmp_cmd_hdr_t *cmd = NULL;
    slmp_server_trx_info_t trx_info = { 0 };

#define FREE_RSRCS()    \
    slmp_free(frame);   \
    frame = NULL;   \
    trx_info.req_frame = NULL;  \
    slmp_free(trx_info.req_cmd);    \
    trx_info.req_cmd = NULL;    \
    slmp_free(trx_info.resp_frame);     \
    trx_info.resp_frame = NULL;

#define CHECK_HINTS()   \
    if (hint == SLMP_SERVER_HINT_DISCONNECT) {  \
        __LOGPRINT0(WARN, "Hook function requested disconnect.");    \
        slmp_pktio_disconnect(pktio);   \
        FREE_RSRCS()    \
        break;  \
    }   \
    else if (hint == SLMP_SERVER_HINT_EXIT_LOOP) {  \
        __LOGPRINT0(WARN, "Hook function requested exit loop."); \
        goto __exit_mainloop;   \
    }   \
    else if (hint == SLMP_SERVER_HINT_CONTINUE) { \
        __DBGPRINT0("Hook function requested continue processing."); \
    }

    assert(svr != NULL);
    if (svr == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_POINTER);
        return -1;
    }
    
    switch (svr->status) {
    case SLMP_SERVER_STATUS_RUNNING:
        __LOGPRINT0(ERR, "Already running.");
        slmp_set_errno(SLMP_ERROR_STILL_RUNNING);
        return -1;
    case SLMP_SERVER_STATUS_NOT_INIT:
        __LOGPRINT0(ERR, "Not initialized.");
        slmp_set_errno(SLMP_ERROR_NOT_INITIALIZED);
        return -1;
    case SLMP_SERVER_STATUS_INIT_FAILED:
        __LOGPRINT0(ERR, "Previous initialization has failed.");
        slmp_set_errno(SLMP_ERROR_INITIALIZATION_FAILED);
        return -1;
    default:
        break;
    }
    
    pktio = svr->pktio;
    userptr = svr->cfg.userptr;
    
    gl_lock_lock(svr->lock);

    __LOGPRINT0(INFO, "Opening connection.");
    if (slmp_pktio_open(pktio) != 0) {
        int err = slmp_get_errno();
        __LOGPRINT2(ERR, "slmp_pktio_open() failed. (%d) %s",
            err, slmp_get_err_msg(err));
        svr->retcode = err;
        goto __done;
    }
    
    svr->retcode = 0;
    svr->notify = SLMP_SERVER_NOTIFY_NOTHING;
    svr->status = SLMP_SERVER_STATUS_RUNNING;

    __LOGPRINT0(INFO, "Entered main loop.");
    while (svr->notify != SLMP_SERVER_NOTIFY_KILL) {
__accept_conn:
        if (svr->cfg.pktio_type == SLMP_PKTIO_TCPIP) {
            __LOGPRINT1(INFO, "Listening on port %d", svr->cfg.port);
            
            if (slmp_pktio_accept(pktio) != 0 ) {
                err = slmp_get_errno();
                __DBGPRINT2("Accept: (%d), %s", err, slmp_get_err_msg(err));
                continue;
            }
            else {
                __LOGPRINT1(INFO, "Accepted connection from %s",
                    slmp_pktio_get_peer_ipaddr(pktio));
            }
        }

        for (;;) {
            __DBGPRINT0("Invoking pre-iteration hook.");
            hint = svr->cfg.hook_pre_loop_iter(svr->notify, userptr);
            CHECK_HINTS()
            if (hint == SLMP_SERVER_HINT_SKIP) {
                __LOGPRINT0(WARN, 
                    "Pre-iteration hook requested skip.");
                continue;
            }

            n = slmp_receive_frames(pktio, &frame, 1, &strm_type, 
                svr->cfg.recv_timeout);
            if (n != 1) {
                err = slmp_get_errno();
                switch (err) {
                case SLMP_ERROR_CONNECTION_CLOSED:
                case SLMP_ERROR_SOCKET_ERROR:
                case SLMP_ERROR_NO_CONNECTION:
                    __LOGPRINT2(ERR, "Failed to receive frames. (%d) %s", 
                        err, slmp_get_err_msg(err));
                    slmp_pktio_disconnect(pktio);
                    __LOGPRINT0(INFO, "Disconnected.");
                    goto __accept_conn;
                default:
                    break;
                }

                __DBGPRINT2("No frame was received. (%d) %s",
                    err, slmp_get_err_msg(err));
                continue;
            }
            else {
                svr->serial = frame->hdr.serial;
                __DBGPRINT0("Valid frame received.");
            }

            cmd_disp = lookup_cmd_disp_entry(&(svr->cfg), frame->cmd_data.st.cmd,
                frame->cmd_data.st.sub_cmd);
            if (cmd_disp == NULL) {
                __LOGPRINT2(WARN, 
                    "cmd = 0x%04X, subcmd = 0x%04X: "
                    "No dispatch entry was found.",
                    frame->cmd_data.st.cmd, frame->cmd_data.st.sub_cmd);
                goto __free_rsrcs;
            }
            else {
                const char *s;
                switch (cmd_disp->addr_width) {
                case SLMP_ADDRESS_16BIT:
                    s = "16bit or don't care";
                    break;
                case SLMP_ADDRESS_32BIT:
                    s = "32bit";
                    break;
                default:
                    s = "unknown";
                    break;
                }
                
                __DBGPRINT6(
                    "cmd = 0x%04X, subcmd = 0x%04X: disp_entry = @0x%X, "
                    "addr_width = %s, decode = @0x%X, handler = @0x%x",
                    frame->cmd_data.st.cmd, frame->cmd_data.st.sub_cmd,
                    cmd_disp, s, cmd_disp->decode, cmd_disp->handler);
            }
            
            trx_info.strm_type = strm_type;
            trx_info.cat = get_frame_category(frame);
            trx_info.req_frame = frame;

            if (cmd_disp->decode != NULL) {
                cmd = cmd_disp->decode(frame->raw_data, SLMP_FRAME_RAW_DATA_SIZE(frame),
                    strm_type, cmd_disp->addr_width);
                if (cmd == NULL) {
                    __LOGPRINT0(ERR, "Error decoding command.");
                }
                trx_info.req_cmd = cmd;
            }
            else {
                __LOGPRINT0(WARN, "Decode function not specified.");
                trx_info.req_cmd = NULL;
            }

            trx_info.resp_frame = NULL;

            __DBGPRINT0("Invoking pre-handler hook.");
            hint = svr->cfg.hook_pre_handle(svr->notify, &trx_info, userptr);
            CHECK_HINTS()
            if (hint == SLMP_SERVER_HINT_SKIP) {
                __LOGPRINT0(WARN, "Pre-handler hook requested skip.");
                goto __free_rsrcs;
            }

            if (cmd_disp->handler != NULL) {
                __DBGPRINT0("Invoking command handler.");
                hint = cmd_disp->handler(&trx_info, userptr);
                CHECK_HINTS()
                if (hint == SLMP_SERVER_HINT_SKIP) {
                    __LOGPRINT0(WARN, "Handler requested skip.");
                    goto __free_rsrcs;
                }
            }
            else {
                __LOGPRINT0(WARN, "Command handler not specified.");
            }

            __DBGPRINT0("Invoking post-handler hook.");
            hint = svr->cfg.hook_post_handle(svr->notify, &trx_info, userptr);
            CHECK_HINTS()
            if (hint == SLMP_SERVER_HINT_SKIP) {
                __LOGPRINT0(WARN, 
                    "Post-handler hook requested to skip response frame "
                    "transmission.");
                goto __free_rsrcs;
            }

            if (trx_info.resp_frame != NULL) {
                slmp_frame_t *resp_frame = trx_info.resp_frame;
                
                __DBGPRINT0("Sending response frame.");

                resp_frame->hdr.serial = svr->serial;
                if (slmp_send_frames(pktio, &resp_frame, 1, strm_type, 0) != 0)
                {
                    err = slmp_get_errno();
                    __LOGPRINT2(ERR, 
                        "Response frame transmission has failed. (%d) %s",
                        err, slmp_get_err_msg(err));
                }
                else {
                    __DBGPRINT0("Response frame sent.");
                }
            }
            else {
                __DBGPRINT0("Response frame not specified.");
            }

__free_rsrcs:
            FREE_RSRCS()
            
            __DBGPRINT0("Invoking post-iteration hook.");
            hint = svr->cfg.hook_post_loop_iter(svr->notify, userptr);
            CHECK_HINTS()
        }
    }

__exit_mainloop:
    slmp_pktio_close(pktio);

__done:
    FREE_RSRCS()
    __LOGPRINT1(INFO, "Main loop exited with retcode %d.", svr->retcode);
    svr->status = SLMP_SERVER_STATUS_STOPPED;
    slmp_set_errno(SLMP_ERROR_SUCCESS);
    gl_lock_unlock(svr->lock);
    return svr->retcode;
}

SLMPAPI int SLMPCALL slmp_server_set_retcode(slmp_server_t* svr, int ret)
{
    assert(svr != NULL);
    if (svr == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_POINTER);
        return -1;
    }

    svr->retcode = ret;
    return 0;
}

SLMPAPI slmp_pktio_t* SLMPCALL slmp_server_get_pktio(slmp_server_t* svr)
{
    assert(svr != NULL);
    if (svr == NULL) {
        slmp_set_errno(SLMP_ERROR_INVALID_POINTER);
        return NULL;
    }

    return svr->pktio;
}

/* ***************************************************************************/

static slmp_frame_category_t get_frame_category(slmp_frame_t *frame)
{
    int ftype = frame->hdr.ftype;

    switch (ftype) {
    case SLMP_FTYPE_REQ_ST:
    case SLMP_FTYPE_RES_ST:
    case SLMP_FTYPE_ERR_ST:
        return SLMP_FRAME_CATEGORY_ST;
    case SLMP_FTYPE_REQ_MT:
    case SLMP_FTYPE_RES_MT:
    case SLMP_FTYPE_ERR_MT:
        return SLMP_FRAME_CATEGORY_MT;
    case SLMP_FTYPE_REQ_EMT:
    case SLMP_FTYPE_PUSH_EMT:
    case SLMP_FTYPE_RES_EMT:
        return SLMP_FRAME_CATEGORY_EMT;
    case SLMP_FTYPE_REQ_LMT:
    case SLMP_FTYPE_RES_LMT:
    case SLMP_FTYPE_ERR_LMT:
        return SLMP_FRAME_CATEGORY_LMT;
    default:
        break;
    }

    return SLMP_FRAME_CATEGORY_UNKNOWN;
}


static const slmp_server_cmd_disp_entry_t* lookup_cmd_disp_entry(
    slmp_server_config_t *cfg, uint16_t cmd, uint16_t subcmd)
{
    const slmp_server_cmd_disp_entry_t *entry;
    for (   entry = cfg->disp_tbl; 
            (entry != NULL) && (entry->cmd != 0xFFFF) && (entry->subcmd != 0xFFFF);
            entry++)
    {
        if ((entry->cmd == cmd) && (entry->subcmd == subcmd)) {
            return entry;
        }
    }

    return NULL;
}

static int default_hook_handle(int notify, slmp_server_trx_info_t* info, 
    void* userptr)
{
    (void)(userptr);
   
    if (notify == SLMP_SERVER_NOTIFY_KILL) {
        return SLMP_SERVER_HINT_EXIT_LOOP;
    }

    if ((info->req_frame == NULL) || (info->req_cmd == NULL)) {
        return SLMP_SERVER_HINT_SKIP;
    }
    
    return SLMP_SERVER_HINT_CONTINUE;
}

static int default_hook_loop_iter(int notify, void* userptr)
{
    (void)(userptr);

    if (notify == SLMP_SERVER_NOTIFY_KILL) {
        return SLMP_SERVER_HINT_EXIT_LOOP;
    }
    
    return SLMP_SERVER_HINT_CONTINUE;
}

static int default_log_printf(const char* fmt, ...)
{
    char buf[256];
    va_list ap;

    time_t t = time(NULL);
    struct tm *tm_local = localtime(&t);
    strftime(buf, 256, "%Y-%m-%d %H:%M:%S ", tm_local);
    fputs(buf, stdout);

    va_start(ap, fmt);
    return vprintf(fmt, ap);
}

