#include "../apps.h"

//ISR (TIMER1_COMPC_vect) {
//    printf("CTC reached %u\n", TCNT1);
//}

void ex_timers(void) {
    DDR_OUTPUT(B,PB7);

    led_init();

    //timer_16bit_init_1c_pwm();
    //OCR1A = STEP16_LOW;
    //OCR1C = OCR1A/2;

    for(;;) {
        printf("C1 %u | C2 %u | PORT %u \n", TCNT1, TCNT2, PORTB);
    }
}
