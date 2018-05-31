//
// Created by ryro on 2018/5/27.
//


#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include <memory.h>
#include "../shared/enums.h"
#include "../shared/instructions.h"
#include "tokenizer.h"
#include "parseDataProcessing.h"
#include "parseMultiply.h"
#include "parseSingleDataTransfer.h"
#include "parseBranch.h"
#include "parseSpecial.h"
#include "symbol_table.h"

bool secondToLastCharIs(const char *target, char c);
struct Entry* find(struct SymbolTable* symbolTable, char* target) {
    for (int i = 0; i < symbolTable->size; i++) {
        char* key;
        if (symbolTable->entries[i].entryType == INSTRUCTION_INFO) {
            struct InstructionInfo* instructionInfo = &symbolTable->entries[i].rawEntry;
            key = instructionInfo->mnemonics;
        } else if (symbolTable->entries[i].entryType == LABEL) {
            struct Label* label = &symbolTable->entries[i].rawEntry;
            key = label->label;
        } else {
            assert(false);
        }

        if (strcmp(key, target) == 0) {
            return &symbolTable->entries[i];
        }
    }
    return NULL;
}


bool addLabel(struct SymbolTable* symbolTable, char* label, uint16_t address) {
    char * label_copy = calloc(100, sizeof(char));//todo memory leak
    memcpy(label_copy,label,(strlen(label)+1)* sizeof(char));

    symbolTable->entries[symbolTable->size].rawEntry.label.label = label_copy;
    symbolTable->entries[symbolTable->size].rawEntry.label.address = address;
    symbolTable->entries[symbolTable->size].entryType = LABEL;
    symbolTable->size++;
    return true;
}

bool addInstruction(struct SymbolTable* symbolTable,
                    enum InstructionType instructionType,
                    char* mnemonics,
                    enum Cond condCode,
                    enum OpCode opCode,
                    struct Instruction (*tokenize) (char**,int,struct Token*),
                    struct Instruction (*assemble)(struct Token*)) {

    assert (symbolTable->size <= 511);

    symbolTable->entries[symbolTable->size].entryType = INSTRUCTION_INFO;
    symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.mnemonics = calloc(400, sizeof(char));//todo

    memcpy(symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.mnemonics, mnemonics, strlen(mnemonics) + 1);
    symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.instructionType = instructionType;
    symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.condCode = condCode;
    symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.opCode = opCode;
    symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.tokenize = tokenize;
    symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.assemble = assemble;
    symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.symbolTable = symbolTable;


    symbolTable->size++;
    return true;
}


void initializeInstructionCodeTable(struct SymbolTable * table) {
    table->size = 0;
    addInstruction(table, DATA_PROCESSING, "add", al, add, &parseDataProcessing1, &assembleDataProcessingInstruction);
    addInstruction(table, DATA_PROCESSING, "sub", al, sub, &parseDataProcessing1, &assembleDataProcessingInstruction);
    addInstruction(table, DATA_PROCESSING, "rsb", al, rsb, &parseDataProcessing1, &assembleDataProcessingInstruction);
    addInstruction(table, DATA_PROCESSING, "and", al, and, &parseDataProcessing1, &assembleDataProcessingInstruction);
    addInstruction(table, DATA_PROCESSING, "eor", al, eor, &parseDataProcessing1, &assembleDataProcessingInstruction);
    addInstruction(table, DATA_PROCESSING, "orr", al, orr, &parseDataProcessing1, &assembleDataProcessingInstruction);
    addInstruction(table, DATA_PROCESSING, "mov", al, mov, &parseDataProcessing2, &assembleDataProcessingInstruction);
    addInstruction(table, DATA_PROCESSING, "tst", al, tst, &parseDataProcessing3, &assembleDataProcessingInstruction);
    addInstruction(table, DATA_PROCESSING, "teq", al, teq, &parseDataProcessing3, &assembleDataProcessingInstruction);
    addInstruction(table, DATA_PROCESSING, "cmp", al, cmp, &parseDataProcessing3, &assembleDataProcessingInstruction);
    addInstruction(table, MULTIPLY, "mul", al, invalidOpcode, &parseMultiply1, &assembleMultiplyInstruction);
    addInstruction(table, MULTIPLY, "mla", al, invalidOpcode, &parseMultiply2, &assembleMultiplyInstruction);
    addInstruction(table, SINGLE_DATA_TRANSFER, "ldr", al, invalidOpcode, &parseSingleDataTransfer1, &assembleSingleDataInstruction);
    addInstruction(table, SINGLE_DATA_TRANSFER, "str", al, invalidOpcode, &parseSingleDataTransfer1, &assembleSingleDataInstruction);
    addInstruction(table, BRANCH_INSTRUCTION, "beq", eq, invalidOpcode, &parseBranch1, &assembleBranchInstruction);
    addInstruction(table, BRANCH_INSTRUCTION, "bne", ne, invalidOpcode, &parseBranch1, &assembleBranchInstruction);
    addInstruction(table, BRANCH_INSTRUCTION, "bge", ge, invalidOpcode, &parseBranch1, &assembleBranchInstruction);
    addInstruction(table, BRANCH_INSTRUCTION,"blt", lt, invalidOpcode, &parseBranch1, &assembleBranchInstruction);
    addInstruction(table, BRANCH_INSTRUCTION, "ble", le, invalidOpcode, &parseBranch1, &assembleBranchInstruction);
    addInstruction(table, BRANCH_INSTRUCTION,"b", al, invalidOpcode, &parseBranch1, &assembleBranchInstruction);
    addInstruction(table, DATA_PROCESSING,"lsl", al, invalidOpcode, &parseSpecial1, NULL);
    addInstruction(table, DATA_PROCESSING, "andeq", eq, and, &parseDataProcessing1, &assembleDataProcessingInstruction);
}