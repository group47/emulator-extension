//
// Created by francis on 6/1/18.
//
#include <assert.h>
#include "emulator_state.h"
#include "../instructions/arm/arm_instruction.h"
#include "../instructions/thumb/thumb_instruction.h"

static struct CPUState state;

Byte get_byte_from_register(RegisterAddress address) {
    assert(false);
}

Word get_word_from_register(RegisterAddress address) {
    assert(false);
}//todo add spsr restrictions, overridable if accessed from psr instruction
Word set_byte_in_register(RegisterAddress address, Byte byte) {
    assert(false);
}

Word set_word_in_register(RegisterAddress address, Word val) {
    assert(false);
}

void change_mode(enum Mode newMode) {
    assert(false);
}//make sure to trash pipeline
enum Mode get_mode() {
    assert(false);
}

struct CPSR_Struct *get_SPSR_by_mode() {
    assert(false);
}

void change_operating_mode(enum OperatingMode newOperatingMode) {
    assert(false);
}

enum OperatingMode get_operating_mode() {
    assert(false);
}

void add_exception_flag(enum ExceptionFlag flag) {
    assert(false);
}

void remove_exception_flag(enum ExceptionFlag flag) {
    assert(false);
}

bool has_exception_flag(enum ExceptionFlag flag) {
    assert(false);
}

struct CPSR_Struct getCPSR() {
    assert(false);
}

void setCPSR(struct CPSR_Struct toSet) {
    assert(false);
}

void setSPSR(struct CPSR_Struct old, struct CPSR_Struct new) {
    assert(false);
}

void init_cpu(void) {
    assert(false);
}

struct ArmInstruction get_fetched_arm() {
    assert(false);
}

struct ThumbInstruction get_fetched_thumb() {
    assert(false);
}

struct ArmInstruction get_decoded_arm() {
    assert(false);
}

struct ThumbInstruction get_decoded_thumb() {
    assert(false);
}

bool fetched_valid() {
    assert(false);
}

bool decoded_valid() {
    assert(false);
}

void transfer_decoded_to_fetched_and_load_decoded() {
    assert(false);
}//todo

void print_registers() {
    assert(false);
}
