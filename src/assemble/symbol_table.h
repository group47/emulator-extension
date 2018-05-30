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
#include "../shared/instructions.h"

struct InstructionInfo {
    uint8_t* mnemonics;
    enum InstructionType instructionType;
    enum Cond condCode;
    enum OpCode opCode;
    uint16_t address;
    struct Instruction (*tokenize) (char**, int, struct Token*);
    struct Instruction (*assemble)(struct Token*);
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


bool addLabel(struct SymbolTable*, uint8_t*, uint16_t);
struct InstructionInfo* intializeInstructionInfo();
struct Entry* find(struct SymbolTable*, uint8_t*);
bool addInstruction(struct SymbolTable*,
                    enum InstructionType,
                    uint8_t*,
                    enum Cond,
                    enum OpCode,
                    struct Instruction (*tokenize) (char**,int, struct Token*),
                    struct Instruction (*assemble)(struct Token*));
void initializeInstructionCodeTable(struct SymbolTable *);

#endif //ASSEMBLE_SYMBOL_TABLE_H
