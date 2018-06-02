//
// Created by fpn17 on 02/06/18.
//

#include <stdbool.h>
#include <assert.h>
#include <x86intrin.h>
#include "alu_operation.h"
#include "../../util/common_enums.h"
#include "../../util/cpsr_util.h"
#include "../../util/shift_util.h"
#include "../../util/overflow_util.h"


bool is_arithmetic_thumb(enum ThumbALUOpCode op){
    return op == ADC_THUMB_ALU || op == SBC_THUMB_ALU || op == NEQ_THUMB_ALU || op == CMN_THUMB_ALU || op == CMN_THUMB_ALU || op == MUL_THUMB_ALU;
}

bool is_logical_thumb(enum ThumbALUOpCode op){
    return !is_arithmetic_thumb(op);
}


enum ExecutionExitCode execute_alu_instruction(struct ALUOperation instruction){
    assert(instruction.filler010000 == 0b01000);
    bool overflow_occurred = false;
    bool borrow_occurred = false;

    uint32_t shift_carry_out = 0;
    int32_t res;

    const uint32_t Rs_val = get_word_from_register(instruction.Rs);
    const uint32_t Rd_val = get_word_from_register(instruction.Rd);

    switch(instruction.Op){
        case AND_THUMB_ALU:
            res = Rd_val & Rs_val;
            set_word_in_register(instruction.Rd,res);
            break;
        case EOR_THUMB_ALU:
            res = Rd_val ^ Rs_val;
            set_word_in_register(instruction.Rd,res);
            break;
        case LSL_THUMB_ALU:
            res = Rd_val << Rs_val;
            shift_carry_out = (uint32_t) ((((uint64_t)Rd_val) << Rs_val) >> 32);
            set_word_in_register(instruction.Rd,res);
            break;
        case LSR_THUMB_ALU:
            res = Rd_val >> Rs_val;
            shift_carry_out = (uint32_t) ((((uint64_t)Rd_val) << 32) >> Rs_val);
            set_word_in_register(instruction.Rd,res);
            break;
        case ASR_THUMB_ALU:
            res = arithmetic_right_shift(Rd_val,Rs_val);//todo check casting correctness
            shift_carry_out = (uint32_t) ((((uint64_t)Rd_val) << 32) >> Rs_val);
            set_word_in_register(instruction.Rd,res);
            break;
        case ADC_THUMB_ALU:
            res = Rd_val + Rs_val + getCPSR().C;//todo unclear if Rs_val + C can overflow, and if we should care
            overflow_occurred = does_overflow_occur(Rd_val,Rs_val + getCPSR().C);
            set_word_in_register(instruction.Rd,res);
            break;
        case SBC_THUMB_ALU:
            res = Rd_val - Rs_val - ~getCPSR().C;
            borrow_occurred = does_borrow_occur(Rd_val,Rs_val + ~getCPSR().C);
            set_word_in_register(instruction.Rd,res);
            break;
        case ROR_THUMB_ALU:
            res = __rord(Rs_val,Rs_val);
            set_word_in_register(instruction.Rd,res);
            break;
        case TST_THUMB_ALU:
            res =  Rd_val & Rs_val;
            break;
        case NEQ_THUMB_ALU:
            res = -Rs_val;
            set_word_in_register(instruction.Rd,res);
            break;
        case CMP_THUMB_ALU:
            res = Rd_val - Rs_val;
            borrow_occurred = does_borrow_occur(Rd_val,Rs_val);
            break;
        case CMN_THUMB_ALU:
            res = Rd_val + Rs_val;
            overflow_occurred = does_overflow_occur(Rd_val,Rs_val);
            break;
        case ORR_THUMB_ALU:
            res = Rd_val | Rs_val;
            set_word_in_register(instruction.Rd,res);
            break;
        case MUL_THUMB_ALU:
            res = Rd_val*Rs_val;
            set_word_in_register(instruction.Rd,res);
            break;
        case BIC_THUMB_ALU:
            res = Rd_val & ~Rs_val;
            set_word_in_register(instruction.Rd,res);
            break;
        case MVN_THUMB_ALU:
            res = ~Rs_val;
            set_word_in_register(instruction.Rd,res);
            break;
    }

    high_level_set_CPSR(true,is_arithmetic_thumb(instruction.Op),instruction.Op == CMN_THUMB_ALU || instruction.Op == ADC_THUMB_ALU,is_logical_thumb(instruction.Op),borrow_occurred,overflow_occurred,res,shift_carry_out);
    return OK;
}