//
// Created by fpn17 on 02/06/18.
//

#ifndef SRC_MOVE_SHIFTED_REGISTER_H
#define SRC_MOVE_SHIFTED_REGISTER_H

#include "../../basic_typedefs.h"


enum ShiftedRegisterOpCode{
    THUMB_SHIFTED_REGISTER_LSL = 0,
    THUMB_SHIFTED_REGISTER_LSR = 1,
    THUMB_SHIFTED_REGISTER_ASR = 2,
};

struct MoveShiftedRegister{
    RegisterAddress Rd : 4;
    RegisterAddress Rs : 4;
    uint8_t offset5 : 5;
    enum ShiftedRegisterOpCode Op : 2;
    uint8_t filler000: 3;
};

#endif //SRC_MOVE_SHIFTED_REGISTER_H
