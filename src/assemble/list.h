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


//const int MAX_FORWARD_REFERENCE_LIST_LENGTH = 200;
//const int MAX_ADDRESS_LIST_LENGTH = 200;

struct ForwardReferenceList {
    struct ForwardReferenceLabel* headLabel;
    struct ForwardReferenceLabel* tailLabel;
};

struct ForwardReferenceLabel {
    char* label;
    struct ForwardReferenceLabel* prevLabel;
    struct ForwardReferenceLabel* nextLabel;
    struct Address* addressList;
};

struct Address {
    uint32_t address;
    struct Label* nextAddress;
};

struct ForwardRefereceList* initializeForwardReferenceList();
struct ForwardReferenceLabel* findLabel(struct ForwardReferenceList*, char*);
void addLabelAndAddress(struct ForwardReferenceList*, char*, uint16_t);
void deleteLabel(struct ForwardReferenceLabel*);
void addAddress(struct ForwardReferenceLabel*, uint32_t);
void writeAddress(struct ForwardReferenceList*, FILE*, char*);



/*

struct ForwardReferenceList {
    struct ForwardReferenceLabel* labelList;

};

struct Address {
    uint32_t address;
};

struct ForwardReferenceLabel {
    char* label;
};

struct ForwardRefereceList* initializeForwardReferenceList() {
    struct ForwardReferenceList* forwardReferenceList = malloc(sizeof(struct ForwardReferenceList));
    forwardReferenceList->labelList = malloc(MAX_FORWARD_REFERENCE_LIST_LENGTH*sizeof(struct ForwardReferenceLabel));
}

struct ForwardReferenceLabel findLabel();
 */




#endif //ASSEMBLE_LIST_H
