//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C2_TRANSLATION_TABLE_BASE_CONTROL_H
#define SRC_C2_TRANSLATION_TABLE_BASE_CONTROL_H

#include <stdint.h>
#include <stdbool.h>
#include "../../../basic_typedefs.h"

struct C2_translation_table_base_control_register {
    uint8_t n : 3;
    uint32_t unp_sbz : 29;
}__attribute__((packed));
#endif //SRC_C2_TRANSLATION_TABLE_BASE_CONTROL_H

enum ExecutionExitCode execute_translation_table_base_control_register(struct CoprocessorRegisterTransferInstruction);

struct C2_translation_table_base_control_register get_translation_table_base_control_register();

void set_word_translation_table_base_control_register(Word);