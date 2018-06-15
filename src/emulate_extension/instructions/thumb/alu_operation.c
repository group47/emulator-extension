//
// Created by fpn17 on 02/06/18.
//

#include <stdbool.h>
#include <assert.h>
#include <x86intrin.h>
#include "alu_operation.h"
#include "../../util/common_enums.h"
#include "../../util/cpsr_util.h"
#include "../../util/overflow_util.h"
#include "../../util/operand_two_util.h"


bool is_arithmetic_thumb(enum ThumbALUOpCode op) {
    return op == ADC_THUMB_ALU || op == SBC_THUMB_ALU || op == NEQ_THUMB_ALU || op == CMP_THUMB_ALU ||
           op == CMN_THUMB_ALU;
}

bool is_logical_thumb(enum ThumbALUOpCode op) {
    return !is_arithmetic_thumb(op) && op != MUL_THUMB_ALU;
}


enum ExecutionExitCode execute_instruction_alu_operation(struct ALUOperation instruction) {
    assert(instruction.filler010000 == 0b10000);
    bool overflow_occurred = false;
    bool borrow_occurred = false;
    bool signed_overflow_occurred = getCPSR().V;

    bool shift_carry_out = getCPSR().C ? 1 : 0;
    int32_t res;

    uint32_t Rs_val = get_word_from_register(instruction.Rs);
    uint32_t Rd_val = get_word_from_register(instruction.Rd);

    switch (instruction.Op) {
        case AND_THUMB_ALU:
            res = Rd_val & Rs_val;
            set_word_in_register(instruction.Rd, res);
            break;
        case EOR_THUMB_ALU:
            res = Rd_val ^ Rs_val;
            set_word_in_register(instruction.Rd, res);
            break;
        case LSL_THUMB_ALU:
            Rs_val &= 0xff;
            operand_two_lsl(&Rd_val, &shift_carry_out, Rs_val, true);
            res = Rd_val;
            set_word_in_register(instruction.Rd, res);
            break;
        case LSR_THUMB_ALU:
            Rs_val &= 0xff;
            operand_two_lsr(&Rd_val, &shift_carry_out, Rs_val, true);
            res = Rd_val;
            set_word_in_register(instruction.Rd, res);
            break;
        case ASR_THUMB_ALU:
            Rs_val &= 0xff;
            operand_two_asr(&(Rd_val), &shift_carry_out, Rs_val, true);
            res = Rd_val;
            set_word_in_register(instruction.Rd, res);
            break;
        case ADC_THUMB_ALU:
            res = Rd_val + Rs_val +
                  (getCPSR().C ? 1 : 0);//todo unclear if Rs_val + C can overflow, and if we should care
            overflow_occurred = does_overflow_occur(Rd_val, Rs_val)
                                || does_overflow_occur(Rd_val + Rs_val, (getCPSR().C ? 1 : 0));
            signed_overflow_occurred = does_signed_overflow(Rd_val, Rs_val)
                                       || does_signed_overflow(Rd_val + Rs_val, (getCPSR().C ? 1 : 0));
            set_word_in_register(instruction.Rd, res);
            break;
        case SBC_THUMB_ALU:
            res = Rd_val - Rs_val - ((~getCPSR().C) ? 1 : 0);
            borrow_occurred = does_borrow_occur(Rd_val, Rs_val)
                              || does_borrow_occur(Rd_val - Rs_val, ((~getCPSR().C) ? 1 : 0));
            set_word_in_register(instruction.Rd, res);
            break;
        case ROR_THUMB_ALU:
            operand_two_ror(&Rd_val, &shift_carry_out, Rs_val, true);
            res = Rd_val;
            set_word_in_register(instruction.Rd, res);
            break;
        case TST_THUMB_ALU:
            res = Rd_val & Rs_val;
            break;
        case NEQ_THUMB_ALU:
            res = -Rs_val;
            set_word_in_register(instruction.Rd, res);
            borrow_occurred = does_borrow_occur(0, Rs_val);
            signed_overflow_occurred = does_signed_overflow(0, Rs_val);
            break;
        case CMP_THUMB_ALU:
            res = Rd_val - Rs_val;
            borrow_occurred = does_borrow_occur(Rd_val, Rs_val);
            signed_overflow_occurred = does_signed_overflow(Rd_val, Rs_val);
            break;
        case CMN_THUMB_ALU:
            res = Rd_val + Rs_val;
            overflow_occurred = does_overflow_occur(Rd_val, Rs_val);
            signed_overflow_occurred = does_signed_overflow(Rd_val, Rs_val);
            break;
        case ORR_THUMB_ALU:
            res = Rd_val | Rs_val;
            set_word_in_register(instruction.Rd, res);
            break;
        case MUL_THUMB_ALU:
            res = Rd_val * Rs_val;
            set_word_in_register(instruction.Rd, res);
            break;
        case BIC_THUMB_ALU:
            res = Rd_val & ~Rs_val;
            set_word_in_register(instruction.Rd, res);
            break;
        case MVN_THUMB_ALU:
            res = ~Rs_val;
            set_word_in_register(instruction.Rd, res);
            break;
        default:
            assert(false);
    }

    high_level_set_CPSR(true, is_arithmetic_thumb(instruction.Op),
                        instruction.Op == CMN_THUMB_ALU || instruction.Op == ADC_THUMB_ALU,
                        is_logical_thumb(instruction.Op), borrow_occurred, overflow_occurred, signed_overflow_occurred,
                        shift_carry_out,
                        res);
    return OK;
}