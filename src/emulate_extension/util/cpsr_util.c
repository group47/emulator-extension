//
// Created by francis on 6/2/18.
//

#include <assert.h>
#include "cpsr_util.h"
#include "../instructions/arm/data_processing.h"


bool should_execute(enum Cond cond){
  //todo check this is correct with main spec
  const bool unsignedHigher = getCPSR().C && !getCPSR().Z;
  const bool greaterOrEqual = getCPSR().N == getCPSR().V;
  const bool greater        = !getCPSR().Z && greaterOrEqual;
  switch (cond) {
    case eq: return getCPSR().Z;
    case ne: return !getCPSR().Z;
    case cs: return getCPSR().C;
    case cc: return !getCPSR().C;
    case mi: return getCPSR().N;
    case pl: return !getCPSR().N;
    case vs: return getCPSR().V;
    case vc: return !getCPSR().V;
    case hi: return unsignedHigher;
    case ls: return !unsignedHigher;
    case ge: return greaterOrEqual;
    case lt: return !greaterOrEqual;
    case gt: return greater;
    case le: return !greater;
    case al: return true;
    default:
      return false; //assert false as never is interruption
  }
}


void high_level_set_CPSR_data_processing(const struct DataProcessingInstruction instruction,
                         const bool borrow,
                         const bool overflow,
                         const uint32_t computation_res,
                         const uint32_t shiftCarryOut) {
  return high_level_set_CPSR(instruction.setConditionCodes,is_arithmetic(instruction.opcode),instruction.opcode == add,is_logical(instruction.opcode),borrow,overflow,computation_res,shiftCarryOut);
}

void high_level_set_CPSR(bool set_condition_codes,bool is_arithmetic,bool is_add,bool is_logical,
            bool borrow,
            bool overflow,
            uint32_t computation_res,
            uint32_t shiftCarryOut) {
  struct CPSR_Struct final_res = getCPSR();
  if (set_condition_codes) {
    //set c bit
    if (is_arithmetic) {
      if (is_add) {
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
    } else if (is_logical) {
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
  return opCode == add || opCode == sub || opCode == rsb || opCode == cmp || opCode == adc || opCode == cmn || opCode == sbc || opCode == rsc;
}
bool is_logical(enum OpCode opCode) {
  return !is_arithmetic(opCode);
}

void high_level_set_CPSR_thumb_move_compare_add_sub(struct MoveCompareAddSubtract subtract, bool occurred,
bool overflow_occurred, uint32_t res, int carryOut) {
    return;high_level_set_CPSR(true,true,subtract.op == ADD_MOVECOMPAREADDSUBTRACTOPCODE,false,occurred,overflow_occurred,res,carryOut);
}