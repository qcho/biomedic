#include "button.h"

uint8_t button_is_pressed(uint8_t *button_history){
    uint8_t pressed = 0;
    if ((*button_history & MASK) == 0b00000111U){
        pressed = 1;
        *button_history = 0b11111111U;
    }
    return pressed;
}

uint8_t button_is_released(uint8_t *button_history){
    uint8_t released = 0;
    if ((*button_history & MASK) == 0b11000000U){
        released = 1;
        *button_history = 0b00000000U;
    }
    return released;
}

uint8_t button_is_down(const uint8_t *button_history){
    return *button_history == 0b11111111U;
}

uint8_t button_is_up(const uint8_t *button_history){
    return *button_history == 0b00000000U;
}

void button_update(uint8_t *button_history, uint8_t value) {
    *button_history = *button_history << 1U;
    *button_history |= value != 0;
}
