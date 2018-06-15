//
// Created by fpn17 on 02/06/18.
//

#ifndef SRC_MOVE_SHIFTED_REGISTER_H
#define SRC_MOVE_SHIFTED_REGISTER_H

#include "../../basic_typedefs.h"


enum ShiftedRegisterOpCode {
    THUMB_SHIFTED_REGISTER_LSL = 0,
    THUMB_SHIFTED_REGISTER_LSR = 1,
    THUMB_SHIFTED_REGISTER_ASR = 2,
};

struct MoveShiftedRegister {
    RegisterAddress Rd : 3;
    RegisterAddress Rs : 3;
    uint8_t offset5 : 5;
    enum ShiftedRegisterOpCode Op : 2;
    uint8_t filler000: 3;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_move_shifted_register(struct MoveShiftedRegister instruction);

#endif //SRC_MOVE_SHIFTED_REGISTER_H
