//
// Created by fpn17 on 11/06/18.
//

#ifndef SRC_SERIAL_CONSOLE_H
#define SRC_SERIAL_CONSOLE_H

#include "../basic_typedefs.h"

#define MAGIC_CONSOLE_ADDRESS (1024*1024*1024 + 100)

void console_handler(ByteAddress address, bool set, Word val);

#endif //SRC_SERIAL_CONSOLE_H
