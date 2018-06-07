//
// Created by francis on 6/2/18.
//

#include <assert.h>
#include "../instructions/thumb/add_subtract.h"
#include "cpsr_util.h"


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
                         const bool shiftCarryOut) {
    return high_level_set_CPSR(instruction.setConditionCodes, is_arithmetic(instruction.opcode),
                               instruction.opcode == add || instruction.opcode == adc || instruction.opcode == cmn,
                               is_logical(instruction.opcode), borrow, overflow, computation_res, shiftCarryOut);
}

void high_level_set_CPSR_thumb_add_subtract(const struct AddSubtractInstruction instruction,
                                            const bool borrow,
                                            const bool overflow,
                                            const uint32_t computation_res,
                                            const bool shiftCarryOut) {
  return high_level_set_CPSR(true, true, instruction.op == ADD, false, borrow, overflow, computation_res, shiftCarryOut);
}

void high_level_set_CPSR(bool set_condition_codes,bool is_arithmetic,bool is_add,bool is_logical,
            bool borrow,
            bool overflow,
            uint32_t computation_res,
            bool shiftCarryOut) {
  if (set_condition_codes) {
    struct CPSR_Struct final_res = getCPSR();
    if (is_arithmetic) {
      if (is_add) {
        final_res.C = overflow;
      } else {
        final_res.C = !borrow;
      }
      //TODO: set V flag if arithmetic
    } else if (is_logical) {
      final_res.C = shiftCarryOut;
    } else {
      assert(false);
    }

    final_res.Z = computation_res == 0;

    final_res.N = (computation_res & (0x1 << 31)) != 0;

    setCPSR(final_res);
  }
}

bool is_arithmetic(enum OpCode opCode) {
  return opCode == add || opCode == sub || opCode == rsb || opCode == cmp || opCode == adc || opCode == cmn || opCode == sbc || opCode == rsc;
}

bool is_logical(enum OpCode opCode) {
  //return !is_arithmetic(opCode);
  return opCode == and || opCode == eor || opCode == tst || opCode == teq || opCode ==orr || opCode == mov || opCode == bic || opCode == mvn;
}

void high_level_set_CPSR_thumb_move_compare_add_sub(struct MoveCompareAddSubtract instruction, bool borrow,
bool overflow, uint32_t res, bool carryOut) {
  return high_level_set_CPSR(true, instruction.op == ADD_MOVECOMPAREADDSUBTRACTOPCODE || instruction.op == SUB_MOVECOMPAREADDSUBTRACTOPCODE || instruction.op == CMP_MOVECOMPAREADDSUBTRACTOPCODE,
                             instruction.op == ADD_MOVECOMPAREADDSUBTRACTOPCODE, instruction.op == MOV_MOVECOMPAREADDSUBTRACTOPCODE, borrow, overflow, res, carryOut);
}