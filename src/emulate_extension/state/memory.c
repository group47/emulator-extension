//
// Created by francis on 6/1/18.
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "memory.h"
#include "emulator_state.h"

static struct Memory memory;



void init_memory(size_t size, enum MemoryFormat mode){
    memory.size = size;
    memory.mode = mode;
    memory.contents = calloc(size,sizeof(unsigned char));
    if(memory.contents == NULL){
        fprintf(stderr,"Can't allocated ram, exiting.. \n");
        exit(-1);
    }
}
void deallocate_memory(){
    free(memory.contents);
}


Word get_word_from_memory(Address address){
    assert (address % 4 == 0);
    if (address + 4 > memory.size) {
       add_exception_flag(DATA_ABORT);
       return 0;
    }

    Word word = 0;
    int i = 0;
    if (memory.mode == LITTLE_ENDIAN_) {
        while (i < 4) {
            word |= (((uint32_t)*(memory.contents + address + i)) << 8 * i);
            i++;
        }
    } else {
        while (i < 4) {
            word |= (((uint32_t)*(memory.contents + address + (3 - i))) << 8 * i);
            i++;
        }
    }
    return word;
}

uint64_t get_word_from_memory_sign_extended(Address address){
    assert (address % 4 == 0);
    if (address + 4 > memory.size) {
       add_exception_flag(DATA_ABORT);
       return 0;
    }
    uint64_t toExtend = *(memory.contents + address);
    return toExtend & 0x1 << 31 ? toExtend | 0xffff0000 : toExtend;
}

HalfWord get_half_word_from_memory(HalfWordAddress address){
    assert (address % 2 == 0);
    if (address + 2 > memory.size) {
       add_exception_flag(DATA_ABORT);
       return 0;
    }
    HalfWord halfWord;
    if (memory.mode == LITTLE_ENDIAN_) {
        halfWord = *(memory.contents + address);
        halfWord |= ((uint16_t) *(memory.contents + address + 1)) << 8;
    } else {
        halfWord = *(memory.contents + address + 1);
        halfWord |= ((uint16_t) *(memory.contents + address)) << 8;
    }
    return halfWord;
}

Word get_half_word_from_memory_sign_extended(HalfWordAddress address){
    assert (address % 2 == 0);
    if (address + 2 > memory.size) {
       add_exception_flag(DATA_ABORT);
       return 0;
    }
    HalfWord halfWord;
    if (memory.mode == LITTLE_ENDIAN_) {
        halfWord = *(memory.contents + address);
        halfWord |= ((uint16_t) *(memory.contents + address + 1)) << 8;
    } else {
        halfWord = *(memory.contents + address + 1);
        halfWord |= ((uint16_t) *(memory.contents + address)) << 8;
    }
    return half_word_to_word_sign_extend(halfWord);
}

Byte get_byte_from_memory(ByteAddress address){
    if (address > memory.size) {
        add_exception_flag(DATA_ABORT);
        return 0;
    }
    return (uint8_t)*(memory.contents + address);
}

Word get_byte_from_memory_sign_extended(ByteAddress address){
    if (address > memory.size) {
        add_exception_flag(DATA_ABORT);
        return 0;
    }
    return byte_to_word_sign_extend(*(memory.contents + address));
}

void set_word_from_memory(Address address, Word val){
    assert (address % 4 == 0);
    if (address + 4 > memory.size) {
        add_exception_flag(DATA_ABORT);
        return;
    }

    int i = 0;
    if (memory.mode == LITTLE_ENDIAN_) {
        while (i < 4) {
            *(memory.contents + address + i) =
                    (Byte) ((val & (0xFF << (8 * i))) >> (8*i));
            i++;
        }
    } else {
        while (i < 4) {
            *(memory.contents + address + (3 - i)) =
                    (Byte) ((val & (0xFF << (8 * i))) >> (8*i));
            i++;
        }
    }
}

void set_half_word_from_memory(HalfWordAddress address, HalfWord val){
    assert (address % 2 == 0);
    if (address + 2 > memory.size) {
        add_exception_flag(DATA_ABORT);
    }
    if (memory.mode == LITTLE_ENDIAN_) {
        *(memory.contents + address)  = (Byte) (val & 0x00ff);
        *(memory.contents + address + 1) = (Byte) (val & 0xff00);
    } else {
        *(memory.contents + address) = (Byte) (val & 0xff00);
        *(memory.contents + address + 1) = (Byte) (val & 0x00ff);
    }
}

void set_byte_from_memory(ByteAddress address, Byte val){
    if (address > memory.size) {
        add_exception_flag(DATA_ABORT);
    }
    *(memory.contents + address) = val;
}

//todo are these the same:

/*
uint32_t set_word_from_memory_sign_extended(Address address,Word val){

}
 */

void set_half_word_from_memory_sign_extended(HalfWordAddress address, HalfWord val){
    set_word_from_memory(address, half_word_to_word_sign_extend(val));
}

void set_byte_from_memory_sign_extended(ByteAddress address, Byte val){
    set_word_from_memory(address, byte_to_word_sign_extend(val));
}

Word byte_to_word_sign_extend(Byte byte) {
     return byte & (0x1 << 7) ? byte |= 0xfff0: byte;
}

Word half_word_to_word_sign_extend(HalfWord halfWord) {
    return halfWord & (0x1 << 15) ? halfWord |= 0xff00 : halfWord;
}

void set_mode(enum MemoryFormat mode){

}

