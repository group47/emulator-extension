//
// Created by ryro on 2018/5/26.
//

#ifndef ASSEMBLE_SYMBOL_TABLE_H
#define ASSEMBLE_SYMBOL_TABLE_H


//const int MAX_NUM_SYMBOL = 1000;

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <emulate_main.h>

#include "../shared/enums.h"

struct InstructionInfo {
    uint8_t* mnemonics;
    enum InstructionType instructionType;
    enum Cond condCode;
    enum OpCode opCode;
    uint16_t address;
    struct Token* (*tokenize) (char**, int, struct Token*);
    struct SymbolTable* symbolTable;
    struct SymbolTable* labelAddress;
};

//
struct Label {
    uint8_t* label;
    uint16_t address;
};

union RawEntry {
    struct InstructionInfo instructionInfo;
    struct Label label;
};

enum EntryType {
    INSTRUCTION_INFO,
    LABEL
};

struct Entry {
    union RawEntry rawEntry;
    enum EntryType entryType;
};

struct SymbolTable {
    size_t size;
    struct Entry entries[100];
};


bool addLabel(struct SymbolTable* symbolTable, uint8_t* label, uint16_t address);
struct InstructionInfo* intializeInstructionInfo();
struct Entry* find(struct SymbolTable* symbolTable, uint8_t* target);
bool addInstruction(struct SymbolTable* symbolTable,
                    enum InstructionType instructionType,
                    uint8_t* mnemonics,
                    enum Cond condCode,
                    enum OpCode opCode,
                    struct Token* (*tokenize) (char**, struct InstructionInfo*));

#endif //ASSEMBLE_SYMBOL_TABLE_H
