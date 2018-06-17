//
// Created by ryro on 2018/5/26.
//

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "symbol_table.h"
#include "tokenizer.h"
#include "utility.h"
#include "extra_data.h"
#include "binary_file_writer.h"
#include "assemble.h"

int main(int argc, char **argv) {

    if (argc != 3) {
        fprintf(stderr,
                "the end of the world has come, or you entered the wrong number of arguments");
        return -100000;
    }

    const char *sourceFileName = argv[1];
    const char *outputFileName = argv[2];

    FILE *fpSource = fopen(sourceFileName, "r");
    FILE *fpOutput = fopen(outputFileName, "w");

    if (fpSource == NULL) {
        fprintf(stderr,
                "the end of the world has come, or you entered the wrong source filename\n");
    }

    if (fpOutput == NULL) {
        fprintf(stderr,
                "the end of the world has come, or you entered the wrong output filename\n");
    }

    char *instruction = NULL;
    size_t instructionLength = 0;
    struct SymbolTable instructionCode;
    initializeInstructionCodeTable(&instructionCode);
    struct SymbolTable labelAddress;
    memset(&labelAddress, 0, sizeof(struct SymbolTable));

    uint16_t offset = 0;
    uint16_t current_address = 0;
    // build labelAddress table
    struct Token newToken;
    while (getline(&instruction, &instructionLength, fpSource) != -1) {//todo alloc
        initializeToken(&newToken);
        struct Instruction token = tokenizer(&newToken, instruction, &instructionCode, &labelAddress,
                                             current_address);//todo make this faster kuyg
        if (token.type == INVALID) {
            if (secondToLastCharIs(instruction, ':')) {
                char colonRemoved[100];
                int i = 0;
                while (i < strlen(instruction) - 2) {
                    colonRemoved[i] = instruction[i];
                    ++i;
                }
                colonRemoved[i] = '\0';
                addLabel(&labelAddress, colonRemoved, current_address);
            }
        } else {
            current_address++;
        }
    }
    fclose(fpSource);
    set_extra_data_location(current_address);
    FILE *fpSource2 = fopen(sourceFileName, "r");
    current_address = 0;
    while (getline(&instruction, &instructionLength, fpSource2) != -1) {
        initializeToken(&newToken);
        instruction[strlen(instruction)] = '\0';
        struct Instruction token = tokenizer(&newToken, instruction, &instructionCode, &labelAddress, current_address);

        if (token.type != INVALID) {
            binary_file_writer32(fpOutput, *(uint32_t *) &token.rawInstruction);
            fflush(fpOutput);
            current_address++;
        }

        offset += 4;
    }

    write_extra_data(fpOutput);

    free_symbol_table(instructionCode);
    free_symbol_table(labelAddress);

    fclose(fpSource2);
    fclose(fpOutput);
    return 0;
}

void free_symbol_table(struct SymbolTable table) {
    for (int i = 0; i < table.size; ++i) {
        if (table.entries[i].entryType == INSTRUCTION_INFO) {
            char *ptr = table.entries[i].rawEntry.instructionInfo.mnemonics;
            if (ptr != NULL)
                free(ptr);
        } else if (table.entries[i].entryType == LABEL) {
            char *ptr = table.entries[i].rawEntry.label.label;
            if (ptr != NULL)
                free(ptr);
        } else {
            assert(false);
        }
    }

}

bool is_label(char *instruction) {
    int i = 0;
    while (instruction[i] != '\0') {
        if (instruction[i] == ':')
            return true;
        i++;
    }
    return false;

}


