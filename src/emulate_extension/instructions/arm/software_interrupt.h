//
// Created by qs4617 on 02/06/18.
//

#ifndef SRC_SOFTWARE_INTERRUPT_H
#define SRC_SOFTWARE_INTERRUPT_H


#include <stdint.h>
#include "../../util/common_enums.h"

struct SoftWareInterruptInstruction {
    uint32_t commentField : 24;
    uint8_t filler1111_position27 : 4;
    enum Cond cond:4;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_software_interrupt(struct SoftWareInterruptInstruction);

#endif //SRC_SOFTWARE_INTERRUPT_H
