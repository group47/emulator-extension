//
// Created by fpn17 on 15/06/18.
//

#include "logger.h"
#include "../emulator_main.h"
#include <signal.h>
#include <stdlib.h>
#include <assert.h>


//We almost exceed a million unique states, just to setup a page table, so this value is not at all excessive
#define MAX_LOGGER_ENTRIES (1024*1024*32)
//todo if logs become unmanageable again, implement a system which only shows the last value of a loop similar to qemu

static struct LogEntry *past_states;
static uint32_t past_states_i = 0;

void print_past_registers(struct CPUState state) {
    print_debug_instruction(state);
    for (uint8_t i = 0; i < 15; ++i) {
        fprintf(get_logfile(), "R%02d=%08x\n", i, get_set_word_from_register(i, false, -1, &state));
    }
    fprintf(get_logfile(), "R%02d=%08x\n", PC_ADDRESS, get_set_word_from_register(PC_ADDRESS, false, -1, &state) - 8);
    fprintf(get_logfile(), "PSR=%08x\n", get_past_CPSR(state));
    fprintf(get_logfile(), "-Z--\nA\nsvc32\n");
}


void print_entry(struct LogEntry entry) {
    switch (entry.type) {
        case CPUSTATE_LOGENTRY:
            if (!past_decoded_valid(entry.state)) {
                return;
            }
            print_past_registers(entry.state);
            break;
        case COPROCESSOR_REGISTER_TRANSFER_LOGENTRY:
            print_debug_coprocessor_register_transfer(entry.registerTransferInstruction);
            break;
        case COPROCESSOR_DATA_TRANSFER_LOGENTRY:
            print_debug_coprocessor_data_transfer(entry.dataTransfersInstruction);
            break;
        case COPROCESSOR_DATA_OPERATION_LOG_ENTRY:
            print_debug_coprocessor_data_operations(entry.dataOperationsInstruction);
            break;
    }
}

void add_to_log(struct LogEntry entry) {
    past_states[past_states_i] = entry;
    past_states_i++;
}

static void print_logs(int signal) {
    bool should_print = false;
    for (unsigned long i = 0; i < past_states_i; ++i) {
        if (past_states[i].type == CPUSTATE_LOGENTRY) {
            const uint32_t pc = get_set_word_from_register(PC_ADDRESS, false, -1, &(past_states[i].state));
            if (pc >= get_log_start() && pc <= get_log_end()) {
                should_print = true;
            } else {
                should_print = false;
            }
        }
        if (should_print) {
            print_entry(past_states[i]);
        }
    }
}

void init_logging(enum CommandLineFlags flags) {
    signal(SIGILL, print_logs);
    signal(SIGSEGV, print_logs);
    signal(SIGABRT, print_logs);
    signal(SIGTERM, print_logs);
    signal(SIGKILL, print_logs);
    signal(SIGQUIT, print_logs);
    if (flags & BIG_LOGS_MODE) {
        assert(flags & QEMU_PRINT);
        past_states = calloc(MAX_LOGGER_ENTRIES, sizeof(struct LogEntry));

    }

}


void print_debug_coprocessor_register_transfer(struct CoprocessorRegisterTransferInstruction instruction) {
    fprintf(get_logfile(), "Coprocessor CP: %d\n", instruction.CP);
    fprintf(get_logfile(), "Coprocessor CPNum: %d\n", instruction.CPNum);
    fprintf(get_logfile(), "Coprocessor CPOpc: %d\n", instruction.CPOpc);
    fprintf(get_logfile(), "Coprocessor CRm: %d\n", instruction.CRm);
    fprintf(get_logfile(), "Coprocessor CRn: %d\n", instruction.CRn);
    fprintf(get_logfile(), "Coprocessor load/store bit: %d\n", instruction.loadStore);
    fprintf(get_logfile(), "Coprocessor Rd: %d\n", instruction.Rd);
}

void print_debug_coprocessor_data_transfer(struct CoprocessorDataTransfersInstruction instruction) {
    fprintf(get_logfile(), "Coprocesor number %d\n", instruction.CoNumber);
    fprintf(get_logfile(), "Coprocesor base register %d\n", instruction.baseRegister);
    fprintf(get_logfile(), "Coprocesor source destination register %d\n", instruction.CoSourceDestinationRegister);
    fprintf(get_logfile(), "Coprocesor load store bit %d\n", instruction.loadStoreBit);
    fprintf(get_logfile(), "Coprocesor offset %d\n", instruction.offset);
    fprintf(get_logfile(), "Coprocesor pre post indexing %d\n", instruction.prePostIndexingBit);
    fprintf(get_logfile(), "Coprocesor transfer length %d\n", instruction.transferLength);
    fprintf(get_logfile(), "Coprocesor up down bit %d\n", instruction.upDownBit);
    fprintf(get_logfile(), "Coprocesor write back bit %d\n", instruction.writeBackBit);
}

void print_debug_coprocessor_data_operations(struct CoprocessorDataOperationsInstruction instruction) {
    fprintf(get_logfile(), "Try to execute coprocessor data operations\n");
    fprintf(get_logfile(), "Coprocessor number : %d\n", instruction.CoNumber);
    fprintf(get_logfile(), "Coprocessor destination register: %d\n", instruction.CoDestinationRegister);
    fprintf(get_logfile(), "Coprocessor cooperand register position 3: %d\n", instruction.CoOperandRegister_position3);
    fprintf(get_logfile(), "Coprocessor cooperand register position 19: %d\n",
            instruction.CoOperandRegister_position19);
    fprintf(get_logfile(), "Coprocessor operation code: %d\n", instruction.CoOperationCode);
    fprintf(get_logfile(), "Coprocessor information: %d\n", instruction.CoInformation);
}

void print_debug_instruction(struct CPUState state) {
    static const char *type_to_string_[18] = {"ARM_BLOCK_DATA_TRANSFER",
                                              "ARM_BRANCH",
                                              "ARM_BRANCH_AND_EXCHANGE",
                                              "ARM_COPROCESSOR_DATA_OPERATIONS",
                                              "ARM_COPROCESSOR_DATA_TRANSFER",
                                              "ARM_COPROCESSOR_REGISTER_TRANSFER",
                                              "ARM_DATA_PROCESSING",
                                              "ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_REGISTER_OFFSET",
                                              "ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_IMMEDIATE_OFFSET",
                                              "ARM_MULTIPLY",
                                              "ARM_MULTIPLY_LONG",
                                              "ARM_SINGLE_DATA_SWAP",
                                              "ARM_SINGLE_DATA_TRANSFER",
                                              "ARM_SOFTWARE_INTERRUPT",
                                              "ARM_UNDEFINED", " ", " ", " "};
    static const char *opcode_to_string[18] = {"and",
                                               "eor",
                                               "sub",
                                               "rsb",
                                               "add",
                                               "adc",
                                               "sbc",
                                               "rsc",
                                               "tst",
                                               "teq",
                                               "cmp",
                                               "cmn",
                                               "orr",
                                               "mov",
                                               "bic", "mvn", " ", " "};
    const char *extra = "";
    uint32_t rd = -1;
    uint32_t rn = -1;
    struct ArmInstruction instruct = ARMfromRaw(*(union RawArmInstruction *) &state.decoded_arm);
    switch (instruct.type) {
        case ARM_BLOCK_DATA_TRANSFER:
            rn = instruct.rawArmInstruction.blockDataTransferInstruction.Rn;
            break;
        case ARM_BRANCH:
            break;
        case ARM_BRANCH_AND_EXCHANGE:
            rn = instruct.rawArmInstruction.branchAndExchangeInstruction.Rn;
            break;
        case ARM_COPROCESSOR_DATA_OPERATIONS:
        case ARM_COPROCESSOR_DATA_TRANSFER:
        case ARM_COPROCESSOR_REGISTER_TRANSFER:
            break;
        case ARM_DATA_PROCESSING:
            rd = instruct.rawArmInstruction.dataProcessingInstruction.Rd;
            rn = instruct.rawArmInstruction.dataProcessingInstruction.Rn;
            extra = opcode_to_string[instruct.rawArmInstruction.dataProcessingInstruction.opcode];
            break;
        case ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_REGISTER_OFFSET:
            rn = instruct.rawArmInstruction.halfWordAndSignedDataTransferRegisterOffset.Rn;
            rd = instruct.rawArmInstruction.halfWordAndSignedDataTransferRegisterOffset.Rd;
            break;
        case ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_IMMEDIATE_OFFSET:
            rn = instruct.rawArmInstruction.halfWordAndSignedDataTransferImmediateOffset.Rn;
            rd = instruct.rawArmInstruction.halfWordAndSignedDataTransferImmediateOffset.Rd;
            break;
        case ARM_MULIPLY:
            rn = instruct.rawArmInstruction.multiplyInstruction.Rn;
            rd = instruct.rawArmInstruction.multiplyInstruction.Rd;
            break;
        case ARM_MULTIPLY_LONG:
            break;
        case ARM_SINGLE_DATA_SWAP:
            rn = instruct.rawArmInstruction.dataSwapInstruction.Rn;
            rd = instruct.rawArmInstruction.dataSwapInstruction.Rd;
            break;
        case ARM_SINGLE_DATA_TRANSFER:
            rn = instruct.rawArmInstruction.singleDataTransferInstruction.Rn;
            rd = instruct.rawArmInstruction.singleDataTransferInstruction.Rd;
            if (instruct.rawArmInstruction.singleDataTransferInstruction.loadStoreBit) {
                extra = "ldr";
            } else {
                extra = "str";
            }
            break;
        case ARM_SOFTWARE_INTERRUPT:
        case ARM_UNDEFINED:
        case ARM_INVALID:
            break;
        case ARM_TRANSFER_PSR_TO_REGISTER:
        case ARM_TRANSFER_REGISTER_CONTENTS_TO_PSR:
        case ARM_TRANSFER_REGISTER_CONTENTS_OR_IMMEDIATE_VALUE_TO_PSR_FLAG:
            break;
    }
    fprintf(get_logfile(), "%s Rd:%d Rn:%d extra:%s\n", type_to_string_[ARMfromRaw(get_decoded_arm()).type], rd, rn,
            extra);
}


void print_registers(enum CommandLineFlags flags) {
    if (flags & USE_THUMB) {
        for (uint8_t i = 0; i < 8; ++i) {
            fprintf(get_logfile(), "r%u             0x%x  %u\n", i, get_word_from_register(i),
                    get_word_from_register(i));
        }
        for (uint8_t i = 8; i < 13; ++i) {
            fprintf(get_logfile(), "r%u            0x%x  %u\n", i, 0, 0);
        }
        fprintf(get_logfile(), "sp             0x%x  %u\n",
                (uint32_t) (get_word_from_register(SP_ADDRESS) + get_sp_offset()),
                (uint32_t) (get_word_from_register(SP_ADDRESS) + get_sp_offset()));
        fprintf(get_logfile(), "lr             0x%x  %u\n", 0, 0);
        fprintf(get_logfile(), "pc             0x%x  %u\n",
                (uint32_t) (get_word_from_register(PC_ADDRESS) + get_pc_offset()),
                (uint32_t) (get_word_from_register(PC_ADDRESS) + get_pc_offset()));
        fprintf(get_logfile(), "cpsr           0x%x  %d\n", getCPSR(), getCPSR());
        if (get_operating_mode() == usr || get_operating_mode() == sys) {
            fprintf(get_logfile(), "fpscr          0x%o  %x\n", 0, 0);
        } else {
            fprintf(get_logfile(), "fpscr          0x%o  %x\n", get_SPSR_by_mode(), get_SPSR_by_mode());
        }
        fprintf(get_logfile(), "=> \n\n");
    } else if (flags & BIG_LOGS_MODE) {
        struct LogEntry entry;
        entry.type = CPUSTATE_LOGENTRY;
        entry.state = *getCPUState();
        add_to_log(entry);
    } else if (flags & QEMU_PRINT) {
        for (uint8_t i = 0; i < 15; ++i) {
            fprintf(get_logfile(), "R%02d=%08x\n", i, get_word_from_register(i));
        }
        fprintf(get_logfile(), "R%02d=%08x\n", PC_ADDRESS, get_word_from_register(PC_ADDRESS) - 8);
        fprintf(get_logfile(), "PSR=%08x\n", getCPSR());
        fprintf(get_logfile(), "-Z--\nA\nsvc32\n");
    } else {
        for (uint8_t i = 0; i < 10; ++i) {
            fprintf(get_logfile(), "r%u             0x%x  %u\n", i, get_word_from_register(i),
                    get_word_from_register(i));
        }
        for (uint8_t i = 10; i < 13; ++i) {
            fprintf(get_logfile(), "r%u            0x%x  %u\n", i, get_word_from_register(i),
                    get_word_from_register(i));
        }
        fprintf(get_logfile(), "sp             0x%x  %u\n",
                (uint32_t) (get_word_from_register(SP_ADDRESS) + get_sp_offset()),
                (uint32_t) (get_word_from_register(SP_ADDRESS) + get_sp_offset()));
        fprintf(get_logfile(), "lr             0x%x  %u\n", get_word_from_register(LR_ADDRESS),
                get_word_from_register(LR_ADDRESS));
        fprintf(get_logfile(), "pc             0x%x  %u\n",
                (uint32_t) (get_word_from_register(PC_ADDRESS) + get_pc_offset()),
                (uint32_t) (get_word_from_register(PC_ADDRESS) + get_pc_offset()));
        fprintf(get_logfile(), "cpsr           0x%x  %d\n", getCPSR(), getCPSR());
        if (get_operating_mode() == usr || get_operating_mode() == sys) {
            fprintf(get_logfile(), "fpscr          0x%o  %x\n", 0, 0);
        } else {
            fprintf(get_logfile(), "fpscr          0x%o  %x\n", get_SPSR_by_mode(), get_SPSR_by_mode());
        }
        fprintf(get_logfile(), "=> \n\n");
    }

}