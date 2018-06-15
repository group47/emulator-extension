//
// Created by francis on 6/1/18.
//

#include <assert.h>
#include "multiply_long.h"
#include "../../util/cpsr_util.h"


enum ExecutionExitCode execute_instruction_multiply_long(const struct MultiplyLongInstruction instruction) {

    //execute condition
    if (!should_execute(instruction.cond)) {
        return DIDNT_EXECUTE;
    }

    //operand restriction
    assert(instruction.RdHi != instruction.Rm);
    assert(instruction.RdHi != instruction.RdLo);
    assert(instruction.RdLo != instruction.Rm);
    assert(instruction.Rm != PC_ADDRESS);
    assert(instruction.Rs != PC_ADDRESS);
    assert(instruction.RdLo != PC_ADDRESS);
    assert(instruction.RdHi != PC_ADDRESS);

    //execution
    if (instruction.signedVal) {

        const int32_t Rm = get_word_from_register(instruction.Rm);
        const int32_t Rs = get_word_from_register(instruction.Rs);
        int64_t result = Rm * Rs;

        if (instruction.accumulate) {
            const uint64_t RdLo = get_word_from_register(instruction.RdLo);
            const uint64_t RdHi = get_word_from_register(instruction.RdHi);
            result += RdHi << 32 + RdLo;
        }

        //CSPR flags
        if (instruction.setConditionCodes) {
            struct CPSR_Struct CSPR = getCPSR();
            CSPR.Z = result == 0;
            CSPR.N = result < 0;
        }

        const uint32_t final_low = (uint32_t) (result & 0xffffffff);
        const uint32_t final_high = (uint32_t) ((result >> 32) & 0xffffffff);
        set_word_in_register(instruction.RdLo, final_low);
        set_word_in_register(instruction.RdHi, final_high);

    } else {

        const uint32_t Rm = get_word_from_register(instruction.Rm);
        const uint32_t Rs = get_word_from_register(instruction.Rs);
        uint64_t result = Rm * Rs;

        if (instruction.accumulate) {
            const uint64_t RdLo = get_word_from_register(instruction.RdLo);
            const uint64_t RdHi = get_word_from_register(instruction.RdHi);
            result += RdHi << 32 + RdLo;
        }

        //CSPR flags
        if (instruction.setConditionCodes) {
            struct CPSR_Struct CSPR = getCPSR();
            CSPR.Z = result == 0;
            CSPR.N = result < 0;
        }

        const uint32_t final_low = (uint32_t) (result & 0xffffffff);
        const uint32_t final_high = (uint32_t) ((result >> 32) & 0xffffffff);
        set_word_in_register(instruction.RdLo, final_low);
        set_word_in_register(instruction.RdHi, final_high);
    }

    return OK;

}
