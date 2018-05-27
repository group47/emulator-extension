//
// Created by ryro on 2018/5/26.
//

#ifndef ASSEMBLE_SYMBOL_TABLE_H
#define ASSEMBLE_SYMBOL_TABLE_H

#define MAX_LABEL_LENGTH = 511
#define MAX_NUM_SYMBOL = 1000

#include <assert.h>
#include <stdlib.h>

enum InstructionType {
    DATAPROCESSING,
    MULTIPLY,
    SINGLEDATATRANSFER,
    BRANCH,
    SPECIAL
};

enum opCode {
    and = 0b0000,
    eor = 0b0001,
    sub = 0b0010,
    rsb = 0b0011,
    add = 0b0100,
    orr = 0b1100,
    mov = 0b1101,
    tst = 0b1000,
    teq = 0b1001,
    cmp = 0b1010
};

enum Cond {
    eq = 0b0000,
    ne = 0b0001,
    ge = 0b1010,
    lt = 0b1011,
    gt = 0b1100,
    le = 0b1101,
    al = 0b1110
};

/*
struct SymbolTable {
    struct Entry** entries;
    size_t size;
};

struct Entry {
    char* string;
    int integer;
};


int find(struct SymbolTable* symbolTable, char* key) {
    for (int i = 0; i < symbolTable->size; i++) {
        struct Entry* entry = symbolTable->entries[symbolTable->size];
        if (entry != NULL) {
            if (strcmp(entry->string, key) == 0) {
                // honestly, I think we could just encode all the operation
                // so that we don't have to compare it for every search
                return entry->integer;
            }
        }
    }
    return -100000;
}


int addToSymbolTable(struct SymbolTable* symbolTable, const char* key, int val) {

}

struct SymbolTable* initializeMnemonicsToOpCode() {
    struct SymbolTable* symbolTable;
    addToSymbolTable(symbolTable, "add", add);
}

struct SymbolTable* initializeMnemonicsToCondCode() {

}
*/


struct SymbolTable {
    size_t size;
    struct Entry* entries: sizeof(struct Entry) * MAX_NUM_SYMBOL;
};


struct InstructionInfo {
    uint8_t* mnemonics;
    enum InstructionType instructionType;
    uint8_t condCode;
    uint8_t opCode;
    uint8_t operandCount;
    int (*operationPointer) (int);
};

struct Label {
    uint8_t* label;
    uint16_t address;
};

union RawEntry {
    struct InstructionInfo;
    struct Label;
};

struct Entry {
    union RawEntry rawEntry;
    enum EntryType entryType;
};

enum EntryType {
    INSTRUCTION_INFO,
    LABEL
};

bool addLabel(struct SymbolTable* symbolTable, uint8_t* label, uint16_t address) {
    struct Label* labelEntry = malloc(sizeof(struct Label));
    labelEntry->label = label; // concern: the original object might be destroyed
    labelEntry->address = address;

    struct Entry entry;
    entry.rawEntry = *((union RawEntry*) labelEntry);
    entry.entryType = LABEL;
    symbolTable->entries[symbolTable->size] = entry;

    symbolTable->size++;
    return true;
}

bool addInstruction(struct SymbolTable* symbolTable,
              enum InstructionType instructionType,
              uint8_t* mnemonics,
              uint8_t condCode,
              uint8_t opCode,
              uint8_t operandCount) {

    assert (symbolTable->size <= MAX_LABEL_LENGTH);

    struct InstructionInfo* instructionInfo = malloc(sizeof(struct InstructionInfo));
    instructionInfo->mnemonics = mnemonics;
    instructionInfo->condCode = condCode;
    instructionInfo->opCode = opCode;
    instructionInfo->operandCount = operandCount;

    struct Entry entry;
    entry.rawEntry = *((union RawEntry*) instructionInfo);
    entry.entryType = INSTRUCTION_INFO;
    symbolTable->entries[symbolTable->size] = entry;

    symbolTable->size++;
    return true;
}


struct Entry* find(struct SymbolTable* symbolTable, uint8_t* target) {
    for (int i = 0; i < symbolTable->size; i++) {
        uint8_t* key;
        if (symbolTable->entries[i].entryType == INSTRUCTION_INFO) {
            struct InstructionInfo* instructionInfo = &symbolTable->entries[i].rawEntry;
            key = instructionInfo->mnemonics;
        } else if (symbolTable->entries[i].entryType == LABEL) {
            struct Label* label = &symbolTable->entries[i].rawEntry;
            key = label->label;
        }

        if (strcmp(key, target) == 0) {
            return &symbolTable->entries[i];
        }
      }
    return NULL;
}


#endif //ASSEMBLE_SYMBOL_TABLE_H
