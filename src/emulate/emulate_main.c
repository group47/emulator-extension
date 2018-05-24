
#include <stdint-gcc.h>
#include <assert.h>
#include <stdio.h>
#include "emulate_main.h"
#include "instructions.h"


void emulateImpl(struct EmulatorState *state,
                 struct Instruction instructions[],
                 unsigned int instructions_l);

int execute_instruction_data_processing(struct EmulatorState* state, struct DataProcessingInstruction instruction) ;
int execute_instruction_multiply(struct EmulatorState* state, struct MultiplyInstruction instruction);
int execute_instruction_single_data_transfer(struct EmulatorState* state, struct SingleDataTransferInstruction instruction);
void emulate(struct EmulatorState *state,
             int32_t *instructions,
             unsigned int instructions_l) {
  struct Instruction instructionsWithType[instructions_l];
  for (int i = 0; i < instructions_l; ++i) {
    const struct BranchInstruction branchInstruction =
        *((const struct BranchInstruction *) (&(instructions[i])));
    const struct MultiplyInstruction multiplyInstruction =
        *((const struct MultiplyInstruction *) (&(instructions[i])));
    const struct SingleDataTransferInstruction singleDataTransferInstruction =
        *((const struct SingleDataTransferInstruction *) (&(instructions[i])));
    const struct DataProcessingInstruction dataProcessingInstruction =
        *((const struct DataProcessingInstruction *) (&(instructions[i])));
    //todo magic constants
    if (branchInstruction.filler1 == 0b0
        && branchInstruction.filler2 == 0b101) {
      instructionsWithType[i].branchInstruction = branchInstruction;
      instructionsWithType[i].type = BRANCH_INSTRUCTION;
    } else if (singleDataTransferInstruction.filler == 0b01) {
      instructionsWithType[i].singleDataTransferInstruction =
          singleDataTransferInstruction;
      instructionsWithType[i].type = SINGLE_DATA_TRANSFER;
    } else if (multiplyInstruction.filler == 0b000000
        && multiplyInstruction.filler2 == 0b1001) {
      instructionsWithType[i].multiplyInstruction = multiplyInstruction;
      instructionsWithType[i].type = MULTIPLY;
    } else if (dataProcessingInstruction.filler == 0b000) {
      instructionsWithType[i].dataProcessingInstruction =
          dataProcessingInstruction;
      instructionsWithType[i].type = DATA_PROCESSING;
    } else {
      assert(false);
    }
  }
  emulateImpl(state, instructionsWithType, instructions_l);
}

void emulateImpl(struct EmulatorState *state,
                 struct Instruction instructions[],
                 unsigned int instructions_l) {
#ifdef INSTRUCTION_TYPES_TEST

  const char *instructionTypeNames[] =
      {"DATA_PROCESSING", "MULTIPLY", "SINGLE_DATA_TRANSFER",
       "BRANCH_INSTRUCTION"};
  for (int i = 0; i < instructions_l; i++) {
    printf("Instruction #%d, Instruction type:%s\n",
           i,
           instructionTypeNames[instructions[i].type]);
  }

#endif
  state->PC = 0;

  while (true){
    (state->PC)++;

  }
}

int execute_instruction(struct EmulatorState* state, struct Instruction instruction){
  switch (instruction.type){

    case DATA_PROCESSING:
      return execute_instruction_data_processing(state,instruction.dataProcessingInstruction);
    case MULTIPLY:
      return execute_instruction_multiply(state,instruction.multiplyInstruction);
    case SINGLE_DATA_TRANSFER:
      return execute_instruction_single_data_transfer(state,instruction.singleDataTransferInstruction);
    case BRANCH_INSTRUCTION:break;
  }
}

int execute_instruction_data_processing(struct EmulatorState* state, struct DataProcessingInstruction instruction) {
  //todo
}

int execute_instruction_multiply(struct EmulatorState* state, struct MultiplyInstruction instruction){
  //todo
}

int execute_instruction_single_data_transfer(struct EmulatorState* state, struct SingleDataTransferInstruction instruction){
  //todo
}

int execute_instruction_branch(struct EmulatorState* state, struct BranchInstruction instruction){
  //todo
}
