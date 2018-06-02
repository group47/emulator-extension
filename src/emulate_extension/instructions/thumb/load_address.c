//
// Created by mhl1817 on 02/06/18.
//

#include "load_address.h"
#include "../../state/emulator_state.h"

enum ExecutionExitCode execute_instruction_load_address(const struct LoadAddressInstruction instruction) {

  Word Rs;
  if (instruction.stackPointer) {
    Rs = get_word_from_register(SP_ADDRESS);
  } else {
    Rs = get_word_from_register(PC_ADDRESS) - 4;
  }
  uint16_t imm = (uint16_t) (instruction.word * 4);

  set_word_in_register(instruction.Rd, Rs + imm);

  return OK;
}
