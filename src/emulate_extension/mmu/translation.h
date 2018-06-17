//
// Created by qs4617 on 12/06/18.
//

#ifndef SRC_TRANSLATION_H
#define SRC_TRANSLATION_H

typedef uint32_t VirtualAddress;
enum TableType{
  TABLE_0,TABLE_1
};

union PhysicalAddress translate_address(VirtualAddress virtualAddress);

#endif //SRC_TRANSLATION_H
