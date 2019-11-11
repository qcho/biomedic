#include "led.h"

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
    OCR2 = x/100U + (x%100U != 0);
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

void led_timer_8bit_init_2_pwm(void) {
    bit_set(TCCR2, WGM21);
    bit_set(TCCR2, WGM20); // set Fast PWM. TOP: 0xFF

    bit_set(TCCR2, COM21);
    bit_set(TCCR2, COM20); // set inverting mode

    bit_set(TCCR2, CS22);
    bit_clr(TCCR2, CS21);
    bit_set(TCCR2, CS20); // set prescaler to 1024
}

void led_timer_16bit_init_1c_pwm(void) {
    bit_set(TCCR1B, WGM13);
    bit_set(TCCR1B, WGM12);
    bit_set(TCCR1A, WGM11);
    bit_set(TCCR1A, WGM10); // set Fast PWM. TOP: OCR1A

    bit_set(TCCR1A, COM1C1);
    bit_clr(TCCR1A, COM1C0); // set non-inverting mode

    bit_set(TCCR1B, CS12);
    bit_clr(TCCR1B, CS11);
    bit_set(TCCR1B, CS10); // set prescaler to 1024
}

void led_init(void) {
    led_timer_8bit_init_2_pwm();
    led_duty_cycle_set_percentage(DC_L);
    led_timer_16bit_init_1c_pwm();
    led_frequency_set_hertz(FREQ_L);
}
