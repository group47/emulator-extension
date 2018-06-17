//
// Created by francis on 5/27/18.
//
#include <assert.h>
#include "cpsr_overflow_detection.h"
#include "data_processing_instruction.h"

int execute_instruction_data_processing(struct EmulatorState *state,
                                        const struct DataProcessingInstruction instruction) {
    //todo duplication

    bool overflow_occurred = false;
    bool borrow_occurred = false;

    if (!should_execute(state, instruction.cond)) {
        return DIDNT_EXECUTE;
    }
    const uint32_t rnVal = (state->registers)[instruction.Rn];

    uint32_t operand2Val;
    uint32_t shiftCarryOut = 0;
    getOperand2Val(state, instruction.secondOperand, instruction.immediateOperand, 1, &operand2Val, &shiftCarryOut);


    uint32_t computation_res;
    // for distinguishing between operator thing
    // Maybe we could use a utility function
    // The operation on them is the same for single data transfer as well

    switch (instruction.opcode) {
        case and:
            computation_res = rnVal & operand2Val;
            (state->registers)[instruction.Rd] = computation_res;
            break;
        case eor:
            computation_res = rnVal ^ operand2Val;
            (state->registers)[instruction.Rd] = computation_res;
            return 1;
        case sub:
            computation_res = rnVal - operand2Val;
            if (does_borrow_occur(rnVal, operand2Val)) {
                borrow_occurred = true;
            }
            (state->registers)[instruction.Rd] = computation_res;
            break;
        case rsb:
            computation_res = operand2Val - rnVal;
            if (does_borrow_occur(operand2Val, rnVal)) {
                borrow_occurred = true;
            }
            (state->registers)[instruction.Rd] = computation_res;
            break;
        case add:
            computation_res = operand2Val + rnVal;
            if (does_overflow_occur(operand2Val, rnVal)) {
                overflow_occurred = true;
            }
            (state->registers)[instruction.Rd] = computation_res;
            break;
        case tst:
            computation_res = rnVal & operand2Val;
            break;
        case teq:
            computation_res = rnVal ^ operand2Val;
            break;
        case cmp:
            computation_res = rnVal - operand2Val;
            if (does_borrow_occur(rnVal, operand2Val)) {
                borrow_occurred = true;
            }
            break;
        case orr:
            computation_res = rnVal | operand2Val;
            (state->registers)[instruction.Rd] = (rnVal | operand2Val);
            break;
        case mov:
            computation_res = operand2Val;
            state->registers[instruction.Rd] = operand2Val;
            break;
        default:
            assert(false);
    }
    return setCPSR(state, instruction, borrow_occurred, overflow_occurred, computation_res,
                   shiftCarryOut);
}
