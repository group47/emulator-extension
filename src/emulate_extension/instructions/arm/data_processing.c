//
// Created by francis on 6/1/18.
//

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "data_processing.h"
#include "../../util/cpsr_util.h"
#include "../../util/overflow_util.h"
#include "../../util/operand_two_util.h"


void exception_handler_exit(const struct DataProcessingInstruction instruction, uint32_t operand2Val);

enum ExecutionExitCode execute_instruction_data_processing(const struct DataProcessingInstruction instruction) {
    //todo duplication

    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    bool overflow_occurred = false;
    bool borrow_occurred = false;
    bool signed_overflow_occurred = getCPSR().V;//todo check
    const uint32_t rnVal = get_word_from_register(instruction.Rn);

    uint32_t operand2Val = 0;
    bool shiftCarryOut = getCPSR().C;
    get_operand2(instruction.secondOperand, instruction.immediateOperand, IMMEDIATE_BIT_FLAG_DATA_PROCESSING, &operand2Val, &shiftCarryOut);

    uint32_t carry = (getCPSR().C) ? 1 : 0;

    uint32_t computation_res;
    // for distinguishing between operator thing
    // Maybe we could use a utility function
    // The operation on them is the same for single data transfer as well

    switch (instruction.opcode) {
        case and:
            computation_res = rnVal & operand2Val;
            set_word_in_register(instruction.Rd, computation_res);
            break;
        case eor:
            computation_res = rnVal ^ operand2Val;
            set_word_in_register(instruction.Rd, computation_res);
            break;
        case sub:
            computation_res = rnVal - operand2Val;
            borrow_occurred = does_borrow_occur(rnVal, operand2Val);
            signed_overflow_occurred = does_signed_overflow(rnVal, operand2Val);
            set_word_in_register(instruction.Rd, computation_res);
            break;
        case rsb:
            computation_res = operand2Val - rnVal;
            borrow_occurred = does_borrow_occur(operand2Val, rnVal);
            signed_overflow_occurred = does_signed_overflow(rnVal, operand2Val);
            set_word_in_register(instruction.Rd, computation_res);
            break;
        case add:
            computation_res = operand2Val + rnVal;
            overflow_occurred = (does_overflow_occur(operand2Val, rnVal));
            signed_overflow_occurred = does_signed_overflow(rnVal, operand2Val);
            set_word_in_register(instruction.Rd, computation_res);
            break;
        case tst:
            computation_res = rnVal & operand2Val;
            break;
        case teq:
            computation_res = rnVal ^ operand2Val;
            break;
        case cmp:
            computation_res = rnVal - operand2Val;
            signed_overflow_occurred = does_signed_overflow(rnVal, operand2Val);
            borrow_occurred = does_borrow_occur(rnVal, operand2Val);
            break;
        case orr:
            computation_res = rnVal | operand2Val;
            set_word_in_register(instruction.Rd, computation_res);
            break;
        case mov:
            computation_res = operand2Val;
            set_word_in_register(instruction.Rd, operand2Val);
            break;
        default:
            assert(false);
        case adc:
            computation_res = rnVal + operand2Val + carry;
            overflow_occurred =
                    does_overflow_occur(operand2Val, rnVal) || does_overflow_occur(operand2Val, rnVal + carry);
            signed_overflow_occurred =
                    does_signed_overflow(rnVal, operand2Val) || does_overflow_occur(rnVal + operand2Val, carry);
            set_word_in_register(instruction.Rd,computation_res);
            break;
        case sbc:
            computation_res = rnVal - operand2Val + carry - 1;
            borrow_occurred = does_borrow_occur(rnVal + carry, operand2Val +
                                                               1);//todo what if rnVal + carry overflows and should we care
            signed_overflow_occurred =
                    does_signed_overflow(rnVal, operand2Val) || does_signed_overflow(rnVal + operand2Val, carry - 1);
            set_word_in_register(instruction.Rd,computation_res);
            break;
        case rsc:
            computation_res = operand2Val - rnVal + carry - 1;
            borrow_occurred = does_borrow_occur(operand2Val + carry, rnVal + 1);
            signed_overflow_occurred =
                    does_signed_overflow(rnVal, operand2Val) || does_signed_overflow(-rnVal + operand2Val, carry - 1);
            set_word_in_register(instruction.Rd,computation_res);
            break;
        case cmn:
            computation_res = operand2Val + rnVal;
            overflow_occurred = does_overflow_occur(operand2Val, rnVal);
            signed_overflow_occurred = does_signed_overflow(rnVal, operand2Val);
            break;
        case bic:
            computation_res = rnVal& ~operand2Val;
            set_word_in_register(instruction.Rd,computation_res);
            break;
        case mvn:
            computation_res = ~operand2Val;
            set_word_in_register(instruction.Rd,computation_res);
            break;
    }
    high_level_set_CPSR_data_processing(instruction, borrow_occurred, overflow_occurred, signed_overflow_occurred,
                                        computation_res,
                                        shiftCarryOut);
    exception_handler_exit(instruction, operand2Val);
    if (instruction.Rd == PC_ADDRESS)
        return BRANCH;
    return OK;
}

void exception_handler_exit(const struct DataProcessingInstruction instruction, uint32_t operand2Val) {
    //todo clear interrupt disable flags
    if (instruction.Rd == PC_ADDRESS && instruction.Rn == LR_ADDRESS) {
        if (instruction.opcode == mov) {
            if (instruction.setConditionCodes && get_operating_mode() == und) {
                setCPSR(get_SPSR_by_mode());
            }
        } else if (instruction.opcode == sub) {
            if ((operand2Val == 4 && get_operating_mode() == irq) ||
                (operand2Val == 8 && get_operating_mode() == abt) ||
                (operand2Val == 4 && get_operating_mode() == abt) ||
                (operand2Val == 4 && get_operating_mode() == fiq)) {
                setCPSR(get_SPSR_by_mode());
            }

        }
    }
}
