
#include <stdint-gcc.h>
#include <assert.h>
#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include <stdint-gcc.h>
#include <stdlib.h>
#include <zconf.h>
#include <fcntl.h>
#include <string.h>
#include "emulate_main.h"
#include "instructions.h"


void emulateImpl(struct EmulatorState *state,
                 struct Instruction instructions[],
                 unsigned int instructions_l);

int execute_instruction_data_processing(struct EmulatorState* state, struct DataProcessingInstruction instruction) ;
int execute_instruction_multiply(struct EmulatorState* state, struct MultiplyInstruction instruction);
int execute_instruction_single_data_transfer(struct EmulatorState* state, struct SingleDataTransferInstruction instruction);
int execute_instruction(struct EmulatorState* state, struct Instruction instruction);
void print_registers(struct EmulatorState* state);
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
  execute_instruction(state,instructions[0]);
  print_registers(state);
//  while (true){
//
//    (state->PC)++;
//
//  }
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

bool should_execute(struct  EmulatorState* state,uint8_t cond){
  //todo switch
  const bool NequalsV =
      (bool) ((state->CPSR) & CPSR_N == (state->CPSR) & CPSR_V);
  const bool Zset = (bool) ((state->CPSR) & CPSR_Z);
  if(cond == eqCond){
    //Z set
    return Zset;
  }else if(cond == neCond){
    //Z clear
    return !Zset;
  }else if(cond == geCond){
    return NequalsV;
  }else if(cond == ltCond){
    return (bool) ((state->CPSR) & CPSR_N != (state->CPSR) & CPSR_V);
  }else if(cond ==gtCond){
    return (!Zset) && NequalsV;
  }else if(cond == leCond){
    return Zset || (!NequalsV);
  }else if(cond == alCond){
    return true;
  } else{
    assert(false);
  }
}

int execute_instruction_data_processing(struct EmulatorState* state, struct DataProcessingInstruction instruction) {
  //todo duplication
  if(!should_execute(state,instruction.cond)){
    return 0;
  }
  const int32_t rnVal = (state->registers)[instruction.Rn];
  int32_t operand2Val;
  if(instruction.immediateOperand){
    operand2Val = instruction.secondOperand;
  } else{
    operand2Val = (state->registers)[(instruction.secondOperand) << 8];//no way this works todo
  }
  switch (instruction.opcode){
    case and:
      (state->registers)[instruction.Rd] = (rnVal & operand2Val);//notsure if this should be bitwise or not. the spec isn't clear todo
      return 1;
    case eor:
      (state->registers)[instruction.Rd] = (rnVal ^ operand2Val);
      return 1;
    case sub:
      (state->registers)[instruction.Rd] = (rnVal - operand2Val);
      return 1;
    case rsb:
      (state->registers)[instruction.Rd] = (operand2Val - rnVal);
      return 1;
    case add:
      (state->registers)[instruction.Rd] = (operand2Val + rnVal);
      return 1;
    case tst:
      //todo
      break;
    case teq:
      //todo
      break;
    case cmp:
      //todo
      break;
    case orr:
      (state->registers)[instruction.Rd] = (rnVal | operand2Val);
      return 1;
    case mov:
      //todo
      break;
  }
  //todo set cpsr
}

int execute_instruction_multiply(struct EmulatorState* state, struct MultiplyInstruction instruction){
  if(!should_execute(state,instruction.cond)){
    return 0;
  }
}

int execute_instruction_single_data_transfer(struct EmulatorState* state, struct SingleDataTransferInstruction instruction){
  if(!should_execute(state,instruction.cond)){
    return 0;
  }
}

int execute_instruction_branch(struct EmulatorState* state, struct BranchInstruction instruction){
  if(!should_execute(state,instruction.cond)){
    return 0;
  }

}


void print_registers(struct EmulatorState* state){
  printf("Registers:\n");
  for (int i = 0; i < 13; ++i) {
    printf("$%d:%d (%x)\n",i,state->registers[i],state->registers[i]);
  }
  printf("PC  : %d (%x)\n");
  printf("CPSR: %d (%x)\n");
  //todo non-zero memory.
}

#ifdef USE_EMULATE_MAIN
int main(int argc, char **argv) {
  if(argc != 2){
    fprintf(stderr,
            "the end of the world has come, or you entered the wrong number of arguments");
    return -100000;
  }
  printf("%s\n", argv[1]);
  const char *filename = argv[1];
  int fileDescriptor = open(filename, O_RDONLY);
  if (fileDescriptor == -1) {
    fprintf(stderr,
            "the end of the world has come, or you entered the wrong filename");
    return -100000;
  }

  int32_t *rawData = (int32_t *) malloc(sizeof(int32_t[MAX_INSTRUCTION_INPUT_FILE_SIZE]));
  size_t amountRead = sizeof(byte) * read(fileDescriptor,rawData,sizeof(int32_t[MAX_INSTRUCTION_INPUT_FILE_SIZE]));
  assert(amountRead % sizeof(int32_t) == 0);
  struct EmulatorState* emulatorState = malloc(sizeof(struct EmulatorState));
  memset(rawData,0, sizeof(struct EmulatorState));
  emulate(emulatorState,
          rawData,
          (unsigned int) (amountRead / sizeof(int32_t)));
  close(fileDescriptor);
  free(emulatorState);
  free(rawData);
}

#endif