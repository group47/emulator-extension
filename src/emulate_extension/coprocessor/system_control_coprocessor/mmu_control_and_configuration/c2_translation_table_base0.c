//
// Created by qs4617 on 07/06/18.
//

#include <assert.h>
#include <string.h>
#include "c2_translation_table_base0.h"
#include "../../../util/common_enums.h"
#include "../../../instructions/arm/coprocessor_register_transfer.h"
#include "c2_translation_table_base_control.h"
#include "../../../state/emulator_state.h"

static struct C2_translation_table_base_register0 c2_translation_table_base_register0;

enum ExecutionExitCode
execute_translation_table_base_register0(struct CoprocessorRegisterTransferInstruction instruction) {
    switch (instruction.loadStore) {
        case LOAD:
            set_word_in_register(instruction.Rd, *(uint32_t *) &c2_translation_table_base_register0);
            return OK;
        case STORE:
            *(uint32_t *) &c2_translation_table_base_register0 = get_word_from_register(instruction.Rd);
            return OK;
        default:
            assert(false);
    }
}

void init_c2_translation_table_base_register0() {
    init_c2_translation_table_base_control_register();
    c2_translation_table_base_register0.P = 0;
    c2_translation_table_base_register0.S = 0;
    c2_translation_table_base_register0.C = 0;
    memset(&c2_translation_table_base_register0, 0, sizeof(struct C2_translation_table_base_register0));
}