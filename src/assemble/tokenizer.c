//
// Created by ryro on 2018/5/26.
//

#include <string.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "tokenizer.h"

const int MAX_TOKENS = 32;

// Might need to modify based on further included cases
// This will definitely break with register cases
// I didn't extract the register number or the immediate value from the string
// Might need to distinguish them later


struct Token* tokenizer(char* instruction, struct SymbolTable* symbolTable) {

    // Breaking the lines into tokens
    char* tokensFirstPass[MAX_TOKENS];
    char* tokensSecondPass[MAX_TOKENS];

    char* token1;
    char* token2;

    token1 = strtok(instruction, ",");

    int countFirstPass = 0;

    while (token1 != NULL) {
        tokensFirstPass[countFirstPass] = malloc(511);
        memcpy(tokensFirstPass[countFirstPass], token1, strlen(token1));
        token1 = strtok(NULL, ",");
        countFirstPass++;
    }

    int countSecondPass = 0;

    for (int i = 0; i < countFirstPass; i++) {
        token2 = strtok(tokensFirstPass[i], " ");
        while (token2 != NULL) {
            tokensSecondPass[countSecondPass] = malloc(511);
            memcpy(tokensSecondPass[countSecondPass], token2, strlen(token2));
            token2 = strtok(NULL, " ");
            countSecondPass++;
        }
    }

    // Structure them according to their operation

    struct Token* token;

    if (strlen(tokensSecondPass) == 1) {
        token = malloc(sizeof(struct Token));
        token->label = tokensSecondPass[0];
    } else {
        struct Entry *entry = find(symbolTable, tokensSecondPass[0]);
        token = entry->rawEntry.instructionInfo.tokenize(tokensSecondPass, entry);

    }

    return token;
}

/*
int extractField(char* token) {
    if (token[0] == 'r')
}
 */