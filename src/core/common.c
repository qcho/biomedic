#include "common.h"

bool string_starts_with(const char *string, const char *prefix) {
    size_t prefix_length = strlen(prefix);
    size_t string_length = strlen(string);
    return string_length < prefix_length
        ? false
        : memcmp(prefix, string, prefix_length) == 0;
}

uint8_t cti(char c) {
    return c - '0';
}

uint16_t integer_division_ceil(uint16_t x, uint16_t y) {
    return x/y + (x%y != 0);
}
