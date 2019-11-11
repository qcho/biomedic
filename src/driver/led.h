#ifndef ITBA_FIRMWARE_LED_H
#define ITBA_FIRMWARE_LED_H

#include "../core/common.h"

typedef enum DutyCycle {
    DC_L = 00U,
    DC_M = 50U,
    DC_H = 90U,
} DutyCycle_t;

typedef enum Frequency {
    FREQ_L = 1U,
    FREQ_M = 4U,
    FREQ_H = 8U,
} Frequency_t;

void led_init(void);

void led_duty_cycle_rotate(void);
uint8_t led_duty_cycle_get_percentage(void);
bool led_duty_cycle_set_percentage(uint8_t duty_cycle_in_percentage);

void led_frequency_rotate(void);
uint8_t led_frequency_get_hertz(void);
bool led_frequency_set_hertz(uint8_t frequency_in_hertz);



#endif //ITBA_FIRMWARE_LED_H
