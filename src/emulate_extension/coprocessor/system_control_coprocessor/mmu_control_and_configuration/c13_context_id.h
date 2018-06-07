//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C13_CONTEXT_ID_H
#define SRC_C13_CONTEXT_ID_H

struct C13_context_id_register {
    uint8_t asid : 8;
    uint32_t procid : 24;
}__attribute__((packed));

enum ExecutionExitCode execute_context_id_register(struct CoprocessorRegisterTransferInstruction);

#endif //SRC_C13_CONTEXT_ID_H
