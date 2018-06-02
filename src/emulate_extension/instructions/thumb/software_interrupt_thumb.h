//
// Created by fpn17 on 02/06/18.
//

#ifndef SRC_SOFTWARE_INTERRUPT_THUMB_H
#define SRC_SOFTWARE_INTERRUPT_THUMB_H

struct SoftwareInterruptThumb{
    uint8_t value8 : 8;
    uint8_t filler11011111: 8;
};

#endif //SRC_SOFTWARE_INTERRUPT_THUMB_H
