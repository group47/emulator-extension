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
  SPECIAL
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

#endif //SRC_ENUMS_H
