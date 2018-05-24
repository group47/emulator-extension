
#include <stdint-gcc.h>
#include <assert.h>
#include <printf.h>
#include <stdio.h>
#include "emulate_main.h"
#include "util.h"
#include "instructions.h"


void emulateImpl(struct EmulatorState* state,struct Instruction instructions[],unsigned int instructions_l);

void emulate(struct EmulatorState* state, int32_t* instructions, unsigned int instructions_l){
    struct Instruction instructionsWithType[instructions_l];
    for (int i = 0; i < instructions_l; ++i) {
        const struct BranchInstruction branchInstruction = *((const struct BranchInstruction *)(&(instructions[i])));
        const struct MultiplyInstruction multiplyInstruction = *((const struct MultiplyInstruction *)(&(instructions[i])));
        const struct SingleDataTransferInstruction singleDataTransferInstruction = *((const struct SingleDataTransferInstruction *)(&(instructions[i])));
        const struct DataProcessingInstruction dataProcessingInstruction = *((const struct DataProcessingInstruction *)(&(instructions[i])));
        //todo magic constants
        if(branchInstruction.filler1 == 0b0 && branchInstruction.filler2 == 0b101){
            instructionsWithType[i].branchInstruction = branchInstruction;
            instructionsWithType[i].type = BRANCH_INSTRUCTION;
        }
        else if(singleDataTransferInstruction.filler == 0b01){
            instructionsWithType[i].singleDataTransferInstruction = singleDataTransferInstruction;
            instructionsWithType[i].type = SINGLE_DATA_TRANSFER;
        } else if(multiplyInstruction.filler == 0b000000 && multiplyInstruction.filler2 == 0b1001){
            instructionsWithType[i].multiplyInstruction = multiplyInstruction;
            instructionsWithType[i].type = MULTIPLY;
        }else if(dataProcessingInstruction.filler == 0b000){
            instructionsWithType[i].dataProcessingInstruction = dataProcessingInstruction;
            instructionsWithType[i].type = DATA_PROCESSING;
        } else{
            assert(false);
        }
    }
    emulateImpl(state,instructionsWithType,instructions_l);
}

void emulateImpl(struct EmulatorState* state,struct Instruction instructions[],unsigned int instructions_l){
    #ifdef INSTRUCTION_TYPES_TEST

    const char *instructionTypeNames[] = {"DATA_PROCESSING", "MULTIPLY", "SINGLE_DATA_TRANSFER", "BRANCH_INSTRUCTION"};
    for(int i = 0; i < instructions_l;i++){
        printf("Instruction #%d, Instruction type:%s\n",i,instructionTypeNames[instructions[i].type]);
    }

    #endif

    //todo
}