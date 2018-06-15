//
// Created by francis on 5/23/18.
//

#ifndef EMULATE_INSTRUCTIONS_H
#define EMULATE_INSTRUCTIONS_H


#include <stdbool.h>
#include <stdint.h>
#include "common_structs.h"
#include "enums.h"

struct ImmediateTrue{
  uint8_t Imm: 8;
  uint8_t rotate: 4;
}__attribute__((packed));

struct ImmediateFalseShiftByRegisterTrue{
  uint8_t Rm : 4;
  bool shift_by_register: 1;//should be true
  enum ShiftType shift_type: 2;
  bool filler:1;
  uint8_t Rs:4;
}__attribute__((packed));


struct ImmediateFalseShiftByRegisterFalse{
  uint8_t Rm : 4;
  bool shift_by_register: 1;//should be 0
  enum ShiftType shift_type: 2;
  uint8_t integer: 5;
}__attribute__((packed));

struct TerminateInstruction {
  uint32_t filler : 32;
};


// Can't have the InstructionType in the struct becuase the structs need to be
// in main memory with a size of 32 bits. Also need to be interpreted from main memory.
union RawInstruction{
  struct DataProcessingInstruction dataProcessingInstruction;
  struct MultiplyInstruction multiplyInstruction;
  struct SingleDataTransferInstruction singleDataTransferInstruction;
  struct BranchInstruction branchInstruction;
  struct TerminateInstruction terminateInstruction;
};

struct Instruction {
  enum InstructionType type;
  union RawInstruction rawInstruction;

};

bool is_logical(enum OpCode opCode);
bool is_arithmetic(enum OpCode opCode);
#endif //EMULATE_INSTRUCTIONS_H
