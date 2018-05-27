//
// Created by ryro on 2018/5/26.
//

#ifndef ASSEMBLE_LIST_H
#define ASSEMBLE_LIST_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_LABEL_LENGTH = 511

void writeAddress(struct List* list, char* label, uint16_t address);
bool findLabel(struct List* list, char* label);
void addAddress(struct List* list, char* label);
void addNode(struct List* list, struct Node* node);
void deleteNode(struct List* list);


struct List {
    struct Node* head;
    struct Node* tail;
};

struct Node {
    union NodeVal;
    struct Node* nextNode;
};

struct Label {
    uint8_t* label: 32;
};

struct Address {
    uint16_t address : 16;
    uint16_t filler : 16;
};

union NodeVal {
    struct Label;
    struct Address;
};






#endif //ASSEMBLE_LIST_H
