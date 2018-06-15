//
// Created by ryro on 2018/5/26.
//

#ifndef ASSEMBLE_TOKENIZER_H
#define ASSEMBLE_TOKENIZER_H

#include <stdbool.h>
#include <stdint.h>
#include "token.h"
#include "../shared/enums.h"
#include "symbol_table.h"

struct Instruction tokenizer(struct Token *, char *, struct SymbolTable *, struct SymbolTable *, uint16_t);
struct Token* initializeToken(struct Token *);
int separateString2(char**, char*, char*);
int separateSpecialCharacters(char**, char**, int, char*);

#endif //ASSEMBLE_TOKENIZER_H
