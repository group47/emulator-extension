//
// Created by francis on 6/1/18.
//

#include <assert.h>
#include "memory.h"
#include "emulator_state.h"

static struct Memory memory;

void init_memory(uint32_t size, enum MemoryFormat mode);

Word get_word_from_memory(Address address){
    assert(false);
}
uint64_t get_word_from_memory_sign_extended(Address address){
    assert(false);
}
HalfWord get_half_word_from_memory(HalfWordAddress address){
    assert(false);
}
Word get_half_word_from_memory_sign_extended(HalfWordAddress address){
    assert(false);
}
Byte get_byte_from_memory(ByteAddress address){
    /*
    if (address > memory.size) {
        add_exception_flag(DATA_ABORT);
        return 0;
    }
    return (uint8_t)*(memory.contents + address / 4);
     */
    assert(false);
}
Word get_byte_from_memory_sign_extended(ByteAddress address){
    /*
    if (address > memory.size) {
        add_exception_flag(DATA_ABORT);
        return 0;
    }
    uint32_t toExtend = *(memory.contents + address / 4);
    return toExtend & 0x1 << 7 ? toExtend |= 0xff0 : toExtend;
     */
    assert(false);
}

uint32_t set_word_from_memory(Address address,Word val){

    assert(false);
}
uint32_t set_half_word_from_memory(HalfWordAddress address,HalfWord val){
    assert(false);
}
uint32_t set_byte_from_memory(ByteAddress address,Byte val){
    assert(false);
}

//todo are these the same:
uint32_t set_word_from_memory_sign_extended(Address address,Word val){
    assert(false);
}
uint32_t set_half_word_from_memory_sign_extended(HalfWordAddress address,HalfWord val){
    assert(false);
}
uint32_t set_byte_from_memory_sign_extended(ByteAddress address,Byte val){
    assert(false);
}

void set_mode(enum MemoryFormat mode){
    assert(false);
}

