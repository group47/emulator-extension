//
// Created by ryro on 2018/5/26.
//

#ifndef ASSEMBLE_TOKENIZER_H
#define ASSEMBLE_TOKENIZER_H

#include <stdbool.h>
#include <stdint-gcc.h>
#include "../shared/enums.h"
struct Token {
    struct InstructionInfo* instructionInfo;
    char* label;
    uint8_t Rn;
    uint8_t Rd;
    uint8_t Rs;
    uint8_t Rm;
    uint16_t operand2 : 12;
    uint32_t offset;
    bool operand2IsImmediate;
    bool offsetIsImmediate;
    bool offsetIsNegative;
    bool isPreIndexing;
    bool use_extra_data;
};



struct Instruction tokenizer(struct Token*, const char*, struct SymbolTable*,struct SymbolTable*,uint16_t);
struct Token* initializeToken(struct Token *);
int separateString2(char**, char*, char*);
int separateSpecialCharacters(char**, char**, int, char*);

#endif //ASSEMBLE_TOKENIZER_H
