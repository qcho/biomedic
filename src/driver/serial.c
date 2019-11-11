#include "serial.h"

void serial_init(void) {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

int serial_putchar(char c, FILE *stream) {
    if (c == '\n') {
        serial_putchar('\r', stream);
    }
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    return 0;
}

int serial_getchar(FILE *stream) {
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    return UDR0;
}

bool serial_incomming_data(void) {
    return bit_is_set(UCSR0A, RXC0);
}

int serial_getchar_echo(FILE *stream) {
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    char c = UDR0;
    switch(c) {
        case '\b':
            serial_putchar(c, stream);
            serial_putchar(' ', stream);
            break;
        default:
            break;
    }
    serial_putchar(c, stream);
    return c;
}

FILE serial_output = FDEV_SETUP_STREAM(serial_putchar, NULL, _FDEV_SETUP_WRITE);
FILE serial_input = FDEV_SETUP_STREAM(NULL, serial_getchar, _FDEV_SETUP_READ);
FILE serial_input_echo = FDEV_SETUP_STREAM(NULL, serial_getchar_echo, _FDEV_SETUP_READ);
