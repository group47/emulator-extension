//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C2_TRANSLATION_TABLE_BASE0_H
#define SRC_C2_TRANSLATION_TABLE_BASE0_H

#include <stdbool.h>
#include <stdint.h>
#include "../../../basic_typedefs.h"



struct C2_translation_table_base_register0 {
    bool C : 1;
    bool S : 1;
    bool P : 1;
    uint8_t rgn : 2;
    uint32_t translation_table_base_0_unp_sbz : 17;
}__attribute__((packed));


enum ExecutionExitCode execute_translation_table_base_register0(struct CoprocessorRegisterTransferInstruction);
Word get_word_translation_table_base_register0();
void set_word_translation_table_base_register0(Word);

void init_c2_translation_table_base_register0();

#endif //SRC_C2_TRANSLATION_TABLE_BASE0_H
