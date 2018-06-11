//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C2_TRANSLATION_TABLE_BASE1_H
#define SRC_C2_TRANSLATION_TABLE_BASE1_H

#endif //SRC_C2_TRANSLATION_TABLE_BASE1_H



struct C2_translation_table_base_register1 {
    bool C : 1;
    bool S : 1;
    bool P : 1;
    uint8_t rgn : 2;
    uint32_t translation_table_base_1_unp_sbz : 17;
}__attribute__((packed));


enum ExecutionExitCode execute_translation_table_base_register1(struct CoprocessorRegisterTransferInstruction);
