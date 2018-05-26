
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
                                        const struct DataProcessingInstruction);
int execute_instruction_multiply(struct EmulatorState *,
                                 const struct MultiplyInstruction);
int execute_instruction_single_data_transfer(struct EmulatorState *,
                                             const struct SingleDataTransferInstruction);
int execute_instruction(struct EmulatorState *, const struct Instruction);
void print_registers(struct EmulatorState *);
void load_program_into_ram(struct EmulatorState *, const uint8_t *, unsigned int);

void emulateImpl(struct EmulatorState *state);
int
setCPSR(struct EmulatorState *state,
        struct DataProcessingInstruction instruction,
        bool b,
        bool b1,
        uint32_t,
        uint32_t);

void emulate(struct EmulatorState *state,
             uint8_t *instructions,
             unsigned int instructions_l) {
  memset(state, 0, sizeof(struct EmulatorState));
  load_program_into_ram(state, instructions, instructions_l);
  emulateImpl(state);
}

// Newly added declaration for function 

uint32_t *compute_secondOperand(struct EmulatorState *state,
                                uint32_t secondOperand,
                                bool immediateFlag,
                                bool immediateVal);

uint32_t extract_rotate(uint16_t secondOperand);

uint32_t extract_shift(uint16_t secondOperand);

int execute_instruction_branch(struct EmulatorState *state,
                               const struct BranchInstruction instruction);
struct Instruction rawInstructionToInstruction(union RawInstruction rawInstruction) {
  struct Instruction res;
  const struct BranchInstruction branchInstruction = rawInstruction.branchInstruction;
  const struct MultiplyInstruction multiplyInstruction = rawInstruction.multiplyInstruction;
  const struct SingleDataTransferInstruction
      singleDataTransferInstruction = rawInstruction.singleDataTransferInstruction;
  const struct DataProcessingInstruction
      dataProcessingInstruction = rawInstruction.dataProcessingInstruction;
  const struct TerminateInstruction terminateInstruction = rawInstruction.terminateInstruction;
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
                           const uint8_t *instructs,
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
    if (fetched_valid) {
      const int executionResult =
          execute_instruction(state, rawInstructionToInstruction(fetched));
      if (executionResult == -2) {//todo magic constants
        fetched_valid = false;
        decode_valid = false;
      }
      if (executionResult == -1) {
        break;
      }
    }
    fetched = decoded;
    fetched_valid = decode_valid;
    if (state->PC < MEMORY_SIZE) {
      decoded = *(union RawInstruction *) &((state->memory)[state->PC]);
      decode_valid = true;
    } else {
      assert(false);
    }
    (state->PC) += 4;
  }

  print_registers(state);

}

int execute_instruction(struct EmulatorState *state,
                        const struct Instruction instruction) {
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
      return execute_instruction_branch(state, instruction.rawInstruction.branchInstruction);
    case TERMINATE:
      return -1;
    default:
      assert(false);
  }
}

bool should_execute(const struct EmulatorState *state, const enum Cond cond) {
  const bool NequalsV =
      (bool) (((state->CPSR) & CPSR_N) == ((state->CPSR) & CPSR_V));
  const bool Zset = (bool) ((state->CPSR) & CPSR_Z);
  switch (cond) {
    case eq:
      return Zset;
    case ne:
      return !Zset;
    case ge:
      return NequalsV;
    case lt:
      return !NequalsV;
    case gt:
      return (!Zset) && NequalsV;
    case le:
      return Zset || (!NequalsV);
    case al:
      return true;
    default:
      return false;
  }
}


uint32_t *getOperand2Val(struct EmulatorState *state,
                         const uint16_t secondOperand,
                         const bool immediate,
                         const bool flag) {
  uint32_t res;
  uint32_t carry_out = 0;

  if (immediate == flag) {

    struct ImmediateTrue immediateTrue = *(struct ImmediateTrue *) &secondOperand;
    //rotate stack overflow community wiki:
    //https://stackoverflow.com/questions/776508/best-practices-for-circular-shift-rotate-operations-in-c
    uint32_t imm = immediateTrue.Imm;
    res = __rord(imm, 2 * immediateTrue.rotate);
  } else {
    struct ImmediateFalseShiftByRegisterFalse immediateFalse = *(struct ImmediateFalseShiftByRegisterFalse *) &secondOperand;
    if (immediateFalse.shift_by_register) {
      //todo
      assert(false);//not implemented
    } else {
      switch (immediateFalse.shift_type) {
        case lsl:
          carry_out = immediateFalse.integer == 0 ? 0 :
                      (((0x1) << (32 - immediateFalse.integer) & immediateFalse.Rm) % 2);
          res = (state->registers[immediateFalse.Rm]) << immediateFalse.integer;
          break;
        case lsr:
          carry_out = immediateFalse.integer == 0 ? 0 :
                      (((0x1) << (immediateFalse.integer - 1) & immediateFalse.Rm) % 2);
          res = (state->registers[immediateFalse.Rm]) >> immediateFalse.integer;
          break;
        case asr:
          carry_out = immediateFalse.integer == 0 ? 0 :
                      (((0x1) << (immediateFalse.integer - 1) & immediateFalse.Rm) % 2);
          res = (int32_t) ((state->registers[immediateFalse.Rm]) >> immediateFalse.integer);
          break;
        case ror:
          carry_out = immediateFalse.integer == 0 ? 0 :
                      (((0x1) << (immediateFalse.integer - 1) & immediateFalse.Rm) % 2);
          res = __rord((uint32_t) immediateFalse.Rm, immediateFalse.integer);
          break;
      }
    }
  }
  uint32_t *result = malloc(2 * sizeof(uint32_t));
  *result = res;
  *(result + 1) = carry_out << 29;
  return result;
}


int execute_instruction_data_processing(struct EmulatorState *state,
                                        const struct DataProcessingInstruction instruction) {
  //todo duplication

  bool overflow_occurred = false;
  bool borrow_occurred = false;

  if (!should_execute(state, instruction.cond)) {
    return 0;
  }
  const uint32_t rnVal = (state->registers)[instruction.Rn];
  uint32_t *result =
      getOperand2Val(state, instruction.secondOperand, instruction.immediateOperand, 1);
  uint32_t operand2Val = result[0];
  uint32_t shiftCarryOut = result[1];

  free(result);

  uint32_t computation_res;
  // for distinguishing between operator thing
  // Maybe we could use a utility function
  // The operation on them is the same for single data transfer as well

  switch (instruction.opcode) {
    case and:
      computation_res = rnVal & operand2Val;
      (state->registers)[instruction.Rd] = computation_res;
      break;
    case eor:
      computation_res = rnVal ^ operand2Val;
      (state->registers)[instruction.Rd] = computation_res;
      return 1;
    case sub:
      computation_res = rnVal - operand2Val;
      if (does_borrow_occur(rnVal, operand2Val)) {
        borrow_occurred = true;
      }
      (state->registers)[instruction.Rd] = computation_res;
      break;
    case rsb:
      computation_res = operand2Val - rnVal;
      if (does_borrow_occur(operand2Val, rnVal)) {
        borrow_occurred = true;
      }
      (state->registers)[instruction.Rd] = computation_res;
      break;
    case add:
      computation_res = operand2Val + rnVal;
      if (does_overflow_occur(operand2Val, rnVal)) {
        overflow_occurred = true;
      }
      (state->registers)[instruction.Rd] = computation_res;
      break;
    case tst:
      computation_res = rnVal & operand2Val;
      //todo
      break;
    case teq:
      computation_res = rnVal ^ operand2Val;
      //todo
      break;
    case cmp:
      computation_res = rnVal - operand2Val;
      if (does_borrow_occur(rnVal, operand2Val)) {
        borrow_occurred = true;
      }//todo duplication with sub, use fallthrough
      break;
    case orr:
      computation_res = rnVal | operand2Val;
      (state->registers)[instruction.Rd] = (rnVal | operand2Val);
      break;
    case mov:
      computation_res = operand2Val;
      state->registers[instruction.Rd] = operand2Val;
      break;
  }
  return setCPSR(state, instruction, borrow_occurred, overflow_occurred, computation_res,
                 shiftCarryOut);
}
int setCPSR(struct EmulatorState *state,
            const struct DataProcessingInstruction instruction,
            const bool borrow,
            const bool overflow,
            const uint32_t computation_res,
            const uint32_t shiftCarryOut) {//set cpsr
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
          //printf("have borrow\n");
        } else {
          //printf("no borrow\n");
          state->CPSR |= CPSR_C;
        }

      }
    } else if (is_logical(instruction.opcode)) {
      state->CPSR |= shiftCarryOut;
    } else {
      assert(false);
    }
    //set z bit
    if (computation_res == 0) {
      state->CPSR |= CPSR_Z;
    }else{
      state->CPSR &= ~CPSR_Z;
    }
    //set n bit
    if (computation_res & CPSR_N) {// CPSR_N is the 31st bit mask
      state->CPSR |= CPSR_N;
    } else {
      state->CPSR &= ~CPSR_N;
    }
  }
  return 1;
}

uint32_t extract_rotate(uint16_t secondOperand) {
  return secondOperand >> 8;
}

uint32_t extract_shift(uint16_t secondOperand) {
  return (secondOperand & 0xff0) >> 4;
}

int
execute_instruction_multiply(struct EmulatorState *state, struct MultiplyInstruction instruction) {

  if (!should_execute(state, instruction.cond)) {
    return 0;
  }

  uint32_t result = state->registers[instruction.Rm] * state->registers[instruction.Rs];

  if (instruction.accumulate) {
    result += state->registers[instruction.Rn];
  }

  if (result == 0) {
    // set z bit
    state->CPSR |= CPSR_Z;
    // set n bit
    state->CPSR != (result & CPSR_N);
  }

  state->registers[instruction.destinationRegister] = result;

  return 1;
}

void handle_out_of_bounds(uint32_t index);


int execute_instruction_single_data_transfer(struct EmulatorState *state,
                                             struct SingleDataTransferInstruction instruction) {
  if (!should_execute(state, instruction.cond)) {
    return 0;
  }

  uint32_t offset;

  if (instruction.immediateOffset == 0) {
    offset = instruction.offset;
  } else {
    uint32_t *result = getOperand2Val(state, instruction.offset, instruction.immediateOffset, 0);
    offset = result[0];
    free(result);
  }

  // pre indexing
  uint32_t address = state->registers[instruction.Rn];

  if (instruction.prePostIndexingBit) {
    if (instruction.upBit) {
      address += offset;
    } else {
      address -= offset;
    }
  }

  if (instruction.loadStore) {
    uint32_t result = 0;
    bool access_was_successful = true;
    for (int i = 0; i < 4; i++) {
      const uint32_t memory_access_index = address + i;
      if (memory_access_index < MEMORY_SIZE) {
        result |= ((uint32_t) state->memory[memory_access_index]) << (8 * i);
      } else {
        access_was_successful = false;
      }
    }
    if (!access_was_successful) {
      handle_out_of_bounds(address);
    }

    state->registers[instruction.Rd] = result;
  } else {
    for (int i = 0; i < 4; i++) {
      const uint32_t mask = (0xff) << (8 * i);
      const uint32_t memory_access_index = address + i;
      if (memory_access_index < MEMORY_SIZE) {
        state->memory[memory_access_index] =
            (((uint32_t) state->registers[instruction.Rd]) & mask) >> (8 * i);
      } else {
        handle_out_of_bounds(memory_access_index);
      }
    }
  }

  // I need a better solution for this duplication
  // post indexing
  if (!instruction.prePostIndexingBit) {
    if (instruction.upBit) {
      state->registers[instruction.Rn] += offset;
    } else {
      state->registers[instruction.Rn] -= offset;
    }
  }

  return 0;
}


void handle_out_of_bounds(uint32_t index) {
  //todo magic constants
  if (index >= 0x20200000 && index < 0x20200012) {
    if(index < 0x20200004 && index >= 0x20200000){
      printf("One GPIO pin from 0 to 9 has been accessed\n");
    }
    if(index < 0x20200008 && index >= 0x20200004){
      printf("One GPIO pin from 10 to 19 has been accessed\n");
    }
    if(index > 0x20200008){
      printf("One GPIO pin from 20 to 29 has been accessed\n");
    }
  } else
    printf("Error: Out of bounds memory access at address 0x%08x\n", index);
}


int execute_instruction_branch(struct EmulatorState *state,
                               const struct BranchInstruction instruction) {
  if (!should_execute(state, instruction.cond)) {
    return 0;
  }
  const int32_t offset = instruction.offset * 4;
  state->PC += offset;
  return -2;
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
    if ((state->memory_as_uints)[i] != 0) {
//      printf("0x%08x: 0x%x\n",4*i,state->memory[i]);
      //swap endiannes to match test cases
      printf("0x%08x: 0x%08x\n", 4 * i, __bswap_32(state->memory_as_uints[i]));
      // printf("0x%08x: 0x%08x\n", i, *(uint32_t *)&state->memory[i]);

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

  assert(sizeof(struct SingleDataTransferInstruction) == sizeof(int32_t));
  assert(sizeof(struct MultiplyInstruction) == sizeof(int32_t));
  assert(sizeof(struct DataProcessingInstruction) == sizeof(int32_t));
  assert(sizeof(struct BranchInstruction) == sizeof(int32_t));
  assert(sizeof(struct ImmediateFalseShiftByRegisterFalse) == 2*sizeof(unsigned char));
  assert(sizeof(struct ImmediateFalseShiftByRegisterTrue) == 2*sizeof(unsigned char));

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
  memset(rawData + amountRead / sizeof(uint32_t), 0, 4);
  //rawData[amountRead / sizeof(uint32_t)] = 0;
  emulate(state,
          rawData,
          (unsigned int) (amountRead / sizeof(uint32_t)) + 1);
  close(fileDescriptor);
  free(state);
  free(rawData);
}

#endif
