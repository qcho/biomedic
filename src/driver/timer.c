#include "timer.h"

uint8_t timer_8bit_cycle(Step8bit current) {
    switch (current) {
        case STEP8_LOW: return STEP8_MED;
        case STEP8_MED: return STEP8_HIGH;
        default: return STEP8_LOW;
    }
}

uint16_t timer_16bit_cycle(Step16bit current) {
    switch (current) {
        case STEP16_LOW: return STEP16_MED;
        case STEP16_MED: return STEP16_HIGH;
        default: return STEP16_LOW;
    }
}

void timer_8bit_init_2_pwm(void) {
    bit_set(TCCR2, WGM21);
    bit_set(TCCR2, WGM20); // set Fast PWM. TOP: 0xFF

    bit_set(TCCR2, COM21);
    bit_set(TCCR2, COM20); // set inverting mode

    bit_set(TCCR2, CS22);
    bit_clr(TCCR2, CS21);
    bit_set(TCCR2, CS20); // set prescaler to 1024
}

void timer_16bit_init_1c_pwm(void) {
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