#include "../apps.h"

#define LED B,7
#define BUTTON D,7

void ex_button(void) {
    DDR_OUTPUT(LED);
    DDR_INPUT(BUTTON);
    uint8_t button_history = 0;
    unsigned long press_cycles = 0;

    for(;;) {
        // uint8_t value = PORTF & _BV(PD7);
        button_update(&button_history, PIN_IS_HIGH(BUTTON));

        if (button_is_pressed(&button_history)) {
            printf("Button pressed\n");
            PORT_LOW(LED);
            press_cycles = 0;
        }

        if (button_is_released(&button_history)) {
            printf("Button released for %lu cycles\n", press_cycles);
            PORT_HIGH(LED);
            if (press_cycles > CYCLES_IN_SECOND * 2) {
                printf("LONG PRESS! (2 seconds)");
            }
            press_cycles = 0;
        }

        if (button_is_down(&button_history)) {
            press_cycles++;
        }
    }
}
