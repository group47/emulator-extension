//
// Created by francis on 5/23/18.
//

#ifndef EMULATE_EMULATE_MAIN_H
#define EMULATE_EMULATE_MAIN_H

#include "util.h"

#define MEMORY_SIZE 65536

struct EmulatorState{
    byte memory[MEMORY_SIZE];
    //todo registers should go here etc.:
};
void emulate(struct EmulatorState* state,int32_t instructions[],unsigned int instructions_l);

#endif //EMULATE_EMULATE_MAIN_H
