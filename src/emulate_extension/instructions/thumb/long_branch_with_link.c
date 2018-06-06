//
// Created by mhl1817 on 02/06/18.
//

#include <assert.h>
#include "long_branch_with_link.h"
#include "../../state/emulator_state.h"

enum ExecutionExitCode execute_instruction_long_branch_with_link(const struct LongBranchWithLinkInstruction instruction) {

  assert(instruction.filler1111 == 0b1111);

  int32_t offset = instruction.offset & 0x7ff;
    ByteAddress PC_result;

  if (instruction.lowOffsetBit) {

    //instruction after BL
      ByteAddress LR_result = get_word_from_register(PC_ADDRESS) - 2;
    //set bit0
    LR_result |= 0b1;

    offset <<= 1;
    PC_result = get_word_from_register(LR_ADDRESS) + offset - 4;

    set_word_in_register(PC_ADDRESS, PC_result);
    set_word_in_register(LR_ADDRESS, LR_result);

  } else {

    offset <<= 12;
    PC_result = get_word_from_register(PC_ADDRESS) + offset;

      set_word_in_register(LR_ADDRESS, PC_result);//todo shouldn't do this?
      add_exception_flag(BRANCH_LINK_EXCEPTION);
  }


  return BRANCH;
}
