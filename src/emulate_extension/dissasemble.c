//
// Created by fpn17 on 04/06/18.
//

#include <stdbool.h>
#include <stdint.h>
#include "dissasemble.h"
#include "instructions/arm/arm_instruction.h"

static const char *type_to_string_[15] = {"ARM_BLOCK_DATA_TRANSFER",
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
                                         "ARM_UNDEFINED"};

void disassemble(FILE *binary){
    uint32_t instruction;
    while (fread(&instruction,sizeof(uint32_t),1,binary)){
        struct ArmInstruction arm = ARMfromRaw(*(union RawArmInstruction *)&instruction);
        printf(type_to_string_[arm.type]);
        printf("\n");

    }

}