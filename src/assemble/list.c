//
// Created by ryro on 2018/5/26.
//

#include <stdint.h>
#include <stdio.h>
#include "list.h"

struct ForwardRefereceList* initializeForwardReferenceList() {
    struct ForwardReferenceList* forwardReferenceList = malloc(sizeof(struct ForwardReferenceList*));
    forwardReferenceList->headLabel = malloc(sizeof(struct Label));
    forwardReferenceList->tailLabel = malloc(sizeof(struct Label));
    forwardReferenceList->headLabel->label = NULL;
    forwardReferenceList->headLabel->nextLabel = forwardReferenceList->tailLabel;
    forwardReferenceList->tailLabel->label = NULL;
}

struct ForwardReferenceLabel* findLabel(struct ForwardReferenceList* forwardReferenceList, char* label) {
    struct ForwardReferenceLabel* cur = forwardReferenceList->headLabel->nextLabel;
    while (cur != NULL) {
        if (strcmp(cur->label, label) == 0) {
            return cur;
        }
        cur = cur->nextLabel;
    }
    return NULL;
}

void addLabelAndAddress(struct ForwardReferenceList* forwardReferenceList, char* label, uint16_t offset) {
    struct ForwardReferenceLabel* newLabel = findLabel(forwardReferenceList, label);
    if (newLabel != NULL) {
        addAddress(newLabel, offset);
        return;
    }

    // Add the new element to the front of the list
    newLabel = malloc(sizeof(struct Label));
    memcpy(newLabel->label, label, strlen(label));

    newLabel->prevLabel = forwardReferenceList->headLabel;
    newLabel->nextLabel = forwardReferenceList->headLabel->nextLabel;

    forwardReferenceList->headLabel->nextLabel->prevLabel = newLabel;
    forwardReferenceList->headLabel->nextLabel = newLabel;
}

//todo free memory
void deleteLabel(struct ForwardReferenceLabel* label) {
    label->prevLabel->nextLabel = label->nextLabel;
    label->nextLabel->prevLabel = label->prevLabel;
}

void addAddress(struct ForwardReferenceLabel* label, uint32_t address) {
    struct Address* newAddress = malloc(sizeof(struct Address));
    newAddress->address = address;
    newAddress->nextAddress = label->addressList;
    label->addressList = newAddress;
}

void writeAddress(struct ForwardReferenceList* forwardReferenceList, FILE* fpOutput, char* labelString) {
    struct ForwardReferenceLabel* label = findLabel(forwardReferenceList, labelString);
    if (label == NULL) {
        assert(false);
    }

    struct Address* addressList = label->addressList;

    while (addressList != NULL) {
        binary_file_writer16(fpOutput, addressList->address);
        addressList = addressList->nextAddress;
    }
}


