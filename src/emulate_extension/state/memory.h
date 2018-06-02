//
// Created by francis on 6/1/18.
//

#ifndef SRC_MEMORY_H
#define SRC_MEMORY_H


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

uint32_t get_word_from_memory(Address address);
uint32_t get_half_word_from_memory(HalfWordAddress address);
uint32_t get_byte_from_memory(ByteAddress address);

uint32_t set_word_from_memory(Address address,Word val);
uint32_t set_half_word_from_memory(HalfWordAddress address,HalfWord val);
uint32_t set_byte_from_memory(ByteAddress address,Address val);

void set_mode(enum MemoryFormat mode);


#endif //SRC_MEMORY_H
