//
// Created by fpn17 on 02/06/18.
//

#ifndef SRC_SOFTWARE_INTERRUPT_THUMB_H
#define SRC_SOFTWARE_INTERRUPT_THUMB_H

struct SoftwareInterruptThumb{
    uint8_t value8 : 8;
    uint8_t filler11011111: 8;
};

enum ExecutionExitCode execute_instruction_thumb_software_interrupt(struct SoftwareInterruptThumb instruction);
#endif //SRC_SOFTWARE_INTERRUPT_THUMB_H
