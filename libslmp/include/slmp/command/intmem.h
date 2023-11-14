/**
 * \file intmem.h
 * 
 * \brief Internal Memory (Device) Commands.
 * 
 * This file was generated from C:\work\libslmp2\libslmp\CommandCodecGenerator\CgeFiles\InternalMemory.cge by CCGEN program.
 */

#ifndef INTMEM_H
#define INTMEM_H

#include "slmp/command/cmdhdr.h" 
#include "slmp/_pushpack4.h" 


/**
 * \brief ReqDeviceRead (ReqDeviceReadInextension)
 */
typedef struct slmp_req_device_read {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name tarDevice
 * @{
 */
    /**
     * Memory type.
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address of first unit.
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[8]; /* string */
        } ascii;
    } addr_begin;
/**
 * @}
 */
/**
 * \name deviceNum
 * @{
 */
    /**
     * Number of units
     */
    uint16_t num;
/**
 * @}
 */
} slmp_req_device_read_t;

/**
 * \brief ReqDeviceRead (ReqDeviceReadExtension)
 */
typedef struct slmp_req_device_read_ext {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name tarDevice
 * @{
 */
    /**
     * Indirect specification
     */
    union {
        uint16_t bin;
        uint8_t ascii[2]; /* string */
    } indir_spec;
    /**
     * Extension specification
     */
    union {
        uint16_t bin;
        uint8_t ascii[4]; /* string */
    } ext_spec;
    /**
     * Extension specification modification
     */
    union {
        uint16_t bin;
        union {
            uint8_t s[3]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } ext_spec_mod;
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address of first unit
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[10]; /* string */
        } ascii;
    } addr_begin;
    /**
     * Device modification
     */
    union {
        union {
            uint8_t s[3]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } dev_mod;
    /**
     * Direct memory specification
     */
    union {
        uint8_t bin;
    } dir_mem_spec;
/**
 * @}
 */
/**
 * \name deviceNum
 * @{
 */
    /**
     * Number of units
     */
    uint16_t num;
/**
 * @}
 */
} slmp_req_device_read_ext_t;

/**
 * \brief ReqDeviceWrite (ReqDeviceWriteInextension)
 */
typedef struct slmp_req_device_write {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name tarDevice
 * @{
 */
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address of first unit
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[8]; /* string */
        } ascii;
    } addr_begin;
/**
 * @}
 */
/**
 * \name deviceNum
 * @{
 */
    /**
     * Number of units to write
     */
    uint16_t num;
/**
 * @}
 */
/**
 * \name data
 * @{
 */
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
/**
 * @}
 */
} slmp_req_device_write_t;

/**
 * \brief ReqDeviceWrite (ReqDeviceWriteExtension)
 */
typedef struct slmp_req_device_write_ext {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name tarDevice
 * @{
 */
    /**
     * Indirect specification
     */
    union {
        uint16_t bin;
        uint16_t ascii;
    } indir_spec;
    /**
     * Extension specification
     */
    union {
        uint16_t bin;
        uint8_t ascii[4]; /* string */
    } ext_spec;
    /**
     * Extension specification modification
     */
    union {
        uint16_t bin;
        union {
            uint8_t s[3]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } ext_spec_mod;
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address of first unit
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[10]; /* string */
        } ascii;
    } addr_begin;
    /**
     * Device modification
     */
    union {
        union {
            uint8_t s[3]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } dev_mod;
    /**
     * Direct memory specification
     */
    union {
        uint8_t bin;
    } dir_mem_spec;
/**
 * @}
 */
/**
 * \name deviceNum
 * @{
 */
    /**
     * Number of units to write
     */
    uint16_t num;
/**
 * @}
 */
/**
 * \name data
 * @{
 */
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
/**
 * @}
 */
} slmp_req_device_write_ext_t;

/**
 * \brief ReqDeviceReadRandom (noMonitorDeviceInextension)
 */
typedef struct slmp_req_device_read_random {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of word units
     */
    uint8_t num_wd;
    /**
     * Number of dword units
     */
    uint8_t num_dwd;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_device_read_random_t;

/**
 * \brief Use along with ReqDeviceReadRandom to indicate a word or double word unit
 * to read from.
 */
typedef struct slmp_req_device_read_random_unit {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name unit
 * @{
 */
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[8]; /* string */
        } ascii;
    } addr;
/**
 * @}
 */
} slmp_req_device_read_random_unit_t;

/**
 * \brief ReqDeviceReadRandom (noMonitorDeviceExtension)
 */
typedef struct slmp_req_device_read_random_ext {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of word units
     */
    uint8_t num_wd;
    /**
     * Number of dword units
     */
    uint8_t num_dwd;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_device_read_random_ext_t;

/**
 * \brief Use along with ReqDeviceReadRandomExt to indicate a word unit to read from.
 */
typedef struct slmp_req_device_read_random_ext_word_unit {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name word_unit
 * @{
 */
    /**
     * Indirect specification
     */
    union {
        uint16_t bin;
        uint8_t ascii[2]; /* string */
    } indir_spec;
    /**
     * Extension specification
     */
    union {
        uint16_t bin;
        uint8_t ascii[4]; /* string */
    } ext_spec;
    /**
     * Extension specification modification
     */
    union {
        uint16_t bin;
        union {
            uint8_t s[3]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } ext_spec_mod;
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[10]; /* string */
        } ascii;
    } addr;
    /**
     * Device modification
     */
    union {
        union {
            uint8_t s[3]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } dev_mod;
    /**
     * Direct memory specification
     */
    union {
        uint8_t bin;
    } dir_mem_spec;
/**
 * @}
 */
} slmp_req_device_read_random_ext_word_unit_t;

/**
 * \brief Use along with ReqDeviceReadRandomExt to indicate a double-word unit 
 * to read from.
 */
typedef struct slmp_req_device_read_random_ext_dword_unit {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name dword_unit
 * @{
 */
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[8]; /* string */
        } ascii;
    } addr;
/**
 * @}
 */
} slmp_req_device_read_random_ext_dword_unit_t;

/**
 * \brief ReqDeviceWriteRandom (Word Access) (ReqDeviceWriteRandomInextension)
 */
typedef struct slmp_req_device_write_random {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of word units
     */
    uint8_t num_wd;
    /**
     * Number of dword units
     */
    uint8_t num_dwd;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_device_write_random_t;

/**
 * \brief Used with ReqDeviceWriteRandom command indicating the address of a word unit
 * and the data to be written into that unit.
 */
typedef struct slmp_req_device_write_random_word_unit {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name word_unit
 * @{
 */
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[8]; /* string */
        } ascii;
    } addr;
/**
 * @}
 */
    /**
     * Word value
     */
    uint16_t data;
} slmp_req_device_write_random_word_unit_t;

/**
 * \brief Used with ReqDeviceWriteRandom command indicating the address of a double-word
 * unit and the data to be written into that unit.
 */
typedef struct slmp_req_device_write_random_dword_unit {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name dword_unit
 * @{
 */
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[8]; /* string */
        } ascii;
    } addr;
/**
 * @}
 */
    /**
     * DWord value
     */
    uint32_t data; /* 32b */
} slmp_req_device_write_random_dword_unit_t;

/**
 * \brief ReqDeviceWriteRandom (Bit Access) (ReqDeviceWriteRandomInextension)
 */
typedef struct slmp_req_device_write_random_bit {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of bit units
     */
    uint8_t num;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_device_write_random_bit_t;

/**
 * \brief Used with ReqDeviceWriteRandomBit command indicating the address of a bit unit
 * and the data to be written into that unit.
 */
typedef struct slmp_req_device_write_random_bit_unit {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name bit_unit
 * @{
 */
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint16_t s;
            uint32_t l; /* 32b */
        } ascii;
    } mem_type;
    /**
     * Address
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[8]; /* string */
        } ascii;
    } addr;
/**
 * @}
 */
    /**
     * Bit set/reset
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint16_t s;
            uint32_t l; /* 32b */
        } ascii;
    } data;
} slmp_req_device_write_random_bit_unit_t;

/**
 * \brief ReqDeviceWriteRandom (Word Access) (ReqDeviceWriteRandomExtension)
 */
typedef struct slmp_req_device_write_random_ext {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of word units
     */
    uint8_t num_wd;
    /**
     * Number of dword units
     */
    uint8_t num_dwd;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_device_write_random_ext_t;

/**
 * \brief Used with ReqDeviceWriteRandomExt command indicating the address of a word unit
 * and the data to be written into that unit.
 */
typedef struct slmp_req_device_write_random_ext_word_unit {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name word_unit
 * @{
 */
    /**
     * Indirect specification
     */
    union {
        uint16_t bin;
        uint8_t ascii[2]; /* string */
    } indir_spec;
    /**
     * Extension specification
     */
    union {
        uint16_t bin;
        uint8_t ascii[4]; /* string */
    } ext_spec;
    /**
     * Extension specification modification
     */
    union {
        uint16_t bin;
        union {
            uint8_t s[3]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } ext_spec_mod;
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[10]; /* string */
        } ascii;
    } addr;
    /**
     * Device modification
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } ascii;
    } dev_mod;
    /**
     * Direct memory specification
     */
    union {
        uint8_t bin;
    } dir_mem_spec;
/**
 * @}
 */
    /**
     * Word value
     */
    uint16_t data;
} slmp_req_device_write_random_ext_word_unit_t;

/**
 * \brief Used with ReqDeviceWriteRandomExt command indicating the address of a dword unit
 * and the data to be written into that unit.
 */
typedef struct slmp_req_device_write_random_ext_dword_unit {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name dword_unit
 * @{
 */
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[8]; /* string */
        } ascii;
    } addr;
/**
 * @}
 */
    /**
     * DWORD value
     */
    uint32_t data; /* 32b */
} slmp_req_device_write_random_ext_dword_unit_t;

/**
 * \brief ReqDeviceWriteRandom (Bit Access) (ReqDeviceWriteRandomExtension)
 */
typedef struct slmp_req_device_write_random_ext_bit {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of bit units
     */
    uint8_t num;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_device_write_random_ext_bit_t;

/**
 * \brief Used with ReqDeviceWriteRandomExtBit command indicating the address of a
 * bit unit and the data to be written into that unit.
 */
typedef struct slmp_req_device_write_random_ext_bit_unit {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name bit_unit
 * @{
 */
    /**
     * Indirect specification
     */
    union {
        uint16_t bin;
        uint8_t ascii[2]; /* string */
    } indir_spec;
    /**
     * Extension specification
     */
    union {
        uint16_t bin;
        uint8_t ascii[4]; /* string */
    } ext_spec;
    /**
     * Extension specification modification
     */
    union {
        uint16_t bin;
        union {
            uint8_t s[3]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } ext_spec_mod;
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[10]; /* string */
        } ascii;
    } addr;
    /**
     * Device modification
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } ascii;
    } dev_mod;
    /**
     * Direct memory specification
     */
    union {
        uint8_t bin;
    } dir_mem_spec;
/**
 * @}
 */
    /**
     * Bit set / reset
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint16_t s;
            uint32_t l; /* 32b */
        } ascii;
    } data;
} slmp_req_device_write_random_ext_bit_unit_t;

/**
 * \brief ReqDeviceReadBlock (ReqDeviceReadBlockInextension)
 */
typedef struct slmp_req_device_read_block {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of word memory blocks
     */
    uint8_t num_wd;
    /**
     * Number of bit memory blocks
     */
    uint8_t num_bit;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_device_read_block_t;

/**
 * \brief Used along with ReqDeviceReadBlock command indicating a consecutive word memory
 * block to be read from.
 */
typedef struct slmp_req_device_read_block_word_block {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name typeWdDevice
 * @{
 */
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address of first unit
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[8]; /* string */
        } ascii;
    } addr_begin;
/**
 * @}
 */
    /**
     * Number of word units
     */
    uint16_t num;
} slmp_req_device_read_block_word_block_t;

/**
 * \brief Used along with ReqDeviceReadBlock command indicating a consecutive bit memory
 * block to be read from.
 */
typedef struct slmp_req_device_read_block_bit_block {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name typeBtDevice
 * @{
 */
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address of first unit
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[8]; /* string */
        } ascii;
    } addr_begin;
/**
 * @}
 */
    /**
     * Number of bit units
     */
    uint16_t num;
} slmp_req_device_read_block_bit_block_t;

/**
 * \brief ReqDeviceReadBlock (ReqDeviceReadBlockExtension)
 */
typedef struct slmp_req_device_read_block_ext {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of word memory blocks
     */
    uint8_t num_wd;
    /**
     * Number of bit memory blocks
     */
    uint8_t num_bit;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_device_read_block_ext_t;

/**
 * \brief Used along with ReqDeviceReadBlockExt command indicating a consecutive word 
 * memory block to be read from.
 */
typedef struct slmp_req_device_read_block_ext_word_block {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name typeWdDevice
 * @{
 */
    /**
     * Indirect specification
     */
    union {
        uint16_t bin;
        uint8_t ascii[2]; /* string */
    } indir_spec;
    /**
     * Extension specification
     */
    union {
        uint16_t bin;
        uint8_t ascii[4]; /* string */
    } ext_spec;
    /**
     * Extension specification modification
     */
    union {
        uint16_t bin;
        union {
            uint8_t s[3]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } ext_spec_mod;
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address of first unit
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[10]; /* string */
        } ascii;
    } addr_begin;
    /**
     * Device modification
     */
    union {
        union {
            uint8_t s[3]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } dev_mod;
    /**
     * Direct memory specification
     */
    union {
        uint8_t bin;
    } dir_mem_spec;
/**
 * @}
 */
    /**
     * Number of word units
     */
    uint16_t num;
} slmp_req_device_read_block_ext_word_block_t;

/**
 * \brief Used along with ReqDeviceReadBlockExt command indicating a consecutive bit
 * memory block to be read from.
 */
typedef struct slmp_req_device_read_block_ext_bit_block {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name typeBtDevice
 * @{
 */
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address of first unit
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[8]; /* string */
        } ascii;
    } addr_begin;
/**
 * @}
 */
    /**
     * Number of bit units
     */
    uint16_t num;
} slmp_req_device_read_block_ext_bit_block_t;

/**
 * \brief ReqDeviceWriteBlock (ReqDeviceWriteBlockInextension)
 */
typedef struct slmp_req_device_write_block {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of word memory blocks
     */
    uint8_t num_wd;
    /**
     * Number of bit memory blocks
     */
    uint8_t num_bit;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_device_write_block_t;

/**
 * \brief Used along with ReqDeviceWriteBlock command indicating a consecutive word 
 * memory block and the data to be written into that block.
 */
typedef struct slmp_req_device_write_block_word_block {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name typeWdDevice
 * @{
 */
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address of first unit
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[8]; /* string */
        } ascii;
    } addr_begin;
/**
 * @}
 */
    /**
     * Number of word units
     */
    uint16_t num;
    /**
     * Data block
     */
    uint8_t data[1]; /* variable size */
} slmp_req_device_write_block_word_block_t;

/**
 * \brief Used along with ReqDeviceWriteBlock command indicating a consecutive bit 
 * memory block and the data to be written into that block.
 */
typedef struct slmp_req_device_write_block_bit_block {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name typeBtDevice
 * @{
 */
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address of first unit
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[8]; /* string */
        } ascii;
    } addr_begin;
/**
 * @}
 */
    /**
     * Number of bit units
     */
    uint16_t num;
    /**
     * Data block
     */
    uint8_t data[1]; /* variable size */
} slmp_req_device_write_block_bit_block_t;

/**
 * \brief ReqDeviceWriteBlock (ReqDeviceWriteBlockExtension)
 */
typedef struct slmp_req_device_write_block_ext {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of word memory blocks
     */
    uint8_t num_wd;
    /**
     * Number of bit units
     */
    uint8_t num_bit;
    /**
     * Data blocks
     */
    uint8_t data[1]; /* variable size */
} slmp_req_device_write_block_ext_t;

/**
 * \brief Used along with ReqDeviceWriteBlockExt command indicating a consecutive word 
 * memory block and the data to be written into that block.
 */
typedef struct slmp_req_device_write_block_ext_word_block {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name typeWdDevice
 * @{
 */
    /**
     * Indirect specification
     */
    union {
        uint16_t bin;
        uint8_t ascii[2]; /* string */
    } indir_spec;
    /**
     * Extension specification
     */
    union {
        uint16_t bin;
        uint8_t ascii[4]; /* string */
    } ext_spec;
    /**
     * Extension specification modification
     */
    union {
        uint16_t bin;
        union {
            uint8_t s[3]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } ext_spec_mod;
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address of first unit 
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[10]; /* string */
        } ascii;
    } addr_begin;
    /**
     * Device modification
     */
    union {
        union {
            uint8_t s[3]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } dev_mod;
    /**
     * Direct memory specification
     */
    union {
        uint8_t bin;
    } dir_mem_spec;
/**
 * @}
 */
    /**
     * Number of units
     */
    uint16_t num;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_device_write_block_ext_word_block_t;

/**
 * \brief Used along with ReqDeviceWriteBlockExt command indicating a consecutive bit 
 * memory block and the data to be written into that block.
 */
typedef struct slmp_req_device_write_block_ext_bit_block {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

/**
 * \name typeBtDevice
 * @{
 */
    /**
     * Memory type
     */
    union {
        union {
            uint8_t s;
            uint16_t l;
        } bin;
        union {
            uint8_t s[2]; /* string */
            uint8_t l[4]; /* string */
        } ascii;
    } mem_type;
    /**
     * Address of first unit
     */
    union {
        union {
            uint32_t s; /* 24b */
            uint32_t l; /* 32b */
        } bin;
        union {
            uint8_t s[6]; /* string */
            uint8_t l[8]; /* string */
        } ascii;
    } addr_begin;
/**
 * @}
 */
    /**
     * Number of bit units
     */
    uint16_t num;
    /**
     * Data block
     */
    uint8_t data[1]; /* variable size */
} slmp_req_device_write_block_ext_bit_block_t;

/**
 * \brief ReqLabelRead (ReqLabelReadInextension)
 */
typedef struct slmp_req_label_read {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of labels
     */
    uint16_t num;
    /**
     * Reserved
     */
    uint16_t reserved2;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_label_read_t;

/**
 * \brief Used along with ReqLabelRead command.
 */
typedef struct slmp_req_label_read_label {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Length of label name
     */
    uint16_t label_len;
    /**
     * Label
     */
    uint8_t *label; /* (size = 'label_len') */
    /**
     * Reading unit specification
     */
    uint8_t read_unit;
    /**
     * Reserved 
     */
    uint8_t reserved1;
    /**
     * Length of array data to read
     */
    uint16_t data_len;
} slmp_req_label_read_label_t;

/**
 * \brief ReqLabelRead (ReqLabelReadExtension)
 */
typedef struct slmp_req_label_read_ext {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of labels
     */
    uint16_t num;
    /**
     * Number of extension specification labels
     */
    uint16_t num_ext;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_label_read_ext_t;

/**
 * \brief Used along with ReqLabelReadExt command.
 */
typedef struct slmp_req_label_read_ext_label_ext {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Length of label name extension
     */
    uint16_t label_ext_len;
    /**
     * Label name extension
     */
    uint8_t *label_ext; /* (size = 'label_ext_len') */
} slmp_req_label_read_ext_label_ext_t;

/**
 * \brief Used along with ReqLabelReadExt command.
 */
typedef struct slmp_req_label_read_ext_label {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Label name length
     */
    uint16_t label_len;
    /**
     * Label name
     */
    uint8_t *label; /* (size = 'label_len') */
    /**
     * Reading unit specification
     */
    uint8_t read_unit;
    /**
     * Reserved
     */
    uint8_t reserved1;
    /**
     * Length of array data to read
     */
    uint16_t data_len;
} slmp_req_label_read_ext_label_t;

/**
 * \brief Response of ReqLabelRead and ReqLabelReadExt commands.
 */
typedef struct slmp_res_label_read {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of labels
     */
    uint8_t num;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_res_label_read_t;

/**
 * \brief Used along with ResLabelRead.
 */
typedef struct slmp_res_label_read_label {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Data type ID
     */
    uint8_t type_id;
    /**
     * Reading unit specification.
     */
    uint8_t read_unit;
    /**
     * Data length
     */
    uint16_t data_len;
    /**
     * Data array read
     */
    uint8_t *data; /* (size = 'data_len') */
} slmp_res_label_read_label_t;

/**
 * \brief ReqLabelWrite (ReqLabelWriteInextension)
 */
typedef struct slmp_req_label_write {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of labels
     */
    uint16_t num;
    /**
     * Reserved 0
     */
    uint16_t reserved2;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_label_write_t;

/**
 * \brief Used with ReqLabelWrite command to indicate a label and the data to be written
 * to the memory location of that label.
 */
typedef struct slmp_req_label_write_label {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Length of label name
     */
    uint16_t label_len;
    /**
     * Label name
     */
    uint8_t *label; /* (size = 'label_len') */
    /**
     * Write unit specification
     */
    uint8_t write_unit;
    /**
     * Reserved
     */
    uint8_t reserved1;
    /**
     * Length of data to write
     */
    uint16_t data_len;
    /**
     * Data to write
     */
    uint8_t *data; /* (size = 'data_len') */
} slmp_req_label_write_label_t;

/**
 * \brief ReqLabelWrite (ReqLabelWriteExtension)
 */
typedef struct slmp_req_label_write_ext {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of labels
     */
    uint16_t num;
    /**
     * Number of extension specification labels
     */
    uint16_t num_ext;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_label_write_ext_t;

/**
 * \brief Used with ReqLabelWriteExt.
 */
typedef struct slmp_req_label_write_ext_label_ext {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Length of label name extension
     */
    uint16_t label_ext_len;
    /**
     * Label name extension
     */
    uint8_t *label_ext; /* (size = 'label_ext_len') */
} slmp_req_label_write_ext_label_ext_t;

/**
 * \brief Used with ReqLabelWriteExt command to indicate a label and the data to be 
 * written to the memory location of that label.
 */
typedef struct slmp_req_label_write_ext_label {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Length of label name
     */
    uint16_t label_len;
    /**
     * Label name
     */
    uint8_t *label; /* (size = 'label_len') */
    /**
     * Write unit specification
     */
    uint8_t write_unit;
    /**
     * Reserved
     */
    uint8_t reserved1;
    /**
     * Length of data to write
     */
    uint16_t data_len;
    /**
     * Data to write
     */
    uint8_t *data; /* (size = 'data_len') */
} slmp_req_label_write_ext_label_t;

/**
 * \brief ReqLabelReadRandom (ReqLabelReadRandomInextension)
 */
typedef struct slmp_req_label_read_random {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of labels
     */
    uint16_t num;
    /**
     * Reserved
     */
    uint16_t reserved2;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_label_read_random_t;

/**
 * \brief Used with ReqLabelReadRandom to indicate a label to read.
 */
typedef struct slmp_req_label_read_random_label {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Length of label name
     */
    uint16_t label_len;
    /**
     * Label name
     */
    uint8_t *label; /* (size = 'label_len') */
} slmp_req_label_read_random_label_t;

/**
 * \brief ReqLabelReadRandom (ReqLabelReadRandomExtension)
 */
typedef struct slmp_req_label_read_random_ext {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of labels
     */
    uint16_t num;
    /**
     * Number of extension specification labels
     */
    uint16_t num_ext;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_label_read_random_ext_t;

/**
 * \brief Used along with ReqLabelReadRandomExt command.
 */
typedef struct slmp_req_label_read_random_ext_label_ext {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Length of label name extension
     */
    uint16_t label_ext_len;
    /**
     * Label name extension
     */
    uint8_t *label_ext; /* (size = 'label_ext_len') */
} slmp_req_label_read_random_ext_label_ext_t;

/**
 * \brief Used along with ReqLabelReadRandomExt command.
 */
typedef struct slmp_req_label_read_random_ext_label {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Length of label name
     */
    uint16_t label_len;
    /**
     * Label name
     */
    uint8_t *label; /* (size = 'label_len') */
} slmp_req_label_read_random_ext_label_t;

/**
 * \brief Response of ReqLabelReadRandom and ReqLabelReadRandomExt commands.
 */
typedef struct slmp_res_label_read_random {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of labels
     */
    uint16_t num;
    /**
     * Response data
     */
    uint8_t data[1]; /* variable size */
} slmp_res_label_read_random_t;

/**
 * \brief Used along with ResLabelReadRandom.
 */
typedef struct slmp_res_label_read_random_label {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Data type ID
     */
    uint8_t type_id;
    /**
     * Reserved
     */
    uint8_t reserved1;
    /**
     * Data length
     */
    uint16_t data_len;
    /**
     * Data
     */
    uint8_t *data; /* (size = 'data_len') */
} slmp_res_label_read_random_label_t;

/**
 * \brief ReqLabelWriteRandom (ReqLabelWriteRandomInextension) 
 */
typedef struct slmp_req_label_write_random {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of labels
     */
    uint16_t num;
    /**
     * Reserved
     */
    uint16_t reserved2;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_label_write_random_t;

/**
 * \brief Used along with ReqLabelWriteRandom command.
 */
typedef struct slmp_req_label_write_random_label {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Label name length
     */
    uint16_t label_len;
    /**
     * Label name
     */
    uint8_t *label; /* (size = 'label_len') */
    /**
     * Data length
     */
    uint16_t data_len;
    /**
     * Data to write
     */
    uint8_t *data; /* (size = 'data_len') */
} slmp_req_label_write_random_label_t;

/**
 * \brief ReqLabelWriteRandom (ReqLabelWriteRandomExtension)
 */
typedef struct slmp_req_label_write_random_ext {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Number of labels
     */
    uint16_t num;
    /**
     * Number of extension specification labels
     */
    uint16_t num_ext;
    /**
     * Data
     */
    uint8_t data[1]; /* variable size */
} slmp_req_label_write_random_ext_t;

/**
 * \brief Used along with ReqLabelWriteRandomExt command.
 */
typedef struct slmp_req_label_write_random_ext_label_ext {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Length of label name extension
     */
    uint16_t label_ext_len;
    /**
     * Label name extension
     */
    uint8_t *label_ext; /* (size = 'label_ext_len') */
} slmp_req_label_write_random_ext_label_ext_t;

/**
 * \brief Used along with ReqLabelWriteRandomExt command.
 */
typedef struct slmp_req_label_write_random_ext_label {
    /** Header */ 
    slmp_cmd_hdr_t hdr; 

    /**
     * Label name length
     */
    uint16_t label_len;
    /**
     * Label name
     */
    uint8_t *label; /* (size = 'label_len') */
    /**
     * Data length
     */
    uint16_t data_len;
    /**
     * Data
     */
    uint8_t *data; /* (size = 'data_len') */
} slmp_req_label_write_random_ext_label_t;


#include "slmp/_poppack.h" 

#endif /* INTMEM_H */
