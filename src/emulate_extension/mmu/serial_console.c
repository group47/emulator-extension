//
// Created by fpn17 on 11/06/18.
//

#include <stdbool.h>
#include <stdio.h>
#include "serial_console.h"
#include "../util/entry_point.h"


void console_handler(ByteAddress address, bool set, Word val) {
    //todo
    fprintf(get_logfile(), "%d", val);
}