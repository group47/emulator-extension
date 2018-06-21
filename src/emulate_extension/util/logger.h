//
// Created by fpn17 on 15/06/18.
//

#ifndef SRC_LOGGER_H
#define SRC_LOGGER_H


#include "entry_point.h"
#include "../state/emulator_state.h"


struct SectionDescriptor {
    struct CPUState state;
};

struct SectionMetaData {
    bool first;
    struct CPUState state;
};


enum LogEntryType {
    CPUSTATE_LOGENTRY,
    COPROCESSOR_REGISTER_TRANSFER_LOGENTRY,
    COPROCESSOR_DATA_TRANSFER_LOGENTRY,
    COPROCESSOR_DATA_OPERATION_LOG_ENTRY,
    SECTION_META_DATA,
    SECTION_DESCRIPTOR,
};

struct LogEntry {
    enum LogEntryType type;
    union {
        struct CPUState state;
        struct CoprocessorRegisterTransferInstruction registerTransferInstruction;
        struct CoprocessorDataOperationsInstruction dataOperationsInstruction;
        struct CoprocessorDataTransfersInstruction dataTransfersInstruction;
        struct SectionMetaData sectionMetaData;
        struct SectionDescriptor sectionDescriptor;
    };
};


void add_to_log(struct LogEntry entry);

void print_debug_instruction(struct CPUState);

void init_logging(enum CommandLineFlags flags);

void print_registers(enum CommandLineFlags);

void print_debug_coprocessor_register_transfer(struct CoprocessorRegisterTransferInstruction instruction);

void print_debug_coprocessor_data_transfer(struct CoprocessorDataTransfersInstruction instruction);

void print_debug_coprocessor_data_operations(struct CoprocessorDataOperationsInstruction instruction);

void enable_log();

void disable_log();

#endif //SRC_LOGGER_H
