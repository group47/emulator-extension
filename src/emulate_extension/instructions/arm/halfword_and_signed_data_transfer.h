//
// Created by fpn17 on 02/06/18.
//

#ifndef SRC_HALFWORD_AND_SIGNED_DATA_TRANSFER_H
#define SRC_HALFWORD_AND_SIGNED_DATA_TRANSFER_H

#include <stdbool.h>
#include "../../basic_typedefs.h"
#include "../../util/common_enums.h"

struct HalfWordAndSignedDataTransferRegisterOffset {
    RegisterAddress Rm:4;
    bool shouldBe1:1;
    bool halfword: 1;
    bool signed_ :1;
    uint8_t shouldBe00001:5;
    RegisterAddress Rd:4;
    RegisterAddress Rn:4;
    enum LoadStore loadStore:1;
    bool writeBack : 1;
    bool shouldBe0 : 1;
    bool upDown:1;
    enum PrePostIndexing indexing: 1;
    uint8_t shouldBe0b000 : 3;
    enum Cond cond : 4;
}__attribute((packed));

enum ExecutionExitCode
execute_halfword_and_signed_data_transfer_register_offset(struct HalfWordAndSignedDataTransferRegisterOffset);


struct HalfWordAndSignedDataTransferImmediateOffset {
    uint8_t offsetLowNibble : 4;
    bool filler1position4 :1;
    bool halfword: 1;
    bool signed_ :1;
    bool filler1position7 :1;
    uint8_t offsetHighNibble : 4;
    RegisterAddress Rd:4;
    RegisterAddress Rn:4;
    enum LoadStore loadStore:1;
    bool writeBack : 1;
    bool filler1Position22 : 1;
    bool upDown:1;
    enum PrePostIndexing indexing: 1;
    uint8_t shouldBe0b000 : 3;
    enum Cond cond : 4;
}__attribute((packed));


enum ExecutionExitCode
execute_halfword_and_signed_data_transfer_immediate_offset(struct HalfWordAndSignedDataTransferImmediateOffset);

const ByteAddress getFinalAddress(bool, ByteAddress, ByteAddress);

const ByteAddress get_offset(struct HalfWordAndSignedDataTransferImmediateOffset);

#endif //SRC_HALFWORD_AND_SIGNED_DATA_TRANSFER_H
