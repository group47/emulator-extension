//
// Created by ryro on 2018/5/26.
//

#include "stdio.h"
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "../shared/branch_instruction.h"
#include "symbol_table.h"
#include "tokenizer.h"
#include "list.h"
#include "assemble.h"


const uint32_t MASK20 = 0b00000000000100000000000000000000;

//todo : determine whether the value is representable
uint16_t getOperand2Immediate(uint32_t operand2Val) {
    uint32_t mask = 0x00000001;
    uint32_t tmpOperand2Val = operand2Val;
    while ((tmpOperand2Val & mask) == 0 && tmpOperand2Val != 0) {
        if (((tmpOperand2Val >> 1) << 1) != tmpOperand2Val) {
            // operand2Val is not representable
            // cannot preserve original bit field by doing even rotation
            assert(false);
        }
        tmpOperand2Val >>= 2;
    }
    if ((tmpOperand2Val & 0x000000ff) != tmpOperand2Val) {
        // operand2Val is not representable
        // original bit field cannot fit in 8-bit memory
        assert(false);
    }
    //return (uint8_t) (tmpOperand2Val == 0? operand2Val : tmpOperand2Val);
    return 0x0fff & (uint16_t)operand2Val;
}

//todo: handle case where opereand2 is a register
uint16_t getOperand2ShiftRegister(uint32_t operand2Val) {
    return operand2Val;
}


void assembleDataProcessingInstruction(FILE* fpOutput, struct Token* token) {
    uint32_t binary = 0;
    // set cond code
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

    // set Rn
    binary |= ((uint8_t)token->Rn) << 16;
    // set Rd
    binary |= ((uint8_t)token->Rd) << 12;
    // set Operand2
    binary |= token->operand2;

    binary_file_writer32(fpOutput, binary);
}

void assembleMultiplyInstruction(FILE* fpOutput, struct Token* token) {
    uint32_t binary = 0;
    // set cond code
    binary |= ((uint32_t)token->instructionInfo->condCode) << 28;

    // set A bit
    if (strcmp((char*)token->instructionInfo->mnemonics, "mla") == 0) {
        binary |= (0x1) << 21;
    }

    // set S bit -> S bit is always zero

    // set Rd
    binary |= ((uint8_t)token->Rd) << 16;
    // set Rn
    binary |= ((uint8_t)token->Rn) << 12;
    // set Rs
    binary |= ((uint8_t)token->Rs) << 8;
    // set special 1001 bit
    binary |= (0x9 << 4);
    // set Rm
    binary |= ((uint8_t)token->Rm);

    binary_file_writer32(fpOutput, binary);
}

void assembleSingleDataInstruction(FILE* fpOutput, struct Token* token) {
    uint32_t binary = 0;
    // set cond code
    binary |= ((uint32_t)token->instructionInfo->condCode) << 28;

    // set special 01 bit
    binary |= (0x1) << 26;
    // set P bit
    if (token->isPreIndexing) {
        binary |= (0x1) << 24;
    }
    // set U bit

    // set L bit
    if (strcmp(token->instructionInfo->mnemonics, "ldr") == 0) {
        binary |= (0x1) << 20;
    }
    // set Rn
    binary |= token->Rn << 16;
    // set Rd
    binary |= token->Rd << 12;
    // set Offset
    binary |= 0x0fff & token->offset;

    binary_file_writer32(fpOutput, binary);
}

void assembleBranchInstruction(FILE* fpOutput, struct Token* token) {
    struct BranchInstruction binary;
    binary.offset =token->offset;
    binary.cond =  token->instructionInfo->condCode;
    binary.filler1 = 0b0;
    binary.filler2 = 0b101;
    binary_file_writer32(fpOutput,*(uint32_t*)&binary);
}

//data processing syntax1 :<opcode> Rd, Rn, <Operand2>
struct Token* tokenizeDataProcessing1(char** tokens, struct InstructionInfo* instructionInfo) {
    //assert(sizeof(tokens)/sizeof(tokens[0]) >= 4);

    char dummy[500][500];
    struct Token* token = initializeToken();
    token->instructionInfo = instructionInfo;
    token->Rd = strtol(tokens[1]+1, dummy, 10);
    token->Rn = strtol(tokens[2]+1, dummy, 10);
    if (tokens[3][0] == '#') {
        token->operand2IsImmediate = true;
        if (tokens[3][1] == '0') {
            // hex representation
            token->operand2 = getOperand2Immediate(strtol(tokens[3]+1, dummy, 16));
        } else {
            // 10 representation
            token->operand2 = getOperand2Immediate(strtol(tokens[3] + 1, dummy, 10));
        }
    } else {
        token->operand2IsImmediate = false;
        token->operand2 = getOperand2ShiftRegister(strtol(tokens[3]+1, dummy, 10));
    }

   return token;
}

//data processing syntax 2 : mov Rd, <Operand2>
struct Token* tokenizeDataProcessing2(char** tokens, struct InstructionInfo* instructionInfo) {
    //assert(sizeof(tokens)/sizeof(tokens[0]) >= 3);

    char dummy[500];
    struct Token* token = initializeToken();
    token->instructionInfo = instructionInfo;
    token->Rd = (uint8_t)strtol(tokens[1]+1, dummy, 10);
    // Handling expression case only
    if (tokens[2][0] == '#') {
        token->operand2IsImmediate = true;
        if (tokens[2][1] == '0') {
            token->operand2 = getOperand2Immediate(strtol(tokens[2] + 1, dummy, 16));
        } else {
            token->operand2 = getOperand2Immediate(strtol(tokens[2] + 1, dummy, 10));
        }
    } else {
        token->operand2IsImmediate = false;
        //printf("doing wrong stuff");
        token->operand2 = getOperand2ShiftRegister(strtol(tokens[2]+1, dummy, 10));
    }
    return token;
}

//data processing syntax 3: <opcode> Rn, <Operand2>
struct Token* tokenizeDataProcessing3(char** tokens, struct InstructionInfo* instructionInfo) {
    //assert(sizeof(tokens)/sizeof(tokens[0]) >= 3);

    char dummy[500];
    struct Token* token = initializeToken();
    token->instructionInfo = instructionInfo;
    token->Rn = (uint8_t)strtol(tokens[1]+1, dummy, 10);

    if (tokens[2][0] == '#') {
        token->operand2IsImmediate = true;
        token->operand2 = getOperand2Immediate(strtol(tokens[2]+1, dummy, 10));
    } else {
        token->operand2IsImmediate = false;
        token->operand2 = getOperand2ShiftRegister(strtol(tokens[2]+1, dummy, 10));
    }
    return token;
}

// multiply syntax 1 : mul Rd, Rm, Rs
struct Token* tokenizeMultiply1(char** tokens, struct InstructionInfo* instructionInfo) {
    char dummy[500];
    struct Token* token = initializeToken();
    token->instructionInfo = instructionInfo;
    token->Rd = (uint8_t)strtol(tokens[1]+1, dummy, 10);
    token->Rm = (uint8_t)strtol(tokens[2]+1, dummy, 10);
    token->Rs = (uint8_t)strtol(tokens[3]+1, dummy, 10);
    return token;
}

// multiply syntax 2 : mla Rd, Rm, Rs, Rn
struct Token* tokenizeMultiply2(char** tokens, struct InstructionInfo* instructionInfo) {
    char dummy[500];
    struct Token* token = initializeToken();
    token->instructionInfo = instructionInfo;
    token->Rd = (uint8_t)strtol(tokens[1]+1, dummy, 10);
    token->Rm = (uint8_t)strtol(tokens[2]+1, dummy, 10);
    token->Rs = (uint8_t)strtol(tokens[3]+1, dummy, 10);
    token->Rn = (uint8_t)strtol(tokens[4]+1, dummy, 10);
    return token;
}

// single data transfer syntax 1 : <ldr/str> Rd, <address>
struct Token* tokenizeSingleDataTransfer1(char** tokens, struct InstructionInfo* instructionInfo) {
    char dummy[500];
    uint32_t offset = 0;
    bool isPreIndexAddress = false;
    uint8_t Rn = 0;

    if (tokens[2] == NULL) {
        offset = 0;
    } else if (tokens[2][0] == '=') {
        offset = (uint32_t) strtol(tokens[2] + 1, dummy, 16);
        // I don't see any test cases involving offset of base ten
    } else if (tokens[2][0] == '[') {
        Rn = (uint8_t) strtol(tokens[2] + 1, dummy, 10);
        if (tokens[3] == NULL) {
            isPreIndexAddress = true;
            offset = 0;
        } else if (tokens[3][0] == '#') {
            if (tokens[3][strlen(tokens[3])-2] == ']') {
                isPreIndexAddress = true;
            } else {
                isPreIndexAddress = false;
            }

            //todo: duplication of parsing a base10 constant and a base16 constant
            if (tokens[3][1] == '0') {
                offset = (uint32_t)strtol(tokens[3] + 1, dummy, 16);
            } else {
                offset = (uint32_t)strtol(tokens[3] + 1, dummy, 10);
            }
        }

    } else {
        assert(false);
    }

    if (offset < 0x00ff && strcmp(instructionInfo->mnemonics, "ldr") == 0) {
        return tokenizeDataProcessing2(tokens, &find(instructionInfo->symbolTable, "mov")->rawEntry.instructionInfo);
    }

    struct Token* token = initializeToken();

    token->instructionInfo = instructionInfo;
    token->Rd = (uint8_t)strtol(tokens[1]+1, dummy, 10);
    token->Rn = Rn;
    token->offset = offset;
    token ->isPreIndexing = isPreIndexAddress;

    return token;
}

// branch syntax 1 : b <cond> <expression>
struct Token* tokenizeBranch1(char** tokens, struct InstructionInfo* instructionInfo) {
    assert(instructionInfo->instructionType == BRANCH);
    struct Token* token = initializeToken();
    token->instructionInfo = instructionInfo;
    // todo: figure out how to combine labelling process with tokenization
    char* label= tokens[1];
    //remove newline:
    label[strlen(label) - 1] = '\0';
    struct Entry* entry = find(instructionInfo->labelAddress,label);
    if(entry == NULL){
        //must be in first pass, and this value is unused
        return token;
    }
    assert(entry->entryType ==  LABEL);
    const uint32_t  target_address = 4*entry->rawEntry.label.address;
    const int32_t offset = (target_address - 4*instructionInfo->address - 8)/4;
    token->offset= offset;
    return token;
}

struct Token* tokenizeSpecial1(char** tokens, struct InstructionInfo* instructionInfo) {
    return NULL;
}


struct SymbolTable* initializeInstructionCodeTable() {
    struct SymbolTable* instructionCodeTable = malloc(sizeof(struct SymbolTable));
    instructionCodeTable->size = 0;
    addInstruction(instructionCodeTable, DATA_PROCESSING, "add", al, add, 3, &tokenizeDataProcessing1);
    addInstruction(instructionCodeTable, DATA_PROCESSING, "sub", al, sub, 3, &tokenizeDataProcessing1);
    addInstruction(instructionCodeTable, DATA_PROCESSING, "rsb", al, rsb, 3, &tokenizeDataProcessing1);
    addInstruction(instructionCodeTable, DATA_PROCESSING, "and", al, and, 3, &tokenizeDataProcessing1);
    addInstruction(instructionCodeTable, DATA_PROCESSING, "eor", al, eor, 3, &tokenizeDataProcessing1);
    addInstruction(instructionCodeTable, DATA_PROCESSING, "orr", al, orr, 3, &tokenizeDataProcessing1);
    addInstruction(instructionCodeTable, DATA_PROCESSING, "mov", al, mov, 2, &tokenizeDataProcessing2);
    addInstruction(instructionCodeTable, DATA_PROCESSING, "tst", al, tst, 2, &tokenizeDataProcessing3);
    addInstruction(instructionCodeTable, DATA_PROCESSING, "teq", al, teq, 2, &tokenizeDataProcessing3);
    addInstruction(instructionCodeTable, DATA_PROCESSING, "cmp", al, cmp, 2, &tokenizeDataProcessing3);
    addInstruction(instructionCodeTable, MULTIPLY, "mul", al, 0, 3, &tokenizeMultiply1);
    addInstruction(instructionCodeTable, MULTIPLY, "mla", al, 0, 4, &tokenizeMultiply2);
    addInstruction(instructionCodeTable, SINGLE_DATA_TRANSFER, "ldr", 0, 0, 2, &tokenizeSingleDataTransfer1);
    addInstruction(instructionCodeTable, SINGLE_DATA_TRANSFER, "str", 0, 0, 2, &tokenizeSingleDataTransfer1);
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
bool secondToLastCharIs(const char *target, char c) {
  return target[strlen(target) - 2] == c;
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
    memset(&labelAddress,0, sizeof(struct SymbolTable));
    struct ForwardReferenceList* forwardReferenceLabels;

    uint16_t offset = 0;
    uint16_t current_address = 0;
    // build labelAddress table
    while(getline(&instruction, &instructionLength, fpSource)!= -1){
        struct Token* token = tokenizer(instruction, instructionCode,&labelAddress,current_address);
        if (token == NULL) {
            if(secondToLastCharIs(instruction, ':')){
                char colonRemoved[100];
                int i = 0;
                while (i < strlen(instruction) - 2) {
                    colonRemoved[i] = instruction[i];
                    ++i;
                }
                colonRemoved[i] = '\0';
                addLabel(&labelAddress,colonRemoved,current_address);
            } else{
                assert(false);
            }
        } else{
            current_address++;
        }
    }
    fclose(fpSource);

    FILE* fpOutputHead = fpOutput;
    FILE* fpSource2 = fopen(sourceFileName, "r");
    current_address = 0;
    while (getline(&instruction, &instructionLength, fpSource2)!= -1) {
        //assert(instructionLength == INSTRUCTION_LENGTH);

        struct Token* token = tokenizer(instruction, instructionCode,&labelAddress,current_address);
        if (token == NULL) {
            break;
        }
        current_address++;
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

            if (token->instructionInfo->instructionType == DATA_PROCESSING) {
                assembleDataProcessingInstruction(fpOutput, token);
            } else if (token->instructionInfo->instructionType == MULTIPLY) {
                assembleMultiplyInstruction(fpOutput, token);
            } else if (token->instructionInfo->instructionType == SINGLE_DATA_TRANSFER) {
                assembleSingleDataInstruction(fpOutput, token);
            } else if (token->instructionInfo->instructionType == BRANCH) {
                assembleBranchInstruction(fpOutput, token);
            } else if (token->instructionInfo->instructionType == SPECIAL) {
                assert(false);
            }
        offset += 4;
    }

    fclose(fpSource2);
    fclose(fpOutput);
    return 0;
}

