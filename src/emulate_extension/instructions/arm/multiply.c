//
// Created by francis on 6/1/18.
//

#include <assert.h>
#include "multiply.h"
#include "../../util/cpsr_util.h"

#define PC_REGISTER 15

enum ExecutionExitCode execute_instruction_multiply(const struct MultiplyInstruction instruction) {

  //execute condition
  if (!should_execute(instruction.cond)) {
    return DIDNT_EXECUTE;
  }

  //operand restriction
  assert(instruction.Rd != instruction.Rm);
  assert(instruction.Rm != PC_REGISTER);
  assert(instruction.Rs != PC_REGISTER);
  assert(instruction.Rn != PC_REGISTER);
  assert(instruction.Rd != PC_REGISTER);

  //execution
  const int32_t Rm = get_word_from_register(instruction.Rm);
  const int32_t Rs = get_word_from_register(instruction.Rs);
  int64_t result = Rm * Rs;

  if (instruction.accumulate) {
    const int32_t Rn = get_word_from_register(instruction.Rn);
    result += Rn;
  }

  //CSPR flags
  if (instruction.setConditionCodes) {
    struct CPSR_Struct CSPR = getCPSR();
    CSPR.Z = result == 0;
    CSPR.N = result < 0;
  }

  const uint32_t final_res = (uint32_t) (result & 0xffffffff);
  set_word_in_register(instruction.Rd, final_res);

  return OK;

}
