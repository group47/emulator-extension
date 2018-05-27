//
// Created by francis on 5/23/18.
//

#ifndef EMULATE_INSTRUCTIONS_H
#define EMULATE_INSTRUCTIONS_H

enum InstructionType {
  DATA_PROCESSING,
  MULTIPLY,
  SINGLE_DATA_TRANSFER,
  BRANCH_INSTRUCTION,
  TERMINATE_INSTRUCTION
};

enum Cond {
  eq = 0b0000,
  ne = 0b0001,
  ge = 0b1010,
  lt = 0b1011,
  gt = 0b1100,
  le = 0b1101,
  al = 0b1110
};


// added by rory
enum ShiftType {
  lsl = 0b00,
  lsr = 0b01,
  asr = 0b10,
  ror = 0b11
};

#include <stdbool.h>
#include <stdint-gcc.h>
#include "emulate_main.h"
#include "data_processing_instruction.h"
#include "multiply_instruction.h"
#include "single_data_transfer_instruction.h"
#include "branch_instruction.h"



//todo ImmediateFalseShiftByRegisterTrue:

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
