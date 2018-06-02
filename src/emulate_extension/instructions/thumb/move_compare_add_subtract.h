//
// Created by fpn17 on 02/06/18.
//

#ifndef SRC_MOVE_COMPARE_ADD_SUBTRACT_H
#define SRC_MOVE_COMPARE_ADD_SUBTRACT_H

#include <stdint.h>
#include "../../basic_typedefs.h"


enum MoveCompareAddSubtractOpCode{
    MOV = 0,
    CMP = 1,
    ADD = 2,
    SUB = 3
};

struct MoveCompareAddSubtract{
    uint8_t offset8: 8;
    RegisterAddress Rd: 3;
    enum MoveCompareAddSubtractOpCode  op:2;
    uint8_t filler001:3;
}__attribute__((packed));


#endif //SRC_MOVE_COMPARE_ADD_SUBTRACT_H
