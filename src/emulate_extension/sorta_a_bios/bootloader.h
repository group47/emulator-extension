//
// Created by fpn17 on 11/06/18.
//

#ifndef SRC_BOOTLOADER_H
#define SRC_BOOTLOADER_H

#include <stdio.h>
#include <stdint.h>
#include "../util/entry_point.h"

#define START_ADDRESS_LOCATION_KERNEL 0x28
#define END_ADDRESS_LOCATION_KERNEL 0x2C
#define KERNEL_LOAD_TO_ADDRESS 0x10000
#define PARAMETER_BLOCK_START_ADDRESS 0x100
#define MAGIC_ARM_BOOT_NUMBER 0x016F2818
#define MAGIC_NUMBER_LOCATION 0x24


void boot(FILE *kernel_binary, enum CommandLineFlags);

struct ATAG_CORE {
    uint32_t flags;
    uint32_t pagesize;
    uint32_t rootdev;
};

struct ATAG_MEM {
    uint32_t size;
    uint32_t start;
};

struct ATAG_VIDEOTEXT {
    uint8_t x;
    uint8_t y;
    uint16_t video_page;
    uint8_t video_mode;
    uint8_t video_cols;
    uint16_t video_ega_bx;
    uint8_t video_lines;
    uint8_t video_isvga;
    uint16_t video_points;
};

struct ATAG_RAMDISK {
    uint32_t flags;
    uint32_t size;
    uint32_t start;
};

struct ATAG_INITRD2 {
    uint32_t start;
    uint32_t size;
};

struct ATAG_SERIAL {
    uint64_t serial_num;
};

struct ATAG_REVISION {
    uint32_t rev;
};

struct ATAG_VIDEOLFB {
    uint16_t lfb_width;
    uint16_t lfb_height;
    uint16_t lfb_depth;
    uint16_t lfb_linelength;
    uint32_t lfb_base;
    uint32_t lfb_size;
    uint8_t red_size;
    uint8_t red_pos;
    uint8_t green_pos;
    uint8_t blue_size;
    uint8_t blue_pos;
    uint8_t rsvd_size;
    uint8_t rsvd_pos;
};

struct ATAG_CMDLINE {
    char cmdline[2048];//must be null terminated
};


enum ATAG_TAG {
    ATAG_TAG_NONE = 0x0000000,
    ATAG_TAG_CORE = 0x54410001,
    ATAG_TAG_MEM = 0x54410002,
    ATAG_TAG_VIDEOTEXT = 0x54410003,
    ATAG_TAG_RAMDISK = 0x54410004,
    ATAG_TAG_INITRD2 = 0x54410005,
    ATAG_TAG_SERIAL = 0x54410006,
    ATAG_TAG_REVISION = 0x54410007,
    ATAG_TAG_VIDEOLFB = 0x54410008,
    ATAG_TAG_CMDLINE = 0x54410009,
};

struct ATAG_HEADER {
    uint32_t size;
    enum ATAG_TAG tag;
};

struct ATAG {
    struct ATAG_HEADER header;
    union {
        struct ATAG_CORE core;
        struct ATAG_MEM mem;
        struct ATAG_VIDEOTEXT videotext;
        struct ATAG_RAMDISK ramdisk;
        struct ATAG_INITRD2 initrd2;
        struct ATAG_SERIAL serial;
        struct ATAG_REVISION revision;
        struct ATAG_VIDEOLFB videolfb;
        struct ATAG_CMDLINE atag_cmdline;
    };
};


void boot_loader_entry_point(const char *image_path, enum CommandLineFlags flags);

#endif //SRC_BOOTLOADER_H
