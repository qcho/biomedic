//
// Created by Qcho on 11/11/2019.
//

#ifndef ITBA_FIRMWARE_ADC_H
#define ITBA_FIRMWARE_ADC_H

#include "../core/common.h"

#define ADC_MEASURED_VREF_VOLT 2.471
#define ADC_MAX_VALUE 1023.0

void adc_init(void);
uint16_t adc_read(uint8_t ch);

#endif //ITBA_FIRMWARE_ADC_H
