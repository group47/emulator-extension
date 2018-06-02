//
// Created by francis on 5/28/18.
//

#ifndef SRC_ENUMS_H
#define SRC_ENUMS_H
enum InstructionType {
  DATA_PROCESSING,
  MULTIPLY,
  SINGLE_DATA_TRANSFER,
  BRANCH_INSTRUCTION,
  TERMINATE_INSTRUCTION,
  INVALID,
  BRANCH_INSTRUCTION_INVALID
};


// added by rory
enum ShiftType {
  lsl = 0b00,
  lsr = 0b01,
  asr = 0b10,
  ror = 0b11
};

#endif //SRC_ENUMS_H
