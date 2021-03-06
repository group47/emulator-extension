//
// Created by fpn17 on 02/06/18.
//

#ifndef SRC_MOVE_COMPARE_ADD_SUBTRACT_H
#define SRC_MOVE_COMPARE_ADD_SUBTRACT_H

#include <stdint.h>
#include "../../basic_typedefs.h"


enum MoveCompareAddSubtractOpCode {
    MOV_MOVECOMPAREADDSUBTRACTOPCODE = 0,
    CMP_MOVECOMPAREADDSUBTRACTOPCODE = 1,
    ADD_MOVECOMPAREADDSUBTRACTOPCODE = 2,
    SUB_MOVECOMPAREADDSUBTRACTOPCODE = 3
};

struct MoveCompareAddSubtract {
    uint8_t offset8: 8;
    RegisterAddress Rd: 3;
    enum MoveCompareAddSubtractOpCode op:2;
    uint8_t filler001:3;
}__attribute__((packed));


enum ExecutionExitCode execute_instruction_move_compare_add_subtract(struct MoveCompareAddSubtract instruction);

#endif //SRC_MOVE_COMPARE_ADD_SUBTRACT_H
