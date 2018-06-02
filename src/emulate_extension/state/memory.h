//
// Created by francis on 6/1/18.
//

#ifndef SRC_MEMORY_H
#define SRC_MEMORY_H


#include <stdbool.h>
#include "../basic_typedefs.h"


enum MemoryFormat {
  BIG_ENDIAN_,LITTLE_ENDIAN_// underscores are placed after names, becuase BIG_ENDIAN is used internally in libc
};

struct Memory {
  Word* contents;
  uint32_t size;
  enum MemoryFormat mode;
};

// todo: add memory checks here for out of bound
void init_memory(uint32_t size, enum MemoryFormat mode);

Word get_word_from_memory(Address address);
uint64_t get_word_from_memory_sign_extended(Address address);
HalfWord get_half_word_from_memory(HalfWordAddress address);
Word get_half_word_from_memory_sign_extended(HalfWordAddress address);
Byte get_byte_from_memory(ByteAddress address);
Word get_byte_from_memory_sign_extended(ByteAddress address);

uint32_t set_word_from_memory(Address address,Word val);
uint32_t set_half_word_from_memory(HalfWordAddress address,HalfWord val);
uint32_t set_byte_from_memory(ByteAddress address,Byte val);

//todo are these the same:
uint32_t set_word_from_memory_sign_extended(Address address,Word val);
uint32_t set_half_word_from_memory_sign_extended(HalfWordAddress address,HalfWord val);
uint32_t set_byte_from_memory_sign_extended(ByteAddress address,Byte val);

void set_mode(enum MemoryFormat mode);


#endif //SRC_MEMORY_H
