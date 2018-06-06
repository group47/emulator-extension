//
// Created by francis on 6/2/18.
//

#include <assert.h>
#include "add_subtract.h"
#include "../../state/emulator_state.h"
#include "../../util/common_enums.h"
#include "../../util/cpsr_util.h"
#include "../../util/overflow_util.h"

enum ExecutionExitCode execute_instruction_add_subtract(const struct AddSubtractInstruction instruction){
  assert(get_mode() == THUMB);
  assert(instruction.shouldBe0b00011 == 0b00011);

  Word first_operand = get_word_from_register(instruction.Rs);
  Word second_operand;

  if (instruction.immediate) {
    second_operand = instruction.RnOffset3;
  } else {
    second_operand = get_word_from_register((RegisterAddress) instruction.RnOffset3);
  }

  const bool borrow = does_borrow_occur(first_operand, second_operand) ;
  const bool overflow = does_overflow_occur(first_operand, second_operand);

  if (instruction.op == ADD) {
    first_operand += second_operand;
  } else if (instruction.op == SUB) {
    first_operand -= second_operand;
  } else {
    assert(false);
  }

  set_word_in_register(instruction.Rd, first_operand);

  high_level_set_CPSR_thumb_add_subtract(instruction, borrow, overflow, first_operand, getCPSR().C);
  //shift_cary_out could be anything as arithmetic doesnt care about it

  return OK;
}

