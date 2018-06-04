//
// Created by francis on 6/1/18.
//
#include <assert.h>
#include <stdio.h>
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
    return state.CPSR.T ? THUMB : ARM;
}

struct CPSR_Struct get_SPSR_by_mode() {
    /*
    switch (state.CPSR.M) {
        case usr:
            return state.CPSR;
        case fiq:
            return state.SPSR_fiq;
        case irq:
            return state.SPSR_irq;
        case svc:
            return state.SPSR_svc;
        case und:
            return state.SPSR_und;
        case abt:
            return state.SPSR_abt;
        case sys:
            return state.CPSR;
        default:
            fprintf(stderr, "unknown operating mode\n");
            assert(false);
    }
    */
    assert(false);
}

// change based on mode? ie. change cpsr, spsr ?
void change_operating_mode(enum OperatingMode newOperatingMode) {
    /*
    state.CPSR.M = newOperatingMode;
     */
    assert(false);
}

enum OperatingMode get_operating_mode() {
    /*
    return state.CPSR.M;
     */
    assert(false);
}

void add_exception_flag(enum ExceptionFlag flag) {
    /*
    state.flags |= flag;
     */
    assert(false);
}

void remove_exception_flag(enum ExceptionFlag flag) {
    /*
    state.flags &= ~flag;
     */
    assert(false);
}

bool has_exception_flag(enum ExceptionFlag flag) {
    /*
    return state.flags & flag;
     */
    assert(false);
}

struct CPSR_Struct getCPSR() {
    /*
    return state.CPSR;
     */
    assert(false);
}

void setCPSR(struct CPSR_Struct toSet) {
    /*
    state.CPSR = toSet;
     */
    assert(false);
}

void setSPSR(struct CPSR_Struct toSet) {
    /*
    switch (state.CPSR.M) {
        case usr:
            state.CPSR = toSet;
            break;
        case fiq:
            state.SPSR_fiq = toSet;
            break;
        case irq:
            state.SPSR_irq = toSet;
            break;
        case svc:
            state.SPSR_svc = toSet;
            break;
        case und:
            state.SPSR_und = toSet;
            break;
        case abt:
            state.SPSR_abt = toSet;
            break;
        case sys:
            state.CPSR = toSet;
            break;
        default:
            fprintf(stderr, "unknown operating mode\n");
            assert(false);
    }
     */
    assert(false);
}

void init_cpu(void) {
    assert(false);
}

union RawArmInstruction get_fetched_arm() {
    /*
    return *((union RawArmInstruction*) &state.fetched_arm);
     */
    assert(false);
}

union RawThumbInstruction get_fetched_thumb() {
    /*
    return *((union RawThumbInstruction*) &state.fetched_thumb);
     */
    assert(false);
}

union RawArmInstruction get_decoded_arm() {
    /*
    return *((union RawArmInstruction*) &state.decoded_arm);
     */
    assert(false);
}

union RawThumbInstruction get_decoded_thumb() {
    /*
    return *((union RawThumbInstruction*) &state.decoded_thumb);
     */
    assert(false);
}

bool fetched_valid() {
    /*
    return state.fetched_valid;
     */
    assert(false);
}

bool decoded_valid() {
    /*
    return state.decoded_valid;
     */
    assert(false);
}

void transfer_decoded_to_fetched_and_load_decoded() {
    assert(false);
}//todo

void print_registers() {
    assert(false);
}
