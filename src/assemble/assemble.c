//
// Created by ryro on 2018/5/26.
//

#include "stdio.h"
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "symbol_table.h"
#include "tokenizer.h"
#include "list.h"
#include "assemble.h"


const uint32_t MASK20 = 0b00000000000100000000000000000000;

void assembleDataProcessingInstruction(FILE* fpOutput, struct Token* token) {
    uint32_t binary = 0;
    binary |= ((uint32_t)token->instructionInfo->condCode) << 28;

    // set I bit
    if (token->operand2IsImmediate) {
        binary |= (0x1) << 25;
    }

    // set opcode
    binary |= (token->instructionInfo->opCode) << 21;

    // set S bit
    if (token->instructionInfo->opCode == tst
        || token->instructionInfo->opCode == teq
        || token->instructionInfo->opCode == cmp) {
        binary |= (0x1) << 20;
    }

    char dummy[100];

    binary |= ((uint8_t)token->Rn) << 16;
    binary |= ((uint8_t)token->Rd) << 12;
    binary |= getOperand2Immediate(token->operand2);

    char binaryArray[32];
    //sprintf(binaryArray, "%lu",binary);
    //fwrite(binaryArray, 32, 1, fpOutput);
    binary_file_writer32(fpOutput, binary);
}


//todo : determine whether the value is representable
uint8_t getOperand2Immediate(uint32_t operand2Val) {
    uint32_t mask = 0x0001;
    return operand2Val;
}


void assembleMultiplyInstruction(FILE* fpOutput, struct Token* token) {
}

void assembleSingleDataInstruction(FILE* fpOutput, struct Token* token) {
}

void assembleBranchInstruction(FILE* fpOutput, struct Token* token) {
}

struct Token* tokenizeDataProcessing1(char** tokens, struct InstructionInfo* instructionInfo) {
    assert(strlen(tokens) >= 4);
    char dummy[500];
    struct Token* token = initializeToken();
    token->instructionInfo = instructionInfo;
    if (tokens[3][0] == '#') {
        token->operand2IsImmediate = true;
    } else {
        token->operand2IsImmediate = false;
    }
    token->Rd = strtol(tokens[1]+1, dummy, 10);
    token->Rn = strtol(tokens[2]+1, dummy, 10);
    // Handling expression case only
    token->operand2 = strtol(tokens[3]+1, dummy, 10);
    return token;
}

struct Token* tokenizeDataProcessing2(char** tokens, struct InstructionInfo* instructionInfo) {
    assert(strlen(tokens) >=3);
    char dummy[500];
    struct Token* token = initializeToken();
    token->instructionInfo = instructionInfo;
    token->Rn = 0;
    token->Rd = (uint8_t)strtol(tokens[1]+1, dummy, 10);
    // Handling expression case only
    if (tokens[2][0] == '#') {
        token->operand2IsImmediate = true;
    } else {
        token->operand2IsImmediate = false;
    }
    token->operand2 = strtol(tokens[2]+1, dummy, 10);
    return token;
}

struct Token* tokenizeDataProcessing3(char** tokens, struct InstructionInfo* instructionInfo) {
    return NULL;
}

struct Token* tokenizeMultiply1(char** tokens, struct InstructionInfo* instructionInfo) {
    return NULL;
}

struct Token* tokenizeMultiply2(char** tokens, struct InstructionInfo* instructionInfo) {
    return NULL;
}

struct Token* tokenizeSingleDataTransfer1(char** tokens, struct InstructionInfo* instructionInfo) {
    return NULL;
}

struct Token* tokenizeBranch1(char** tokens, struct InstructionInfo* instructionInfo) {
    return NULL;
}

struct Token* tokenizeSpecial1(char** tokens, struct InstructionInfo* instructionInfo) {
    return NULL;
}


struct SymbolTable* initializeInstructionCodeTable() {
    struct SymbolTable* instructionCodeTable = malloc(sizeof(struct SymbolTable));
    instructionCodeTable->size = 0;
    addInstruction(instructionCodeTable, DATAPROCESSING, "add", al, add, 3, &tokenizeDataProcessing1);
    addInstruction(instructionCodeTable, DATAPROCESSING, "sub", al, sub, 3, &tokenizeDataProcessing1);
    addInstruction(instructionCodeTable, DATAPROCESSING, "rsb", al, rsb, 3, &tokenizeDataProcessing1);
    addInstruction(instructionCodeTable, DATAPROCESSING, "and", al, and, 3, &tokenizeDataProcessing1);
    addInstruction(instructionCodeTable, DATAPROCESSING, "eor", al, eor, 3, &tokenizeDataProcessing1);
    addInstruction(instructionCodeTable, DATAPROCESSING, "orr", al, orr, 3, &tokenizeDataProcessing1);
    addInstruction(instructionCodeTable, DATAPROCESSING, "mov", al, mov, 2, &tokenizeDataProcessing2);
    addInstruction(instructionCodeTable, DATAPROCESSING, "tst", al, tst, 2, &tokenizeDataProcessing3);
    addInstruction(instructionCodeTable, DATAPROCESSING, "teq", al, teq, 2, &tokenizeDataProcessing3);
    addInstruction(instructionCodeTable, DATAPROCESSING, "cmp", al, cmp, 2, &tokenizeDataProcessing3);
    addInstruction(instructionCodeTable, MULTIPLY, "mul", al, 0, 3, &tokenizeMultiply1);
    addInstruction(instructionCodeTable, MULTIPLY, "mla", al, 0, 4, &tokenizeMultiply2);
    addInstruction(instructionCodeTable, SINGLEDATATRANSFER, "ldr", 0, 0, 2, &tokenizeSingleDataTransfer1);
    addInstruction(instructionCodeTable, SINGLEDATATRANSFER, "str", 0, 0, 2, &tokenizeSingleDataTransfer1);
    addInstruction(instructionCodeTable, BRANCH, "beq", eq, 0, 1, &tokenizeBranch1);
    addInstruction(instructionCodeTable, BRANCH, "bne", ne, 0, 1, &tokenizeBranch1);
    addInstruction(instructionCodeTable, BRANCH, "bge", ge, 0, 1, &tokenizeBranch1);
    addInstruction(instructionCodeTable, BRANCH,"blt", lt, 0, 1, &tokenizeBranch1);
    addInstruction(instructionCodeTable, BRANCH, "ble", le, 0, 1, &tokenizeBranch1);
    addInstruction(instructionCodeTable, BRANCH,"b", gt, 0, 1, &tokenizeBranch1);
    addInstruction(instructionCodeTable, SPECIAL,"lsl", al, 0, 2, &tokenizeSpecial1);
    addInstruction(instructionCodeTable, SPECIAL, "andeq", eq, 0, 3, &tokenizeSpecial1);
    return instructionCodeTable;
}

int main(int argc, char** argv) {

    if (argc != 3) {
        fprintf(stderr,
                "the end of the world has come, or you entered the wrong number of arguments");
        return -100000;
    }

    const char* sourceFileName = argv[1];
    const char* outputFileName = argv[2];

    FILE* fpSource = fopen(sourceFileName, "r");
    FILE* fpOutput = fopen(outputFileName, "w");

    if (fpSource == NULL) {
        fprintf(stderr,
                "the end of the world has come, or you entered the wrong source filename\n");
    }

    if (fpOutput == NULL) {
        fprintf(stderr,
                "the end of the world has come, or you entered the wrong output filename\n");
    }

    char* instruction = NULL;
    size_t instructionLength = 0;
    struct SymbolTable* instructionCode = initializeInstructionCodeTable();
    struct SymbolTable labelAddress;
    struct ForwardReferenceList* forwardReferenceLabels;

    FILE* fpOutputHead = fpOutput;
    uint16_t offset = 0;


    while (getline(&instruction, &instructionLength, fpSource)) {
        //assert(instructionLength == INSTRUCTION_LENGTH);

        struct Token* token = tokenizer(instruction, instructionCode);
        if (token == NULL) {
            break;
        }
        /*
        if (strlen(tokens) == 1) {
            char* label = malloc(8*strlen(tokens[0]-1)); // remove the : in the end


            // It is a label
            writeAddress(&forwardReferenceLabels, tokens[0], offset);
            addLabel(&labelAddress, tokens[0], offset);
        } else {
            // It is an instruction
            char* mnemonic = tokens[0];
            struct Entry* entry = find(&instructionCode, mnemonic);
            if (entry == NULL) {
                assert(false);
            }
            
            if (entry->entryType != INSTRUCTION_INFO) {
                assert(false);
            }

            
            struct InstructionInfo* instructionInfo = &entry->rawEntry;
            */

            if (token->instructionInfo->instructionType == DATAPROCESSING) {
                assembleDataProcessingInstruction(fpOutput, token);
            } else if (token->instructionInfo->instructionType == MULTIPLY) {
                assembleMultiplyInstruction(fpOutput, token);
            } else if (token->instructionInfo->instructionType == SINGLEDATATRANSFER) {
                assembleSingleDataInstruction(fpOutput, token);
            } else if (token->instructionInfo->instructionType == BRANCH) {
                assembleBranchInstruction(fpOutput, token);
            } else if (token->instructionInfo->instructionType == SPECIAL) {
                assert(false);
            }
        offset += 4;
    }

    fclose(fpSource);
    fclose(fpOutput);
    return 0;
}

