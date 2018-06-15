//
// Created by fpn17 on 03/06/18.
//

#include <stdbool.h>
#include <assert.h>
#include "main_loop.h"
#include "state/emulator_state.h"
#include "state/exception.h"
#include "instructions/thumb/thumb_instruction.h"


void print_debug() {
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
    struct ArmInstruction instruct = ARMfromRaw(get_decoded_arm());
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

void main_loop(enum CommandLineFlags flags) {
    uint64_t master_instruction_counter = 0;
    while (true) {

        if (decoded_valid()) {
            if (flags & DEBUG_PRINT_REGISTER) {
                print_registers(flags);
            }
            union RawArmInstruction instruction = get_decoded_arm();
            if ((flags & TERMINATE_ON__ZERO) && ((*(uint32_t *) &instruction) == 0)) {
                return;
            }
            if ((flags & TERMINATE_AFTER_200) && master_instruction_counter == 200) {
                return;
            }
            enum ExecutionExitCode exitCode;
            if (get_mode() == ARM) {
                exitCode = execute_arm_instruction(ARMfromRaw(get_decoded_arm()));
                print_debug();
            } else if (get_mode() == THUMB) {
                exitCode = execute_thumb_instruction(ThumbFromRaw(get_decoded_thumb()));
            } else {
                assert(false);
            }
            if (exitCode == BRANCH) {
                invalidate_pipeline();
            }
            master_instruction_counter++;
        } else if (prefetch_aborted()) {
            add_exception_flag(PREFETCH_ABORT);
        }

        //check if exceptions
        if (has_exceptions()) {
            handle_exception();
        }

        //this function is used so that the cpu isn't in an inconsistent state in this loop
        transfer_fetched_to_decoded_and_load_fetched();


        if (flags & MEMORY) {
            print_memory();
        }
    }

}

