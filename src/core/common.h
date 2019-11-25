#ifndef ITBA_FIRMWARE_COMMON_H
#define ITBA_FIRMWARE_COMMON_H

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdbool.h>

#define CYCLES_IN_SECOND F_CPU/60/2

#define bit_clr(word, bit) (word) &= ~_BV(bit)
#define bit_set(word, bit) (word) |=  _BV(bit)
#define bit_tgl(word, bit) (word) ^=  _BV(bit)

/**
 * These macros are needed to perform two-staged pre-processing macro expansion
 */
#define _bit_clr(name, letter, bit)         bit_clr(name##letter, bit)
#define _bit_set(name, letter, bit)         bit_set(name##letter, bit)
#define _bit_tgl(name, letter, bit)         bit_tgl(name##letter, bit)
#define _bit_is_set(name, letter, bit)      bit_is_set(name##letter, bit)
#define _bit_is_clear(name, letter, bit)    bit_is_clear(name##letter, bit)

#define DDR_INPUT(port_id)      _bit_clr(DDR, port_id)
#define DDR_OUTPUT(port_id)     _bit_set(DDR, port_id)
#define PORT_HIGH(port_id)      _bit_set(PORT, port_id)
#define PORT_LOW(port_id)       _bit_clr(PORT, port_id)
#define PORT_TOGGLE(port_id)    _bit_tgl(PORT, port_id)
#define PIN_IS_HIGH(port_id)    _bit_is_set(PIN, port_id)
#define PIN_IS_LOW(port_id)     _bit_is_clear(PIN, port_id)

bool string_starts_with(const char *string, const char *prefix);

uint8_t cti(char c); // char to integer

uint16_t integer_division_ceil(uint16_t x, uint16_t y);

#endif //ITBA_FIRMWARE_COMMON_H
