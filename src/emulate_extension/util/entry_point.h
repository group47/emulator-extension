//
// Created by fpn17 on 03/06/18.
//

#ifndef SRC_ENTRY_POINT_H
#define SRC_ENTRY_POINT_H

#include <stdio.h>


enum CommandLineFlags {
    DEBUG_PRINT_REGISTER = 0b00000000000000001,
    HELP_MESSAGE = 0b00000000000000010,
    DISASSEMBLE = 0b00000000000000100,
    TERMINATE_ON__ZERO = 0b00000000000001000,
    TERMINATE_AFTER_200 = 0b00000000000010000,
    MEMORY = 0b00000000000100000,
    USE_THUMB = 0b00000000001000000,
    SP_PRINT_OFFSET_SET = 0b00000000010000000,
    PC_PRINT_OFFSET_SET = 0b00000000100000000,
    ZIMAGE = 0b00000001000000000,
    KERNEL = 0b00000010000000000,
    QEMU_PRINT = 0b00000100000000000,
    INVALID = 0b00001000000000000,
    MMAP = 0b00010000000000000

};


void main_emulation_entry_point(enum CommandLineFlags, FILE *, FILE *);

FILE *get_logfile();

void set_logfile(FILE *fp);

#endif //SRC_ENTRY_POINT_H
