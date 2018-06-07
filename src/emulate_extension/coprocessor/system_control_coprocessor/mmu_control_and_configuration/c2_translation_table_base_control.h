//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C2_TRANSLATION_TABLE_BASE_CONTROL_H
#define SRC_C2_TRANSLATION_TABLE_BASE_CONTROL_H

#include <stdint.h>
#include <stdbool.h>

struct C2_translation_table_base_control_register {
    uint8_t n : 2;
    bool sbz : 1;
    bool pd0 : 1;
    bool pd1 : 1;
    uint32_t unp_sbz : 27;
}__attribute__((packed));
#endif //SRC_C2_TRANSLATION_TABLE_BASE_CONTROL_H

enum ExecutionExitCode execute_translation_table_base_control_register(struct CoprocessorRegisterTransferInstruction);