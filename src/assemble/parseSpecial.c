//
// Created by qs4617 on 30/05/18.
//


#include <memory.h>
#include "symbol_table.h"
#include "tokenizer.h"
#include "parseDataProcessing.h"

// for lsl
struct Instruction parseSpecial1(char **tokens, int tokenOffset, struct Token * token) {
    char** tokensRestructure = malloc(sizeof(char*)*20);
    for (int i = 0; i < 5; i++) {
        tokensRestructure[i] = malloc(sizeof(char)*10);
    }
    memcpy(tokensRestructure[0], "mov", 3);
    tokensRestructure[1] = tokens[1];
    tokensRestructure[2] = tokens[1];
    memcpy(tokensRestructure[3], "lsl", 3);
    tokensRestructure[4] = tokens[3];

    token->instructionInfo = &find(token->instructionInfo->symbolTable, "mov")->rawEntry.instructionInfo;

    return parseDataProcessing2(tokensRestructure, 1, token);//todo
}
