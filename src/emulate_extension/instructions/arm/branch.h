//
// Created by qs4617 on 02/06/18.
//

#ifndef SRC_BRANCH_H
#define SRC_BRANCH_H

#include <stdint.h>
#include <stdbool.h>
#include "../../util/common_enums.h"

struct BranchInstruction {
    uint32_t offset : 24;
    bool linkBit : 1;
    uint8_t filler101_position27 :3;
    enum Cond cond : 4;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_branch(struct BranchInstruction);

#endif //SRC_BRANCH_H
