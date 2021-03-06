//
// Created by francis on 6/1/18.
//

#include <assert.h>
#include "multiply.h"
#include "../../util/cpsr_util.h"

enum ExecutionExitCode execute_instruction_multiply(const struct MultiplyInstruction instruction) {

    assert(instruction.filler000000 == 0b000000);
    assert(instruction.filler1001 == 0b1001);

    //execute condition
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    //operand restriction
    assert(instruction.Rd != instruction.Rm);
    assert(instruction.Rm != PC_ADDRESS);
    assert(instruction.Rs != PC_ADDRESS);
    assert(instruction.Rn != PC_ADDRESS);
    assert(instruction.Rd != PC_ADDRESS);

    //execution
    const int32_t Rm = get_word_from_register(instruction.Rm);
    const int32_t Rs = get_word_from_register(instruction.Rs);
    int64_t result = Rm * Rs;

    if (instruction.accumulate) {
        const int32_t Rn = get_word_from_register(instruction.Rn);
        result += Rn;
    }

    //CSPR flags
    if (instruction.setConditionCodes) {
        struct CPSR_Struct CSPR = getCPSR();
        CSPR.Z = result == 0;
        CSPR.N = result < 0;
        setCPSR(CSPR);
    }

    const uint32_t final_res = (uint32_t) (result & 0xffffffff);
    set_word_in_register(instruction.Rd, final_res);


    return OK;

}
