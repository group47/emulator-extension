//
// Created by ryro on 2018/5/26.
//



#include "stdio.h"
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "symbol_table.h"
#include "tokenizer.h"
#include "list.h"
#include "binary_file_writer.h"

#define MAX_SOURCE_FILE_SIZE = 10000
#define INSTRUCTION_LENGTH = 32
/*
const uint32_t DATAPROCESSING_INSTRUCTION_SIZE = 10;
const uint32_t MULTIPLY_INSTRUCTION_SIZE = 2;
const uint32_t SINGLE_DATA_TRANSFER_INSTRUCTION_SIZE = 2;
const uint32_t BRANCH_INSTRUCTION_SIZE = 7;
const uint32_t SPECIAL_INSTRUCTION_SIZE = 2;

const int DATAPROCESSING_INSTRUCTION_BASE = 0;
const int MULTIPLY_INSTRUCTION_BASE = DATAPROCESSING_INSTRUCTION_BASE + DATAPROCESSING_INSTRUCTION_SIZE;
const int SINGLE_DATA_TRANSFER_INSTRUCTION_BASE = MULTIPLY_INSTRUCTION_BASE + MULTIPLY_INSTRUCTION_SIZE;
const int BRNACH_INSTRUCTION_BASE = SINGLE_DATA_TRANSFER_INSTRUCTION_BASE + SINGLE_DATA_TRANSFER_INSTRUCTION_SIZE;
const int SPECIAL_INSTRUCTION_BASE = BRNACH_INSTRUCTION_BASE + BRANCH_INSTRUCTION_SIZE;
const int MAX_BASE = SPECIAL_INSTRUCTION_BASE + SPECIAL_INSTRUCTION_SIZE;
 */

/*
char* add = "add";
char* sub = "sub";
char* rsb = "rsb";
char* and = "and";
char* eor = "eor";
char* orr = "orr";
char* mov = "mov";
char* tst = "tst";
char* teq = "teq";
char* cmp = "cmp";
char* mul = "mul";
char* mla = "mla";
char* ldr = "ldr";
char* str = "str";
char* beq = "beq";
char* bne = "bne";
char* bge = "bge";
char* blt = "blt";
char* bgt = "bgt";
char* ble = "ble";
char* b   = "b";
char* lsl = "lsl";
char* andeq = "andeq";
 */

const uint32_t MASK20 = 0b00000000000100000000000000000000;

void assembleDataProcessingInstruction(FILE* fpOutput, char** tokens, struct InstructionInfo*);
void assembleMultiplyInstruction(FILE* fpOutput, char** tokens, struct InstructionInfo*);
void assembleSingleDataInstruction(FILE* fpOutput, char** tokens, struct InstructionInfo*);
void assembleBranchInstruction(FILE* fpOutput, char** tokens, struct InstructionInfo*, struct List* list);


void assembleDataProcessingInstruction(FILE* fpOutput, char** tokens, struct InstructionInfo* entry) {
    uint32_t binaryFormat = 0;
    binaryFormat |= ((uint32_t)entry->condCode) << 28;

    // set S bit
    if (entry->opCode == tst || entry->opCode == teq || entry->opCode == cmp) {
        binaryFormat |= MASK20;
    }


}

void assembleMultiplyInstruction(FILE* fpOutput, char** tokens, struct InstructionInfo* entry) {

}

void assembleSingleDataInstruction(FILE* fpOutput, char** tokens, struct InstructionInfo* entry) {

}

void assembleBranchInstruction(FILE* fpOutput, char** tokens, struct InstructionInfo* entry, struct List* list) {

}


void initializeInstructionCodeTable(struct SymbolTable* instructionCodeTable) {
    addInstruction(instructionCodeTable, "add", DATAPROCESSING, al, add, 3);
    addInstruction(instructionCodeTable, "sub", DATAPROCESSING, al, sub, 3);
    addInstruction(instructionCodeTable, "rsb", DATAPROCESSING, al, rsb, 3);
    addInstruction(instructionCodeTable, "and", DATAPROCESSING, al, and, 3);
    addInstruction(instructionCodeTable, "eor", DATAPROCESSING, al, eor, 3);
    addInstruction(instructionCodeTable, "orr", DATAPROCESSING, al, orr, 3);
    addInstruction(instructionCodeTable, "mov", DATAPROCESSING, al, mov, 2);
    addInstruction(instructionCodeTable, "tst", DATAPROCESSING, al, tst, 2);
    addInstruction(instructionCodeTable, "teq", DATAPROCESSING, al, teq, 2);
    addInstruction(instructionCodeTable, "cmp", DATAPROCESSING, al, cmp, 2);
    addInstruction(instructionCodeTable, "mul", MULTIPLY, al, 0, 3);
    addInstruction(instructionCodeTable, "mla", MULTIPLY, al, 0, 4);
    addInstruction(instructionCodeTable, "ldr", SINGLEDATATRANSFER, 0, 0, 2);
    addInstruction(instructionCodeTable, "str", SINGLEDATATRANSFER, 0, 0, 2);
    addInstruction(instructionCodeTable, "beq", BRANCH, eq, 0, 1);
    addInstruction(instructionCodeTable, "bne", BRANCH, ne, 0, 1);
    addInstruction(instructionCodeTable, "bge", BRANCH, ge, 0, 1);
    addInstruction(instructionCodeTable, "blt", BRANCH, lt, 0, 1);
    addInstruction(instructionCodeTable, "ble", BRANCH, le, 0, 1);
    addInstruction(instructionCodeTable, "b",   BRANCH, gt, 0, 1);
    addInstruction(instructionCodeTable, "lsl", SPECIAL, al, 0, 2);
    addInstruction(instructionCodeTable, "andeq", SPECIAL, eq, 0, 3);
}

int main(int argc, char** argv) {

    if (argc != 3) {
        fprintf(stderr,
                "the end of the world has come, or you entered the wrong number of arguments");
        return -100000;
    }

    const char* sourceFileName = argv[1];
    const char* outputFileName = argv[2];

    FILE* fpSource = fopen(sourceFileName, O_RDONLY);
    FILE* fpOutput = fopen(outputFileName, O_WRONLY);

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
    struct SymbolTable labelAddress;
    

    struct List list;
    initializeInstructionCodeTable(&instructionCode);

    FILE* fpOutputHead = fpOutput;
    uint16_t offset = 0;


    while (getline(&instruction, &instructionLength, fpSource)) {
        assert(instructionLength == INSTRUCTION_LENGTH);

        char** tokens = tokenizer(instruction);
        if (strlen(tokens) == 1) {
            // It is a label
            // todo: add label to the symbol table
            writeAddress(&list, tokens[0], offset);
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

            if (instructionInfo->instructionType == DATAPROCESSING) {
                assembleDataProcessingInstruction(fpOutput, tokens, instructionInfo);
            } else if (instructionInfo->instructionType == MULTIPLY) {
                assembleMultiplyInstruction(fpOutput, tokens, instructionInfo);
            } else if (instructionInfo->instructionType == SINGLEDATATRANSFER) {
                assembleSingleDataInstruction(fpOutput, tokens, instructionInfo);
            } else if (instructionInfo->instructionType == BRANCH) {
                assembleBranchInstruction(fpOutput, tokens, instructionInfo, &list);
            } else if (instructionInfo->instructionType == SPECIAL) {
                assert(false);
            }
            
        }
        offset += 4;
    }
    return 0;
}

