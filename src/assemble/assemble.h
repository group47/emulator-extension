//
// Created by ryro on 2018/5/27.
//

#ifndef ASSEMBLE_ASSEMBLE_H
#define ASSEMBLE_ASSEMBLE_H

#include <stdio.h>
#include "tokenizer.h"
#include "symbol_table.h"
#include "stdint.h"

struct Token* tokenizeDataProcessing1(char**, struct InstructionInfo*);
struct Token* tokenizeDataProcessing2(char**, struct InstructionInfo*);
struct Token* tokenizeDataProcessing3(char**, struct InstructionInfo*);
struct Token* tokenizeMultiply1(char**, struct InstructionInfo*);
struct Token* tokenizeMultiply2(char**, struct InstructionInfo*);
struct Token* tokenizeSingleDataTransfer1(char**, struct InstructionInfo*);
struct Token* tokenizeBranch1(char**, struct InstructionInfo*);
struct Token* tokenizeSpecial1(char**, struct InstructionInfo*);

void assembleDataProcessingInstruction(FILE* fpOutput, struct Token*);
void assembleMultiplyInstruction(FILE* fpOutput, struct Token*);
void assembleSingleDataInstruction(FILE* fpOutput, struct Token*);
void assembleBranchInstruction(FILE* fpOutput, struct Token*);

uint16_t getOperand2Immediate(long operand2Val);
uint16_t getOperand2ShiftRegister(uint32_t operand2Val);
struct SymbolTable* initializeInstructionCodeTable();






#endif //ASSEMBLE_ASSEMBLE_H
