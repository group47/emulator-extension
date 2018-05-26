//
// Created by francis on 5/23/18.
//

#ifndef EMULATE_EMULATE_MAIN_H
#define EMULATE_EMULATE_MAIN_H

#define MEMORY_SIZE 65536
#define MAX_INSTRUCTION_INPUT_FILE_SIZE 1000
#define NUM_REGISTERS 17
#include "stdint-gcc.h"

struct EmulatorState {
  union {
    uint8_t memory[MEMORY_SIZE];
    uint32_t memory_as_uints[MEMORY_SIZE/4];
  };

  //todo registers should go here etc.:
  uint32_t registers[NUM_REGISTERS-2];
  //conceptual bug:, register 15 is a valid register, but will overflow the array access, but still get the right register
  //by luck since this packed in a struct, the overflowed access still gets the correct register, but this is by chance only
  uint32_t PC;
  uint32_t CPSR;
};

enum CPSR{
  CPSR_N = 0b10000000000000000000000000000000,   //todo hex
  CPSR_Z = 0b01000000000000000000000000000000,
  CPSR_C = 0b00100000000000000000000000000000,
  CPSR_V = 0b00010000000000000000000000000000
//         0b01100000000000000000000000000000
//         0b11000000000000000000000000000000
};

/*
enum CPSR {
    CPSR_N = 0x8000;
    CPSR_Z = 0x4000;
    CPSR_C = 0x2000;
    CPSR_V = 0x1000;
};
*/

enum OpCode{
  and = 0b0000,
  eor = 0b0001,
  sub = 0b0010,
  rsb = 0b0011,
  add = 0b0100,
  tst = 0b1000,
  teq = 0b1001,
  cmp = 0b1010,
  orr = 0b1100,
  mov = 0b1101
};

void emulate(struct EmulatorState *state,
             uint32_t instructions[],
             unsigned int instructions_l);

#endif //EMULATE_EMULATE_MAIN_H
