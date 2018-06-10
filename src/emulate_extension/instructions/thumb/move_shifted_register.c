//
// Created by fpn17 on 02/06/18.
//

#include "move_shifted_register.h"
#include "../../util/common_enums.h"
#include "../../state/emulator_state.h"
#include "../../util/cpsr_util.h"
#include "../../util/operand_two_util.h"


enum ExecutionExitCode execute_instruction_move_shifted_register(struct MoveShiftedRegister instruction) {
    struct DataProcessingInstruction armProxy;
    struct ImmediateFalseShiftByRegisterFalse operand2;
    switch (instruction.Op) {
        case THUMB_SHIFTED_REGISTER_LSL:
            operand2.shift_type = lsl;
            break;
        case THUMB_SHIFTED_REGISTER_LSR:
            operand2.shift_type = lsr;
            break;
        case THUMB_SHIFTED_REGISTER_ASR:
            operand2.shift_type = asr;
            break;
    }
    operand2.Rm = instruction.Rs;
    operand2.shift_by_register = false;
    operand2.shift_amount = instruction.offset5;
    armProxy.cond = al;
    armProxy.Rd = instruction.Rd;
    armProxy.immediateOperand = false;
    armProxy.opcode = mov;
    armProxy.setConditionCodes = true;
    armProxy.secondOperand = *(uint16_t *) &operand2;
    return execute_instruction_data_processing(armProxy);
}