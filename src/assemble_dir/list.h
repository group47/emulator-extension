//
// Created by ryro on 2018/5/26.
//

#ifndef ASSEMBLE_LIST_H
#define ASSEMBLE_LIST_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "binary_file_writer.h"


#define MAX_FORWARD_REFERENCE_LIST_LENGTH 200
#define  MAX_ADDRESS_LIST_LENGTH  200

struct ForwardReferenceLabel {
    char* label[511];
    uint32_t* addressList[MAX_ADDRESS_LIST_LENGTH];
    size_t size;
};


struct ForwardReferenceList {
    struct ForwardReferenceLabel labelList[MAX_FORWARD_REFERENCE_LIST_LENGTH];
    size_t size;

};



struct ForwardReferenceLabel* findLabel(struct ForwardReferenceList*, char*);
void addForwardReferenceLabel(struct ForwardReferenceList*, char*);
void addAddress(struct ForwardReferenceList*, char*, uint32_t);




#endif //ASSEMBLE_LIST_H
