//

#ifndef EMULATE_EMULATE_MAIN_H
//
// Created by francis on 5/23/18.
enum OpCode {
  and = 0b0000,
  eor = 0b0001,
  sub = 0b0010,
  rsb = 0b0011,
  add = 0b0100,
  tst = 0b1000,
  teq = 0b1001,
  cmp = 0b1010,
  orr = 0b1100,
  mov = 0b1101,
  invalidOpcode
};

enum CPSR {
  CPSR_N = 0x80000000,
  CPSR_Z = 0x40000000,
  CPSR_C = 0x20000000,
  CPSR_V = 0x10000000
};
#define EMULATE_EMULATE_MAIN_H
#define MEMORY_SIZE 65536
#define MAX_INSTRUCTION_INPUT_FILE_SIZE 1000
#define NUM_REGISTERS 17
#include "stdint-gcc.h"
struct CPUState {
  union {
    uint8_t memory[MEMORY_SIZE];
    uint32_t memory_as_uints[MEMORY_SIZE / 4];
  };

  uint32_t registers[NUM_REGISTERS - 2];
  //conceptual bug:, register 15 is a valid register, but will overflow the array access, but still get the right register
  //by luck since this packed in a struct, the overflowed access still gets the correct register, but this is by chance only
  uint32_t PC;
  uint32_t CPSR;
  uint8_t pinControlBits[3*4];
  uint8_t pinClearingBits[4];
  uint8_t pinTurnOnBits[4];
};
#include <stdbool.h>
#include "../shared/instructions.h"
#include "../shared/data_processing_instruction.h"

int execute_instruction(struct CPUState *, struct Instruction);
void print_registers(struct CPUState *);
void load_program_into_ram(struct CPUState *, const uint8_t *, unsigned int);

void emulateImpl(struct CPUState *state);

int
setCPSR(struct CPUState *, struct DataProcessingInstruction , bool , bool , uint32_t, uint32_t);
uint32_t *compute_secondOperand(struct CPUState *,
                                uint32_t ,
                                bool ,
                                bool );

uint32_t extract_rotate(uint16_t );
uint32_t extract_shift(uint16_t );
bool should_execute(const struct CPUState *, enum Cond );

int getOperand2Val(struct CPUState *,
                         uint16_t ,
                         bool ,
                         bool ,
                         uint32_t *,
                         uint32_t *);

uint32_t handle_out_of_bounds(struct CPUState*,uint32_t ,bool,uint32_t);

enum ExecutionExitCode{
  BRANCH = -2,TERMINATE = -1,DIDNT_EXECUTE = 0, OK = 1
};

void emulate(struct CPUState *state,
             uint8_t instructions[],
             unsigned int instructions_l);

#endif //EMULATE_EMULATE_MAIN_H
