//
// Created by ryro on 2018/5/26.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "tokenizer.h"

const int MAX_TOKENS = 32;

// Might need to modify based on further included cases
// This will definitely break with register cases
// I didn't extract the register number or the immediate value from the string
// Might need to distinguish them later


struct Token* tokenizer(char* instruction, struct SymbolTable* symbolTable, struct SymbolTable* labelAddress,uint16_t current_address) {
    if (instruction == NULL){
        assert(false);
    }

    // Breaking the lines into tokens
    char** tokensFirstPass = malloc(sizeof(char*)*100);
    char** tokensSecondPass = malloc(sizeof(char*)*100);

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
            //printf("%s\n", token2);
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
        if (tokensSecondPass[0] == NULL) {
            return NULL;
        }
        struct Entry *entry = find(symbolTable, tokensSecondPass[0]);
        struct InstructionInfo instructionInfo;
        if (entry == NULL) {
            return NULL;
            assert(false);
        }
        instructionInfo = entry->rawEntry.instructionInfo;
        instructionInfo.symbolTable = symbolTable;
        instructionInfo.labelAddress = labelAddress;
        instructionInfo.address = current_address;
        token = entry->rawEntry.instructionInfo.tokenize(tokensSecondPass, &instructionInfo);
    }

    return token;
}

struct Token* initializeToken() {
    // Clearing the field is necessary, as not all of them are assigned
    struct Token* token = malloc(sizeof(struct Token));
    token->Rd = 0;
    token->Rn = 0;
    token->offset = 0;
    token->Rm = 0;
    token->Rs = 0;
    token->operand2 = 0;
    token->operand2IsImmediate = false;
    token->isPreIndexing = false;
    token->label = NULL;
    return token;
}

/*
int extractField(char* token) {
    if (token[0] == 'r')
}
 */