//
// Created by fpn17 on 15/06/18.
//

#ifndef SRC_LOGGER_H
#define SRC_LOGGER_H


#include "entry_point.h"
#include "emulator_state.c"
#include "../state/emulator_state.h"

enum LogEntryType {
    CPUSTATE
};

struct LogEntry {
    enum LogEntryType type;
    union {
        struct CPUState state;
    };
};


void add_to_log(struct LogEntry entry);

void print_debug_coprocessor();

void init_logging(enum CommandLineFlags flags);

void print_registers(enum CommandLineFlags);

#endif //SRC_LOGGER_H
