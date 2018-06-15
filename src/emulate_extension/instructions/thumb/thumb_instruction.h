//
// Created by qs4617 on 03/06/18.
//

#ifndef SRC_THUMB_INSTRUCTION_H
#define SRC_THUMB_INSTRUCTION_H

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

union RawThumbInstruction {
    struct AddOffsetToStackPointerInstruction addOffsetToStackPointerInstruction;
    struct AddSubtractInstruction addSubtractInstruction;
    struct ALUOperation aluOperation;
    struct ConditionalBranchInstruction conditionalBranchInstruction;
    struct HiRegisterOperationsBranchExchangeInstruction hiRegisterOperationsBranchExchangeInstruction;
    struct LoadAddressInstruction loadAddressInstruction;
    struct LoadStoreHalfWord loadStoreHalfWord;
    struct LoadStoreRegisterOffset loadStoreRegisterOffset;
    struct LoadStoreSignExtendedByteHalfword loadStoreSignExtendedByteHalfword;
    struct LoadStoreWithImmediateOffsetInstruction loadStoreWithImmediateOffsetInstruction;
    struct LongBranchWithLinkInstruction longBranchWithLinkInstruction;
    struct MoveCompareAddSubtract moveCompareAddSubtract;
    struct MoveShiftedRegister moveShiftedRegister;
    struct MultipleLoadStoreInstruction multipleLoadStoreInstruction;
    struct PCRelativeLoadInstruction pcRelativeLoadInstruction;
    struct PushPopRegistersInstruction pushPopRegistersInstruction;
    struct SoftwareInterruptThumb softwareInterruptThumb;
    struct SPRelativeLoadStoreInstruction spRelativeLoadStoreInstruction;
    struct UnconditionalBranchInstruction unconditionalBranchInstruction;
};


enum ThumbInstructionType {
    THUMB_ADD_OFFSET_TO_STACK_POINTER,
    THUMB_ADD_SUBTRACT,
    THUMB_ALU_OPERATION,
    THUMB_CONDITIONAL_BRANCH,
    THUMB_HI_REGISTER_OPERATIONS_BRANCH_EXCHANGE,
    THUMB_LOAD_ADDRESS,
    THUMB_LOAD_STORE_HALFWORD,
    THUMB_LOAD_STORE_REGISTER_OFFSET,
    THUMB_LOAD_STORE_SIGN_EXTENDED_BYTE_HALFWORD,
    THUMB_LOAD_STORE_WITH_IMMEDIATE,
    THUMB_LONG_BRANCH_WITH_LINK,
    THUMB_MOVE_COMPARE_ADD_SUBTRACT,
    THUMB_MOVE_SHIFTED_REGISTER,
    THUMB_MULTIPLE_LOAD_STORE,
    THUMB_PC_RELATIVE_LOAD,
    THUMB_PUSH_POP_REGISTERS,
    THUMB_SOFTWARE_INTERRUPT_THUMB,
    THUMB_SP_RELATIVE_LOAD_STORE,
    THUMB_UNCONDITIONAL_BRANCH
};

struct ThumbInstruction {
    union RawThumbInstruction rawThumbInstruction;
    enum ThumbInstructionType type;
};

enum ExecutionExitCode execute_thumb_instruction(struct ThumbInstruction thumbInstruction);

struct ThumbInstruction ThumbFromRaw(union RawThumbInstruction instruction);


#endif //SRC_THUMB_INSTRUCTION_H
