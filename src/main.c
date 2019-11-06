#include "apps.h"

int main(void)
{
    /** For some reason only starting serial in main works **/
    serial_init();
    FILE serial_output = FDEV_SETUP_STREAM(serial_putchar, NULL, _FDEV_SETUP_WRITE);
    FILE serial_input = FDEV_SETUP_STREAM(NULL, serial_getchar, _FDEV_SETUP_READ);
    stdout = stderr = &serial_output;
    stdin  = &serial_input;

    tp_01();
}
