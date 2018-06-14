//
// Created by francis on 6/1/18.
//

#ifndef SRC_MEMORY_H
#define SRC_MEMORY_H


#include <stdbool.h>
#include <stddef.h>
#include "../basic_typedefs.h"

#define MEMORY_OFFSET 0x00000000

enum MemoryFormat {
    BIG_ENDIAN_, LITTLE_ENDIAN_// underscores are placed after names, becuase BIG_ENDIAN is used internally in libc
};

struct Memory {
    Byte *contents;
    size_t size;
    enum MemoryFormat mode;
};

// todo: add memory checks here for out of bound
void init_memory(size_t size, enum MemoryFormat mode);

Word get_word_from_memory(ByteAddress address);

uint64_t get_word_from_memory_sign_extended(ByteAddress address);

HalfWord get_half_word_from_memory(ByteAddress address);

Word get_half_word_from_memory_sign_extended(ByteAddress address);

Byte get_byte_from_memory(ByteAddress address);

Word get_byte_from_memory_sign_extended(ByteAddress address);

void set_word_in_memory(ByteAddress address, Word val);

void set_half_word_in_memory(ByteAddress address, HalfWord val);

void set_byte_in_memory(ByteAddress address, Byte val);

//todo are these the same:
uint32_t set_word_from_memory_sign_extended(ByteAddress address, Word val);

void set_half_word_in_memory_sign_extended(ByteAddress address, HalfWord val);

void set_byte_in_memory_sign_extended(ByteAddress address, Byte val);

Word byte_to_word_sign_extend(Byte byte);

Word half_word_to_word_sign_extend(HalfWord halfWord);

void set_mode(enum MemoryFormat mode);

void deallocate_memory();

void print_memory();

bool memory_access_will_fail(ByteAddress memoryAddress);

void set_memory(struct Memory memory1);
#endif //SRC_MEMORY_H
