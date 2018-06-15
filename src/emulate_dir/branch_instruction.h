//
// Created by francis on 5/27/18.
//

#ifndef EMULATE_BRANCH_INSTRUCTION_H
#define EMULATE_BRANCH_INSTRUCTION_H

#include "../emulate_dir/emulate_main.h"
int execute_instruction_branch(struct EmulatorState *state,
                               struct BranchInstruction instruction);

#endif //EMULATE_BRANCH_INSTRUCTION_H
