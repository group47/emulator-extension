//
// Created by qs4617 on 07/06/18.
//

#include <stdbool.h>
#include "../../../instructions/arm/coprocessor_register_transfer.h"

#ifndef SRC_C2_TRANSLATION_TABLE_BASE1_H
#define SRC_C2_TRANSLATION_TABLE_BASE1_H

#endif //SRC_C2_TRANSLATION_TABLE_BASE1_H



struct C2_translation_table_base_register1 {
    bool C : 1;
    bool S : 1;
    bool P : 1;
    uint8_t rgn : 2;
    uint16_t unp_sbz : 9;
    uint32_t translation_table_base_1:18;
}__attribute__((packed));


enum ExecutionExitCode
execute_translation_table_base_register1(struct CoprocessorRegisterTransferInstruction instruction);
Word get_word_translation_table_base_register1();

struct C2_translation_table_base_register1 get_translation_table_base_register1();
void set_word_translation_table_base_register1(Word);