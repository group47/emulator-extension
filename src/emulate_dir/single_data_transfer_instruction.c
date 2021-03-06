//
// Created by francis on 5/27/18.
//

#include "single_data_transfer_instruction.h"

int execute_instruction_single_data_transfer(struct EmulatorState *state,
                                             struct SingleDataTransferInstruction instruction) {
  if (!should_execute(state, instruction.cond)) {
    return DIDNT_EXECUTE;
  }

  uint32_t offset;

  if (instruction.immediateOffset == 0) {
    offset = instruction.offset;
  } else {
    uint32_t dummy;
    getOperand2Val(state, instruction.offset, instruction.immediateOffset, 0, &offset, &dummy);
  }

  // pre indexing
  uint32_t address = state->registers[instruction.Rn];

  if (instruction.prePostIndexingBit) {
    if (instruction.upBit) {
      address += offset;
    } else {
      address -= offset;
    }
  }

  if (instruction.loadStore) {
    uint32_t result = 0;
    bool access_was_successful = true;
    for (int i = 0; i < 4; i++) {
      const uint32_t memory_access_index = address + i;
      if (memory_access_index < MEMORY_SIZE) {
        result |= ((uint32_t) state->memory[memory_access_index]) << (8 * i);
      } else {
        access_was_successful = false;
      }
    }
    if (!access_was_successful) {
      result = handle_out_of_bounds(state, address, false, (uint32_t) -1);

    }

    state->registers[instruction.Rd] = result;
  } else {
    bool access_was_succesful = true;
    for (int i = 0; i < 4; i++) {
      const uint32_t mask = (0xff) << (8 * i);
      const uint32_t memory_access_index = address + i;
      if (memory_access_index < MEMORY_SIZE) {
        state->memory[memory_access_index] =
            (((uint32_t) state->registers[instruction.Rd]) & mask) >> (8 * i);
      } else {
        access_was_succesful = false;
      }
    }
    if(!access_was_succesful){
      handle_out_of_bounds(state,address,true,state->registers[instruction.Rd]);
    }
  }

  // I need a better solution for this duplication
  // post indexing
  if (!instruction.prePostIndexingBit) {
    if (instruction.upBit) {
      state->registers[instruction.Rn] += offset;
    } else {
      state->registers[instruction.Rn] -= offset;
    }
  }

  return 0;
}