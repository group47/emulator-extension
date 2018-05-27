//
// Created by francis on 5/27/18.
//

#include "instructions.h"
#include "emulate_main.h"
#include "multiply_instruction.h"

int
execute_instruction_multiply(struct EmulatorState *state, struct MultiplyInstruction instruction) {

  if (!should_execute(state, instruction.cond)) {
    return DIDNT_EXECUTE;
  }

  uint32_t result = state->registers[instruction.Rm] * state->registers[instruction.Rs];

  if (instruction.accumulate) {
    result += state->registers[instruction.Rn];
  }

  if (result == 0) {
    // set z bit
    state->CPSR |= CPSR_Z;
    // set n bit
    state->CPSR |= (result & CPSR_N);
  }

  state->registers[instruction.destinationRegister] = result;

  return OK;
}