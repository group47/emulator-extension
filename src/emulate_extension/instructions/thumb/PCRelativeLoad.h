//
// Created by qs4617 on 02/06/18.
//

#ifndef SRC_PCRELATIVELOAD_H
#define SRC_PCRELATIVELOAD_H


#include <stdint.h>

struct PCRelativeLoadInstruction {
    uint8_t word8 : 8;
    uint8_t Rd : 3;
    uint8_t filler01001_position15 : 5;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_PCRelativeLoad(struct PCRelativeLoadInstruction);

#endif //SRC_PCRELATIVELOAD_H
