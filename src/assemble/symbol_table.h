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

#include "../shared/enums.h"

//enum InstructionType {
//    DATAPROCESSING,
//    MULTIPLY,
//    SINGLEDATATRANSFER,
//    BRANCH,
//    SPECIAL
//};

//enum opCode {
//    and = 0b0000,
//    eor = 0b0001,
//    sub = 0b0010,
//    rsb = 0b0011,
//    add = 0b0100,
//    orr = 0b1100,
//    mov = 0b1101,
//    tst = 0b1000,
//    teq = 0b1001,
//    cmp = 0b1010
//};

//enum Cond {
//    eq = 0b0000,
//    ne = 0b0001,
//    ge = 0b1010,
//    lt = 0b1011,
//    gt = 0b1100,
//    le = 0b1101,
//    al = 0b1110
//};

struct InstructionInfo {
    uint8_t* mnemonics;
    enum InstructionType instructionType;
    enum Cond condCode;
    uint8_t opCode;
    uint8_t operandCount;
    struct Token* (*tokenize) (char*, struct InstructionInfo*);
    struct SymbolTable* symbolTable;
    struct SymbolTable* labelAddress;
    uint16_t address;
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
                    uint8_t opCode,
                    uint8_t operandCount,
                    struct Token* (*tokenize) (char**, struct InstructionInfo*));

#endif //ASSEMBLE_SYMBOL_TABLE_H
