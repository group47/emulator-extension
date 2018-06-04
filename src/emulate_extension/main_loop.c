//
// Created by fpn17 on 03/06/18.
//

#include <stdbool.h>
#include <assert.h>
#include "main_loop.h"
#include "util/entry_point.h"
#include "state/emulator_state.h"
#include "state/exception.h"
#include "instructions/arm/arm_instruction.h"
#include "instructions/thumb/thumb_instruction.h"


void main_loop(enum CommandLineFlags flags){
    __uint128_t master_instruction_counter = 0;
    while(true){

        if(fetched_valid()){
            union RawArmInstruction instruction = get_fetched_arm();
            if((flags & TERMINATE_ON__ZERO) && ((*(uint32_t *)&instruction) == 0)){
                return;
            }
            if(flags & TERMINATE_AFTER_200 && master_instruction_counter == 200){
                return;
            }
            if(get_mode() == ARM){
                const enum ExecutionExitCode exitCode = execute_arm_instruction(ARMfromRaw(get_fetched_arm()));
            }
            else if(get_mode() == THUMB){
                const enum ExecutionExitCode exitCode = execute_thumb_instruction(ThumbFromRaw(get_fetched_thumb()));
            } else {
                assert(false);
            }
            master_instruction_counter++;
        }

        //check if exceptions
        if(has_exceptions()){
            handle_exception();
        }

        //this function is used so that the cpu isn't in an inconsistent state in this loop
        transfer_fetched_to_decoded_and_load_fetched();

        if(flags & DEBUG_PRINT_REGISTER){
            print_registers();
        }
    }

}