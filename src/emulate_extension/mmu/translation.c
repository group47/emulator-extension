//
// Created by qs4617 on 12/06/18.
//

#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "translation.h"
#include "address.h"
#include "../coprocessor/system_control_coprocessor/mmu_control_and_configuration/c2_translation_table_base_control.h"
#include "../coprocessor/system_control_coprocessor/mmu_control_and_configuration/c2_translation_table_base1.h"
#include "../coprocessor/system_control_coprocessor/mmu_control_and_configuration/c2_translation_table_base0.h"
#include "first_level_descriptor.h"
#include "second_level_descriptor.h"
#include "../coprocessor/system_control_coprocessor/system_control_and_configuration/c1_control.h"

#include "../state/memory.h"
#include "../coprocessor/system_control_coprocessor/mmu_control_and_configuration/c3_context_id_register.h"


union First_level_descriptor get_first_level_descriptor(struct First_level_descriptor_address fd_address) {
    uint32_t fld = get_word_from_memory_raw(*((uint32_t *) &fd_address));
    return *(union First_level_descriptor *) &fld;
    //assert(false);
}

union Second_level_descriptor get_second_level_descriptor(struct Second_level_descriptor_address sd_address) {
    uint32_t sld = get_word_from_memory_raw(*((uint32_t *) &sd_address));
    return *(union Second_level_descriptor *) &sld;
    //assert(false);
}

#define FSCEMULTIPLIER (32*1024*1024)

union ModifiedVirtualAddress modify_virtual(VirtualAddress virtualAddress) {
    if (virtualAddress < FSCEMULTIPLIER) {
        const VirtualAddress mva = virtualAddress + FSCEMULTIPLIER * (get_c3_context_id_register().procid);
        return *(union ModifiedVirtualAddress *) &mva;
    } else {
        return *(union ModifiedVirtualAddress *) &virtualAddress;
    }
}


union PhysicalAddress translate_address(VirtualAddress virtualAddress) {
    return translation(modify_virtual(virtualAddress));
}


#define KILOBYTE 1024

enum TableType which_table(union ModifiedVirtualAddress modifiedVirtualAddress) {
    struct C2_translation_table_base_control_register ttbcr = get_translation_table_base_control_register();
    const uint32_t n = ttbcr.n;
    const uint32_t mva_as_word = *(uint32_t *) &modifiedVirtualAddress;
    assert(n >= 0 && n <= 7);
    if (n == 0) {
        return TABLE_0;
    } else {
        if ((mva_as_word >> (32 - n)) == 0) {//todo off by one?
            return TABLE_0;
        } else {
            return TABLE_1;
        }

    }
}


/**
 * calculates page size based on the N in the Translation Table Base Control Register
 * @return the page size for table base 0
 */
ByteAddress get_page_table_boundary_size_table_base_0() {

    /**
     * Values from table 3-56 in spec.
     *
     */
    switch (get_translation_table_base_control_register().n) {
        case 0:
            return 16 * KILOBYTE;
        case 1:
            return 8 * KILOBYTE;
        case 2:
            return 4 * KILOBYTE;
        case 3:
            return 2 * KILOBYTE;
        case 4:
            return KILOBYTE;
        case 5:
            return 512;
        case 6:
            return 256;
        case 7:
            return 128;
        default:
            assert(false);
    }
}

/**
 * gets the translation table address.
 * There are two translation tables., and the choice as to which one to use is determined as follows:
 * obtain N from from the translation table base control register
 * if n == 0: use table base 0 // backwards compatability with armv5
 * if n > 0:
 *      if virtual address[31:32-N](inclusive) == 0 use table base 0
 *      else: use table base register 1
 * @return
 */
ByteAddress get_translation_table_base(enum TableType table) {
    /*
     * Comment by Rory:
     * If N is zero, translation table base register0 is used for all addresses
     * If N is not zero, translation table base1 is used for os and memory mapped IO,
     * and translation table base0 is used processes in same virtuaal address space
     * Comment by Francis:
     * I'm not sure the above comment is the full story. My interpretation of the spec is that
     * there are two table base registers at all times, which can be used by either the os or
     * the user,however table base 1 is preferred for the os. The size of one can be set to zero if desired.
     * Additional comment by Francis:
     * this is not really needed anyway since its functionality has been made irrelevant by which_table and
     * calculate_first_level_descriptor_address.
     * */
//    bool one_base_for_all_address = !(*(struct C2_translation_table_base_control_register *)&ttbcr).n;

    // whether a process in virtual space or os is access the memory
//    bool is_os = true;
//    bool is_ap_enabled = !get_control_register().xp;

    // if is_ap_enabled, use the backwards-compatible format
    // if not, use the v6 format
//    if (!is_os || one_base_for_all_address) {
//        return get_word_translation_table_base_register0();
//    } else {
//        return get_word_translation_table_base_register1();
//    }

    if (table == TABLE_0) {
        return get_page_table_boundary_size_table_base_0() *
               (get_translation_table_base_register0().translation_table_base_0_unp_sbz
                       >> 9);// 9 is the isize of unp/spz
    } else {
        //here we can just return the value in the register, with the s/c bits masked, since the size of the table base does not change
        return get_word_translation_table_base_register1() & 0xff;

    }

    /**
     * when booting linux we should expect this function to return 0x4000, since that is where linux seems to set up
     * its table with our hardware.
     */

}


/**
 * this effectively implements diagram 6-11 from the arm1136 documentation
 * @return
 */
struct First_level_descriptor_address calculate_first_level_descriptor_address(
        union ModifiedVirtualAddress mva, enum TableType table) {
    const uint8_t N = get_translation_table_base_control_register().n;
    struct First_level_descriptor_address res;
    if (table == TABLE_0) {
        /**
         * we take the translation table base address and with first level table index from the mva
         */
        //todo chek this in debugger
        memset(&res, 0, sizeof(struct First_level_descriptor_address));
        uint32_t val = ((*(uint32_t *) &res) | get_word_translation_table_base_register0());
        res = *(struct First_level_descriptor_address *) &val;
        const uint32_t first_level_index = (mva.mvafd.first_level_table_index >> N);
        res.filler00 = 0;
        res.first_level_table_index = 0;
        res.first_level_table_index |= first_level_index;
    } else if (table == TABLE_1) {
        res.filler00 = 0;
        res.translation_base = get_translation_table_base_register1().translation_table_base_1;
        res.first_level_table_index = mva.mvafd.first_level_table_index;
    } else {
        assert(false);
    }
    return res;
}

union PhysicalAddress
MB_section_table_walk(union ModifiedVirtualAddress mva, union First_level_descriptor descriptor);

/**
 * effectively implements figure 6-14
 * @param mva
 * @param fd
 **** ttbr we can assume that the ttbr doesn't have offsets by n because this is a backwards
 * compatible format and because the documentation seems to completely forget about the -n after level 1 lookups. go figure.
 * @return
 */
union PhysicalAddress backwards_compatible_MB_section_table_walk(union ModifiedVirtualAddress mva,
                                                                 union First_level_descriptor fd);

union PhysicalAddress second_level_walk(union ModifiedVirtualAddress mva, union Second_level_descriptor descriptor);

// If you figured out how to get the mva, then you should be able to get the physical address
// I'm gonna assume it's all correct, there are many checks to be made
union PhysicalAddress translation(union ModifiedVirtualAddress mva) {
    const enum TableType tableType = which_table(mva);
//    const Word ttbr = get_translation_table_base(tableType);
    const bool backward_compatible_mode = get_control_register().xp == 0;
    const struct First_level_descriptor_address fd_address = calculate_first_level_descriptor_address(mva,
                                                                                                      tableType);
    const union First_level_descriptor fd = get_first_level_descriptor(fd_address);
    struct Second_level_descriptor_address sd_address;
    switch ((*(uint32_t *) &fd) & 0b11) {
        case 0b00:
            //todo: if instruction, prefetch abort
            //todo: if data, data abort
            assert(false);
            break;
        case 0b01: {
            union Second_level_descriptor sd;
            sd_address.filler00 = 0;
            sd_address.coarse_page_table_base_address = fd.v6_fd_coarse_page_table.coarse_page_table_base_address;
            sd_address.second_level_table_index = mva.mvasd1.second_level_table_index;
            sd = get_second_level_descriptor(sd_address);
            return second_level_walk(mva, sd);
        }
        case 0b10:
            //implementation is same for backwards compatible or otherwise.
            return MB_section_table_walk(mva, fd);
        case 0b11:
            assert(false);
            //todo: fault checking
            break;
        default:
            assert(false);
    }
}

union PhysicalAddress
MB_section_table_walk(union ModifiedVirtualAddress mva, const union First_level_descriptor descriptor) {
    union PhysicalAddress res;
    res.physicalAddress_1MB_section.section_base_address = descriptor.v6_fd_section.section_base_address;
    res.physicalAddress_1MB_section.section_index = mva.mvafd.section_index;
    return res;
}


union PhysicalAddress
second_level_large_page_walk(union ModifiedVirtualAddress mva, union Second_level_descriptor descriptor);

union PhysicalAddress
second_level_small_page_walk(union ModifiedVirtualAddress mva, union Second_level_descriptor descriptor);

union PhysicalAddress
second_level_extended_small_page(union ModifiedVirtualAddress mva, union Second_level_descriptor descriptor);

union PhysicalAddress second_level_walk(union ModifiedVirtualAddress mva, union Second_level_descriptor descriptor) {
    const bool backward_compatible_mode = get_control_register().xp == 0;
    switch (descriptor.backwards_sd_extended_small_page.filler10) {
        //todo set access fault flags
        case 0b00:
            assert(false);//todo translation fault
        case 0b01:
            //large page, should be backwards compatible without changes
            return second_level_large_page_walk(mva, descriptor);
        case 0b10:
            //small page if backwards compatible otherwise extended small page
            if (backward_compatible_mode) {
                return second_level_small_page_walk(mva, descriptor);
            } else {
                return second_level_extended_small_page(mva, descriptor);
            }
            break;
        case 0b11:
            assert(backward_compatible_mode);//todo what about non-backwards compatible
            //extended small page
            return second_level_extended_small_page(mva, descriptor);
        default:
            assert(false);
    }
}

union PhysicalAddress
second_level_extended_small_page(union ModifiedVirtualAddress mva, union Second_level_descriptor descriptor) {
    union PhysicalAddress result;
    result.physicalAddress_small_page.page_base_address = descriptor.backwards_sd_extended_small_page.extended_small_page_base_address;
    result.physicalAddress_small_page.page_index = mva.mvasd1.filler;
    return result;
}

union PhysicalAddress
second_level_small_page_walk(union ModifiedVirtualAddress mva, union Second_level_descriptor descriptor) {
    union PhysicalAddress result;
    result.physicalAddress_small_page.page_base_address = descriptor.backwards_sd_small_page.small_page_base_address;
    result.physicalAddress_small_page.page_index = mva.mvasd1.filler;//todo sketch, we need better packed structs
    return result;
}

union PhysicalAddress
second_level_large_page_walk(union ModifiedVirtualAddress mva, union Second_level_descriptor descriptor) {
    union PhysicalAddress result;
    result.physicalAddress_large_page.page_base_address = descriptor.v6_sd_large_page.large_page_base_address;
    result.physicalAddress_large_page.page_index = mva.mvasd2.page_index;
    return result;
}


//the below is wrong and should be deleted at a later date
///**
// * effectively implements figure 6-14
// * @param mva
// * @param fd
// **** ttbr we can assume that the ttbr doesn't have offsets by n because this is a backwards
// * compatible format and because the documentation seems to completely forget about the -n after level 1 lookups. go figure.
// * @return
// */
//union PhysicalAddress backwards_compatible_MB_section_table_walk(union ModifiedVirtualAddress mva,
//                                                                 union First_level_descriptor fd) {
//    struct Second_level_descriptor_address second_level_address;
//    second_level_address.filler00 = 00;
//    second_level_address.coarse_page_table_base_address = fd.backwards_fd_course_page_table.coarse_page_table_base_address;
//    second_level_address.second_level_table_index = mva.mvasd1.second_level_table_index;
//    union Second_level_descriptor sd = get_second_level_descriptor(second_level_address);
//    return second_level_walk(mva, sd);
//}
