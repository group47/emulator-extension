//
// Created by qs4617 on 07/06/18.
//

#include <assert.h>
#include <memory.h>
#include "../../../basic_typedefs.h"
#include "c2_translation_table_base1.h"
#include "../../../state/emulator_state.h"


static struct C2_translation_table_base_register1 c2_translation_table_base_register1;


enum ExecutionExitCode
execute_translation_table_base_register1(struct CoprocessorRegisterTransferInstruction instruction) {
    if (instruction.loadStore == LOAD) {
        set_word_in_register(instruction.Rd, *(uint32_t *) &c2_translation_table_base_register1);
    } else if (instruction.loadStore == STORE) {
        Word val = get_word_from_register(instruction.Rd);
        c2_translation_table_base_register1 = *(struct C2_translation_table_base_register1 *) &val;
    } else {
        assert(false);
    }
    return OK;
}

uint32_t get_word_translation_table_base_register1() {
    return *(uint32_t *) &c2_translation_table_base_register1;
}

void init_c2_translation_table_base_register1() {
    memset(&c2_translation_table_base_register1, 0, sizeof(struct C2_translation_table_base_register1));
}

struct C2_translation_table_base_register1 get_translation_table_base_register1() {
    return c2_translation_table_base_register1;
}