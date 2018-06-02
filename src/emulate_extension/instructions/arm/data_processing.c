//
// Created by francis on 6/1/18.
//

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "data_processing.h"
#include "../../util/cpsr_util.h"
#include "../../util/overflow_util.h"
#include "../../util/operand_two_util.h"


enum ExecutionExitCode execute_instruction_data_processing(const struct DataProcessingInstruction instruction) {
  //todo duplication

  bool overflow_occurred = false;
  bool borrow_occurred = false;

  if (!should_execute(instruction.cond)) {
    return DIDNT_EXECUTE;
  }
  const uint32_t rnVal = get_byte_from_register(instruction.Rn);

  uint32_t operand2Val;
  uint32_t shiftCarryOut = 0;
    get_operand2(instruction.secondOperand, instruction.immediateOperand, 1, &operand2Val, &shiftCarryOut);


  uint32_t computation_res;
  // for distinguishing between operator thing
  // Maybe we could use a utility function
  // The operation on them is the same for single data transfer as well

  switch (instruction.opcode) {
    case and:
      computation_res = rnVal & operand2Val;
      set_word_in_register(instruction.Rd, computation_res);
      break;
    case eor:
      computation_res = rnVal ^ operand2Val;
      set_word_in_register(instruction.Rd, computation_res);
      return 1;
    case sub:
      computation_res = rnVal - operand2Val;
      if (does_borrow_occur(rnVal, operand2Val)) {
        borrow_occurred = true;
      }
      set_word_in_register(instruction.Rd, computation_res);
      break;
    case rsb:
      computation_res = operand2Val - rnVal;
      if (does_borrow_occur(operand2Val, rnVal)) {
        borrow_occurred = true;
      }
      set_word_in_register(instruction.Rd, computation_res);
      break;
    case add:
      computation_res = operand2Val + rnVal;
      if (does_overflow_occur(operand2Val, rnVal)) {
        overflow_occurred = true;
      }
      set_word_in_register(instruction.Rd, computation_res);
      break;
    case tst:
      computation_res = rnVal & operand2Val;
      break;
    case teq:
      computation_res = rnVal ^ operand2Val;
      break;
    case cmp:
      computation_res = rnVal - operand2Val;
      if (does_borrow_occur(rnVal, operand2Val)) {
        borrow_occurred = true;
      }//todo duplication with sub, use fallthrough
      break;
    case orr:
      computation_res = rnVal | operand2Val;
          set_word_in_register(instruction.Rd, (rnVal | operand2Val));
      break;
    case mov:
      computation_res = operand2Val;
          set_word_in_register(instruction.Rd, operand2Val);
      break;
    default:
      assert(false);
  }
  high_level_set_CPSR_data_processing(instruction, borrow_occurred, overflow_occurred, computation_res, shiftCarryOut);
  return OK;
}
