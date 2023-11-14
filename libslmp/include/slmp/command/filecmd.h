/**
 * \file filecmd.h
 * 
 * \brief File Management Commands
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\File.cge by CCGEN program.
 */

#ifndef FILECMD_H
#define FILECMD_H

#include "slmp/command/cmdhdr.h" 
#include "slmp/_pushpack4.h" 


/**
 * \brief Read file information list.
 */
typedef struct slmp_req_get_file_info {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name pwd
 * @{
 */
    /**
     * File password
     */
    uint32_t pwd; /* 24b */
    /**
     * Settings flag
     */
    uint8_t flag;
/**
 * @}
 */
    /**
     * Drive name
     */
    uint16_t drv_name;
    /**
     * Starting file number
     */
    uint16_t file_num_begin;
    /**
     * Number of files
     */
    uint16_t num;
} slmp_req_get_file_info_t;

/**
 * \brief Read the file number usage state.
 */
typedef struct slmp_req_get_file_num_usage {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name pwd
 * @{
 */
    /**
     * File password
     */
    uint32_t pwd; /* 24b */

    uint8_t flag;
/**
 * @}
 */
    /**
     * Drive name
     */
    uint16_t drv_name;
} slmp_req_get_file_num_usage_t;

/**
 * \brief Response of ReqGetFileInfo command.
 */
typedef struct slmp_res_get_file_info {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Total number of registered files
     */
    uint16_t num_total;
    /**
     * Number of file info entries
     */
    uint16_t num_info;
    /**
     * File information
     */
    uint8_t data[1]; /* variable size */
} slmp_res_get_file_info_t;

/**
 * \brief File information entry.
 */
typedef struct slmp_res_get_file_info_entry {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * File number
     */
    uint16_t fnum;
    /**
     * File name
     */
    uint8_t name[8]; /* string */
    /**
     * File extension
     */
    uint8_t ext[3]; /* string */
    /**
     * File attributes
     */
    uint8_t attr;
    /**
     * Time last edited
     */
    uint16_t last_edit_time;
    /**
     * Date last edited
     */
    uint16_t last_edit_date;
    /**
     * File size in bytes
     */
    uint32_t size; /* 32b */
} slmp_res_get_file_info_entry_t;

/**
 * \brief File information entry for files with header text.
 */
typedef struct slmp_res_get_file_info_detail_entry {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * File number
     */
    uint16_t fnum;
    /**
     * File name
     */
    uint8_t name[8]; /* string */
    /**
     * File extension
     */
    uint8_t ext[3]; /* string */
    /**
     * File attributes
     */
    uint8_t attr;
    /**
     * Time last edited
     */
    uint16_t last_edit_time;
    /**
     * Date last edited
     */
    uint16_t last_edit_date;
    /**
     * File size
     */
    uint32_t size; /* 32b */
    /**
     * Header text
     */
    uint8_t hdr_text[32];
} slmp_res_get_file_info_detail_entry_t;

/**
 * \brief Change the datetime that the file was last edited.
 */
typedef struct slmp_req_change_file_edit_time {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name pwd
 * @{
 */
    /**
     * Password
     */
    uint32_t pwd; /* 24b */
    /**
     * Setting flag
     */
    uint8_t flag;
/**
 * @}
 */
    /**
     * Drive name
     */
    uint16_t drv_name;
    /**
     * File number
     */
    uint16_t fnum;
    /**
     * Filename
     */
    uint8_t name[8]; /* string */
    /**
     * File extension
     */
    uint8_t ext[3]; /* string */
    /**
     * File attributes
     */
    uint8_t attr;
    /**
     * Pattern to change
     */
    uint16_t pattern;
    /**
     * Time last edited
     */
    uint16_t last_edit_time;
    /**
     * Date last edited
     */
    uint16_t last_edit_date;
} slmp_req_change_file_edit_time_t;

/**
 * \brief Change the file name and size.
 */
typedef struct slmp_req_change_file_info {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name pwd
 * @{
 */
    /**
     * File password
     */
    uint32_t pwd; /* 24b */
    /**
     * Setting flag
     */
    uint8_t flag;
/**
 * @}
 */
    /**
     * Drive name
     */
    uint16_t drv_name;
    /**
     * File number
     */
    uint16_t fnum;
    /**
     * Old filename
     */
    uint8_t old_name[8]; /* string */
    /**
     * Old file extension
     */
    uint8_t old_ext[3]; /* string */
    /**
     * Old file attributes
     */
    uint8_t old_attr;
    /**
     * Pattern to change
     */
    uint16_t pattern;
    /**
     * New filename
     */
    uint8_t new_name[8]; /* string */
    /**
     * New file extension
     */
    uint8_t new_ext[3]; /* string */
    /**
     * New file attributes
     */
    uint8_t new_attr;
    /**
     * File size
     */
    uint32_t size; /* 32b */
    /**
     * Reserved for future expansion
     */
    uint16_t reserved2;
} slmp_req_change_file_info_t;

/**
 * \brief Search for the specified file.
 */
typedef struct slmp_req_file_search {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name pwd
 * @{
 */
    /**
     * File password
     */
    uint32_t pwd; /* 24b */
    /**
     * Setting flag
     */
    uint8_t flag;
/**
 * @}
 */
    /**
     * Drive name
     */
    uint16_t drv_name;
    /**
     * File name
     */
    uint8_t name[8]; /* string */
    /**
     * File extension
     */
    uint8_t ext[3]; /* string */
    /**
     * File attributes
     */
    uint8_t attr;
} slmp_req_file_search_t;

/**
 * \brief Response to ReqFileSearch command.
 */
typedef struct slmp_res_file_search {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * File number
     */
    uint16_t fnum;
    /**
     * File size
     */
    uint32_t size; /* 32b */
} slmp_res_file_search_t;

/**
 * \brief Read file.
 */
typedef struct slmp_req_file_read {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name pwd
 * @{
 */
    /**
     * File password
     */
    uint32_t pwd; /* 24b */
    /**
     * Setting flag
     */
    uint8_t flag;
/**
 * @}
 */
    /**
     * Drive name
     */
    uint16_t drv_name;
    /**
     * File number
     */
    uint16_t fnum;
    /**
     * File name
     */
    uint8_t name[8]; /* string */
    /**
     * File extension
     */
    uint8_t ext[3]; /* string */
    /**
     * File attributes
     */
    uint8_t attr;
    /**
     * Offset
     */
    uint32_t offset; /* 32b */
    /**
     * Number of bytes to read
     */
    uint16_t num_bytes;
} slmp_req_file_read_t;

/**
 * \brief Response to ReqFileRead.
 */
typedef struct slmp_res_file_read {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 


    uint8_t data[1]; /* string (variable size) */
} slmp_res_file_read_t;

/**
 * \brief Write data to a specified file.
 */
typedef struct slmp_req_file_write {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name pwd
 * @{
 */
    /**
     * File password
     */
    uint32_t pwd; /* 24b */
    /**
     * Setting flag
     */
    uint8_t flag;
/**
 * @}
 */
    /**
     * Drive name
     */
    uint16_t drv_name;
    /**
     * File number
     */
    uint16_t fnum;
    /**
     * Filename
     */
    uint8_t name[8]; /* string */
    /**
     * File extension
     */
    uint8_t ext[3]; /* string */
    /**
     * Attributes
     */
    uint8_t attr;
    /**
     * Offset
     */
    uint32_t offset; /* 32b */
    /**
     * Number of bytes to write
     */
    uint16_t num_bytes;
    /**
     * Data to write
     */
    uint8_t *data; /* (size = 'num_bytes') */
} slmp_req_file_write_t;

/**
 * \brief Lock / unlock the file lock.
 */
typedef struct slmp_req_file_set_reset_file_lock {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

} slmp_req_file_set_reset_file_lock_t;

/**
 * \brief Response of ReqFileSetResetFileLock
 */
typedef struct slmp_res_file_set_reset_file_lock {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * File lock mode
     */
    uint16_t mode;
    /**
     * Drive name
     */
    uint16_t drv_name;
    /**
     * File number
     */
    uint16_t fnum;
    /**
     * Filename
     */
    uint8_t name[8]; /* string */
    /**
     * File extension
     */
    uint8_t ext[3]; /* string */
    /**
     * File attributes
     */
    uint8_t attr;
} slmp_res_file_set_reset_file_lock_t;

/**
 * \brief Copy a file.
 */
typedef struct slmp_req_file_copy_a {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name src_pwd
 * @{
 */
    /**
     * Password of the source file
     */
    uint32_t src_pwd; /* 24b */
    /**
     * Setting flag
     */
    uint8_t src_flag;
/**
 * @}
 */
    /**
     * Source drive name
     */
    uint16_t src_drv_name;
    /**
     * Source file number
     */
    uint16_t src_fnum;
    /**
     * Source filename
     */
    uint8_t src_name[8]; /* string */
    /**
     * Source file extension
     */
    uint8_t src_ext[3]; /* string */
    /**
     * Source file attributes
     */
    uint8_t src_attr;
    /**
     * Source offset address
     */
    uint32_t src_offset; /* 32b */
    /**
     * Number of bytes to copy
     */
    uint16_t num_bytes;
    /**
     * Copy mode
     */
    uint16_t mode;
/**
 * \name dst_pwd
 * @{
 */
    /**
     * Destination file password
     */
    uint32_t dst_pwd; /* 24b */
    /**
     * Flag
     */
    uint8_t dst_flag;
/**
 * @}
 */
    /**
     * Destination drive name
     */
    uint16_t dst_drv_name;
    /**
     * Destination file number
     */
    uint16_t dst_fnum;
    /**
     * Destination file name
     */
    uint8_t dst_name[8]; /* string */
    /**
     * Destination file extension
     */
    uint8_t dst_ext[3]; /* string */
    /**
     * Destination file attributes
     */
    uint8_t dst_attr;
    /**
     * Destination offset address
     */
    uint32_t dst_offset; /* 32b */
} slmp_req_file_copy_a_t;

/**
 * \brief Copy a file.
 */
typedef struct slmp_req_file_copy_b {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Dummy data
     */
    uint8_t dummy[8];
    /**
     * Destination file password
     */
    uint8_t dst_pwd[4]; /* string */
    /**
     * Destination drive name
     */
    uint16_t dst_drv_name;
    /**
     * Length of destination file name
     */
    uint16_t dst_name_len;
    /**
     * Destination file name
     */
    uint8_t *dst_name; /* (size = 'dst_name_len') */
    /**
     * Source file password
     */
    uint8_t src_pwd[4]; /* string */
    /**
     * Source drive name
     */
    uint16_t src_drv_name;
    /**
     * Length of source file name
     */
    uint16_t src_name_len;
    /**
     * Source filename
     */
    uint8_t *src_name; /* (size = 'src_name_len') */
} slmp_req_file_copy_b_t;

/**
 * \brief Delete an existing file.
 */
typedef struct slmp_req_file_delete_a {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name pwd
 * @{
 */
    /**
     * File password
     */
    uint32_t pwd; /* 24b */
    /**
     * Setting flag
     */
    uint8_t flag;
/**
 * @}
 */
    /**
     * Drive name
     */
    uint16_t drv_name;
    /**
     * File number
     */
    uint16_t fnum;
    /**
     * File name
     */
    uint8_t name[8]; /* string */
    /**
     * File extension
     */
    uint8_t ext[3]; /* string */
    /**
     * File attributes
     */
    uint8_t attr;
} slmp_req_file_delete_a_t;

/**
 * \brief Delete an existing file.
 */
typedef struct slmp_req_file_delete_b {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * File password
     */
    uint8_t pwd[4]; /* string */
    /**
     * Drive name
     */
    uint16_t drv_name;
    /**
     * Length of file name
     */
    uint16_t name_len;
    /**
     * Filename
     */
    uint8_t *name; /* (size = 'name_len') */
} slmp_req_file_delete_b_t;

/**
 * \brief Retrieves information about a file or directory.
 */
typedef struct slmp_req_read_dir_unicode {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Reserved
     */
    uint32_t reserved4; /* 32b */
    /**
     * Drive name
     */
    uint16_t drv_name;
    /**
     * Starting file number
     */
    uint16_t fnum_begin;
    /**
     * Number of files
     */
    uint16_t num_files;
    /**
     * Length of directory name
     */
    uint8_t name_len;
    /**
     * Directory name
     */
    uint8_t *name_utf16le; /* (size = 'name_len') */
    /**
     * Reserved
     */
    uint16_t reserved2;
} slmp_req_read_dir_unicode_t;

/**
 * \brief Response of ReqReadDirUnicode.
 */
typedef struct slmp_res_read_dir_unicode {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of entries
     */
    uint16_t num_entries;
    /**
     * Last file number
     */
    uint32_t last_fnum; /* 32b */
    /**
     * Entries
     */
    uint8_t entries[1]; /* variable size */
} slmp_res_read_dir_unicode_t;

/**
 * \brief File information entry.
 */
typedef struct slmp_res_read_dir_unicode_entry {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Length of file name
     */
    uint16_t name_len;
    /**
     * File name
     */
    uint8_t *name; /* (size = 'name_len') */
    /**
     * File attributes
     */
    uint16_t attr;

    union {
        uint8_t bin[7]; /* string */
        uint8_t ascii[14]; /* string */
    } reserved7;

    uint16_t reserved2_1;
    /**
     * Time last edited
     */
    uint16_t last_edit_time;
    /**
     * Date last edited
     */
    uint16_t last_edit_date;

    uint16_t reserved2_2;
    /**
     * File size
     */
    uint32_t size; /* 32b */
} slmp_res_read_dir_unicode_entry_t;

/**
 * \brief Read file number of the specified file.
 */
typedef struct slmp_req_search_dir_file {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Password
     */
    uint8_t pwd[4]; /* string */
    /**
     * Drive name
     */
    uint16_t drv_name;
    /**
     * Length of directory name (0)
     */
    uint16_t num_dir_name;
    /**
     * Length of filename
     */
    uint16_t num_file_name;
    /**
     * Filename
     */
    uint8_t *file_name; /* (size = 'num_file_name') */
} slmp_req_search_dir_file_t;

/**
 * \brief Response of ReqSearchDirFile.
 */
typedef struct slmp_res_search_dir_file {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * File number
     */
    uint16_t fnum;
} slmp_res_search_dir_file_t;

/**
 * \brief Create a new file.
 */
typedef struct slmp_req_new_file_a {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name pwd
 * @{
 */
    /**
     * Password
     */
    uint32_t pwd; /* 24b */
    /**
     * Setting flags
     */
    uint8_t flag;
/**
 * @}
 */
    /**
     * Drive name
     */
    uint16_t drv_name;

    uint32_t reserved4; /* 32b */
    /**
     * Filename
     */
    uint8_t name[8]; /* string */
    /**
     * File extension
     */
    uint8_t ext[3]; /* string */
    /**
     * File attributes
     */
    uint8_t attr;
    /**
     * File size
     */
    uint32_t size; /* 32b */

    uint16_t reserved2;
} slmp_req_new_file_a_t;

/**
 * \brief Response of command ReqNewFileA.
 */
typedef struct slmp_res_new_file_a {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * File number
     */
    uint16_t fnum;
} slmp_res_new_file_a_t;

/**
 * \brief Create a new file.
 */
typedef struct slmp_req_new_file_b {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Password
     */
    uint8_t pwd[4]; /* string */
    /**
     * Drive name
     */
    uint16_t drv_name;
    /**
     * File size
     */
    uint32_t size; /* 32b */
    /**
     * Length of file name
     */
    uint16_t name_len;
    /**
     * Filename
     */
    uint8_t *name; /* (size = 'name_len') */
} slmp_req_new_file_b_t;

/**
 * \brief Change file creation date and time.
 */
typedef struct slmp_req_file_change_date {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Password
     */
    uint8_t pwd[4]; /* string */
    /**
     * Drive name
     */
    uint16_t drv_name;
    /**
     * Date
     */
    uint16_t date;
    /**
     * Time
     */
    uint16_t time;
    /**
     * Length of filename
     */
    uint16_t name_len;
    /**
     * Filename
     */
    uint8_t *name; /* (size = 'name_len') */
} slmp_req_file_change_date_t;

/**
 * \brief Open a file.
 */
typedef struct slmp_req_open_file {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Password
     */
    uint8_t pwd[4]; /* string */
    /**
     * Open mode
     */
    uint16_t mode;
    /**
     * Drive name
     */
    uint16_t drv_name;
    /**
     * Length of filename
     */
    uint16_t name_len;
    /**
     * Filename
     */
    uint8_t *name; /* (size = 'name_len') */
} slmp_req_open_file_t;

/**
 * \brief Response of ReqOpenFile.
 */
typedef struct slmp_res_open_file {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * File pointer
     */
    uint16_t fp;
} slmp_res_open_file_t;

/**
 * \brief Read file.
 */
typedef struct slmp_req_read_file {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * File pointer
     */
    uint16_t fp;
    /**
     * Offset
     */
    uint32_t offset; /* 32b */
    /**
     * Number of bytes to read
     */
    uint16_t num_bytes;
} slmp_req_read_file_t;

/**
 * \brief Response of ReqReadFile.
 */
typedef struct slmp_res_read_file {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of bytes read
     */
    uint16_t num_bytes;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_res_read_file_t;

/**
 * \brief Write file.
 */
typedef struct slmp_req_write_file {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * File pointer
     */
    uint16_t fp;
    /**
     * Offset
     */
    uint32_t offset; /* 32b */
    /**
     * Number of bytes to write
     */
    uint16_t num_bytes;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_write_file_t;

/**
 * \brief Response of ReqWriteFile.
 */
typedef struct slmp_res_write_file {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of bytes written
     */
    uint16_t num_bytes;
} slmp_res_write_file_t;

/**
 * \brief Close a opened file pointer.
 */
typedef struct slmp_req_close_file {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * File pointer
     */
    uint16_t fp;
    /**
     * Close type
     */
    uint16_t type;
} slmp_req_close_file_t;


#include "slmp/_poppack.h" 

#endif /* FILECMD_H */
