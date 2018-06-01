//
// Created by francis on 5/27/18.
//

#include "../shared/instructions.h"
#include "emulate_main.h"
#include "../shared/branch_instruction.h"


int execute_instruction_branch(struct CPUState *state,
                               const struct BranchInstruction instruction) {
  if (!should_execute(state, instruction.cond)) {
    return DIDNT_EXECUTE;
  }
  const int32_t offset = instruction.offset * 4;
  state->PC += offset;
  return BRANCH;
}