//
// Created by mhl1817 on 02/06/18.
//

#ifndef SRC_UNCONDITIONAL_BRANCH_H
#define SRC_UNCONDITIONAL_BRANCH_H

#include "../../basic_typedefs.h"
#include "../../util/common_enums.h"

struct UnconditionalBranchInstruction {
  uint8_t filler : 5; //11100
  int16_t offset : 11;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_unconditional_branch(const struct UnconditionalBranchInstruction);

#endif //SRC_UNCONDITIONAL_BRANCH_H
