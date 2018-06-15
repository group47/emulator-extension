//
// Created by francis on 5/27/18.
//

#ifndef EMULATE_MULTIPLY_INSTRUCTION_H
#define EMULATE_MULTIPLY_INSTRUCTION_H
#include "../emulate_dir/emulate_main.h"
int execute_instruction_multiply(struct EmulatorState *,
                                 const struct MultiplyInstruction);
#endif //EMULATE_MULTIPLY_INSTRUCTION_H
