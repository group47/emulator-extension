//
// Created by ryro on 2018/5/26.
//

#include <stdint.h>
#include <stdio.h>
#include "list.h"


struct ForwardRefereceList* initializeForwardReferenceList() {
    struct ForwardReferenceList* forwardReferenceList = malloc(sizeof(struct ForwardReferenceList));
    forwardReferenceList->size = 0;
}

struct ForwardReferenceLabel* findLabel(struct ForwardReferenceList* forwardReferenceList, char* label) {
    for (int i = 0; i < forwardReferenceList->size; i++) {
        if (strcmp(forwardReferenceList->labelList[i].label, label) == 0) {
            return &forwardReferenceList->labelList[i];
        }
    }
}

void addForwardReferenceLabel(struct ForwardReferenceList* forwardReferenceList, char* label) {
    if (findLabel(forwardReferenceList, label) == NULL) {
        memcpy(forwardReferenceList->labelList[forwardReferenceList->size].label, label, sizeof(label));
        forwardReferenceList->size++;
    }
}

void addAddress(struct ForwardReferenceList* forwardReferenceList, char* label, uint32_t address) {
    struct ForwardReferenceLabel* forwardReferenceLabel = findLabel(forwardReferenceList, label);
    if (forwardReferenceLabel != NULL) {
        forwardReferenceLabel->addressList[forwardReferenceLabel->size] = address;
        forwardReferenceLabel->size++;
    }
}