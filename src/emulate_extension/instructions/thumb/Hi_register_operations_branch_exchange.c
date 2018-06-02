//
// Created by qs4617 on 02/06/18.
//

#include <assert.h>
#include "Hi_register_operations_branch_exchange.h"
#include "../../state/emulator_state.h"
#include "../../util/overflow_util.h"
#include "../../util/cpsr_util.h"


enum ExecutionExitCode execute_instruction_hi_register_operations_branch_exchange(struct HiRegisterOperationsBranchExchangeInstruction instruction) {
    if (instruction.H1 == 0 && instruction.H2 == 0) {
        assert(instruction.Op == 0b11);
    }

    uint16_t rs = instruction.RsHs;
    uint16_t rd = instruction.RdHd;

    if (instruction.H1) {
        rs += 8;
    }

    if (instruction.H2) {
        rd += 8;
    }

    bool borrow_occur;


    switch (instruction.Op) {
        case 0b00:
            set_word_in_register(rd, get_word_from_register(rs) + get_word_from_register(rd));
            break;
        case 0b01:
            borrow_occur = does_borrow_occur(get_word_from_register(rd), get_word_from_register(rs));
            set_word_in_register(rd, get_word_from_register(rd) - get_word_from_register(rs));
            //todo: set condition code
            break;
        case 0b10:
            set_word_in_register(rd, get_word_from_register(rs));
            break;
        case 0b11:
            assert(!instruction.H1);
            if (get_word_from_register(rs) & 0x1) {
                change_mode(THUMB);
            } else {
                change_mode(ARM);
            }
            break;
    }
    return OK;
}
