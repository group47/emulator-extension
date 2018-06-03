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

union RawArmInstruction{
    struct BlockDataTransferInstruction blockDataTransferInstruction;
    struct BranchInstruction branchInstruction;
    struct BranchAndExchangeInstruction branchAndExchangeInstruction;
    struct CoprocessorDataOperationsInstruction coprocessorDataOperationsInstruction;
    struct CoprocessorDataTransfersInstruction coprocessorDataTransfersInstruction;
    struct CoProcessorRegisterTransfer coProcessorRegisterTransfer;
    struct DataProcessingInstruction dataProcessingInstruction;
    struct HalfWordAndSignedDataTransferRegisterOffset halfWordAndSignedDataTransferRegisterOffset;
    struct HalfWordAndSignedDataTransferImmediateOffset halfWordAndSignedDataTransferImmediateOffset;
    struct MultiplyInstruction multiplyInstruction;
    struct MultiplyLongInstruction multiplyLongInstruction;
    struct SingleDataSwapInstruction dataSwapInstruction;
    struct SingleDataTransferInstruction singleDataTransferInstruction;
    struct SoftWareInterruptInstruction softWareInterruptInstruction;
    struct UndefinedInstruction undefinedInstruction;
};


enum ArmInstructionType{
    ARM_BLOCK_DATA_TRANSFER,
    ARM_BRANCH,
    ARM_BRANCH_AND_EXCHANGE,
    ARM_COPROCESSOR_DATA_OPERATIONS,
    ARM_COPROCESSOR_DATA_TRANSFER,
    ARM_COPROCESSOR_REGISTER_TRANSFER,
    ARM_DATA_PROCESSING,
    ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_REGISTER_OFFSET,
    ARM_HALFWORD_AND_SIGNED_DATA_TRANSFER_IMMEDIATE_OFFSET,
    ARM_MULIPLY,
    ARM_MULTIPLY_LONG,
    ARM_SINGLE_DATA_SWAP,
    ARM_SINGLE_DATA_TRANSFER,
    ARM_SOFTWARE_INTERRUPT,
    ARM_UNDEFINED,
};


struct ArmInstruction{
    enum ArmInstructionType type;
    union RawArmInstruction rawArmInstruction;
};


#endif //SRC_ARM_INSTRUCTION_H
