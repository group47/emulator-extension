//
// Created by qs4617 on 07/06/18.
//

#include <string.h>
#include <assert.h>
#include "c2_translation_table_base0.h"
#include "../../../state/emulator_state.h"

static struct C2_translation_table_base_register0 c2_translation_table_base_register0;

enum ExecutionExitCode
execute_translation_table_base_register0(struct CoprocessorRegisterTransferInstruction instruction) {
    if (instruction.loadStore == LOAD) {
        set_word_in_register(instruction.Rd, *(uint32_t *) &c2_translation_table_base_register0);
    } else if (instruction.loadStore == STORE) {
        Word val = get_word_from_register(instruction.Rd);
        c2_translation_table_base_register0 = *(struct C2_translation_table_base_register0 *) &val;
    } else {
        assert(false);
    }
    return OK;
}

Word get_word_translation_table_base_register0() {
    return *(Word *) &c2_translation_table_base_register0;
}

struct C2_translation_table_base_register0 get_translation_table_base_register0() {
    return c2_translation_table_base_register0;
}

void init_c2_translation_table_base_register0() {
    memset(&c2_translation_table_base_register0, 0, sizeof(struct C2_translation_table_base_register0));
}