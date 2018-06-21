//
// Created by francis on 6/1/18.
//
#include "../util/entry_point.h"
#include <assert.h>
#include <memory.h>
#include <endian.h>
#include "../instructions/thumb/thumb_instruction.h"
#include "exception.h"
#include "../mmu/translation.h"
#include "../mmu/address.h"

static struct CPUState state;

Byte get_byte_from_register(RegisterAddress address) {
    return (Byte) get_word_from_register(address);
}

Word get_set_register(Word *register_, bool set, Word val) {
    if (set) {
        *register_ = val;
        return *register_;
    } else {
        return *register_;
    }
}

void increment_pc(enum Mode thumb_mode) {
    state.general_registers[PC_ADDRESS] = state.general_registers[PC_ADDRESS] + (thumb_mode == THUMB ? 2 : 4);
}


Word get_set_pc(bool set, Word val, struct CPUState *state_in) {
    if (set) {
        invalidate_pipeline();
    }
    return get_set_register(&(state_in->general_registers[PC_ADDRESS]), set, val);
}

Word *get_banked_array_by_operating_mode();

Word *get_banked_array_by_operating_mode_prev(struct CPUState *state_in);

Word get_set_sp_or_lr(RegisterAddress address, bool set, Word val, struct CPUState *state_in) {
    if (get_operating_mode() == usr || get_operating_mode() == sys) {
        return get_set_register(&(state_in->general_registers[SP_ADDRESS]), set, val);
    } else if (get_operating_mode() != fiq) {
        Word *banked_array = get_banked_array_by_operating_mode_prev(state_in);
        return get_set_register(&banked_array[address - SP_ADDRESS], set, val);
    } else if (get_operating_mode() == fiq) {
        return get_set_register(&(state_in->fiq_banked[address - 8]), set, val);
    } else {
        assert(false);
    }
}

Word get_set_cpsr(bool set, Word val, struct CPUState *state_in) {
    assert(!set);
    return get_set_register((Word *) &(state.CPSR), set, val);
}


Word get_set_word_from_special_register(RegisterAddress address, bool set, Word val, struct CPUState *state_in) {
    switch (address) {
        case PC_ADDRESS:
            return get_set_pc(set, val, state_in);
        case SP_ADDRESS:
            return get_set_sp_or_lr(address, set, val, state_in);
        case LR_ADDRESS:
            return get_set_sp_or_lr(address, set, val, state_in);
        case CPSR_ADDRESS:
            return get_set_cpsr(set, val, state_in);
            break;
        default:
            assert(false);
    }
}

Word get_set_word_from_register(RegisterAddress address, bool set, Word val, struct CPUState *state_in) {
    if (has_exceptions_prev(state_in)) {
        return 0;//don't allow register access if exceptions raised
    }
    assert(address != SPSR_ADDRESS);
    if (address == PC_ADDRESS || address == SP_ADDRESS || address == CPSR_ADDRESS || address == LR_ADDRESS) {
        return get_set_word_from_special_register(address, set, val, state_in);
    }

    RegisterAddress max_valid_register_address;
    if (get_mode() == ARM) {
        max_valid_register_address = NUM_GENERAL_PURPOSE_REGISTERS_ARM - 1;
    } else {
        max_valid_register_address = NUM_GENERAL_PURPOSE_REGISTERS_THUMB - 1;
    }
    const RegisterAddress max_unbanked_address_fiq = NUM_FIQ_UNBANKED - 1;
    const RegisterAddress max_banked_address_fiq = NUM_FIQ_UNBANKED + NUM_FIQ_BANKED - 1;
    const RegisterAddress max_banked_address_other = PC_ADDRESS - 1;
    const RegisterAddress max_unbanked_address_other = max_valid_register_address;
    Word *banked_array;
    switch (get_operating_mode()) {
        case usr:
        case sys:
            assert (address <= max_valid_register_address);
            return get_set_register(&(state_in->general_registers[address]), set, val);
        case fiq:
            if (address > max_unbanked_address_fiq) {
                if (address <= max_banked_address_fiq) {
                    return get_set_register(&(state_in->fiq_banked[address - NUM_FIQ_UNBANKED]), set, val);
                } else {
                    assert(false);
                }
            } else {
                return get_set_register(&(state_in->general_registers[address]), set, val);
            }
        case irq:
        case svc:
        case und:
        case abt:
            if (address <= max_unbanked_address_other) {
                return get_set_register(&(state_in->general_registers[address]), set, val);
            } else if (address <= max_banked_address_other) {
                banked_array = get_banked_array_by_operating_mode_prev(state_in);
                return get_set_register(&banked_array[address - max_unbanked_address_other], set, val);
            } else {
                assert(false);
            }
        default:
            assert(false);
    }
}

enum OperatingMode get_past_operating_mode(struct CPUState *state_in);

Word *get_banked_array_by_operating_mode_prev(struct CPUState *state_in) {
    switch (get_past_operating_mode(state_in)) {
        case irq:
            return state_in->irq_banked;
        case svc:
            return state_in->svc_banked;
        case abt:
            return state_in->abt_banked;
        case und:
            return state_in->und_banked;
        default:
            assert(false);
    }
}


Word *get_banked_array_by_operating_mode() {
    return get_banked_array_by_operating_mode_prev(&state);
}


Word get_word_from_register(RegisterAddress address) {
    return get_set_word_from_register(address, false, -1, &state);
}


//todo add spsr restrictions, overridable if accessed from psr instruction

struct CPSR_Struct get_spsr() {
    switch (get_operating_mode()) {
        case usr:
            assert(false);//this shouldn't happen
        case fiq:
            return state.SPSR_fiq;
        case irq:
            return state.SPSR_irq;
        case svc:
            return state.SPSR_svc;
        case abt:
            return state.SPSR_abt;
        case sys:
            assert(false);
        case und:
            return state.SPSR_und;
        default:
            assert(false);
    }
}

void set_byte_in_register(RegisterAddress address, Byte byte) {
    set_word_in_register(address, get_byte_from_register(address) | (uint32_t) byte);
}

void set_word_in_register(RegisterAddress address, Word val) {
    if (has_exceptions()) {
        return;//don't allow register access if exceptions raised
    }
    get_set_word_from_register(address, true, val, &state);
}

void change_mode(enum Mode newMode) {
    assert(false);
}//make sure to trash pipeline and that this is part of spsr


enum Mode get_mode() {
    return state.CPSR.T ? THUMB : ARM;
}

struct CPSR_Struct get_SPSR_by_mode() {

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
            fprintf(get_logfile(), "unknown operating mode\n");
            assert(false);
    }
}

void set_operating_mode(enum OperatingMode newOperatingMode) {
    struct CPSR_Struct new_cpsr = getCPSR();
    new_cpsr.M = newOperatingMode;
    setCPSR(new_cpsr);
}

enum OperatingMode get_past_operating_mode(struct CPUState *state_in) {
    return state_in->CPSR.M;
}

enum OperatingMode get_operating_mode() {
    return get_past_operating_mode(&state);
}

void add_exception_flag(enum ExceptionFlag flag) {
    state.flags |= flag;
}

void remove_exception_flag(enum ExceptionFlag flag) {
    /*
    state.flags &= ~flag;
     */
    assert(false);
}

bool has_exception_flag(enum ExceptionFlag flag) {
    return state.flags & flag;
}

enum ExceptionFlag get_exception_flags() {
    return state.flags;
}

enum ExceptionFlag get_exception_flags_prev(struct CPUState *state_in) {
    return state_in->flags;
}


struct CPSR_Struct getCPSR() {
    return state.CPSR;
}

struct CPSR_Struct get_past_CPSR(struct CPUState state) {
    return state.CPSR;
}

void setCPSR(struct CPSR_Struct toSet) {
    state.CPSR = toSet;
}

void setSPSR(struct CPSR_Struct toSet) {
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
            fprintf(get_logfile(), "unknown operating mode\n");
            assert(false);
    }
}

void init_cpu(enum CommandLineFlags flags) {
    memset(&state, 0, sizeof(struct CPUState));
    state.decoded_valid = false;
    state.fetched_valid = false;
    state.CPSR.M = usr;
    if (flags & USE_THUMB) {
        state.CPSR.T = true;
    }
}

void init_system_control_coprocessor() {
//    state.systemControlCoprocessor.c0_main_id_register.implementor = 0x41;
//    state.systemControlCoprocessor.c0_main_id_register.variant_number = 0x0;
//    state.systemControlCoprocessor.c0_main_id_register.architecture = 0xF;
//    state.systemControlCoprocessor.c0_main_id_register.primary_part_number = 0x876;
//    state.systemControlCoprocessor.c0_main_id_register.revision = 0x7;
}

void init_coprocessors() {
    init_system_control_coprocessor();
}

union RawArmInstruction get_fetched_arm() {
    assert(!state.fetched_prefetch_aborted);
    uint32_t lValue = __bswap_32(__bswap_32(state.fetched_arm));
    return *((union RawArmInstruction *) &lValue);
}

union RawThumbInstruction get_fetched_thumb() {
    return *(union RawThumbInstruction *) &state.fetched_thumb;
}

union RawArmInstruction get_decoded_arm() {
    return *(union RawArmInstruction *) &state.decoded_arm;
}

union RawThumbInstruction get_decoded_thumb() {
    return *(union RawThumbInstruction *) &state.decoded_thumb;
}

bool fetched_valid() {
    return state.fetched_valid && !state.fetched_prefetch_aborted;
}

bool past_decoded_valid(struct CPUState state) {
    return state.decoded_valid && !state.decoded_prefetch_aborted;
}

bool decoded_valid() {
    return past_decoded_valid(state);
}

bool prefetch_aborted() {
    return state.decoded_prefetch_aborted;
}

//static Word curent = (uint32_t)-1;
void transfer_fetched_to_decoded_and_load_fetched() {

    if (get_mode() == THUMB) {
        state.decoded_thumb = state.fetched_thumb;
    } else if (get_mode() == ARM) {
        state.decoded_arm = state.fetched_arm;
    } else {
        assert(false);
    }
    state.decoded_valid = state.fetched_valid;
    state.decoded_prefetch_aborted = state.fetched_prefetch_aborted;
    if (get_mode() == THUMB) {
        if (memory_access_will_fail(get_word_from_register(PC_ADDRESS))) {
            state.fetched_prefetch_aborted = true;
            state.fetched_valid = true;
        } else {
            state.fetched_thumb = get_half_word_from_memory(get_word_from_register(PC_ADDRESS));
            state.fetched_valid = true;
        }
    } else if (get_mode() == ARM) {
        const union PhysicalAddress address = translate_address(get_word_from_register(PC_ADDRESS));
        if (memory_access_will_fail(*(uint32_t *) &address)) {
            state.fetched_prefetch_aborted = true;
            state.fetched_valid = true;
        } else {
            state.fetched_arm = get_word_from_memory(*(uint32_t *) &address);
            state.fetched_valid = true;
        }
    } else {
        assert(false);
    }
    uint32_t val = get_word_from_memory(get_word_from_register(PC_ADDRESS) - 8);
    struct ArmInstruction instruction = ARMfromRaw(*(union RawArmInstruction *) &val);
//    Word prev = curent;
    increment_pc(get_mode());
//    curent = get_word_from_register(PC_ADDRESS);
//    if (curent == prev) {
//        return ;
//    }
//    assert(curent != prev);//implies infinite loop.
}

void set_spsr_by_mode(struct CPSR_Struct cpsr_struct, enum OperatingMode mode) {
    switch (mode) {
        case usr:
            assert(false);
            break;
        case fiq:
            state.SPSR_fiq = cpsr_struct;
            break;
        case irq:
            state.SPSR_irq = cpsr_struct;
            break;
        case svc:
            state.SPSR_svc = cpsr_struct;
            break;
        case abt:
            state.SPSR_abt = cpsr_struct;
            break;
        case sys:
            assert(false);
            break;
        case und:
            state.SPSR_und = cpsr_struct;
            break;
    }
}

void invalidate_pipeline() {
    state.decoded_valid = false;
    state.fetched_valid = false;
    state.fetched_prefetch_aborted = false;
    state.decoded_prefetch_aborted = false;
}


/**
 * primarily used by bootloader
 * please use this function sparingly
 * @return
 */
struct CPUState *getCPUState() {
    return &state;
}



