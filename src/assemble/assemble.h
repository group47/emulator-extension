//
// Created by ryro on 2018/5/27.
//

#ifndef ASSEMBLE_ASSEMBLE_H
#define ASSEMBLE_ASSEMBLE_H

#include <stdio.h>
#include "tokenizer.h"
#include "symbol_table.h"
#include "stdint.h"



struct Token *parseDataProcessing1(char **, int, struct Token *);
struct Token *parseDataProcessing2(char **, int, struct Token *);
struct Token *parseDataProcessing3(char **, int, struct Token *);
struct Token *parseMultiply1(char **, int tokenOffset, struct Token *);
struct Token *tokenizeMultiply2(char **, int tokenOffset, struct Token *);
struct Token *parseSingleDataTransfer1(char **, int tokenOffset, struct Token *);
struct Token *parseBranch1(char **, int tokenOffset, struct Token *);
struct Token *parseSpecial1(char **, int tokenOffset, struct Token *);

void assembleDataProcessingInstruction(FILE* fpOutput, struct Token*);
void assembleMultiplyInstruction(FILE* fpOutput, struct Token*);
void assembleSingleDataInstruction(FILE* fpOutput, struct Token*);
void assembleBranchInstruction(FILE* fpOutput, struct Token*);

uint16_t getOperand2Immediate(long operand2Val);
uint16_t getOperand2ShiftRegister(uint32_t operand2Val);
struct SymbolTable* initializeInstructionCodeTable();

#endif //ASSEMBLE_ASSEMBLE_H
