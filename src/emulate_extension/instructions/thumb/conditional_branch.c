//
// Created by mhl1817 on 02/06/18.
//

#include <assert.h>
#include "conditional_branch.h"
#include "../../util/cpsr_util.h"

enum ExecutionExitCode execute_instruction_conditional_branch(const struct ConditionalBranchInstruction instruction) {

  assert(instruction.filler1101 == 0b1101);

  if (!should_execute(instruction.cond)) {
    return DIDNT_EXECUTE;
  }

  int16_t offset = (int16_t) (instruction.sOffset * 2);

  set_word_in_register(PC_ADDRESS, get_word_from_register(PC_ADDRESS) - 4 + offset);

//  add_exception_flag(BRANCH_LINK_EXCEPTION);

  return BRANCH;
}
