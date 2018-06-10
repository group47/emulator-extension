//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_C3_DOMAIN_ACCESS_CONTROL_H
#define SRC_C3_DOMAIN_ACCESS_CONTROL_H

#include <stdint.h>

struct C3_domain_access_control_register {
   uint8_t d0 : 2;
   uint8_t d1 : 2;
   uint8_t d2 : 2;
   uint8_t d3 : 2;
   uint8_t d4 : 2;
   uint8_t d5 : 2;
   uint8_t d6 : 2;
   uint8_t d7 : 2;
   uint8_t d8 : 2;
   uint8_t d9 : 2;
   uint8_t d10 : 2;
   uint8_t d11 : 2;
   uint8_t d12 : 2;
   uint8_t d13 : 2;
   uint8_t d14 : 2;
   uint8_t d15 : 2;
}__attribute__((packed));

#endif //SRC_C3_DOMAIN_ACCESS_CONTROL_H
