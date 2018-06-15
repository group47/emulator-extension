//
// Created by qs4617 on 12/06/18.
//

#include <stdint.h>
#include <assert.h>
#include "translation.h"
#include "address.h"
#include "../coprocessor/system_control_coprocessor/mmu_control_and_configuration/c2_translation_table_base_control.h"
#include "../coprocessor/system_control_coprocessor/mmu_control_and_configuration/c2_translation_table_base1.h"
#include "../coprocessor/system_control_coprocessor/mmu_control_and_configuration/c2_translation_table_base0.h"
#include "first_level_descriptor.h"
#include "second_level_descriptor.h"
#include "../coprocessor/system_control_coprocessor/system_control_and_configuration/c1_control.h"

#include "../basic_typedefs.h"
#include "../state/memory.h"


union First_level_descriptor get_frist_level_descriptor(struct First_level_descriptor_address fd_address) {
    get_word_from_memory(*((uint32_t *)&fd_address));
    //assert(false);
}

union Second_level_descriptor get_second_level_descriptor(struct Second_level_descriptor_address sd_address) {
    get_word_from_memory(*((uint32_t *)&sd_address));
    //assert(false);
}


// If you figured out how to get the mva, then you should be able to get the physical address
// I'm gonna assume it's all correct, there are many checks to be mad
union PhysicalAddress translation(union ModifiedVirtualAddress mva) {
    Word ttbcr = get_word_translation_table_base_control_register();

    // If N is zero, translation table base register0 is used for all addresses
    // If N is not zero, translation table base1 is used for os and memory mapped IO,
    //   and translation table base0 is used processes in same virtuaal address space
    bool one_base_for_all_address = !(*(struct C2_translation_table_base_control_register *)&ttbcr).n;

    // whether a process in virtual space or os is access the memory
    bool is_os = true;
    bool is_ap_enabled = !get_word_control_register().xp;

    // if is_ap_enabled, use the backwards-compatible format
    // if not, use the v6 format


    Word ttbr;
    if (!is_os || one_base_for_all_address) {
        ttbr = get_word_translation_table_base_register0();
    } else {
        ttbr = get_word_translation_table_base_register1();
    }

    struct First_level_descriptor_address fd_address;
    fd_address.filler00 = 0;
    fd_address.first_level_table_index = mva.mvafd.first_level_table_index;
    fd_address.translation_base = (*(struct C2_translation_table_base_register0 *) &ttbr).translation_table_base_0_unp_sbz;

    union First_level_descriptor fd = get_frist_level_descriptor(fd_address);

    // todo: determine between v6 and backward compatible format
    union Second_level_descriptor sd;
    struct Second_level_descriptor_address sd_address;
    union PhysicalAddress physicalAddress;

    switch ((*(uint32_t*) &fd) & 0b11) {
        case 0b00:
            //todo: if instruction, prefetch abort
            //todo: if data, data abort
            assert(false);
            break;
        case 0b01:
            sd_address.filler00 = 0;
            sd_address.coarse_page_table_base_address = fd.v6_fd_coarse_page_table.coarse_page_table_base_address;
            sd_address.second_level_table_index = mva.mvasd1.second_level_table_index;
            sd = get_second_level_descriptor(sd_address);
            switch ((*(uint32_t *)&sd) & 0b11) {
                case 0b00:
                    //todo: fault checking
                    assert(false);
                    break;
                case 0b01:
                    physicalAddress.physicalAddress_large_page.page_base_address = sd.backwards_sd_large_page.large_page_base_address;
                    physicalAddress.physicalAddress_large_page.page_index = mva.mvasd2.page_index;
                    break;
                case 0b10:
                    physicalAddress.physicalAddress_small_page.page_index = mva.mvasd1.filler;
                    physicalAddress.physicalAddress_small_page.page_base_address = sd.backwards_sd_small_page.small_page_base_address;
                    break;
                case 0b11:
                    assert(false);
                    break;
                default:
                    assert(false);
            }
            break;
        case 0b10:
            physicalAddress.physicalAddress_1MB_section.section_index = mva.mvafd.first_level_table_index;
            // same for v6 and bgackward compatible format
            physicalAddress.physicalAddress_1MB_section.section_base_address = fd.v6_fd_section.section_base_address;
            break;
        case 0b11:
            assert(false);
            //todo: fault checking
            break;
        default:
            assert(false);
    }

    return physicalAddress;
}

