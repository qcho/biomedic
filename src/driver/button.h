#ifndef ITBA_FIRMWARE_BUTTON_H
#define ITBA_FIRMWARE_BUTTON_H

#include <avr/io.h>

#define MASK   0b11000111U

uint8_t button_is_pressed(uint8_t *button_history);
uint8_t button_is_released(uint8_t *button_history);
uint8_t button_is_down(const uint8_t *button_history);
uint8_t button_is_up(const uint8_t *button_history);
void button_update(uint8_t *button_history, uint8_t value);

#endif //ITBA_FIRMWARE_BUTTON_H
