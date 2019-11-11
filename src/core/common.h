//
// Created by Qcho on 05/11/2019.
//

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

#define DDR_INPUT(letter, bit)   bit_clr(DDR##letter, bit)
#define DDR_OUTPUT(letter, bit)  bit_set(DDR##letter, bit)
#define PORT_HIGH(letter, bit)   bit_set(PORT##letter, bit)
#define PORT_LOW(letter, bit)    bit_clr(PORT##letter, bit)
#define PORT_TOGGLE(letter, bit) bit_tgl(PORT##letter, bit)
#define PIN_IS_HIGH(letter, bit) bit_is_set(PIN##letter, bit)
#define PIN_IS_LOW(letter, bit)  bit_is_clear(PIN##letter, bit)

bool string_starts_with(const char *string, const char *prefix);
// char to integer
uint8_t cti(char c);

#endif //ITBA_FIRMWARE_COMMON_H
