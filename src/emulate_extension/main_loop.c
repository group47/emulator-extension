//
// Created by fpn17 on 03/06/18.
//

#include <stdbool.h>
#include <assert.h>
#include "main_loop.h"
#include "state/emulator_state.h"
#include "state/exception.h"
#include "instructions/thumb/thumb_instruction.h"


void main_loop(enum CommandLineFlags flags) {
    uint64_t master_instruction_counter = 0;
    while (true) {

        if (decoded_valid()) {
            union RawArmInstruction instruction = get_decoded_arm();
            if ((flags & TERMINATE_ON__ZERO) && ((*(uint32_t *) &instruction) == 0)) {
                return;
            }
            if ((flags & TERMINATE_AFTER_200) && master_instruction_counter == 200) {
                return;
            }
            enum ExecutionExitCode exitCode;
            if (get_mode() == ARM) {
                exitCode = execute_arm_instruction(ARMfromRaw(get_decoded_arm()));
            } else if (get_mode() == THUMB) {
                exitCode = execute_thumb_instruction(ThumbFromRaw(get_decoded_thumb()));
            } else {
                assert(false);
            }
            if (exitCode == BRANCH) {
                invalidate_pipeline();
            }
            master_instruction_counter++;
        } else if (prefetch_aborted()) {
            add_exception_flag(PREFETCH_ABORT);
        }

        //check if exceptions
        if (has_exceptions()) {
            handle_exception();
        }

        //this function is used so that the cpu isn't in an inconsistent state in this loop
        transfer_fetched_to_decoded_and_load_fetched();


        if (flags & MEMORY) {
            print_memory();
        }
        if (flags & DEBUG_PRINT_REGISTER) {
            print_registers(flags);
        }
    }

}

