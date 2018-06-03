//
// Created by mhl1817 on 02/06/18.
//

#include <assert.h>
#include "SP_relative_load_store.h"
#include "../../state/emulator_state.h"

enum ExecutionExitCode execute_instruction_SP_relative_load_store(const struct SPRelativeLoadStoreInstruction instruction) {

  assert(instruction.filler1001 == 0b1001);

  const uint16_t imm = (uint16_t) (instruction.word * 4);
  Address address = get_word_from_register(SP_ADDRESS) + imm;

  if (instruction.loadMemory) {
    set_word_in_register(instruction.Rd, get_word_from_memory(address));
  } else {
    set_word_from_memory(address, get_word_from_register(instruction.Rd));
  }

  return OK;
}
