//
// Created by francis on 5/23/18.
//

#ifndef EMULATE_INSTRUCTIONS_H
#define EMULATE_INSTRUCTIONS_H

#include <stdbool.h>
#include <elf.h>
#include "util.h"

enum InstructionType {
  DATA_PROCESSING, MULTIPLY, SINGLE_DATA_TRANSFER, BRANCH_INSTRUCTION
};


#define eqCond 0b0000
#define neCond 0b0001
#define geCond 0b1010
#define ltCond 0b1011
#define gtCond 0b1100
#define leCond 0b1101
#define alCond 0b1110

//todo magic constants:
struct DataProcessingInstruction {
  uint16_t secondOperand : 12;
  uint8_t Rd:4;
  uint8_t Rn: 4;
  bool setConditionCodes: 1;
  enum OpCode opcode : 4;
  bool immediateOperand: 1;
  uint8_t filler: 2;//The value of the filler should be 0b000
  uint8_t cond : 4;
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
  uint8_t cond : 4;
}__attribute__((packed));

struct SingleDataTransferInstruction {
  short offset:12;
  uint8_t Rd:4;
  uint8_t Rn:4;
  bool loadStore : 1;
  bool upBit:1;
  bool prePostIndexingBit:1;
  bool immediateOffset:1;
  uint8_t filler:2; //should be 0b01
  uint8_t cond:4;
}__attribute__((packed));

struct BranchInstruction {
  int offset:24;
  uint8_t filler1 : 1;// should be 0b0
  uint8_t filler2: 3;//should be 0b101
  uint8_t cond:4;
}__attribute__((packed));

struct Instruction {
  enum InstructionType type;
  union {
    struct DataProcessingInstruction dataProcessingInstruction;
    struct MultiplyInstruction multiplyInstruction;
    struct SingleDataTransferInstruction singleDataTransferInstruction;
    struct BranchInstruction branchInstruction;
  };

};

#endif //EMULATE_INSTRUCTIONS_H
