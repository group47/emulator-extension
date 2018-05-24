//
// Created by francis on 5/23/18.
//

#ifndef EMULATE_EMULATE_MAIN_H
#define EMULATE_EMULATE_MAIN_H

#include "util.h"

#define MEMORY_SIZE 65536

struct EmulatorState {
  byte memory[MEMORY_SIZE];
  //todo registers should go here etc.:
  int32_t r0;
  int32_t r1;
  int32_t r2;
  int32_t r3;
  int32_t r4;
  int32_t r5;
  int32_t r6;
  int32_t r7;
  int32_t r8;
  int32_t r9;
  int32_t r10;
  int32_t r11;
  int32_t r12;
  int32_t r13;
  int32_t r14;
  int32_t PC;
  int32_t CPSR;
};

int32_t CPSR_N = 0b10000000000000000000000000000000;//todo hex
int32_t CPSR_Z = 0b01000000000000000000000000000000;
int32_t CPSR_C = 0b00100000000000000000000000000000;
int32_t CPSR_V = 0b00010000000000000000000000000000;

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
             int32_t instructions[],
             unsigned int instructions_l);

#endif //EMULATE_EMULATE_MAIN_H
