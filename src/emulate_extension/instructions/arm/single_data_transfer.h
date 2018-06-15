//
// Created by qs4617 on 02/06/18.
//

#ifndef SRC_SINGLE_DATA_TRANSFER_H
#define SRC_SINGLE_DATA_TRANSFER_H

#include <stdint.h>
#include <stdbool.h>
#include "../../util/common_enums.h"
#include "../../basic_typedefs.h"

#define IMMEDIATE_BIT_FLAG_SINGLE_DATE_TRANSFER false

struct SingleDataTransferInstruction {
    uint16_t offset:12;
    RegisterAddress Rd:4;
    RegisterAddress Rn:4;
    bool loadStoreBit : 1;
    bool writeBackBit : 1;
    bool byteWordBit : 1;
    bool upDownBit : 1;
    bool prePostBit : 1;
    bool immediateOffsetBit:1;
    uint8_t filler01:2; //should be 0b01
    enum Cond cond:4;
}__attribute__((packed));


enum ExecutionExitCode execute_instruction_single_data_transfer(struct SingleDataTransferInstruction);

#endif //SRC_SINGLE_DATA_TRANSFER_H
