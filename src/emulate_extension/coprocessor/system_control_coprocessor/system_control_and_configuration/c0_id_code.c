//
// Created by qs4617 on 07/06/18.
//

#include "../../../../emulate_extension/instructions/arm/coprocessor_register_transfer.h"
#include "c0_id_code.h"
#include "../../../state/emulator_state.h"

static struct C0_main_id_register c0_main_id_register;

enum ExecutionExitCode execute_co_main_id_register(struct CoprocessorRegisterTransferInstruction instruction) {
    // todo: results of attempted access for each mode
    //set_word_in_register(instruction.Rd, );
    return OK;
}


//todo magic constasnts, also these may not be the constants we want
struct C0_main_id_register get_main_id_register() {
    //TODO TODO TODO REALLY A GOOD IDEA TO UNCOMMENT THE CODE BELOW
//    c0_main_id_register.architecture = 0xf;
//    c0_main_id_register.variant_number = 0x0;
//    c0_main_id_register.implementor = 0x41;
//    c0_main_id_register.primary_part_number = 0xB76;
//    c0_main_id_register.revision = 0x7;
//    return c0_main_id_register;
    uint32_t val = 0x412fc0f1;
    return *(struct C0_main_id_register *) &val;
}