#include "../apps.h"

#define THERMISTOR_SERIES_RESISTANCE 10000.0
#define THERMISTOR_BETA_COEFFICIENT 3900.0
#define THERMISTOR_ZERO_KELVIN 273.15 // NTC 10kohm @25 C.
#define THERMISTOR_NOMINAL_KELVIN 298.15
#define THERMISTOR_NOMINAL_RESISTANCE 10000.0

/**
 * Linear function
 */
uint16_t potentiometer_adc_to_milli_volt(const uint16_t adc_10bit_value) {
    return ADC_MEASURED_VREF_VOLT * adc_10bit_value / ADC_MAX_VALUE * 1000U;
}

/**
 * https://learn.adafruit.com/thermistor/using-a-thermistor
 * https://en.wikipedia.org/wiki/Thermistor#B_or_.CE.B2_parameter_equation
 */
uint16_t thermistor_adc_to_milli_celcius(const uint16_t adc_10bit_value) {
    double resistance = ADC_MAX_VALUE / adc_10bit_value - 1;
    resistance = THERMISTOR_SERIES_RESISTANCE / resistance;
    /**
     * 1/T = ln(R/R_0)/B + 1/T_0
     */
    double temp = log(resistance / THERMISTOR_NOMINAL_RESISTANCE);   // ln(R/Ro)
    temp /= THERMISTOR_BETA_COEFFICIENT;                                // ln(R/Ro)/B
    temp += 1.0 / (THERMISTOR_NOMINAL_KELVIN);                          // ln(R/R_0)/B + (1/To)
    temp = 1.0 / temp;                                                  // T=1/...
    temp -= THERMISTOR_ZERO_KELVIN;                                     // K -> C
    return temp * 1000U;
}

void tp_03(void) {
    adc_init();
    _delay_ms(50);
    for(;;)
    {
        uint16_t pValue = adc_read(0);
        uint16_t tValue = adc_read(1);
        uint16_t pMilliVolt = potentiometer_adc_to_milli_volt(pValue);
        uint16_t tMilliCelcius = thermistor_adc_to_milli_celcius(tValue);
        printf("ADC0(%u): %u.%u[V]. ADC1(%u): %u.%u[C].\n",
               pValue, pMilliVolt / 1000U, pMilliVolt % 1000U,
               tValue, tMilliCelcius / 1000U, tMilliCelcius % 1000U);
        _delay_ms(200);
    }
}
