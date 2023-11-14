/**
 * \file cmdcode.h
 *
 * \brief Command and sub-command codes.
 *
 * Other header files included in this directory except cmdhdr.h are 
 * generated by CCGEN program.
 *
 * \author Neucrede <neucrede@sina.com>
 * \version 1.0
 * \copyright BSD 2-Clause License
 */

#ifndef __CMDCODE_H__
#define __CMDCODE_H__

/**
 * \name Internal memory 
 * @{
 */
#define SLMP_CMD_MEM_BATCH_READ                         0x0401
#define SLMP_CMD_MEM_BATCH_READ_MULTIBLOCKS             0x0406
#define SLMP_CMD_MEM_BATCH_WRITE                        0x1401
#define SLMP_CMD_MEM_BATCH_WRITE_MULTIBLOCKS            0x1406
#define SLMP_CMD_MEM_RANDOM_READ                        0x0403
#define SLMP_CMD_MEM_RANDOM_WRITE                       0x1402
#define SLMP_CMD_MEM_REGISTER_MONITOR                   0x0801
#define SLMP_CMD_MEM_MONITOR                            0x0802
#define SLMP_CMD_MEM_LABEL_BATCH_READ                   0x041A
#define SLMP_CMD_MEM_LABEL_BATCH_WRITE                  0x141A
#define SLMP_CMD_MEM_LABEL_RANDOM_READ                  0x041C
#define SLMP_CMD_MEM_LABEL_RANDOM_WRITE                 0x141B
#define SLMP_SUBCMD_MEM_BIT_ADDR_16                     0x0001
#define SLMP_SUBCMD_MEM_BIT_ADDR_32                     0x0003
#define SLMP_SUBCMD_MEM_WORD_ADDR_16                    0x0000
#define SLMP_SUBCMD_MEM_WORD_ADDR_32                    0x0002
#define SLMP_SUBCMD_MEM_WORD_EXT_ADDR_16                0x0080
#define SLMP_SUBCMD_MEM_WORD_EXT_ADDR_32                0x0082
#define SLMP_SUBCMD_MEM_MONITOR_COND                    0x0040
#define SLMP_SUBCMD_MEM_BLOCK                           0x0000
#define SLMP_SUBCMD_MEM_BLOCK_EXT                       0x0080
#define SLMP_SUBCMD_MEM_DEVFMTEXT_BLOCK                 0x0002
#define SLMP_SUBCMD_MEM_DEVFMTEXT_BLOCK_EXT             0x0082
/** @} */

/**
 * \name Dual-port memory
 * @{
 */
#define SLMP_CMD_DPMEM_BATCH_READ                       0x0613
#define SLMP_CMD_DPMEM_BATCH_WRITE                      0x1613
/** @} */

/**
 * \name Extension module 
 * @{
 */
#define SLMP_CMD_EXT_UNIT_BATCH_READ                    0x0601
#define SLMP_CMD_EXT_UNIT_BATCH_WRITE                   0x1601
/** @} */

/**
 * \name Remote control
 * @{
 */
#define SLMP_CMD_REMOTE_RUN                             0x1001
#define SLMP_CMD_REMOTE_STOP                            0x1002
#define SLMP_CMD_REMOTE_PAUSE                           0x1003
#define SLMP_CMD_REMOTE_LATCH_CLEAR                     0x1005
#define SLMP_CMD_REMOTE_RESET                           0x1006
#define SLMP_CMD_REMOTE_READ_PROCESSOR_TYPE             0x0101
#define SLMP_CMD_REMOTE_INDICATOR_DISPLAY               0x3070
#define SLMP_SUBCMD_REMOTE_RESET_WITH_RESPONSE          0x0001
/** @} */

/**
 * \name Drive memory 
 * @{
 */
#define SLMP_CMD_DRVMEM_READ_USAGE_STATE                0x0205
#define SLMP_CMD_DRVMEM_DEFRAG                          0x1207
/** @} */

/**
 * \name Files
 * @{
 */
#define SLMP_CMD_FILE_READ_INFO_LIST                    0x0201
#define SLMP_CMD_FILE_READ_INFO_LIST_WITH_HEADER_TEXT   0x0202
#define SLMP_CMD_FILE_READ_USAGE_STATE                  0x0204
#define SLMP_CMD_FILE_CHANGE_INFO                       0x1204
#define SLMP_CMD_FILE_SEARCH                            0x0203
#define SLMP_CMD_FILE_READ_CONTENT                      0x0206
#define SLMP_CMD_FILE_WRITE_CONTENT                     0x1203
#define SLMP_CMD_FILE_LOCK                              0x0808
#define SLMP_CMD_FILE_COPY_ACCESS_TYPE_A                0x1206
#define SLMP_CMD_FILE_COPY_ACCESS_TYPE_B                0x1824
#define SLMP_CMD_FILE_DELETE_ACCESS_TYPE_A              0x1205
#define SLMP_CMD_FILE_DELETE_ACCESS_TYPE_B              0x1822
#define SLMP_CMD_FILE_READ_DIR_FILE_INFO                0x1810
#define SLMP_CMD_FILE_SEARCH_DIR_FILE_INFO              0x1811
#define SLMP_CMD_FILE_CREATE_ACCESS_TYPE_A              0x1202
#define SLMP_CMD_FILE_CREATE_ACCESS_TYPE_B              0x1820
#define SLMP_CMD_FILE_CHANGE_ATTRIBUTES                 0x1825
#define SLMP_CMD_FILE_CHANGE_CREATION_DATETIME          0x1826
#define SLMP_CMD_FILE_OPEN                              0x1827
#define SLMP_CMD_FILE_READ                              0x1828
#define SLMP_CMD_FILE_WRITE                             0x1829
#define SLMP_CMD_FILE_CLOSE                             0x182A
#define SLMP_SUBCMD_FILE_CHANGE_EDIT_TIME               0x0000
#define SLMP_SUBCMD_FILE_CHANGE_NAME_AND_SIZE           0x0001
#define SLMP_SUBCMD_FILE_CHANGE_INFO                    0x0002
#define SLMP_SUBCMD_FILE_WRITE_ARBITRARY                0x0000
#define SLMP_SUBCMD_FILE_WRITE_SAME                     0x0001
#define SLMP_SUBCMD_FILE_LOCK_REGISTER                  0x0001
#define SLMP_SUBCMD_FILE_LOCK_UNREGISTER                0x0000
#define SLMP_SUBCMD_FILE_ACCESS_ASCII                   0x0000
#define SLMP_SUBCMD_FILE_ACCESS_SHIFT_JIS               0x0000
#define SLMP_SUBCMD_FILE_ACCESS_UNICODE                 0x0040
#define SLMP_SUBCMD_FILE_ACCESS_UTF16                   0x0040
#define SLMP_SUBCMD_FILE_ACCESS_UTF16LE                 0x0040
/** @} */

/**
 * \name Loopback test
 * @{
 */
#define SLMP_CMD_LOOPBACK_TEST                          0x0619
/** @} */

/**
 * \name Error initialization
 * @{
 */
#define SLMP_CMD_ERROR_CODE_INIT                        0x1617
#define SLMP_CMD_ERROR_HISTORY_INIT                     0x1619
/** @} */

/**
 * \name Remote password
 * @{
 */
#define SLMP_CMD_REMOTE_PASSWORD_LOCK                   0x1631
#define SLMP_CMD_REMOTE_PASSWORD_UNLOCK                 0x1630
/** @} */

/**
 * \name On-demand
 * @{
 */
#define SLMP_CMD_ONDEMAND                               0x2101
/** @} */

/* Data collection */

/* Device connection */

/* Parameter settings */

/* Monitoring device */

/* Accessing CAN application objects */

/* Accessing other open networks */

/* Diagnose CC-Link IE Field network */

/* Managing the CC-Link IE TSN network */

/* Link device parameter */

/* Event history */

/* Backup and restoration */

/* Slave station parameter autosetting */

/* Cyclic start / stop */

/* Reserved station */

/* Watchdog counter */

/* Slave station information */


#endif /* __CMDCODE_H__ */
