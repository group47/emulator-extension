//
// Created by fpn17 on 03/06/18.
//

#ifndef SRC_ENTRY_POINT_H
#define SRC_ENTRY_POINT_H

#include <stdio.h>


enum CommandLineFlags{
    DEBUG_PRINT_REGISTER = 0b0000000000001,
    HELP_MESSAGE         = 0b0000000000010,
    DISASSEMBLE          = 0b0000000000100,
    TERMINATE_ON__ZERO   = 0b0000000001000,
    TERMINATE_AFTER_200  = 0b0000000010000,
    MEMORY = 0b0000000100000,
    USE_THUMB = 0b0000001000000,
    INVALID              = 0b1000000000000

};


void main_emulation_entry_point(enum CommandLineFlags, FILE*,FILE*);
FILE * get_logfile();

#endif //SRC_ENTRY_POINT_H
