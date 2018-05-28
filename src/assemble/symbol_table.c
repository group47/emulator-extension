//
// Created by ryro on 2018/5/27.
//

#include <string.h>
#include "symbol_table.h"
#include "tokenizer.h"


bool secondToLastCharIs(const char *target, char c);
struct Entry* find(struct SymbolTable* symbolTable, uint8_t* target) {
    for (int i = 0; i < symbolTable->size; i++) {
        uint8_t* key;
        if (symbolTable->entries[i].entryType == INSTRUCTION_INFO) {
            struct InstructionInfo* instructionInfo = &symbolTable->entries[i].rawEntry;
            key = instructionInfo->mnemonics;
        } else if (symbolTable->entries[i].entryType == LABEL) {
            struct Label* label = &symbolTable->entries[i].rawEntry;
            key = label->label;
        } else {
//            assert(false);
        }

        if (strcmp(key, target) == 0) {
            return &symbolTable->entries[i];
        }
    }
    return NULL;
}


bool addLabel(struct SymbolTable* symbolTable, uint8_t* label, uint16_t address) {
    /*
    struct Label* labelEntry = malloc(sizeof(struct Label));
    labelEntry->label = label; // concern: the original object might be destroyed
    labelEntry->address = address;

    struct Entry* entry = malloc(sizeof(struct Entry));
    entry->rawEntry = *((union RawEntry*) labelEntry);
    entry->entryType = LABEL;
     */
    uint8_t * label_copy = malloc(100*sizeof(uint8_t));//todo memory leak
    memcpy(label_copy,label,strlen(label)* sizeof(uint8_t));

    symbolTable->entries[symbolTable->size].rawEntry.label.label = label_copy;
    symbolTable->entries[symbolTable->size].rawEntry.label.address = address;
    symbolTable->entries[symbolTable->size].entryType = LABEL;
    symbolTable->size++;
    return true;
}

struct InstructionInfo* intializeInstructionInfo() {
    struct InstructionInfo* instructionInfo = malloc(sizeof(instructionInfo));
    instructionInfo->mnemonics = malloc(8*511);
    return instructionInfo;
}



bool addInstruction(struct SymbolTable* symbolTable,
                    enum InstructionType instructionType,
                    uint8_t* mnemonics,
                    uint8_t condCode,
                    uint8_t opCode,
                    uint8_t operandCount,
                    struct Token* (*tokenize) (char**, struct InstructionInfo*)) {

    assert (symbolTable->size <= 511);

    symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.mnemonics = malloc(400);

    memcpy(symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.mnemonics, mnemonics, strlen(mnemonics));
    symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.instructionType = instructionType;
    symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.condCode = condCode;
    symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.opCode = opCode;
    symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.operandCount = operandCount;
    symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.tokenize = tokenize;
    symbolTable->entries[symbolTable->size].rawEntry.instructionInfo.symbolTable = symbolTable;
    /*

    struct Entry *entry = malloc(sizeof(struct Entry));
    entry->rawEntry.instructionInfo.mnemonics = malloc(2000);
    memcpy(entry->rawEntry.instructionInfo.mnemonics, mnemonics, strlen(mnemonics));
    entry->rawEntry.instructionInfo.condCode = condCode;
    entry->rawEntry.instructionInfo.opCode = opCode;
    entry->rawEntry.instructionInfo.operandCount = operandCount;
    symbolTable->entries[symbolTable->size] = entry;
    */

    /*

    struct InstructionInfo* instructionInfo = intializeInstructionInfo();
    memcpy(instructionInfo->mnemonics, mnemonics, strlen(mnemonics));
    instructionInfo->condCode = condCode;
    instructionInfo->opCode = opCode;
    instructionInfo->operandCount = operandCount;

    struct Entry *entry = malloc(sizeof(struct Entry));
    entry->rawEntry = *((union RawEntry*) instructionInfo);
    entry->entryType = INSTRUCTION_INFO;
    symbolTable->entries[symbolTable->size] = malloc(sizeof(struct Entry));
     */

    symbolTable->size++;
    return true;
}

