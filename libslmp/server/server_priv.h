#ifndef __SERVER_PRIV_H__
#define __SERVER_PRIV_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdarg.h>

#include "slmp/slmpdef.h"
#include "slmp/slmpserver.h"
#include "slmp/slmperr.h"
#include "slmp/slmppktio.h"
#include "slmp/slmpfrmio.h"
#include "slmp/slmpmem.h"
#include "../glthread/lock.h"
#include "../slmp_intl.h"

#define __LOGPRINT_FMT_STR(t, s)    "["#t"] %s(): "s"\n",__FUNCTION__
#define __DBGPRINT_FMT_STR(s)       __LOGPRINT_FMT_STR(DEBUG, s)

#define __DBGPRINT0(s)   \
    if (svr->cfg.debug) { svr->cfg.dbgprint(__DBGPRINT_FMT_STR(s)); }
    
#define __DBGPRINT1(s, x1)   \
    if (svr->cfg.debug) { svr->cfg.dbgprint(__DBGPRINT_FMT_STR(s), x1); }
    
#define __DBGPRINT2(s, x1, x2)   \
    if (svr->cfg.debug) { svr->cfg.dbgprint(__DBGPRINT_FMT_STR(s), x1, x2); }
    
#define __DBGPRINT3(s, x1, x2, x3)   \
    if (svr->cfg.debug) { svr->cfg.dbgprint(__DBGPRINT_FMT_STR(s), x1, x2, x3); }
    
#define __DBGPRINT4(s, x1, x2, x3, x4)   \
    if (svr->cfg.debug) { svr->cfg.dbgprint(__DBGPRINT_FMT_STR(s), \
        x1, x2, x3, x4); }
    
#define __DBGPRINT5(s, x1, x2, x3, x4, x5)   \
    if (svr->cfg.debug) { svr->cfg.dbgprint(__DBGPRINT_FMT_STR(s), \
        x1, x2, x3, x4, x5); }

#define __DBGPRINT6(s, x1, x2, x3, x4, x5, x6)   \
    if (svr->cfg.debug) { svr->cfg.dbgprint(__DBGPRINT_FMT_STR(s), \
        x1, x2, x3, x4, x5, x6); }

#define __LOGPRINT0(t, s)   \
    if (svr->cfg.logging) { svr->cfg.logprint(__LOGPRINT_FMT_STR(t, s)); }
    
#define __LOGPRINT1(t, s, x1)   \
    if (svr->cfg.logging) { svr->cfg.logprint(__LOGPRINT_FMT_STR(t, s), x1); }
    
#define __LOGPRINT2(t, s, x1, x2)   \
    if (svr->cfg.logging) { svr->cfg.logprint(__LOGPRINT_FMT_STR(t, s), x1, x2); }
    
#define __LOGPRINT3(t, s, x1, x2, x3)   \
    if (svr->cfg.logging) { svr->cfg.logprint(__LOGPRINT_FMT_STR(t, s), x1, x2, x3); }
    
#define __LOGPRINT4(t, s, x1, x2, x3, x4)   \
    if (svr->cfg.logging) { svr->cfg.logprint(__LOGPRINT_FMT_STR(t, s), x1, x2, x3, x4); }


/* Server structure */
struct slmp_server
{
    /* Configs */
    slmp_server_config_t cfg;
    
    /* Lock */
    gl_lock_t lock;
    
    /* Pointer to packet IO object */
    slmp_pktio_t *pktio;
    
    /* Next frame serial */
    uint16_t serial;
    
    /* Status */
    int status;  

    /* Return code of main loop */
    int retcode;
    
    /* Notify code */
    int notify;
};

static slmp_frame_category_t get_frame_category(slmp_frame_t *frame);
static const slmp_server_cmd_disp_entry_t* lookup_cmd_disp_entry(
    slmp_server_config_t *cfg, uint16_t cmd, uint16_t subcmd);
static int default_hook_handle(int notify, slmp_server_trx_info_t* info, 
    void* userptr);
static int default_hook_loop_iter(int notify, void* userptr);
static int default_log_printf(const char* fmt, ...);

#endif /* __SERVER_PRIV_H_ */

