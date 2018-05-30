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


struct Instruction tokenizer(char* instruction, struct SymbolTable *symbolTable, struct SymbolTable* labelAddress,uint16_t current_address) {
    if (instruction == NULL){
        assert(false);
    }
    // Breaking the lines into tokens
    char** tokens = malloc(sizeof(char*)*100);//todo

    char* token1;

    token1 = strtok(instruction, ", ");

    int countFirstPass = 0;

    while (token1 != NULL) {
        tokens[countFirstPass] = malloc(511);
        memcpy(tokens[countFirstPass], token1, strlen(token1));
        token1 = strtok(NULL, ", ");
        countFirstPass++;
    }

    // Structure them according to their operation


    struct Instruction badValue;
    badValue.type = INVALID;

    if (countFirstPass == 1) {
        return badValue;
    }

    if (tokens[0] == NULL) {
        return badValue;
    }

    struct Entry *entry = find(symbolTable, tokens[0]);
    struct InstructionInfo instructionInfo;
    if (entry == NULL) {
        return badValue;
    }


    instructionInfo = entry->rawEntry.instructionInfo;
    instructionInfo.symbolTable = symbolTable;
    instructionInfo.labelAddress = labelAddress;
    instructionInfo.address = current_address;
    struct Token newToken;
    initializeToken(&newToken);
    newToken.instructionInfo = &instructionInfo;
    return entry->rawEntry.instructionInfo.tokenize(tokens, 1, &newToken);
}

struct Token* initializeToken(struct Token* token) {
    // Clearing the field is necessary, as not all of them are assigned
    token->Rd = 0;
    token->Rn = 0;
    token->offset = 0;
    token->Rm = 0;
    token->Rs = 0;
    token->operand2 = 0;
    token->operand2IsImmediate = false;
    token->offsetIsImmediate = false;
    token->isPreIndexing = false;
    token->label = NULL;
    token->offsetIsNegative = false;
    token->use_extra_data = false;
    return token;
}

/*
int extractField(char* token) {
    if (token[0] == 'r')
}
 */