#ifndef ITBA_FIRMWARE_TIMER_H
#define ITBA_FIRMWARE_TIMER_H

#include <avr/io.h>
#include "../core/common.h"

typedef enum Steps8Bit {
    STEP8_LOW= 0x00,
    STEP8_MED= 0x80,
    STEP8_HIGH=0xF0,
} Step8bit;

typedef enum Steps16bit {
    STEP16_LOW= F_CPU/1024,
    STEP16_MED= F_CPU/1024/2,
    STEP16_HIGH= F_CPU/1024/8,
} Step16bit;

uint8_t timer_8bit_cycle(Step8bit current);

uint16_t timer_16bit_cycle(Step16bit current);

void timer_8bit_init_2_pwm(void);
void timer_16bit_init_1c_pwm(void);

#endif //ITBA_FIRMWARE_TIMER_H
