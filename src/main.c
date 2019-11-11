#include "apps.h"

int main(void)
{
    /** For some reason only starting serial in main works **/
    serial_init();
    stdout = stderr = &serial_output;
    stdin  = &serial_input;

    tp_02();
}
