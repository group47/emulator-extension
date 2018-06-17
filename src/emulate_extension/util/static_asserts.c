//
// Created by francis on 6/2/18.
//

#include "static_asserts.h"
#include "../instructions/arm/arm_instruction.h"
#include "../instructions/thumb/thumb_instruction.h"
#include "../mmu/address.h"
#include "../mmu/first_level_descriptor.h"

/**
 * these assertions act as basic sanity checks on struct declarations.
 * If this where D I would use static asserts for this.
 */
void do_asserts(void) {
    assert(sizeof(struct DataProcessingInstruction) == sizeof(uint32_t));
    assert(sizeof(struct DataProcessingInstruction) == sizeof(Word));
    assert(sizeof(struct AddSubtractInstruction) == sizeof(HalfWord));
    assert(sizeof(struct AddSubtractInstruction) == sizeof(uint16_t));
    assert(sizeof(struct BlockDataTransferInstruction) == sizeof(uint32_t));
    assert(sizeof(struct BranchInstruction) == sizeof(uint32_t));
    assert(sizeof(struct BranchAndExchangeInstruction) == sizeof(uint32_t));
    assert(sizeof(struct CoprocessorDataOperationsInstruction) == sizeof(uint32_t));
    assert(sizeof(struct CoprocessorDataTransfersInstruction) == sizeof(uint32_t));
    assert(sizeof(struct CoprocessorRegisterTransferInstruction) == sizeof(uint32_t));
    assert(sizeof(struct DataProcessingInstruction) == sizeof(uint32_t));
    assert(sizeof(struct HalfWordAndSignedDataTransferRegisterOffset) == sizeof(uint32_t));
    assert(sizeof(struct HalfWordAndSignedDataTransferImmediateOffset) == sizeof(uint32_t));
    assert(sizeof(struct MultiplyInstruction) == sizeof(uint32_t));
    assert(sizeof(struct MultiplyLongInstruction) == sizeof(uint32_t));
    assert(sizeof(struct SingleDataSwapInstruction) == sizeof(uint32_t));
    assert(sizeof(struct SingleDataTransferInstruction) == sizeof(uint32_t));
    assert(sizeof(struct SoftWareInterruptInstruction) == sizeof(uint32_t));
    assert(sizeof(struct UndefinedInstruction) == sizeof(uint32_t));
    assert(sizeof(struct AddOffsetToStackPointerInstruction) == sizeof(uint16_t));
    assert(sizeof(struct AddSubtractInstruction) == sizeof(uint16_t));
    assert(sizeof(struct ALUOperation) == sizeof(uint16_t));
    assert(sizeof(struct ConditionalBranchInstruction) == sizeof(uint16_t));
    assert(sizeof(struct HiRegisterOperationsBranchExchangeInstruction) == sizeof(uint16_t));
    assert(sizeof(struct LoadAddressInstruction) == sizeof(uint16_t));
    assert(sizeof(struct LoadStoreHalfWord) == sizeof(uint16_t));
    assert(sizeof(struct LoadStoreRegisterOffset) == sizeof(uint16_t));
    assert(sizeof(struct LoadStoreSignExtendedByteHalfword) == sizeof(uint16_t));
    assert(sizeof(struct LoadStoreWithImmediateOffsetInstruction) == sizeof(uint16_t));
    assert(sizeof(struct LongBranchWithLinkInstruction) == sizeof(uint16_t));
    assert(sizeof(struct MoveCompareAddSubtract) == sizeof(uint16_t));
    assert(sizeof(struct MoveShiftedRegister) == sizeof(uint16_t));
    assert(sizeof(struct MultipleLoadStoreInstruction) == sizeof(uint16_t));
    assert(sizeof(struct PCRelativeLoadInstruction) == sizeof(uint16_t));
    assert(sizeof(struct PushPopRegistersInstruction) == sizeof(uint16_t));
    assert(sizeof(struct SoftwareInterruptThumb) == sizeof(uint16_t));
    assert(sizeof(struct SPRelativeLoadStoreInstruction) == sizeof(uint16_t));
    assert(sizeof(struct UnconditionalBranchInstruction) == sizeof(uint16_t));
    assert(sizeof(union RawArmInstruction) == sizeof(uint32_t));
    assert(sizeof(struct ModifiedVirtualAddressSd1) == sizeof(uint32_t));
    assert(sizeof(struct ModifiedVirtualAddressSd2) == sizeof(uint32_t));
    assert(sizeof(struct ModifiedVirtualAddressFd) == sizeof(uint32_t));
    assert(sizeof(struct ModifiedVirtualAddressFd) == sizeof(uint32_t));
    assert(sizeof(struct ModifiedVirtualAddressSd1) == sizeof(uint32_t));
    assert(sizeof(struct ModifiedVirtualAddressSd2) == sizeof(uint32_t));
    assert(sizeof(struct First_level_descriptor_address) == sizeof(uint32_t));
    assert(sizeof(struct Second_level_descriptor_address) == sizeof(uint32_t));
    assert(sizeof(struct PhysicalAddress_1MB_section) == sizeof(uint32_t));
    assert(sizeof(struct PhysicalAddress_large_page) == sizeof(uint32_t));
    assert(sizeof(struct PhysicalAddress_small_page) == sizeof(uint32_t));
    assert(sizeof(struct PhysicalAddress_1MB_section) == sizeof(uint32_t));
    assert(sizeof(struct PhysicalAddress_small_page) == sizeof(uint32_t));
    assert(sizeof(struct PhysicalAddress_large_page) == sizeof(uint32_t));
    assert(sizeof(union ModifiedVirtualAddress) == sizeof(uint32_t));
    assert(sizeof(union PhysicalAddress) == sizeof(uint32_t));
    assert(sizeof(union PhysicalAddress) == sizeof(uint32_t));
    assert(sizeof(union ModifiedVirtualAddress) == sizeof(uint32_t));
    assert(sizeof(struct V6_fd_translation_fault00) == sizeof(uint32_t));
    assert(sizeof(struct V6_fd_coarse_page_table) == sizeof(uint32_t));
    assert(sizeof(struct V6_fd_section) == sizeof(uint32_t));
    assert(sizeof(struct V6_fd_supersection) == sizeof(uint32_t));
    assert(sizeof(struct V6_fd_translation_fault11) == sizeof(uint32_t));
    assert(sizeof(struct Backwards_fd_ignored) == sizeof(uint32_t));
    assert(sizeof(struct Backwards_fd_course_page_table) == sizeof(uint32_t));
    assert(sizeof(struct Backwards_fd_section) == sizeof(uint32_t));
    assert(sizeof(struct Backwards_fd_supersection) == sizeof(uint32_t));
    assert(sizeof(struct Backwards_fd_reserved) == sizeof(uint32_t));
    assert(sizeof(struct V6_fd_section) == sizeof(uint32_t));
    assert(sizeof(struct V6_fd_coarse_page_table) == sizeof(uint32_t));
    assert(sizeof(struct V6_fd_supersection) == sizeof(uint32_t));
    assert(sizeof(struct V6_fd_translation_fault00) == sizeof(uint32_t));
    assert(sizeof(struct V6_fd_translation_fault11) == sizeof(uint32_t));
    assert(sizeof(struct Backwards_fd_course_page_table) == sizeof(uint32_t));
    assert(sizeof(struct Backwards_fd_ignored) == sizeof(uint32_t));
    assert(sizeof(struct Backwards_fd_reserved) == sizeof(uint32_t));
    assert(sizeof(struct Backwards_fd_section) == sizeof(uint32_t));
    assert(sizeof(struct Backwards_fd_supersection) == sizeof(uint32_t));
}
