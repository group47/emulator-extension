//
// Created by francis on 6/1/18.
//

#ifndef SRC_EMULATOR_STATE_H
#define SRC_EMULATOR_STATE_H


#include <stdint.h>
#include <stdbool.h>
#include "../basic_typedefs.h"
#include "memory.h"
#include "../instructions/arm/arm_instruction.h"
#include "../coprocessor/system_control_coprocessor/system_control_coprocessor.h"

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
  RESET              = 0b100000000,
  DATA_ABORT         = 0b010000000,
  FIQ                = 0b001000000,
  IRQ                = 0b000100000,
  PREFETCH_ABORT     = 0b000010000,
  UNDEFINED          = 0b000001000,
  SOFTWARE_INTERRUPT = 0b000000100,
    BRANCH_LINK_EXCEPTION = 0b000000010,
};


#define NUM_GENERAL_PURPOSE_REGISTERS_ARM 16
#define NUM_GENERAL_PURPOSE_REGISTERS_THUMB 8
#define SPSR_ADDRESS 17
#define CPSR_ADDRESS 16
#define PC_ADDRESS 15
#define LR_ADDRESS 14
#define SP_ADDRESS 13

struct CPSR_Struct {
  enum OperatingMode M : 5;
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
#define NUM_FIQ_UNBANKED 8
#define NUM_SVC_BANKED 2
#define NUM_ABT_BANKED 2
#define NUM_IRQ_BANKED 2
#define NUM_UND_BANKED 2


struct CPUState {
  Word general_registers[NUM_GENERAL_PURPOSE_REGISTERS_ARM - 1];// -1 for the cpsr
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
//  enum OperatingMode operatingMode; // actually in cpsr
  //enum Mode mode;// acctually encoded in cpsr t bit
  enum ExceptionFlag flags;
  bool locked;//todo handle this see 4.12
  uint32_t fetched_arm;
  uint32_t decoded_arm;
  uint16_t fetched_thumb;
  uint16_t decoded_thumb;
  bool decoded_valid;//= false
  bool fetched_valid;//= false
    bool decoded_prefetch_aborted;//false
    bool fetched_prefetch_aborted;//false
    struct SystemControlCoprocessor systemControlCoprocessor;

};

//todo: do nothing if exception flag is set

Byte get_byte_from_register(RegisterAddress address);

Word get_word_from_register(RegisterAddress address);//todo add spsr restrictions, overridable if accessed from psr instruction

void set_byte_in_register(RegisterAddress address, Byte byte);

void set_word_in_register(RegisterAddress address, Word val);

void change_mode(enum Mode newMode);//make sure to trash pipeline

enum Mode get_mode();

struct CPSR_Struct get_SPSR_by_mode();

void set_operating_mode(enum OperatingMode newOperatingMode);

enum OperatingMode get_operating_mode();

void add_exception_flag(enum ExceptionFlag flag);

void remove_exception_flag(enum ExceptionFlag flag);

bool has_exception_flag(enum ExceptionFlag flag);

enum ExceptionFlag get_exception_flags();

struct CPSR_Struct getCPSR();

void setCPSR(struct CPSR_Struct toSet);

void setSPSR(struct CPSR_Struct toSet);

void init_cpu(enum CommandLineFlags);

union RawArmInstruction get_fetched_arm();

union RawThumbInstruction get_fetched_thumb();

union RawArmInstruction get_decoded_arm();

union RawThumbInstruction get_decoded_thumb();

bool fetched_valid();

bool decoded_valid();

void transfer_fetched_to_decoded_and_load_fetched();

void print_registers(enum CommandLineFlags);

void invalidate_pipeline();

bool prefetch_aborted();

void set_spsr_by_mode(struct CPSR_Struct cpsr_struct, enum OperatingMode mode);

#endif //SRC_EMULATOR_STATE_H
