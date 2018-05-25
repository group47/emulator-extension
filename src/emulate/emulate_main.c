
#include <stdint-gcc.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <x86intrin.h>
#include "unistd.h"
#include "emulate_main.h"
#include "instructions.h"
#include "cpsr_overflow_detection.h"

int execute_instruction_data_processing(struct EmulatorState *,
                                        struct DataProcessingInstruction);
int execute_instruction_multiply(struct EmulatorState *,
                                 struct MultiplyInstruction);
int execute_instruction_single_data_transfer(struct EmulatorState *,
                                             struct SingleDataTransferInstruction);
int execute_instruction(struct EmulatorState *, struct Instruction);
void print_registers(struct EmulatorState *);
void load_program_into_ram(struct EmulatorState *, uint32_t *, unsigned int);
void emulateImpl(struct EmulatorState *state);
int setCPSR(struct EmulatorState *, struct DataProcessingInstruction, bool, bool);

void emulate(struct EmulatorState *state,
             uint32_t *instructions,
             unsigned int instructions_l) {
  load_program_into_ram(state, instructions, instructions_l);
  emulateImpl(state);
}

struct Instruction rawInstructionToInstruction(union RawInstruction rawInstruction) {
  struct Instruction res;
  const struct BranchInstruction branchInstruction =
      *((const struct BranchInstruction *) (&(rawInstruction)));
  const struct MultiplyInstruction multiplyInstruction =
      *((const struct MultiplyInstruction *) (&(rawInstruction)));
  const struct SingleDataTransferInstruction singleDataTransferInstruction =
      *((const struct SingleDataTransferInstruction *) (&(rawInstruction)));
  const struct DataProcessingInstruction dataProcessingInstruction =
      *((const struct DataProcessingInstruction *) (&(rawInstruction)));
  const struct TerminateInstruction terminateInstruction =
      *((const struct TerminateInstruction *) (&(rawInstruction)));
  const uint32_t asInt = *((uint32_t *) (&(rawInstruction)));
  memcpy(&(res.rawInstruction), &(rawInstruction), sizeof(union RawInstruction));
  //todo magic constants
  if (asInt == 0) {
    res.type = TERMINATE;
  } else if (branchInstruction.filler1 == 0b0
      && branchInstruction.filler2 == 0b101) {
    res.type = BRANCH_INSTRUCTION;
  } else if (singleDataTransferInstruction.filler == 0b01) {
    res.type = SINGLE_DATA_TRANSFER;
  } else if (multiplyInstruction.filler == 0b000000
      && multiplyInstruction.filler2 == 0b1001) {
    res.type = MULTIPLY;
  } else if (dataProcessingInstruction.filler == 0b00) {
    res.type = DATA_PROCESSING;
  } else {
    assert(false);
  }
  return res;
}

void load_program_into_ram(struct EmulatorState *pState,
                           uint32_t *instructs,
                           unsigned int l) {
  memcpy(pState->memory, instructs, l * sizeof(uint32_t));

}

//The instruction parameter needs to be removed since the instructions need to be in main memory
void emulateImpl(struct EmulatorState *state) {
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
  union RawInstruction fetched;
  bool fetched_valid = false;
  union RawInstruction decoded;
  bool decode_valid = false;
  while (true) {
    assert(state->PC % 4 == 0);
    if (fetched_valid)
      if (execute_instruction(state, rawInstructionToInstruction(fetched)) == -1) {
        break;
      }
    fetched = decoded;
    fetched_valid = decode_valid;
    if (state->PC / 4 < MEMORY_SIZE) {
      decoded = *(union RawInstruction *) &((state->memory)[(state->PC) / 4]);
      decode_valid = true;
    } else {
      assert(false);
    }
    (state->PC) += 4;
  }

  print_registers(state);

}

int execute_instruction(struct EmulatorState *state,
                        struct Instruction instruction) {
  switch (instruction.type) {
    case DATA_PROCESSING:
      return execute_instruction_data_processing(state,
                                                 instruction.rawInstruction.dataProcessingInstruction);
    case MULTIPLY:
      return execute_instruction_multiply(state,
                                          instruction.rawInstruction.multiplyInstruction);
    case SINGLE_DATA_TRANSFER:
      return execute_instruction_single_data_transfer(state,
                                                      instruction.rawInstruction.singleDataTransferInstruction);
    case BRANCH_INSTRUCTION:
      break;
    case TERMINATE:
      return -1;
  }
}

bool should_execute(struct EmulatorState *state, enum Cond cond) {
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

  bool overflow_occurred = false;
  bool borrow_occurred = false;

  if (!should_execute(state, instruction.cond)) {
    return 0;
  }
  const uint32_t rnVal = (state->registers)[instruction.Rn];
  uint32_t operand2Val;
  if (instruction.immediateOperand) {
    uint16_t secondOperand = instruction.secondOperand;
    struct ImmediateTrue immediateTrue = *(struct ImmediateTrue *)&secondOperand;
    //rotate stack overflow community wiki:
      //https://stackoverflow.com/questions/776508/best-practices-for-circular-shift-rotate-operations-in-c
    uint32_t  imm = immediateTrue.Imm;
    operand2Val = __rord(imm,2*immediateTrue.rotate);
  } else {
    uint16_t secondOperand = instruction.secondOperand;
    struct ImmediateFalse immediateFalse = *(struct ImmediateFalse *)&secondOperand;
    if(immediateFalse.shift_by_register){
      //todo
      assert(false);//not implemented
    } else{
      operand2Val = immediateFalse.Rm << immediateFalse.shift;
    }
  }
  switch (instruction.opcode) {
    case and:
      (state->registers)[instruction.Rd] = (rnVal
          & operand2Val);//not sure if this should be bitwise or not. the spec isn't clear todo
      break;
    case eor:
      (state->registers)[instruction.Rd] = (rnVal ^ operand2Val);
      return 1;
    case sub:
      if (does_borrow_occur(rnVal, operand2Val)) {
        borrow_occurred = true;
      }
      (state->registers)[instruction.Rd] = (rnVal - operand2Val);
      break;
    case rsb:
      if (does_borrow_occur(operand2Val, rnVal)) {
        borrow_occurred = true;
      }
      (state->registers)[instruction.Rd] = (operand2Val - rnVal);
      break;
    case add:
      if (does_overflow_occur(operand2Val, rnVal)) {
        overflow_occurred = true;
      }
      (state->registers)[instruction.Rd] = (operand2Val + rnVal);
      break;
    case tst:
      //todo
      break;
    case teq:
      //todo
      break;
    case cmp:
      if (does_borrow_occur(rnVal, operand2Val)) {
        borrow_occurred = true;
      }//todo duplication with sub, use fallthrough
      break;
    case orr:
      (state->registers)[instruction.Rd] = (rnVal | operand2Val);
      return 1;
    case mov:
      state->registers[instruction.Rd] = operand2Val;
      break;
  }
  return setCPSR(state, instruction, borrow_occurred, overflow_occurred);
}
int setCPSR(struct EmulatorState *state,
            struct DataProcessingInstruction instruction,
            bool borrow,
            bool overflow) {//set cpsr
  if (instruction.setConditionCodes) {
    //set c bit
    if (is_arithmetic((instruction).opcode)) {
      if ((instruction).opcode == add) {
        if (overflow)
          state->CPSR |= CPSR_C;
        else
          state->CPSR &= ~CPSR_C;
      } else {
        if (borrow) {
          state->CPSR &= ~CPSR_C;
        } else {
          state->CPSR |= CPSR_C;
        }
      }
    } else if (is_logical((instruction).opcode)) {
      //todo
    } else {
      assert(false);
    }
    //set z bit
    if (state->registers[(instruction).Rd] == 0) {
      state->CPSR |= CPSR_Z;
    }
    //set n bit
    if (state->registers[(instruction).Rd] | CPSR_N) {// CPSR_N is the 31st bit mask
      state->CPSR |= CPSR_N;
    } else {
      state->CPSR &= ~CPSR_N;
    }
  }
  return 1;
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

  assert(sizeof(struct DataProcessingInstruction) == sizeof(uint32_t));

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
