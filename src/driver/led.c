#include "led.h"
#include "timer.h"

void led_duty_cycle_rotate() {
    switch (led_duty_cycle_get_percentage()) {
        case DC_L:
            led_duty_cycle_set_percentage(DC_M);
            break;
        case DC_M:
            led_duty_cycle_set_percentage(DC_H);
            break;
        default:
            led_duty_cycle_set_percentage(DC_L);
            break;
    }
}

uint8_t led_duty_cycle_get_percentage() {
    return (100U*OCR2)/0xFFU;
}

bool led_duty_cycle_set_percentage(uint8_t duty_cycle_in_percentage) {
    if (duty_cycle_in_percentage < 0 || duty_cycle_in_percentage > 100) {
        return false;
    }
    // Perform ceiling of an integer division for consistency.
    uint16_t x = 0xFFU*duty_cycle_in_percentage;
    OCR2 = integer_division_ceil(x, 100U);
    return true;
}

void led_frequency_rotate(void) {
    switch (led_frequency_get_hertz()) {
        case FREQ_L:
            led_frequency_set_hertz(FREQ_M);
            break;
        case FREQ_M:
            led_frequency_set_hertz(FREQ_H);
            break;
        default:
            led_frequency_set_hertz(FREQ_L);
            break;
    }
}

uint8_t led_frequency_get_hertz() {
    return F_CPU/1024/2/OCR1C;
}

bool led_frequency_set_hertz(uint8_t frequency_in_hertz) {
    OCR1C = F_CPU/1024/2/frequency_in_hertz;
    OCR1A = 2*OCR1C;
    return true;
}

void led_init(void) {
    timer_8bit_init_2_pwm();
    led_duty_cycle_set_percentage(DC_L);
    timer_16bit_init_1C_pwm();
    led_frequency_set_hertz(FREQ_L);
}
