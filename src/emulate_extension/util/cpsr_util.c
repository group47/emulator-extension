//
// Created by francis on 6/2/18.
//

#include <assert.h>
#include "cpsr_util.h"
#include "../instructions/data_processing.h"
bool is_logical(enum OpCode code);
bool is_arithmetic(enum OpCode code);
bool should_execute(enum Cond cond){
  //todo check this is correct with main spec
  const bool NequalsV =
      (bool) (getCPSR().N == getCPSR().V);
  const bool Zset = (bool) (getCPSR().Z);
  switch (cond) {
    case eq:
      return Zset;
    case ne:
      return !Zset;
    case ge:
      return NequalsV;
    case lt:
      return !NequalsV;
    case gt:
      return (!Zset) && NequalsV;
    case le:
      return Zset || (!NequalsV);
    case al:
      return true;
    default:
      return false;
  }
}

void high_level_set_CPSR(const struct DataProcessingInstruction instruction,
            const bool borrow,
            const bool overflow,
            const uint32_t computation_res,
            const uint32_t shiftCarryOut) {
  struct CPSR_Struct final_res = getCPSR();
  if (instruction.setConditionCodes) {
    //set c bit
    if (is_arithmetic((instruction).opcode)) {
      if ((instruction).opcode == add) {
        if (overflow)
          final_res.C = true;
        else
          final_res.C = false;
      } else {
        if (borrow) {
          final_res.C = false;
        } else {
          final_res.C = true;
        }

      }
    } else if (is_logical(instruction.opcode)) {
      *((uint32_t *)&final_res) |= shiftCarryOut;//todo sketchy
    } else {
      assert(false);
    }
    //set z bit
    if (computation_res == 0) {
      final_res.Z = true;
    } else {
      final_res.Z = false;
    }
    //set n bit
    if (computation_res & (1 << 31)) {// todo check
      final_res.N = true;
    } else {
      final_res.N = false;
    }
  }
  setCPSR(final_res);
}
bool is_arithmetic(enum OpCode opCode) {
  return opCode == add || opCode == sub || opCode == rsb || opCode == cmp;
}
bool is_logical(enum OpCode opCode) {
  return !is_arithmetic(opCode);
}

