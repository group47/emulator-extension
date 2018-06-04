//
// Created by fpn17 on 03/06/18.
//


#include <stdio.h>
#include "entry_point.h"
#include "../main_loop.h"
#include "../state/emulator_state.h"


void main_emulation_entry_point(enum CommandLineFlags flags, FILE* fp) {
    init_cpu();
    init_memory(1024*1024*1024*sizeof(unsigned char),LITTLE_ENDIAN_);
    Word word;
    WordAddress i = 0;
    while(fread(&word,sizeof(Word),1,fp)){
        set_word_from_memory(4*i,word);
    }
    main_loop(flags);
    deallocate_memory();

}

