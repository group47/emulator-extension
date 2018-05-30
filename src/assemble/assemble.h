//
// Created by ryro on 2018/5/27.
//

#ifndef ASSEMBLE_ASSEMBLE_H
#define ASSEMBLE_ASSEMBLE_H

#include <stdio.h>
#include "tokenizer.h"
#include "symbol_table.h"
#include "stdint.h"



struct Instruction parseDataProcessing1(char **, int, struct Token *);
struct Instruction parseDataProcessing2(char **, int, struct Token *);
struct Instruction parseDataProcessing3(char **, int, struct Token *);
struct Instruction parseMultiply1(char **, int tokenOffset, struct Token *);
struct Instruction tokenizeMultiply2(char **, int tokenOffset, struct Token *);
struct Instruction parseSingleDataTransfer1(char **, int tokenOffset, struct Token *);
struct Instruction parseBranch1(char **, int tokenOffset, struct Token *);
struct Instruction parseSpecial1(char **, int tokenOffset, struct Token *);

struct Instruction assembleDataProcessingInstruction(struct Token*);
struct Instruction assembleMultiplyInstruction(struct Token*);
struct Instruction assembleSingleDataInstruction(struct Token*);
struct Instruction assembleBranchInstruction(struct Token*);

uint16_t getOperand2Immediate(long operand2Val);
uint16_t getOperand2ShiftRegister(uint32_t operand2Val);
void initializeInstructionCodeTable(struct SymbolTable *);

#endif //ASSEMBLE_ASSEMBLE_H
