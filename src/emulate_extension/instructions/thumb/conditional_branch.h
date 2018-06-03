//
// Created by mhl1817 on 02/06/18.
//

#ifndef SRC_CONDITIONAL_BRANCH_H
#define SRC_CONDITIONAL_BRANCH_H

#include "../../basic_typedefs.h"
#include "../../util/common_enums.h"

struct ConditionalBranchInstruction {
  uint8_t filler1101 : 4; //1101
  enum Cond cond : 4;
  int8_t sOffset : 8;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_conditional_branch(const struct ConditionalBranchInstruction);

#endif //SRC_CONDITIONAL_BRANCH_H
