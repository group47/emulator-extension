//
// Created by qs4617 on 07/06/18.
//

#include "../../../basic_typedefs.h"
#include "c2_translation_table_base1.h"


static struct C2_translation_table_base_register1 c2_translation_table_base_register1;

Word get_word_translation_table_base_register1() {
    return *(Word *) &c2_translation_table_base_register1;
}

void set_word_translation_table_base_register1(Word word) {
    c2_translation_table_base_register1 = *(struct C2_translation_table_base_register1 *) &word;
}