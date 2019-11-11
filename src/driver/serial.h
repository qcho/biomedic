#pragma once
#ifndef ITBA_FIRMWARE_SERIAL_H
#define ITBA_FIRMWARE_SERIAL_H

/**
 * Useful links:
 * - https://appelsiini.net/2011/simple-usart-with-avr-libc/
 * - http://www.ermicro.com/blog/?p=325
 * - http://www.nongnu.org/avr-libc/user-manual/group__stdiodemo.html
 */

#include <util/setbaud.h>
#include "../core/common.h"

void serial_init(void);

FILE serial_output;
FILE serial_input;
FILE serial_input_echo;

bool serial_incomming_data(void);

#endif //ITBA_FIRMWARE_SERIAL_H
