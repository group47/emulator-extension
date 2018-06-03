//
// Created by fpn17 on 02/06/18.
//

#ifndef SRC_LOAD_STORE_SIGN_EXTENDED_BYTE_HALF_WORD_H
#define SRC_LOAD_STORE_SIGN_EXTENDED_BYTE_HALF_WORD_H

#include <stdbool.h>
#include "../../basic_typedefs.h"

struct LoadStoreSignExtendedByteHalfword{
    RegisterAddress Rd:3;
    RegisterAddress Rb:3;
    RegisterAddress Ro:3;
    bool filler1 : 1;
    bool signed_ : 1;
    bool hFlag : 1;
    uint8_t filler1010 : 4;
}__attribute__((packed));

enum ExecutionExitCode execute_instruction_load_store_sign_extended_byte_half_word(struct LoadStoreSignExtendedByteHalfword instruction);
#endif //SRC_LOAD_STORE_SIGN_EXTENDED_BYTE_HALF_WORD_H
