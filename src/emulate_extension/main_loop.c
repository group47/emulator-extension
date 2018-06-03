//
// Created by fpn17 on 03/06/18.
//

#include <stdbool.h>
#include "main_loop.h"
#include "util/entry_point.h"
#include "state/emulator_state.h"
#include "state/exception.h"


void main_loop(enum CommandLineFlags flags){

    init_cpu();
    bool decoded_valid = false;
    bool prefetch_valid = false;

    while(true){
        //check if exceptions
        if(has_exceptions()){
            //exception handler
        }

        //
    }

}