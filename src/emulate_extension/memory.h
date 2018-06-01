//
// Created by francis on 6/1/18.
//

#ifndef SRC_MEMORY_H
#define SRC_MEMORY_H


#include <stdint-gcc.h>

typedef uint32_t ByteAddress;
typedef uint32_t HalfWordAddress;
typedef uint32_t WordAddress;
typedef uint32_t Word;
typedef uint16_t HalfWord;
typedef uint8_t  Byte;
typedef ByteAddress Address;

enum Mode{
  BIG_ENDIAN,LITTLE_ENDIAN
};

struct Memory {
  uint32_t* contents;
  uint32_t size;
  enum Mode mode;
};

void init_memory(uint32_t size, enum Mode mode);

uint32_t get_word_from_memory(Address address);
uint32_t get_half_word_from_memory(HalfWordAddress address);
uint32_t get_byte_from_memory(ByteAddress address);

uint32_t set_word_from_memory(Address address,Word val);
uint32_t set_half_word_from_memory(HalfWordAddress address,HalfWord val);
uint32_t set_byte_from_memory(ByteAddress address,Address val);


#endif //SRC_MEMORY_H
