#include "timer.h"

/**
 * http://maxembedded.com/2011/07/avr-timers-ctc-mode/
 */
void timer_16bit_init_3A_ctc(void) {
    bit_clr(TCCR3B, WGM33);
    bit_set(TCCR3B, WGM32);
    bit_clr(TCCR3A, WGM31);
    bit_clr(TCCR3A, WGM30); // set CTC. TOP: OCR3A

    //bit_clr(TCCR3A, COM3A1);
    //bit_set(TCCR3A, COM3A0); // Toggle OCnA/OCnB/OCnC on compare match.

    bit_set(TCCR3B, CS32);
    bit_clr(TCCR3B, CS31);
    bit_set(TCCR3B, CS30); // set prescaler to 1024
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

void timer_16bit_init_1C_pwm(void) {
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
