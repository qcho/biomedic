#include "../apps.h"
#include <avr/interrupt.h>

#define LED B,7

ISR (TIMER3_COMPA_vect) {
    //printf("CTC reached %u\n", TCNT3);
    PORT_TOGGLE(LED);
}

ISR (TIMER1_COMPC_vect) {
    //printf("PWM reached %u\n", TCNT3);
    PORT_TOGGLE(LED);
}

ISR (TIMER1_COMPB_vect) {
    //printf("PWM reached %u\n", TCNT3);
    PORT_TOGGLE(LED);
}

ISR (TIMER1_OVF_vect) {
    PORT_TOGGLE(LED);
}

void ex_timers(void) {

    DDR_OUTPUT(LED);
    PORT_HIGH(LED);

    timer_16bit_init_3A_ctc();
    OCR3A = 0x1000;
    TCNT3 = 0;

    timer_16bit_init_1C_pwm();
    OCR1A = 0x0800;
    TCNT1 = 0;

    TIMSK |= (1 << OCIE3A) | (1 << OCIE1C); // enable compare interrupt

    sei(); // enable global interrupts

    for(;;) {
        printf("C1 %u | C2 %u | C3 %u | PORT %u | TIFR %u \n", TCNT1, TCNT2, TCNT3, PORTB, TIFR);
        _delay_ms(100);
        //PORT_TOGGLE(B, 7);
    }
}
