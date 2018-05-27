//
// Created by ryro on 2018/5/26.
//

#ifndef ASSEMBLE_TOKENIZER_H
#define ASSEMBLE_TOKENIZER_H

#include "symbol_table.h"

struct Token {
    struct InstructionInfo* instructionInfo;
    char* label;
    uint8_t Rn;
    uint8_t Rd;
    uint8_t Rs;
    uint8_t Rm;
    uint32_t operand2;
    uint32_t offset;
    bool operand2IsImmediate;
};

struct Token* tokenizer(char*, struct SymbolTable*);
struct Token* initializeToken();

#endif //ASSEMBLE_TOKENIZER_H
