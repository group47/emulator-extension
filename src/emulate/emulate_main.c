
#include <stdint-gcc.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <zconf.h>
#include "emulate_main.h"
#include "instructions.h"

int execute_instruction_data_processing(struct EmulatorState *,
                                        struct DataProcessingInstruction);
int execute_instruction_multiply(struct EmulatorState *,
                                 struct MultiplyInstruction);
int execute_instruction_single_data_transfer(struct EmulatorState *,
                                             struct SingleDataTransferInstruction);
int execute_instruction(struct EmulatorState *, struct Instruction);
void print_registers(struct EmulatorState *);
void load_program_into_ram(struct EmulatorState *, uint32_t *, unsigned int);

void emulateImpl(struct EmulatorState *state,
                 struct Instruction instructions[],
                 unsigned int instructions_l);

void emulate(struct EmulatorState *state,
             uint32_t *instructions,
             unsigned int instructions_l) {
  load_program_into_ram(state, instructions, instructions_l);
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
    const struct TerminateInstruction terminateInstruction =
        *((const struct TerminateInstruction *) (&(instructions[i])));
    //todo magic constants
    if (instructions[i] == 0) {
      instructionsWithType[i].terminateInstruction = terminateInstruction;
      instructionsWithType[i].type = TERMINATE;
    } else if (branchInstruction.filler1 == 0b0
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
void load_program_into_ram(struct EmulatorState *pState,
                           uint32_t *instructs,
                           unsigned int l) {
  memcpy(pState->memory, instructs, l * sizeof(uint32_t));

}

void emulateImpl(struct EmulatorState *state,
                 struct Instruction instructions[],
                 unsigned int instructions_l) {
#ifdef INSTRUCTION_TYPES_TEST

  const char *instructionTypeNames[] =
      {"DATA_PROCESSING", "MULTIPLY", "SINGLE_DATA_TRANSFER",
       "BRANCH_INSTRUCTION","TERMINATE"};
  for (int i = 0; i < instructions_l; i++) {
    printf("Instruction #%d, Instruction type:%s\n",
           i,
           instructionTypeNames[instructions[i].type]);
  }

#endif
  state->PC = 0;
  struct Instruction *fetched = NULL;
  struct Instruction *decoded = NULL;
  while (true) {
    assert(state->PC % 4 == 0);
    if (fetched != NULL)
      if (execute_instruction(state, *fetched) == -1) {
        break;
      }
    fetched = decoded;
    if ((state->PC) / 4 < instructions_l)
      decoded = &(instructions[(state->PC) / 4]);
    else
      decoded = NULL;
    (state->PC) += 4;
  }

  print_registers(state);

}

int execute_instruction(struct EmulatorState *state,
                        struct Instruction instruction) {
  switch (instruction.type) {
    case DATA_PROCESSING:
      return execute_instruction_data_processing(state,
                                                 instruction.dataProcessingInstruction);
    case MULTIPLY:
      return execute_instruction_multiply(state,
                                          instruction.multiplyInstruction);
    case SINGLE_DATA_TRANSFER:
      return execute_instruction_single_data_transfer(state,
                                                      instruction.singleDataTransferInstruction);
    case BRANCH_INSTRUCTION:
      break;
    case TERMINATE:
      return -1;
  }
}

bool should_execute(struct EmulatorState *state, enum Cond cond) {
  //todo switch
  const bool NequalsV =
      (bool) ((state->CPSR) & CPSR_N == (state->CPSR) & CPSR_V);
  const bool Zset = (bool) ((state->CPSR) & CPSR_Z);
  switch (cond) {
    case eq:
      return Zset;
    case ne:
      return !Zset;
    case ge:
      return NequalsV;
    case lt:
      return (bool) ((state->CPSR) & CPSR_N != (state->CPSR) & CPSR_V);
    case gt:
      return (!Zset) && NequalsV;
    case le:
      return Zset || (!NequalsV);
    case al:
      return true;
    default:
      assert(false);
  }
}

int execute_instruction_data_processing(struct EmulatorState *state,
                                        struct DataProcessingInstruction instruction) {
  //todo duplication
  if (!should_execute(state, instruction.cond)) {
    return 0;
  }
  const uint32_t rnVal = (state->registers)[instruction.Rn];
  uint32_t operand2Val;
  if (instruction.immediateOperand) {
    operand2Val = instruction.secondOperand;
  } else {
    operand2Val = (state->registers)[(instruction.secondOperand)
        << 8];//no way this works todo
  }
  switch (instruction.opcode) {
    case and:
      (state->registers)[instruction.Rd] = (rnVal
          & operand2Val);//not sure if this should be bitwise or not. the spec isn't clear todo
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
      state->registers[instruction.Rd] = operand2Val;
      break;
  }
  //todo set cpsr
}

int execute_instruction_multiply(struct EmulatorState *state,
                                 struct MultiplyInstruction instruction) {
  if (!should_execute(state, instruction.cond)) {
    return 0;
  }
}

int execute_instruction_single_data_transfer(struct EmulatorState *state,
                                             struct SingleDataTransferInstruction instruction) {
  if (!should_execute(state, instruction.cond)) {
    return 0;
  }
}

int execute_instruction_branch(struct EmulatorState *state,
                               struct BranchInstruction instruction) {
  if (!should_execute(state, instruction.cond)) {
    return 0;
  }

}


void print_registers(struct EmulatorState *state) {
  printf("Registers:\n");
  for (int i = 0; i < 13; ++i) {
    printf("$%-3d:%11d (0x%08x)\n",
           i,
           state->registers[i],
           state->registers[i]);
  }
  printf("PC  : %10d (0x%08x)\n", state->PC, state->PC);
  printf("CPSR: %10d (0x%08x)\n", state->CPSR, state->CPSR);
  printf("Non-zero memory:\n");
  for (int i = 0; i < MEMORY_SIZE / 4; i++) {
    if (state->memory[i] != 0) {
//      printf("0x%08x: 0x%x\n",4*i,state->memory[i]);
      //swap endiannes to match test cases
      printf("0x%08x: 0x%08x\n", 4 * i, __bswap_32(state->memory[i]));
    }
  }
}

#ifdef USE_EMULATE_MAIN
int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr,
            "the end of the world has come, or you entered the wrong number of arguments\n");
    return -100000;
  }
  const char *filename = argv[1];
  int fileDescriptor = open(filename, O_RDONLY);
  if (fileDescriptor == -1) {
    fprintf(stderr,
            "the end of the world has come, or you entered the wrong filename\n");
    return -100000;
  }

  uint32_t *rawData =
      (uint32_t *) malloc(sizeof(uint32_t[MAX_INSTRUCTION_INPUT_FILE_SIZE]));
  size_t amountRead = sizeof(unsigned char) * read(fileDescriptor,
                                                   rawData,
                                                   sizeof(uint32_t[MAX_INSTRUCTION_INPUT_FILE_SIZE]));
  assert(amountRead % sizeof(uint32_t) == 0);
  struct EmulatorState *state = malloc(sizeof(struct EmulatorState));
  rawData[amountRead / sizeof(uint32_t)] = 0;
  emulate(state,
          rawData,
          (unsigned int) (amountRead / sizeof(uint32_t)) + 1);
  close(fileDescriptor);
}

#endif
