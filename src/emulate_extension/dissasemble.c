//
// Created by fpn17 on 04/06/18.
//

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

void disassemble(FILE *binary) {
    uint32_t instruction;
    while (fread(&instruction, sizeof(uint32_t), 1, binary)) {
        struct ArmInstruction arm = ARMfromRaw(*(union RawArmInstruction *) &instruction);
        if (arm.type == ARM_COPROCESSOR_DATA_OPERATIONS) {
            printf(type_to_string_[arm.type]);
            printf("\n");
            struct CoprocessorDataOperationsInstruction instruction1 = arm.rawArmInstruction.coprocessorDataOperationsInstruction;
            fprintf(stdout, "Coprocessor number : %d\n", instruction1.CoNumber);
            fprintf(stdout, "Coprocessor destination register: %d\n", instruction1.CoDestinationRegister);
            fprintf(stdout, "Coprocessor cooperand register position 3: %d\n",
                    instruction1.CoOperandRegister_position3);
            fprintf(stdout, "Coprocessor cooperand register position 19: %d\n",
                    instruction1.CoOperandRegister_position19);
            fprintf(stdout, "Coprocessor operation code: %d\n", instruction1.CoOperationCode);
            fprintf(stdout, "Coprocessor information: %d\n", instruction1.CoInformation);
            printf("\n");
        } else if (arm.type == ARM_COPROCESSOR_DATA_TRANSFER) {
            printf(type_to_string_[arm.type]);
            printf("\n");
            struct CoprocessorDataTransfersInstruction instruction1 = arm.rawArmInstruction.coprocessorDataTransfersInstruction;
            fprintf(stdout, "Coprocesor number %d\n", instruction1.CoNumber);
            fprintf(stdout, "Coprocesor base register %d\n", instruction1.baseRegister);
            fprintf(stdout, "Coprocesor source destination register %d\n", instruction1.CoSourceDestinationRegister);
            fprintf(stdout, "Coprocesor load store bit %d\n", instruction1.loadStoreBit);
            fprintf(stdout, "Coprocesor offset %d\n", instruction1.offset);
            fprintf(stdout, "Coprocesor pre post indexing %d\n", instruction1.prePostIndexingBit);
            fprintf(stdout, "Coprocesor transfer length %d\n", instruction1.transferLength);
            fprintf(stdout, "Coprocesor up down bit %d\n", instruction1.upDownBit);
            fprintf(stdout, "Coprocesor write back bit %d\n", instruction1.writeBackBit);
            printf("\n");
        } else if (arm.type == ARM_COPROCESSOR_REGISTER_TRANSFER) {
            printf(type_to_string_[arm.type]);
            printf("\n");
            struct CoprocessorRegisterTransferInstruction instruction1 = arm.rawArmInstruction.coProcessorRegisterTransfer;
            fprintf(stdout, "Coprocessor CP: %d\n", instruction1.CP);
            fprintf(stdout, "Coprocessor CPNum: %d\n", instruction1.CPNum);
            fprintf(stdout, "Coprocessor CPOpc: %d\n", instruction1.CPOpc);
            fprintf(stdout, "Coprocessor CRm: %d\n", instruction1.CRm);
            fprintf(stdout, "Coprocessor CRn: %d\n", instruction1.CRn);
            fprintf(stdout, "Coprocessor load/store bit: %d\n", instruction1.loadStore);
            fprintf(stdout, "Coprocessor Rd: %d\n", instruction1.Rd);
            printf("\n");
        }

    }

}