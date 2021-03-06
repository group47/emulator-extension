//
// Created by qs4617 on 07/06/18.
//

#include <assert.h>
#include <string.h>
#include "../../../instructions/arm/coprocessor_register_transfer.h"
#include "c2_translation_table_base_control.h"

static struct C2_translation_table_base_control_register c2_translation_table_base_control_register;

enum ExecutionExitCode
execute_translation_table_base_control_register(struct CoprocessorRegisterTransferInstruction instruction) {
    assert(false);
}


void init_c2_translation_table_base_control_register() {
    memset(&c2_translation_table_base_control_register, 0, sizeof(struct C2_translation_table_base_control_register));
}

Word get_word_translation_table_base_control_register() {
    return *(Word *) &c2_translation_table_base_control_register;
}

void set_word_translation_table_base_control_register(Word word) {
    c2_translation_table_base_control_register = *(struct C2_translation_table_base_control_register *) &word;
}