//
// Created by francis on 5/27/18.
//

#ifndef EMULATE_BRANCH_INSTRUCTION_H
#define EMULATE_BRANCH_INSTRUCTION_H
struct BranchInstruction {
  int32_t offset:24;
  uint8_t filler1 : 1;// should be 0b0
  uint8_t filler2: 3;//should be 0b101
  enum Cond cond:4;
}__attribute__((packed));
#include "emulate_main.h"
int execute_instruction_branch(struct EmulatorState *state,
                               struct BranchInstruction instruction);

#endif //EMULATE_BRANCH_INSTRUCTION_H
