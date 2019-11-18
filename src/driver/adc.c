//
// Created by Qcho on 11/11/2019.
//

#include "adc.h"

void adc_init()
{
    bit_set(ADMUX, REFS1); bit_set(ADMUX, REFS0); // AVCC with external capacitor at AREF pin

    bit_set(ADCSRA, ADEN); //ADC Enable
    bit_set(ADCSRA, ADPS2); bit_set(ADCSRA, ADPS1); bit_set(ADCSRA, ADPS0); // ADC prescaler division factor 128

    // Uso el channel 0
    //bit_clr(ADMUX, MUX4); bit_clr(ADMUX, MUX3); bit_clr(ADMUX, MUX2); bit_clr(ADMUX, MUX1); bit_clr(ADMUX, MUX0);
}

uint16_t adc_read(uint8_t ch)
{
    // Select channel.
    // First unset last 3 chars of ADMUX.
    // Second OR with ch masked for the 3 last bits.
    ADMUX = (ADMUX & 0b11111000) | (ch & 0b00000111);

    bit_set(ADCSRA, ADSC); // start conversion (single)
    loop_until_bit_is_clear(ADCSRA, ADSC); // wait until converion is done

    return ADC;
}

