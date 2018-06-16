//
// Created by qs4617 on 07/06/18.
//

#ifndef SRC_CONTROL_H
#define SRC_CONTROL_H

#include <stdbool.h>
#include "../../../instructions/arm/coprocessor_data_transfers.h"
#include "../../../basic_typedefs.h"
#include "../../../util/common_enums.h"
#include "../../../instructions/arm/coprocessor_register_transfer.h"

enum ExecutionExitCode execute_control_register(struct CoprocessorRegisterTransferInstruction);

struct C1_control_register {
    bool m : 1;
    bool a : 1;
    bool c : 1;
    bool w : 1;
    uint8_t sbo : 3;
    bool b : 1;
    bool s : 1;
    bool r : 1;
    bool f : 1;
    bool z : 1;
    bool i : 1;
    bool v : 1;
    bool rr : 1;
    bool l4 : 1;
    bool dt : 1;
    bool sbz_size1_position17 : 1;
    bool it : 1;
    uint8_t sbz_size2_position20 : 2;
    bool fi : 1;
    bool u : 1;
    bool xp : 1;
    bool ve : 1;
    bool ee : 1;
    uint8_t sbz_size2_position_27 : 2;
    bool tr : 1;
    bool fa : 1;
    uint8_t sbz_size2_position_31 : 2;
}__attribute__((packed));
#endif //SRC_CONTROL_H

struct C1_control_register get_word_control_register();

void set_word_control_register(Word);

bool is_mmu_enabled();

void init_c1_control_register();