//
// Created by qs4617 on 07/06/18.
//

#include <string.h>
#include <assert.h>
#include "c1_control.h"
#include "../../../state/emulator_state.h"


static struct C1_control_register c1_control_register;

enum ExecutionExitCode execute_c1_control_register(struct CoprocessorRegisterTransferInstruction instruction) {
    assert(instruction.Rd != PC_ADDRESS);//this has special behavior which we don't want to implement unless necessary
    if (instruction.loadStore == LOAD) {
        set_word_in_register(instruction.Rd, *(uint32_t *) &c1_control_register);
    } else if (instruction.loadStore == STORE) {
        assert(get_operating_mode() != usr);
        Word val = get_word_from_register(instruction.Rd);
        c1_control_register = *(struct C1_control_register *) &val;
    } else {
        assert(false);
    }
    return OK;
}


//Table 3-45 B bit, U bit, and EE bit settings, and Control Register reset value
//possible init vals are:
//0x00050078 0x00052078
//0x000500F8 0x000520F8
//0x00450078 0x00452078
//0x02450078 0x02452078

void init_c1_control_register() {
    memset(&c1_control_register, 0, sizeof(struct C1_control_register));
    c1_control_register.ee = 1;
    c1_control_register.u = 1;
    c1_control_register.b = 0;

}
