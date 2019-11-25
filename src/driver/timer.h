#ifndef ITBA_FIRMWARE_TIMER_H
#define ITBA_FIRMWARE_TIMER_H

#include "../core/common.h"

void timer_16bit_init_1C_pwm(void);
void timer_8bit_init_2_pwm(void);
void timer_16bit_init_3A_ctc(void);

#endif //ITBA_FIRMWARE_TIMER_H
