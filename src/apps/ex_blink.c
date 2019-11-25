#include "../apps.h"

#define LED B,7

void ex_blink(void) {
    DDR_OUTPUT(LED);
    for(;;) {
        _delay_ms(200);
        PORT_TOGGLE(LED);
    }
}
