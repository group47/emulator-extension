//
// Created by francis on 5/30/18.
//

#include "rotate_right.h"
uint32_t rotr(uint32_t x, uint32_t n)
{
return (x>>n) | (x<<(32-n));
}
