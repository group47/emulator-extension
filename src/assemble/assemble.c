//
// Created by ryro on 2018/5/26.
//

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "list.h"
#include "extra_data.h"
#include "utility.h"
#include "tokenizer.h"
#include "symbol_table.h"
#include "assemble.h"
#include "parseUtility.h"
#include "parseDataProcessing.h"
#include "parseMultiply.h"
#include "parseSingleDataTransfer.h"
#include "parseBranch.h"
#include "parseSpecial.h"


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
    struct SymbolTable instructionCode;
    initializeInstructionCodeTable(&instructionCode);
    struct SymbolTable labelAddress;
    memset(&labelAddress,0, sizeof(struct SymbolTable));

    uint16_t offset = 0;
    uint16_t current_address = 0;
    // build labelAddress table
    while(getline(&instruction, &instructionLength, fpSource)!= -1){//todo alloc
        struct Instruction token = tokenizer(instruction, &instructionCode,&labelAddress,current_address);//todo make this faster kuyg
        if (token.type == INVALID) {
            if(secondToLastCharIs(instruction, ':')){
                char colonRemoved[100];
                int i = 0;
                while (i < strlen(instruction) - 2) {
                    colonRemoved[i] = instruction[i];
                    ++i;
                }
                colonRemoved[i] = '\0';
                addLabel(&labelAddress,colonRemoved,current_address);
            }
        } else{
            current_address++;
        }
    }
    fclose(fpSource);
    set_extra_data_location(current_address);
    FILE* fpSource2 = fopen(sourceFileName, "r");
    current_address = 0;
    while (getline(&instruction, &instructionLength, fpSource2)!= -1) {
        fprintf(stderr, "%s\n", instruction);
        instruction[strlen(instruction)] = '\0';
        struct Instruction token = tokenizer(instruction, &instructionCode,&labelAddress,current_address);

        if(token.type != INVALID){
            binary_file_writer32(fpOutput,*(uint32_t*)&token.rawInstruction);
            current_address++;
        }

        offset += 4;
    }

    write_extra_data(fpOutput);

    fclose(fpSource2);
    fclose(fpOutput);
    return 0;
}

