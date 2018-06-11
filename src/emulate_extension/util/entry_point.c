//
// Created by fpn17 on 03/06/18.
//


#include <stdio.h>
#include "entry_point.h"
#include "../main_loop.h"
#include "../state/emulator_state.h"

static FILE *logfile;


void main_emulation_entry_point(enum CommandLineFlags flags, FILE *fp, FILE *logfile_) {
    init_cpu(flags);
    init_coprocessors();
    init_memory(1024 * 1024 * 1024 * sizeof(unsigned char), LITTLE_ENDIAN_);
    Word word;
    ByteAddress i = 0;
    while (fread(&word, sizeof(Word), 1, fp)) {
        set_word_in_memory(4 * i, word);
        i++;
    }
    logfile = logfile_;
    main_loop(flags);
    deallocate_memory();

}

FILE *get_logfile() {
    return logfile == NULL ? stderr : logfile;
}