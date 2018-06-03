//
// Created by fpn17 on 03/06/18.
//

#include <assert.h>
#include "arm_instruction.h"


enum ExecutionExitCode execute_arm_instruction(struct ArmInstruction armInstruction){
    switch (armInstruction.type){
        case ARM_BLOCK_DATA_TRANSFER:
            return execute_instruction_block_data_transfer(armInstruction.rawArmInstruction.blockDataTransferInstruction);
        case ARM_BRANCH:
            return execute_instruction_branch(armInstruction.rawArmInstruction.branchInstruction);
        case ARM_BRANCH_AND_EXCHANGE:
            return execute_instruction_branch_and_exchange_instruction(armInstruction.rawArmInstruction.branchAndExchangeInstruction);
        case ARM_COPROCESSOR_DATA_OPERATIONS:
            return execute_instruction_coprocessor_data_operations(armInstruction.rawArmInstruction.coprocessorDataOperationsInstruction);
        case ARM_COPROCESSOR_DATA_TRANSFER:
            return execute_instruction_coprocessor_data_transfers(armInstruction.rawArmInstruction.coprocessorDataTransfersInstruction);
        case ARM_COPROCESSOR_REGISTER_TRANSFER:
            return execute_copprocessor_register_transfer(armInstruction.rawArmInstruction.coProcessorRegisterTransfer);
        case ARM_DATA_PROCESSING:
            return execute_instruction_data_processing(armInstruction.rawArmInstruction.dataProcessingInstruction);
        case ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_REGISTER_OFFSET:
            return execute_halfword_and_signed_data_transfer_register_offset(armInstruction.rawArmInstruction.halfWordAndSignedDataTransferRegisterOffset);
        case ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_IMMEDIATE_OFFSET:
            return execute_halfword_and_signed_data_transfer_immediate_offset(armInstruction.rawArmInstruction.halfWordAndSignedDataTransferImmediateOffset);
        case ARM_MULIPLY:
            return execute_instruction_multiply(armInstruction.rawArmInstruction.multiplyInstruction);
        case ARM_MULTIPLY_LONG:
            return execute_instruction_multiply_long(armInstruction.rawArmInstruction.multiplyLongInstruction);
        case ARM_SINGLE_DATA_SWAP:
            return execute_instruction_single_data_swap(armInstruction.rawArmInstruction.dataSwapInstruction);
        case ARM_SINGLE_DATA_TRANSFER:
            return execute_instruction_single_data_transfer(armInstruction.rawArmInstruction.singleDataTransferInstruction);
        case ARM_SOFTWARE_INTERRUPT:
            return execute_instruction_software_interrupt(armInstruction.rawArmInstruction.softWareInterruptInstruction);
        case ARM_UNDEFINED:
            return execute_instruction_undefined(armInstruction.rawArmInstruction.undefinedInstruction);
        default:
            assert(false);
    }
}

struct ArmInstruction ARMfromRaw(union RawArmInstruction raw){
    //todo this needs work because of ambiguities
    struct ArmInstruction res;
    res.rawArmInstruction = raw;
    if(raw.dataProcessingInstruction.filler == 0b00){//todo check opcode is valid
        res.type = ARM_DATA_PROCESSING;
    }else if(raw.multiplyInstruction.filler000000 == 0b000000 && raw.multiplyInstruction.filler1001 == 0b1001){
        res.type = ARM_MULIPLY;
    }else if(raw.multiplyLongInstruction.filler00001 == 0b0001 && raw.multiplyLongInstruction.filler1001 == 0b1001){
        res.type = ARM_MULTIPLY_LONG;
    } else if(raw.dataSwapInstruction.filler00010_position27 == 0b00010 && raw.dataSwapInstruction.filler00_position21 == 0b00 && raw.dataSwapInstruction.filler0000_position11 == 0b0000 && raw.dataSwapInstruction.filler1001_position7 == 0b1001){
        res.type = ARM_SINGLE_DATA_SWAP;
    }else if(raw.branchAndExchangeInstruction.filler0001_0010_1111_1111_1111_0001_position27 == 0b000100101111111111110001){
        res.type = ARM_BRANCH_AND_EXCHANGE;
    }else if(raw.halfWordAndSignedDataTransferRegisterOffset.shouldBe1 == 0b1 && raw.halfWordAndSignedDataTransferRegisterOffset.shouldBe0b000 == 0b000 && raw.halfWordAndSignedDataTransferRegisterOffset.shouldBe0 == 0b0 && raw.halfWordAndSignedDataTransferRegisterOffset.shouldBe00001 == 0b00001){
        res.type = ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_REGISTER_OFFSET;
    }else if(raw.halfWordAndSignedDataTransferImmediateOffset.shouldBe0b000 == 0b00 && raw.halfWordAndSignedDataTransferImmediateOffset.filler1position7 == 0b1&& raw.halfWordAndSignedDataTransferImmediateOffset.filler1Position22 == 0b1 && raw.halfWordAndSignedDataTransferImmediateOffset.filler1position4 == 0b1){
        res.type = ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_IMMEDIATE_OFFSET;
    }else if(raw.singleDataTransferInstruction.filler01 == 0b01){//todo ambiguity
        res.type = ARM_SINGLE_DATA_TRANSFER;
    }else if(raw.undefinedInstruction.filler1_position4 == 0b1 && raw.undefinedInstruction.filler011_position27 == 0b011){
        res.type = ARM_UNDEFINED;
    }else if(raw.blockDataTransferInstruction.filler100 == 0b100){
        res.type = ARM_BLOCK_DATA_TRANSFER;
    }else if(raw.branchInstruction.filler101_position27 == 0b101){
        res.type = ARM_BRANCH;
    }else if(raw.coprocessorDataTransfersInstruction.filler110_position27 == 0b110){
        res.type = ARM_COPROCESSOR_DATA_TRANSFER;
    }else if(raw.coprocessorDataOperationsInstruction.filler0_position4 == 0b0 && raw.coprocessorDataOperationsInstruction.filler1110_position27 == 0b1110){
        res.type = ARM_COPROCESSOR_DATA_OPERATIONS;
    }else if(raw.coProcessorRegisterTransfer.filler1 == 0b1 && raw.coProcessorRegisterTransfer.filler1110 == 0b1110){
        res.type = ARM_COPROCESSOR_REGISTER_TRANSFER;
    }else {
#ifndef TEST_SCRIPT_MAIN
        assert(false);
#endif
#ifdef TEST_SCRIPT_MAIN
        res.type = ARM_INVALID;
#endif
    }

    return res;
}