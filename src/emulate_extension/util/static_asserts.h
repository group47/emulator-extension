//
// Created by francis on 6/2/18.
//

#ifndef SRC_STATIC_ASSERTS_H
#define SRC_STATIC_ASSERTS_H

#include <assert.h>
#include "../instructions/arm/data_processing.h"
#include "../instructions/thumb/add_subtract.h"
/**
 * these assertions act as basic sanity checks on struct declarations.
 * If this where D I would use static asserts for this.
 */
void do_asserts(){
  assert(sizeof(struct DataProcessingInstruction) == sizeof(uint32_t));
  assert(sizeof(struct DataProcessingInstruction) == sizeof(Word));
  assert(sizeof(struct AddSubtractInstruction) == sizeof(HalfWord));
  assert(sizeof(struct AddSubtractInstruction) == sizeof(uint16_t));
}

#endif //SRC_STATIC_ASSERTS_H
