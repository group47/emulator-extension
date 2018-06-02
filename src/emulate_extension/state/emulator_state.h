//
// Created by francis on 6/1/18.
//

#ifndef SRC_EMULATOR_STATE_H
#define SRC_EMULATOR_STATE_H


#include <stdint.h>
#include <stdbool.h>
#include "../basic_typedefs.h"
#include "memory.h"
enum Mode {
  THUMB, ARM
};

enum OperatingMode {
  usr = 0b10000,
  fiq = 0b10001,
  irq = 0b10010,
  svc = 0b10011,
  abt = 0b10111,
  sys = 0b11111,
  und = 0b11011
};

enum ExceptionFlag {
  RESET = 0b10000000,
  DATA_ABORT = 0b01000000,
  FIQ = 0b00100000,
  IRQ = 0b00010000,
  PREFETCH_ABORT = 0b00001000,
  UNDEFINED = 0b00000100,
  SOFTWARE_INTERRUPT = 0b00000010
};


#define NUM_GENERAL_PURPOSE_REGISTERS 16
#define PC_ADDRESS 15

struct CPSR_Struct {
  enum OperatingMode M;
  bool T:1;
  bool F:1;
  bool I:1;
  uint32_t reserved: 20;
  bool V:1;
  bool C:1;
  bool Z:1;
  bool N:1;

}__attribute__((packed));

#define NUM_FIQ_BANKED 7
#define NUM_SVC_BANKED 2
#define NUM_ABT_BANKED 2
#define NUM_IRQ_BANKED 2
#define NUM_UND_BANKED 2


struct CPUState {
  Word general_registers[NUM_GENERAL_PURPOSE_REGISTERS];
  Word fiq_banked[NUM_FIQ_BANKED];
  Word svc_banked[NUM_SVC_BANKED];
  Word abt_banked[NUM_ABT_BANKED];
  Word irq_banked[NUM_IRQ_BANKED];
  Word und_banked[NUM_UND_BANKED];
  struct CPSR_Struct CPSR;
  struct CPSR_Struct SPSR_svc;
  struct CPSR_Struct SPSR_irq;
  struct CPSR_Struct SPSR_fiq;
  struct CPSR_Struct SPSR_abt;
  struct CPSR_Struct SPSR_und;
  enum OperatingMode operatingMode;
  enum Mode mode;
  enum ExceptionFlag flags;
  bool locked;//todo handle this see 4.12
};

//todo: do nothing if exception flag is set
Byte get_byte_from_register(RegisterAddress address);

Word get_word_from_register(RegisterAddress address);

Word set_byte_in_register(RegisterAddress address, Byte byte);

Word set_word_in_register(RegisterAddress address, Word val);

void change_mode(enum Mode newMode);

enum Mode get_mode();

struct CPSR_Struct* get_SPSR_by_mode();

void change_operating_mode(enum OperatingMode newOperatingMode);

void add_exception_flag(enum ExceptionFlag flag);

void remove_exception_flag(enum ExceptionFlag flag);

struct CPSR_Struct getCPSR();

void setCPSR(struct CPSR_Struct toSet);

#endif //SRC_EMULATOR_STATE_H
