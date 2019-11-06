#include "../apps.h"

void ex_blink(void) {
    DDR_OUTPUT(B, PB7);
    for(;;) {
        _delay_ms(200);
        PORT_TOGGLE(B, PB7);
    }
}
