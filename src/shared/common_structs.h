//
// Created by fpn17 on 15/06/18.
//

#ifndef SRC_COMMON_STRUCTS_H
#define SRC_COMMON_STRUCTS_H

#include <stdint.h>
#include <stdbool.h>
#include "enums.h"


struct BranchInstruction {
    int32_t offset:24;
    uint8_t filler1 : 1;// should be 0b0
    uint8_t filler2: 3;//should be 0b101
    enum Cond cond:4;
}__attribute__((packed));


struct DataProcessingInstruction {
    uint16_t secondOperand : 12;
    uint8_t Rd:4;
    uint8_t Rn: 4;
    bool setConditionCodes: 1;
    enum OpCode opcode : 4;
    bool immediateOperand: 1;
    uint8_t filler: 2;//The value of the filler should be 0b000
    enum Cond cond : 4;
}__attribute__((packed));//the attribute is required for the compiler to properly place data types


struct MultiplyInstruction {
    uint8_t Rm : 4;
    uint8_t filler2:4;//should equal 0b1001
    uint8_t Rs:4;
    uint8_t Rn:4;
    uint8_t destinationRegister:4;
    bool setConditionCodes: 1;
    bool accumulate: 1;
    uint8_t filler : 6;//should be 0b000000
    enum Cond cond : 4;
}__attribute__((packed));

struct SingleDataTransferInstruction {
    short offset:12;
    uint8_t Rd:4;
    uint8_t Rn:4;
    bool loadStore : 1;
    uint8_t filler2: 2;
    bool upBit:1;
    bool prePostIndexingBit:1;
    bool immediateOffset:1;
    uint8_t filler:2; //should be 0b01
    enum Cond cond:4;
}__attribute__((packed));

#endif //SRC_COMMON_STRUCTS_H
