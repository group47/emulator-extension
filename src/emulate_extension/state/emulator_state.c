//
// Created by francis on 6/1/18.
//
#include <assert.h>
#include <stdio.h>
#include <memory.h>
#include <endian.h>
#include "../instructions/thumb/thumb_instruction.h"
#include "exception.h"
#include "../util/entry_point.h"
#include "emulator_state.h"
#include "../emulator_main.h"

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

Word get_set_word_from_register(RegisterAddress address, bool set, Word val) {
    if (has_exceptions()) {
        return 0;//don't allow register access if exceptions raised
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
            if (address > max_valid_register_address) {
                if (address == CPSR_ADDRESS) {
                    assert(!set);
                    return get_set_register((Word *) &state.CPSR, set, val);
                } else if (address == PC_ADDRESS) {
                    return get_set_register(&state.general_registers[address], set, val);
                } else if (address == LR_ADDRESS) {
                    return get_set_register(&state.general_registers[address], set, val);
                } else if (address == SP_ADDRESS) {
                    return get_set_register(&state.general_registers[address], set, val);
                } else {
                    assert(false);
                }
            } else {
                return get_set_register(&state.general_registers[address], set, val);
            }
            break;
        case fiq:
            if (address > max_unbanked_address_fiq) {
                if (address <= max_banked_address_fiq) {
                    return get_set_register(&state.fiq_banked[address - NUM_FIQ_UNBANKED], set, val);
                } else {
                    if (address == PC_ADDRESS) {
                        return get_set_register(&state.general_registers[address], set, val);
                    } else if (address == CPSR_ADDRESS) {
                        return get_set_register((Word *) &state.CPSR, set, val);
                    } else if (address == SPSR_ADDRESS) {
                        assert(false);//normal instructions should not need to access the spsr. use get spsrt for internal access.
                    } else {
                        assert(false);
                    }
                }
            } else {
                return get_set_register(&state.general_registers[address], set, val);
            }
            break;
        case irq:
        case svc:
        case und:
        case abt:
            if (address <= max_unbanked_address_other) {
                return get_set_register(&state.general_registers[address], set, val);
            } else if (address <= max_banked_address_other) {
                switch (get_operating_mode()) {
                    case irq:
                        banked_array = state.irq_banked;
                        break;
                    case svc:
                        banked_array = state.svc_banked;
                        break;
                    case abt:
                        banked_array = state.abt_banked;
                        break;
                    case und:
                        banked_array = state.und_banked;
                        break;
                    default:
                        assert(false);
                }
                return get_set_register(&banked_array[address - max_unbanked_address_other], set, val);
            } else if (address == PC_ADDRESS || address == CPSR_ADDRESS) {
                if (get_mode() == THUMB) {
                    assert(address == PC_ADDRESS);
                }
                return get_set_register(&state.general_registers[address], set, val);
            } else {
                assert(false);
            }
        default:
            assert(false);
    }
}

Word get_word_from_register(RegisterAddress address) {
    return get_set_word_from_register(address, false, -1);
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
    get_set_word_from_register(address, true, val);
}

void change_mode(enum Mode newMode) {
    assert(false);
}//make sure to trash pipeline and that this is part of spsr


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
            fprintf(get_logfile(), "unknown operating mode\n");
            assert(false);
    }
    */
    assert(false);
}

void set_operating_mode(enum OperatingMode newOperatingMode) {
    struct CPSR_Struct new_cpsr = getCPSR();
    new_cpsr.M = newOperatingMode;
    setCPSR(new_cpsr);
}

enum OperatingMode get_operating_mode() {
    return state.CPSR.M;
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

struct CPSR_Struct getCPSR() {
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

bool decoded_valid() {
    return state.decoded_valid && !state.decoded_prefetch_aborted;
}

bool prefetch_aborted() {
    return state.decoded_prefetch_aborted;
}

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
        if (memory_access_will_fail(get_word_from_register(PC_ADDRESS))) {
            state.fetched_prefetch_aborted = true;
            state.fetched_valid = true;
        } else {
            state.fetched_arm = get_word_from_memory(get_word_from_register(PC_ADDRESS));
            state.fetched_valid = true;
        }
    } else {
        assert(false);
    }
    if (get_mode() == ARM) {
        set_word_in_register(PC_ADDRESS, get_word_from_register(PC_ADDRESS) +
                                         sizeof(union RawArmInstruction) / sizeof(unsigned char));
    } else if (get_mode() == THUMB) {
        set_word_in_register(PC_ADDRESS, get_word_from_register(PC_ADDRESS) +
                                         sizeof(union RawThumbInstruction) / sizeof(unsigned char));
    }
}

void print_registers(enum CommandLineFlags flags) {
    if (flags & USE_THUMB) {
        for (uint8_t i = 0; i < 8; ++i) {
            fprintf(get_logfile(), "r%u             0x%x  %u\n", i, get_word_from_register(i),
                    get_word_from_register(i));
        }
        for (uint8_t i = 8; i < 13; ++i) {
            fprintf(get_logfile(), "r%u            0x%x  %u\n", i, 0, 0);
        }
        fprintf(get_logfile(), "sp             0x%x  %u\n",
                (uint32_t) (get_word_from_register(SP_ADDRESS) + get_sp_offset()),
                (uint32_t) (get_word_from_register(SP_ADDRESS) + get_sp_offset()));
        fprintf(get_logfile(), "lr             0x%x  %u\n", 0, 0);
        fprintf(get_logfile(), "pc             0x%x  %u\n",
                (uint32_t) (get_word_from_register(PC_ADDRESS) + get_pc_offset()),
                (uint32_t) (get_word_from_register(PC_ADDRESS) + get_pc_offset()));
        fprintf(get_logfile(), "cpsr           0x%x  %d\n", getCPSR(), getCPSR());
        if (get_operating_mode() == usr || get_operating_mode() == sys) {
            fprintf(get_logfile(), "fpscr          0x%o  %x\n", 0, 0);
        } else {
            fprintf(get_logfile(), "fpscr          0x%o  %x\n", get_spsr(), get_spsr());
        }
        fprintf(get_logfile(), "=> \n\n");
    } else {
        for (uint8_t i = 0; i < 10; ++i) {
            fprintf(get_logfile(), "r%u             0x%x  %u\n", i, get_word_from_register(i),
                    get_word_from_register(i));
        }
        for (uint8_t i = 10; i < 13; ++i) {
            fprintf(get_logfile(), "r%u            0x%x  %u\n", i, get_word_from_register(i),
                    get_word_from_register(i));
        }
        fprintf(get_logfile(), "sp             0x%x  %u\n",
                (uint32_t) (get_word_from_register(SP_ADDRESS) + get_sp_offset()),
                (uint32_t) (get_word_from_register(SP_ADDRESS) + get_sp_offset()));
        fprintf(get_logfile(), "lr             0x%x  %u\n", get_word_from_register(LR_ADDRESS),
                get_word_from_register(LR_ADDRESS));
        fprintf(get_logfile(), "pc             0x%x  %u\n",
                (uint32_t) (get_word_from_register(PC_ADDRESS) + get_pc_offset()),
                (uint32_t) (get_word_from_register(PC_ADDRESS) + get_pc_offset()));
        fprintf(get_logfile(), "cpsr           0x%x  %d\n", getCPSR(), getCPSR());
        if (get_operating_mode() == usr || get_operating_mode() == sys) {
            fprintf(get_logfile(), "fpscr          0x%o  %x\n", 0, 0);
        } else {
            fprintf(get_logfile(), "fpscr          0x%o  %x\n", get_spsr(), get_spsr());
        }
        fprintf(get_logfile(), "=> \n\n");
    }

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
