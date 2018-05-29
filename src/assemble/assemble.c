//
// Created by ryro on 2018/5/26.
//

#include "stdio.h"
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <x86intrin.h>
#include "../shared/branch_instruction.h"
#include "symbol_table.h"
#include "tokenizer.h"
#include "list.h"
#include "assemble.h"
#include "extra_data.h"


const uint32_t MASK20 = 0b00000000000100000000000000000000;


//todo : clean up
uint16_t getOperand2Immediate(uint32_t operand2Val) {
    /*
    if (operand2Val < 0xff) {
        return (uint16_t)operand2Val;
    }
    uint32_t mask = 0x00000001;
    uint32_t tmpOperand2Val = operand2Val;
    while ((tmpOperand2Val & mask) == 0 && tmpOperand2Val != 0) {
        tmpOperand2Val >>= 2;
    }

    if ((tmpOperand2Val & 0x000000ff) != tmpOperand2Val) {
        // operand2Val is not representable
        // original bit field cannot fit in 8-bit memory
        assert(false);
    }

    int rotateCount = 0;
    uint32_t ttmpOperand2Val = tmpOperand2Val;

    while (ttmpOperand2Val != operand2Val && ttmpOperand2Val != 0) {
        ttmpOperand2Val = __rord(ttmpOperand2Val, 2);
        rotateCount++;
    }

    uint16_t result = (uint8_t) (tmpOperand2Val == 0? operand2Val : tmpOperand2Val);
    result |= (0x0f & rotateCount) << 8;
    return result;
    //return (0x0fff & (uint16_t)operand2Val);
     */


    bool found = false;
    uint32_t result = operand2Val;
    uint32_t count;
    for (count = 0; count < 16; ++count) {
        if ((0x000000ff & result) == result) {
            found = true;
            break;
        }
        result = __rold(result, 2);
    }
    //assert(found);
    result |= count << 8;
    return (uint16_t) result;


}

//todo: handle case where opereand2 is a register
uint16_t getOperand2ShiftRegister(uint32_t operand2Val) {
    return operand2Val;
}

uint32_t getShiftedRegister(char* shiftname, char* registerOrExpression, uint8_t Rm) {

    enum ShiftType shiftType = lsl;
    uint16_t shiftedRegister = 0;
    if (shiftname != NULL) {
        char dummy[500][500];
        if (strcmp(shiftname, "lsl") == 0) {
            shiftType = lsl;
        } else if (strcmp(shiftname, "lsr") == 0) {
            shiftType = lsr;
        } else if (strcmp(shiftname, "asr") == 0) {
            shiftType = asr;
        } else if (strcmp(shiftname, "ror") == 0) {
            shiftType = ror;
        } else {
            assert(false);
        }

        if (registerOrExpression != NULL) {
            int base = 10;
            if (registerOrExpression[1] == '0') {
                base = 16;
            }
            if (registerOrExpression[0] == 'r') {
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->filler = 0;
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->shift_type = shiftType;
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->Rm = Rm;
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->shift_by_register = true;
                ((struct ImmediateFalseShiftByRegisterTrue *) &shiftedRegister)->Rs =
                        (uint8_t) strtol(registerOrExpression + 1, dummy, 10);
            } else if (registerOrExpression[0] == '#') {
                ((struct ImmediateFalseShiftByRegisterFalse *) &shiftedRegister)->shift_type = shiftType;
                ((struct ImmediateFalseShiftByRegisterFalse *) &shiftedRegister)->Rm = Rm;
                ((struct ImmediateFalseShiftByRegisterFalse *) &shiftedRegister)->shift_by_register = false;
                ((struct ImmediateFalseShiftByRegisterFalse *) &shiftedRegister)->integer =
                        (uint8_t) strtol(registerOrExpression + 1, dummy, base);
            } else {
                assert(false);
            }
        }
    } else {
        shiftedRegister = Rm;
    }

    return shiftedRegister;
}


void assembleDataProcessingInstruction(FILE* fpOutput, struct Token* token) {
    struct DataProcessingInstruction binary;
    binary.cond = token->instructionInfo->condCode;
    binary.filler = 0b00;
    binary.opcode = token->instructionInfo->opCode;
    binary.immediateOperand = token->operand2IsImmediate;
    binary.setConditionCodes =
            token->instructionInfo->opCode == tst
            || token->instructionInfo->opCode == teq
            || token->instructionInfo->opCode == cmp;
    binary.Rn = token->Rn;
    binary.Rd = token->Rd;
    binary.secondOperand = (uint16_t) token->operand2;
    binary_file_writer32(fpOutput, *(uint32_t*)&binary);
}

void assembleMultiplyInstruction(FILE* fpOutput, struct Token* token) {
    struct MultiplyInstruction binary;
    binary.cond = token->instructionInfo->condCode;
    binary.filler = 0b000000;
    binary.accumulate =
      strcmp((char*)token->instructionInfo->mnemonics, "mla") == 0;
    binary.destinationRegister = token->Rd;
    binary.Rn = token->Rn;
    binary.Rs = token->Rs;
    binary.filler2 = 0b1001;
    binary.Rm = token->Rm;
    binary.setConditionCodes = 0b0;

    binary_file_writer32(fpOutput, *(uint32_t*)&binary);
}

void assembleSingleDataInstruction(FILE* fpOutput, struct Token* token) {
    struct SingleDataTransferInstruction binary;
    binary.cond = token->instructionInfo->condCode;
    binary.filler = 0b01;
    binary.filler2 = 0b00;
    binary.immediateOffset = token->offsetIsImmediate;
    binary.prePostIndexingBit = token->isPreIndexing;
    binary.upBit = !token->offsetIsNegative;
    binary.loadStore = strcmp(token->instructionInfo->mnemonics, "ldr") == 0;
    binary.Rn = token->Rn;
    binary.Rd = token->Rd;
    if(token->use_extra_data){
        assert(token->offset > 0x00ff );
        assert(!binary.immediateOffset);
        binary.Rn = 0b1111;//the program counter
        uint32_t  extra_data_address = 4*add_extra_data(token->offset);
        binary.offset = (extra_data_address - 4*token->instructionInfo->address - 8);//todo check
    } else{
        binary.offset = 0x0fff & token->offset;
    }

    binary_file_writer32(fpOutput, *(uint32_t*)&binary);
}

void assembleBranchInstruction(FILE* fpOutput, struct Token* token) {
    struct BranchInstruction binary;
    binary.offset = token->offset;
    binary.cond = token->instructionInfo->condCode;
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
        uint8_t Rm = (uint8_t)strtol(tokens[3]+1, dummy, 10);
        token->operand2 = (uint16_t) getShiftedRegister(tokens[4], tokens[5], Rm);
        //token->operand2 = getOperand2Immediate(strtol(tokens[3]+1, dummy, 10));
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
    // = is for ldr instruction
    if (tokens[2][0] == '#' || tokens[2][0] == '=') {
        token->operand2IsImmediate = true;
        if (tokens[2][1] == '0') {
            token->operand2 = getOperand2Immediate(strtol(tokens[2] + 1, dummy, 16));
        } else {
            token->operand2 = getOperand2Immediate(strtol(tokens[2] + 1, dummy, 10));
        }
    } else {
        token->operand2IsImmediate = false;
        uint8_t Rm = (uint8_t) strtol(tokens[2]+1, dummy, 10);
        token->operand2 = (uint16_t) getShiftedRegister(tokens[3], tokens[4], Rm);
        //token->operand2 = Rm;
        //token->operand2 = getOperand2Immediate(strtol(tokens[2]+1, dummy, 10));
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
        if (tokens[2][1] == '0') {
            token->operand2 = getOperand2Immediate(strtol(tokens[2] + 1, dummy, 16));
        } else {
            token->operand2 = getOperand2Immediate(strtol(tokens[2] + 1, dummy, 10));
        }
        //token->operand2 = getOperand2Immediate(strtol(tokens[2]+1, dummy, 10));
    } else {
        token->operand2IsImmediate = false;
        uint8_t Rm = (uint8_t) strtol(tokens[2]+1, dummy, 10);
        token->operand2 = (uint16_t) getShiftedRegister(tokens[3], tokens[4], Rm);
        //token->operand2 = getOperand2ShiftRegister(strtol(tokens[2]+1, dummy, 10));
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
    long offset = 0;
    bool isPreIndexAddress = false;
    bool offsetIsNegative = false;
    bool offsetIsImmediate = false;
    uint8_t Rn = 0;

    if (tokens[2][0] == '=') {

        isPreIndexAddress = true;
        offsetIsImmediate = false;
        offset = (uint32_t) strtol(tokens[2] + 1, dummy, 16);

    } else if (tokens[2][0] == '[') {
        Rn = (uint8_t) strtol(tokens[2] + 2, dummy, 10);

        if (tokens[3] == NULL) {
            isPreIndexAddress = true;
            offset = 0;
            offsetIsImmediate = false;
        } else if (tokens[3][0] == '#') {
            offsetIsImmediate = false;
            isPreIndexAddress = !(tokens[2][strlen(tokens[2])-1] == ']' || tokens[2][strlen(tokens[2])-2] == ']');
            offsetIsNegative = tokens[3][1] == '-';

            char* hexPointer = strstr(tokens[3]+1, "0x");
            if (hexPointer) {
                offset = (uint16_t) strtol(hexPointer, dummy, 16);
            } else {
                offset = (uint16_t) strtol(tokens[3] + 1, dummy, 10);
            }

        } else {
            offsetIsImmediate = true;
            isPreIndexAddress = !(tokens[2][strlen(tokens[2])-1] == ']' || tokens[2][strlen(tokens[2])-2] == ']');
           //todo: duplication
            uint8_t Rm = 0;
            if (tokens[3][0] == '-') {
                offsetIsNegative = true;
                Rm = (uint8_t)strtol(tokens[3]+2, dummy, 10);
            } else {
                offsetIsNegative = false;
                Rm = (uint8_t)strtol(tokens[3]+1, dummy, 10);
            }
            offset = (uint16_t) getShiftedRegister(tokens[4], tokens[5], Rm);
        }

    } else {
        assert(false);
    }

    struct Token* token = initializeToken();
    if (tokens[2][0] == '=') {
        if (offset <= 0x00ff && strcmp(instructionInfo->mnemonics, "ldr") == 0) {
            return tokenizeDataProcessing2(tokens,
                                           &find(instructionInfo->symbolTable,
                                                 "mov")->rawEntry.instructionInfo);
        } else {
            token->use_extra_data = true;
        }
    }


    token->instructionInfo = instructionInfo;
    token->Rd = (uint8_t)strtol(tokens[1]+1, dummy, 10);
    token->Rn = Rn;
    token->offset = offset;
    token ->isPreIndexing = isPreIndexAddress;
    token->offsetIsNegative = offsetIsNegative;
    token->offsetIsImmediate = offsetIsImmediate;

    return token;
}

// branch syntax 1 : b <cond> <expression>
struct Token* tokenizeBranch1(char** tokens, struct InstructionInfo* instructionInfo) {
    assert(instructionInfo->instructionType == BRANCH_INSTRUCTION);
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

// for lsl
struct Token* tokenizeSpecial1(char** tokens, struct InstructionInfo* instructionInfo) {
    char** tokensRestructure = malloc(sizeof(char*)*20);
    for (int i = 0; i < 5; i++) {
        tokensRestructure[i] = malloc(sizeof(char)*10);
    }
    memcpy(tokensRestructure[0], "mov", strlen("mov"));
    tokensRestructure[1] = tokens[1];
    tokensRestructure[2] = tokens[1];
    memcpy(tokensRestructure[3], "lsl", strlen("lsl"));
    tokensRestructure[4] = tokens[2];
    return tokenizeDataProcessing2(tokensRestructure, &(find(instructionInfo->symbolTable, "mov")->rawEntry.instructionInfo));
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
    addInstruction(instructionCodeTable, SINGLE_DATA_TRANSFER, "ldr", al, 0, 2, &tokenizeSingleDataTransfer1);
    addInstruction(instructionCodeTable, SINGLE_DATA_TRANSFER, "str", al, 0, 2, &tokenizeSingleDataTransfer1);
    addInstruction(instructionCodeTable, BRANCH_INSTRUCTION, "beq", eq, 0, 1, &tokenizeBranch1);
    addInstruction(instructionCodeTable, BRANCH_INSTRUCTION, "bne", ne, 0, 1, &tokenizeBranch1);
    addInstruction(instructionCodeTable, BRANCH_INSTRUCTION, "bge", ge, 0, 1, &tokenizeBranch1);
    addInstruction(instructionCodeTable, BRANCH_INSTRUCTION,"blt", lt, 0, 1, &tokenizeBranch1);
    addInstruction(instructionCodeTable, BRANCH_INSTRUCTION, "ble", le, 0, 1, &tokenizeBranch1);
    addInstruction(instructionCodeTable, BRANCH_INSTRUCTION,"b", al, 0, 1, &tokenizeBranch1);
    addInstruction(instructionCodeTable, DATA_PROCESSING,"lsl", al, 0, 2, &tokenizeSpecial1);
    addInstruction(instructionCodeTable, DATA_PROCESSING, "andeq", eq, 0, 3, &tokenizeDataProcessing1);
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
        struct Token* token = tokenizer(instruction, instructionCode,&labelAddress,current_address);
        if (token == NULL) {
            continue;
        }
        current_address++;

        if (token->instructionInfo->instructionType == DATA_PROCESSING) {
            assembleDataProcessingInstruction(fpOutput, token);
        } else if (token->instructionInfo->instructionType == MULTIPLY) {
            assembleMultiplyInstruction(fpOutput, token);
        } else if (token->instructionInfo->instructionType == SINGLE_DATA_TRANSFER) {
            assembleSingleDataInstruction(fpOutput, token);
        } else if (token->instructionInfo->instructionType == BRANCH_INSTRUCTION) {
            assembleBranchInstruction(fpOutput, token);
        } else if (token->instructionInfo->instructionType == SPECIAL) {
          assert(false);
        }
        offset += 4;
    }

    write_extra_data(fpOutput);

    fclose(fpSource2);
    fclose(fpOutput);
    return 0;
}

