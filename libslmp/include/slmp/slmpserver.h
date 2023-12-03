/**
 * \file slmpserver.h
 *
 * \brief SLMP server.
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 */

#ifndef __SERVER_H__
#define __SERVER_H__

#include "slmp/slmpapi.h"
#include "slmp/slmpframe.h"
#include "slmp/slmppktio.h"
#include "slmp/slmpcodec.h"
#include "slmp/command/cmdhdr.h"

/* ***************************************************************************/

#define SLMP_SERVER_IP_ADDRESS_ANY      "0.0.0.0"
#define SLMP_SERVER_MAC_ADDRESS_AUTO    { 0, 0, 0, 0, 0, 0 }

/**
 * \name Server status code.
 * @{
 */
/** Not initialized */
#define SLMP_SERVER_STATUS_NOT_INIT             0
/** Previous initialization has failed */
#define SLMP_SERVER_STATUS_INIT_FAILED          -1
/** Server is running */
#define SLMP_SERVER_STATUS_RUNNING              1
/** Server is stopped */
#define SLMP_SERVER_STATUS_STOPPED              2
/** Unknown status */
#define SLMP_SERVER_STATUS_UNKNOWN              -10000
/** @} */

/** 
 * \name Hints returned by handlers and hooks.
 * @{
 */
/** Prompt to continue processing */
#define SLMP_SERVER_HINT_CONTINUE               0
/** Prompt to skip current iteration */
#define SLMP_SERVER_HINT_SKIP                   1
/** Prompt to exit main loop */
#define SLMP_SERVER_HINT_EXIT_LOOP              -1
/** Prompt to disconnect from client */
#define SLMP_SERVER_HINT_DISCONNECT             -2
/** @} */

/**
 * \name Notifications
 * @{
 */
/** Do nothing */
#define SLMP_SERVER_NOTIFY_NOTHING              0
/** Kill the running server */
#define SLMP_SERVER_NOTIFY_KILL                 1
/** @} */

/**
 * \name Forward declarations
 * @{
 */
typedef struct slmp_server slmp_server_t;
typedef struct slmp_server_trx_info slmp_server_trx_info_t;
typedef struct slmp_server_cmd_disp_entry slmp_server_cmd_disp_entry_t;
/** @} */

/** \brief Frame type categories. */
typedef enum {
    SLMP_FRAME_CATEGORY_ST        = 1,
    SLMP_FRAME_CATEGORY_MT        = 2,
    SLMP_FRAME_CATEGORY_EMT       = 3, 
    SLMP_FRAME_CATEGORY_LMT       = 4, 
    SLMP_FRAME_CATEGORY_UNKNOWN   = -1
} slmp_frame_category_t;

/** \brief Command handler function pointer */
typedef int (*slmp_server_command_handler_t)(
    slmp_server_trx_info_t* /* info */, void* /* userptr */);

/** Use this macro to (forward) declare a command handler. */
#define SLMP_SERVER_DECLARE_COMMAND_HANDLER(_stgcls, _name)                 \
    _stgcls int _name(slmp_server_trx_info_t*, void*)

/** 
 * \name Hook function types
 * @{
 */
typedef int (*slmp_server_hook_handle_t)(int /* notify */, 
    slmp_server_trx_info_t* /* info */, void* /* userptr */);

/** \brief Function called before command handler */
typedef slmp_server_hook_handle_t slmp_server_hook_pre_handle_t;

/** \brief Function called after command handler */
typedef slmp_server_hook_handle_t slmp_server_hook_post_handle_t;

typedef int (*slmp_server_hook_loop_iter_t)(int /* notify */, 
    void* /* userptr */);

/** \brief Function called at the beginning of each loop iteration */
typedef slmp_server_hook_loop_iter_t slmp_server_hook_pre_loop_iter_t;

/** \brief Function called at the end of each loop iteration */
typedef slmp_server_hook_loop_iter_t slmp_server_hook_post_loop_iter_t;
/** @} */

/** \brief Formatted print function used by debug and logging print */
typedef int (CDECLCALL *slmp_server_printf_t)(const char*, ...);

/** \brief Server configuration */
typedef struct slmp_server_config
{
    /** Server IPv4 address */
    char ipaddr[24];
    /** Port number */
    int port;
    /** PktIO type */
    int pktio_type;
    /** Adapter MAC address (LSB --> MSB) */
    char mac_addr[6];
    /** Whether broadcast transmission & receipt is enabled (UDP) */
    int broadcast;
    /** Accept timeout (TCP) */
    int accept_timeout;
    /** Receive timeout */
    int recv_timeout;
    /** Whether debug print is enabled */
    int debug;
    /** Debug print function */
    slmp_server_printf_t dbgprint;
    /** Whether logging is enabled */
    int logging;
    /** Log print function */
    slmp_server_printf_t logprint;
    /** User pointer */
    void *userptr;
    /** Command dispatch table */
    const slmp_server_cmd_disp_entry_t *disp_tbl;
    /**
     * \name Hooks
     * @{
     */
    slmp_server_hook_pre_handle_t       hook_pre_handle;
    slmp_server_hook_post_handle_t      hook_post_handle;
    slmp_server_hook_pre_loop_iter_t    hook_pre_loop_iter;
    slmp_server_hook_post_loop_iter_t   hook_post_loop_iter;
    /** @} */
} slmp_server_config_t;

/** \brief  Transaction information */
struct slmp_server_trx_info
{
    /** Stream type. */
    int strm_type;
    /** Frame type category. */
    slmp_frame_category_t cat;
    /** Request frame. */
    slmp_frame_t *req_frame;
    /** Request command. */
    slmp_cmd_hdr_t *req_cmd;
    /** Response frame to send back, if not NULL. */
    slmp_frame_t *resp_frame;
};

/** \brief Command dispatch table entry */
struct slmp_server_cmd_disp_entry
{
    /** Command code. */
    uint16_t cmd;
    /** Sub-command code. */
    uint16_t subcmd;
    /** Address width. */
    int addr_width;
    /** Command decode function. */
    slmp_command_decode_t decode;
    /** Command handler. */
    slmp_server_command_handler_t handler;
};

/**
 * \name Command dispatch table declaration / definition.
 * @{
 */
/** Use this macro to declare a command dispatch table. */
#define SLMP_SERVER_DECLARE_COMMAND_DISPATCH_TABLE(_stgcls, _name)          \
    _stgcls slmp_server_cmd_disp_entry_t* _name                            
    
/** Use this macro to start listing command dispatch table entries. */
#define SLMP_SERVER_BEGIN_COMMAND_DISPATCH_TABLE(_stgcls, _name)            \
    _stgcls slmp_server_cmd_disp_entry_t _name[] = {                      
        
/** Use this macro to define a dispatch table entry. */
#define SLMP_SERVER_COMMAND_DISPATCH(_cmd, _subcmd, _addr_width, _decode, _handler)     \
    { _cmd, _subcmd, _addr_width, _decode, _handler },                      
    
/** Use this macro to end dispatch table listing. */
#define SLMP_SERVER_END_COMMAND_DISPATCH_TABLE()                            \
    { 0xFFFF, 0xFFFF, -1, NULL, NULL } };                                   
/**
 * @}
 */
    
/* ***************************************************************************/

/**
 * \brief Create a new SLMP server instance.
 *
 * \param[in] cfg Configurations.
 *
 * \return If the function succeeds, it returns the pointer to the server
 * object. If the function fails, the function returns a value of NULL. Call
 * slmp_get_errno() to get the error number.
 */

SLMPAPI slmp_server_t* SLMPCALL slmp_server_new(
    const slmp_server_config_t* cfg);

/**
 * \brief Destroy an SLMP server instance.
 *
 * \param[in] svr Pointer to server instance.
 *
 * \return If the function succeeds, it returns the value of 0. 
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_server_free(slmp_server_t* svr);

/**
 * \brief Initialize an SLMP server instance.
 *
 * \param[in] svr Pointer to server instance.
 *
 * \return If the function succeeds, it returns the value of 0. 
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */

SLMPAPI int SLMPCALL slmp_server_init(slmp_server_t* svr);

/**
 * \brief Request a running server instance to exit from its mainloop.
 *
 * \param[in] svr Pointer to server instance.
 * \param[in] timeout Timeout value in milliseconds.
 *
 * \return If the function succeeds, it returns the value of 0. 
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_server_kill(slmp_server_t* svr, int timeout);

/**
 * \brief Notify a running server of a user defined code.
 *
 * \param[in] svr Pointer to server instance.
 * \param[in] notify Notification code.
 *
 * \return If the function succeeds, it returns the value of 0. 
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_server_notify(slmp_server_t* svr, int notify);

/**
 * \brief Enter main loop.
 *
 * \param[in] svr Pointer to server instance.
 *
 * \return The return code set by slmp_server_set_retcode().
 */
SLMPAPI int SLMPCALL slmp_server_mainloop(slmp_server_t* svr);

/**
 * \brief Set value to be returned by slmp_server_mainloop().
 *
 * \param[in] svr Pointer to server instance.
 * \param[in] ret Return value.
 *
 * \return If the function succeeds, it returns the value of 0. 
 * If the function fails, the function returns a value of -1. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI int SLMPCALL slmp_server_set_retcode(slmp_server_t* svr, int ret);

/**
 * \brief Get PktIO object associated with given server instance.
 *
 * \param[in] svr Pointer to server instance.
 *
 * \return If the function succeeds, it returns the pointer to the packet IO
 * object. If the function fails, the function returns a value of NULL. Call
 * slmp_get_errno() to get the error number.
 */
SLMPAPI slmp_pktio_t* SLMPCALL slmp_server_get_pktio(slmp_server_t* svr);

#endif /* __SERVER_H__ */
