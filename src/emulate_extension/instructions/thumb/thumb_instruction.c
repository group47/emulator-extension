//
// Created by qs4617 on 03/06/18.
//

#include <assert.h>
#include "add_offset_to_stack_pointer.h"
#include "add_subtract.h"
#include "alu_operation.h"
#include "conditional_branch.h"
#include "Hi_register_operations_branch_exchange.h"
#include "load_address.h"
#include "load_store_halfword.h"
#include "load_store_register_offset.h"
#include "load_store_sign_extended_byte_half_word.h"
#include "load_store_with_immediate_offset.h"
#include "long_branch_with_link.h"
#include "move_compare_add_subtract.h"
#include "move_shifted_register.h"
#include "multiple_load_store.h"
#include "PCRelativeLoad.h"
#include "push_pop_registers.h"
#include "software_interrupt_thumb.h"
#include "SP_relative_load_store.h"
#include "unconditional_branch.h"
#include "thumb_instruction.h"

enum ExecutionExitCode execute_thumb_instruction(struct ThumbInstruction thumbInstruction) {
    switch (thumbInstruction.type) {
        case THUMB_ADD_OFFSET_TO_STACK_POINTER:
            return execute_instruction_add_offset_to_stack_pointer(thumbInstruction.rawThumbInstruction.addOffsetToStackPointerInstruction);
        case THUMB_ADD_SUBTRACT:
            return execute_instruction_add_subtract(thumbInstruction.rawThumbInstruction.addSubtractInstruction);
        case THUMB_ALU_OPERATION:
            return execute_instruction_alu_operation(thumbInstruction.rawThumbInstruction.aluOperation);
        case THUMB_CONDITIONAL_BRANCH:
            return execute_instruction_conditional_branch(thumbInstruction.rawThumbInstruction.conditionalBranchInstruction);
        case THUMB_HI_REGISTER_OPERATIONS_BRANCH_EXCHANGE:
            return execute_instruction_hi_register_operations_branch_exchange(thumbInstruction.rawThumbInstruction.hiRegisterOperationsBranchExchangeInstruction);
        case THUMB_LOAD_ADDRESS:
            return execute_instruction_load_address(thumbInstruction.rawThumbInstruction.loadAddressInstruction);
        case THUMB_LOAD_STORE_HALFWORD:
            return execute_instruction_load_store_halfword(thumbInstruction.rawThumbInstruction.loadStoreHalfWord);
        case THUMB_LOAD_STORE_REGISTER_OFFSET:
            return execute_instruction_load_store_register_offset(thumbInstruction.rawThumbInstruction.loadStoreRegisterOffset);
        case THUMB_LOAD_STORE_SIGN_EXTENDED_BYTE_HALFWORD:
            return execute_instruction_load_store_sign_extended_byte_half_word(thumbInstruction.rawThumbInstruction.loadStoreSignExtendedByteHalfword);
        case THUMB_LOAD_STORE_WITH_IMMEDIATE:
            return execute_instruction_load_store_with_immeditate_offset(thumbInstruction.rawThumbInstruction.loadStoreWithImmediateOffsetInstruction);
        case THUMB_LONG_BRANCH_WITH_LINK:
            return execute_instruction_long_branch_with_link(thumbInstruction.rawThumbInstruction.longBranchWithLinkInstruction);
        case THUMB_MOVE_COMPARE_ADD_SUBTRACT:
            return execute_instruction_move_compare_add_subtract(thumbInstruction.rawThumbInstruction.moveCompareAddSubtract);
        case THUMB_MOVE_SHIFTED_REGISTER:
            return execute_instruction_move_shifted_register(thumbInstruction.rawThumbInstruction.moveShiftedRegister);
        case THUMB_MULTIPLE_LOAD_STORE:
            return execute_instruction_multiple_load_store(thumbInstruction.rawThumbInstruction.multipleLoadStoreInstruction);
        case THUMB_PC_RELATIVE_LOAD:
            return execute_instruction_PCRelativeLoad(thumbInstruction.rawThumbInstruction.pcRelativeLoadInstruction);
        case THUMB_PUSH_POP_REGISTERS:
            return execute_instruction_push_pop_registers(thumbInstruction.rawThumbInstruction.pushPopRegistersInstruction);
        case THUMB_SOFTWARE_INTERRUPT_THUMB:
            return execute_instruction_thumb_software_interrupt(thumbInstruction.rawThumbInstruction.softwareInterruptThumb);
        case THUMB_SP_RELATIVE_LOAD_STORE:
            return execute_instruction_SP_relative_load_store(thumbInstruction.rawThumbInstruction.spRelativeLoadStoreInstruction);
        case THUMB_UNCONDITIONAL_BRANCH:
            return execute_instruction_unconditional_branch(thumbInstruction.rawThumbInstruction.unconditionalBranchInstruction);
        default:
            assert(false);
    }
}


struct ThumbInstruction ThumbFromRaw(union RawThumbInstruction instruction) {
    struct ThumbInstruction thumbInstruction;
    thumbInstruction.rawThumbInstruction = instruction;

    if (instruction.moveShiftedRegister.filler000 == 0b000) {
        thumbInstruction.type = THUMB_MOVE_SHIFTED_REGISTER;
    } else if (instruction.addSubtractInstruction.shouldBe0b00011 == 0b00011) {
        thumbInstruction.type = THUMB_ADD_SUBTRACT;
    } else if (instruction.aluOperation.filler010000 == 0b01000) {
        thumbInstruction.type = THUMB_ALU_OPERATION;
    } else if (instruction.moveCompareAddSubtract.filler001 == 0b001) {
        thumbInstruction.type = THUMB_MOVE_COMPARE_ADD_SUBTRACT;
    } else if (instruction.hiRegisterOperationsBranchExchangeInstruction.filler010001_position15 == 0b000) {
        thumbInstruction.type = THUMB_HI_REGISTER_OPERATIONS_BRANCH_EXCHANGE;
    } else if (instruction.pcRelativeLoadInstruction.filler01001_position15 == 0b01001) {
        thumbInstruction.type = THUMB_PC_RELATIVE_LOAD;
    } else if (instruction.loadStoreRegisterOffset.filler0 == 0b0 &&
               instruction.loadStoreRegisterOffset.filler0101 == 0b0101) {
        thumbInstruction.type = THUMB_LOAD_STORE_REGISTER_OFFSET;
    } else if (instruction.loadStoreSignExtendedByteHalfword.filler1 == 0b1 &&
            instruction.loadStoreSignExtendedByteHalfword.filler1010 == 0b1010) {
        thumbInstruction.type = THUMB_LOAD_STORE_SIGN_EXTENDED_BYTE_HALFWORD;
    } else if (instruction.loadStoreWithImmediateOffsetInstruction.filler011 == 0b011) {
        thumbInstruction.type = THUMB_LOAD_STORE_WITH_IMMEDIATE;
    } else if (instruction.loadStoreHalfWord.filler1000 == 0b100) {
        thumbInstruction.type = THUMB_LOAD_STORE_HALFWORD;
    } else if (instruction.spRelativeLoadStoreInstruction.filler1001 == 0b1001) {
        thumbInstruction.type = THUMB_SP_RELATIVE_LOAD_STORE;
    } else if (instruction.loadAddressInstruction.filler1010 == 0b1010) {
        thumbInstruction.type = THUMB_LOAD_ADDRESS;
    } else if (instruction.addOffsetToStackPointerInstruction.filler1011_0000 == 0b10110000) {
        thumbInstruction.type = THUMB_ADD_OFFSET_TO_STACK_POINTER;
    } else if (instruction.pushPopRegistersInstruction.filler10_position10 == 0b10) {
        thumbInstruction.type = THUMB_PUSH_POP_REGISTERS;
    } else if (instruction.multipleLoadStoreInstruction.filler1100 == 0b1100) {
        thumbInstruction.type = THUMB_MULTIPLE_LOAD_STORE;
    } else if (instruction.conditionalBranchInstruction.filler1101 == 0b1101) {
        thumbInstruction.type = THUMB_CONDITIONAL_BRANCH;
    } else if (instruction.softwareInterruptThumb.filler11011111 == 0b11011111) {
        thumbInstruction.type = THUMB_SOFTWARE_INTERRUPT_THUMB;
    } else if (instruction.unconditionalBranchInstruction.filler11100 == 0b11100) {
        thumbInstruction.type = THUMB_UNCONDITIONAL_BRANCH;
    } else if (instruction.longBranchWithLinkInstruction.filler1111 == 0b1111) {
        thumbInstruction.type = THUMB_LONG_BRANCH_WITH_LINK;
    } else {
        assert(false);
    }

    return thumbInstruction;

}