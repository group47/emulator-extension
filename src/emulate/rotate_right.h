//
// Created by francis on 5/30/18.
//

#ifndef SRC_ROTATE_RIGHT_H
#define SRC_ROTATE_RIGHT_H

#include <stdint.h>

uint32_t rotr(uint32_t x, uint32_t n)
{
  return (x>>n) | (x<<(32-n));
}
#endif //SRC_ROTATE_RIGHT_H
