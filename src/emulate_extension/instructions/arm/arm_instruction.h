//
// Created by fpn17 on 03/06/18.
//

#ifndef SRC_ARM_INSTRUCTION_H
#define SRC_ARM_INSTRUCTION_H

#include "block_data_transfer.h"
#include "branch.h"
#include "branch_and_exchange.h"
#include "coprocessor_data_operations.h"
#include "coprocessor_data_transfers.h"
#include "coprocessor_register_transfer.h"
#include "data_processing.h"
#include "halfword_and_signed_data_transfer.h"
#include "multiply.h"
#include "multiply_long.h"
#include "single_data_swap.h"
#include "single_data_transfer.h"
#include "software_interrupt.h"
#include "Undefined.h"
#include "PSRTransfer.h"

union RawArmInstruction {
    struct BlockDataTransferInstruction blockDataTransferInstruction;
    struct BranchInstruction branchInstruction;
    struct BranchAndExchangeInstruction branchAndExchangeInstruction;
    struct CoprocessorDataOperationsInstruction coprocessorDataOperationsInstruction;
    struct CoprocessorDataTransfersInstruction coprocessorDataTransfersInstruction;
    struct CoprocessorRegisterTransferInstruction coProcessorRegisterTransfer;
    struct DataProcessingInstruction dataProcessingInstruction;
    struct HalfWordAndSignedDataTransferRegisterOffset halfWordAndSignedDataTransferRegisterOffset;
    struct HalfWordAndSignedDataTransferImmediateOffset halfWordAndSignedDataTransferImmediateOffset;
    struct MultiplyInstruction multiplyInstruction;
    struct MultiplyLongInstruction multiplyLongInstruction;
    struct SingleDataSwapInstruction dataSwapInstruction;
    struct SingleDataTransferInstruction singleDataTransferInstruction;
    struct SoftWareInterruptInstruction softWareInterruptInstruction;
    struct UndefinedInstruction undefinedInstruction;
    struct TransferPSRContentsToRegister transferPSRContentsToRegister;
    struct TransferRegisterContentsToPSR transferRegisterContentsToPSR;
    struct TransferRegisterContentsOrImmediateValueToPSRFlag transferRegisterContentsOrImmediateValueToPSRFlag;
};


enum ArmInstructionType {
    ARM_BLOCK_DATA_TRANSFER = 0,
    ARM_BRANCH = 1,
    ARM_BRANCH_AND_EXCHANGE = 2,
    ARM_COPROCESSOR_DATA_OPERATIONS = 3,
    ARM_COPROCESSOR_DATA_TRANSFER = 4,
    ARM_COPROCESSOR_REGISTER_TRANSFER = 5,
    ARM_DATA_PROCESSING = 6,
    ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_REGISTER_OFFSET = 7,
    ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_IMMEDIATE_OFFSET = 8,
    ARM_MULIPLY = 9,
    ARM_MULTIPLY_LONG = 10,
    ARM_SINGLE_DATA_SWAP = 11,
    ARM_SINGLE_DATA_TRANSFER = 12,
    ARM_SOFTWARE_INTERRUPT = 13,
    ARM_UNDEFINED = 14,
    ARM_INVALID = 15,
    ARM_TRANSFER_PSR_TO_REGISTER = 16,
    ARM_TRANSFER_REGISTER_CONTENTS_TO_PSR = 17,
    ARM_TRANSFER_REGISTER_CONTENTS_OR_IMMEDIATE_VALUE_TO_PSR_FLAG = 18
};


struct ArmInstruction {
    enum ArmInstructionType type;
    union RawArmInstruction rawArmInstruction;
};

struct ArmInstruction ARMfromRaw(union RawArmInstruction raw);

enum ExecutionExitCode execute_arm_instruction(struct ArmInstruction armInstruction);

#endif //SRC_ARM_INSTRUCTION_H
