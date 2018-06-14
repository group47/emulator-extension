//
// Created by qs4617 on 07/06/18.
//

#include <assert.h>
#include <string.h>
#include "c3_domain_access_control.h"
#include "../../../state/emulator_state.h"

static struct C3_domain_access_control_register c3_domain_access_control_register;

enum ExecutionExitCode
execute_domain_access_control_register(struct CoprocessorRegisterTransferInstruction instruction) {
    assert(get_operating_mode() != usr);
    if (instruction.loadStore == LOAD) {
        set_word_in_register(instruction.Rd, *(uint32_t *) &c3_domain_access_control_register);
    } else if (instruction.loadStore == STORE) {
        uint32_t val = get_word_from_register(instruction.Rd);
        c3_domain_access_control_register = *(struct C3_domain_access_control_register *) &val;
    } else {
        assert(false);
    }
    return OK;
}

void init_C3_domain_access_control_register() {
    memset(&c3_domain_access_control_register, 0xffffffff, sizeof(struct C3_domain_access_control_register));
}