#include "../apps.h"

void tp_01(void) {
    DDR_OUTPUT(B, PB7);
    DDR_INPUT(D, PD7);
    uint8_t button_history = 0;
    long press_cycles = 0;

    timer_8bit_init_2_pwm();
    OCR2 = STEP8_LOW;

    timer_16bit_init_1c_pwm();
    OCR1A = STEP16_LOW;
    OCR1C = OCR1A/2;

    for(;;) {
        button_update(&button_history, PIN_IS_HIGH(D, PD7));

        if (button_is_down(&button_history)) {
            press_cycles++;
        }

        if (button_is_released(&button_history)) {
            if (press_cycles > CYCLES_IN_SECOND) {
                OCR1A = timer_16bit_cycle(OCR1A);
                OCR1C = OCR1A/2;
                printf("LONG PRESS (%lu c): changed frequency to %uHz\n", press_cycles, 7200/OCR1C);
            } else {
                OCR2 = timer_8bit_cycle(OCR2);
                printf("QUICK PRESS (%lu c): changed duty_cycle to %u%%\n", press_cycles, (100*OCR2)/0xFF);
            }
            press_cycles = 0;
        }
    }
}
