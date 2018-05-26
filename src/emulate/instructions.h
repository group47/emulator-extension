//
// Created by francis on 5/23/18.
//

#ifndef EMULATE_INSTRUCTIONS_H
#define EMULATE_INSTRUCTIONS_H

#include <stdbool.h>

bool is_logical(enum OpCode opCode);
bool is_arithmetic(enum OpCode opCode);



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

struct BranchInstruction {
  int32_t offset:24;
  uint8_t filler1 : 1;// should be 0b0
  uint8_t filler2: 3;//should be 0b101
  enum Cond cond:4;
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

#endif //EMULATE_INSTRUCTIONS_H
