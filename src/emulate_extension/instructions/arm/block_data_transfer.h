//
// Created by qs4617 on 02/06/18.
//

#ifndef SRC_BLOCK_DATA_TRANSFER_H
#define SRC_BLOCK_DATA_TRANSFER_H

#include <stdint.h>
#include <stdbool.h>
#include "../../util/common_enums.h"
#include "../../basic_typedefs.h"

#define NUM_REGISTER_IN_REGISTER_LIST 16

struct BlockDataTransferInstruction {
    uint16_t registerList: 16;
    RegisterAddress Rn : 4;
    bool loadStoreBit : 1;
    bool writeBackBit : 1;
    bool psrAndForceUserBit : 1;
    bool upDownBit : 1;
    bool prePostIndexingBit : 1;
    uint8_t filler100 : 3;
    enum Cond cond : 4;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_block_data_transfer(struct BlockDataTransferInstruction instruction);


#endif //SRC_BLOCK_DATA_TRANSFER_H
