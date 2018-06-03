//
// Created by francis on 6/2/18.
//

#include "static_asserts.h"
/**
 * these assertions act as basic sanity checks on struct declarations.
 * If this where D I would use static asserts for this.
 */
void do_asserts(void){
    assert(sizeof(struct DataProcessingInstruction) == sizeof(uint32_t));
    assert(sizeof(struct DataProcessingInstruction) == sizeof(Word));
    assert(sizeof(struct AddSubtractInstruction) == sizeof(HalfWord));
    assert(sizeof(struct AddSubtractInstruction) == sizeof(uint16_t));
}
