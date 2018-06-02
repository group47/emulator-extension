//
// Created by francis on 6/2/18.
//

#include <assert.h>
#include "add_subtract.h"
#include "../../state/emulator_state.h"
#include "../../util/common_enums.h"

enum ExecutionExitCode execute_instruction_add_subtract(const struct AddSubtractInstruction instruction){
  assert(get_mode() == THUMB);
  assert(instruction.shouldBe0b00011 == 0b00011);
  Word res;
  if(instruction.immediate){
    if(instruction.op == ADD){
      res = instruction.RnOffset3 + get_register(instruction.Rs);
    }
    else if(instruction.op == SUB){
      res = get_register(instruction.Rs) - instruction.RnOffset3;
    }
    else{
      assert(false);
    }
  }else{
    if(instruction.op == ADD){
      res = get_register(instruction.RnOffset3) + get_register(instruction.Rs);
    }
    else if(instruction.op == SUB){
      res = get_register(instruction.Rs) - get_register(instruction.RnOffset3);
    } else{
      assert(false);
    }
  }
  set_register(instruction.Rd,res);
  return OK;
}