//
// Created by qs4617 on 02/06/18.
//

#ifndef SRC_ADD_OFFSET_TO_STACK_POINTER_H
#define SRC_ADD_OFFSET_TO_STACK_POINTER_H

#include <stdint.h>
#include <stdbool.h>

struct AddOffsetToStackPointerInstruction {
    uint8_t sword7 : 7;
    bool signFlag : 1;
    uint8_t filler1011_0000 : 8;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_add_offset_to_stack_pointer(struct AddOffsetToStackPointerInstruction);

#endif //SRC_ADD_OFFSET_TO_STACK_POINTER_H
