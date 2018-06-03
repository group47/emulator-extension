//
// Created by mhl1817 on 02/06/18.
//

#include <assert.h>
#include "multiple_load_store.h"
#include "../../state/emulator_state.h"
#include "../../util/common_enums.h"

enum ExecutionExitCode execute_instruction_multiple_load_store(const struct MultipleLoadStoreInstruction instruction) {

  assert(instruction.filler1100 == 0b1100);

  Address address = get_word_from_register(instruction.Rb);

  if (instruction.loadMemory) {

    for (RegisterAddress lowRegister = 0; lowRegister < 8; ++lowRegister) {
      if (instruction.RList & (0b1 << lowRegister)) {
        set_word_in_register(lowRegister, get_word_from_memory(address));
        ++address;
      }
    }
  } else {

    for (RegisterAddress lowRegister = 0; lowRegister < 8; ++lowRegister) {
      if (instruction.RList & (0b1 << lowRegister)) {
        set_word_from_memory(address, get_word_from_register(lowRegister));
        ++address;
      }
    }
  }

  set_word_in_register(instruction.Rb, address);

  return OK;
}
