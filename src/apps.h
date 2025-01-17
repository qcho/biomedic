#ifndef ITBA_FIRMWARE_APPS_H
#define ITBA_FIRMWARE_APPS_H

#include "core/common.h"
#include "driver/serial.h"
#include "driver/led.h"
#include "driver/button.h"
#include "driver/adc.h"
#include "driver/timer.h"

/**
 * Some examples to try things
 */
void ex_blink(void);
void ex_button(void);
void ex_serial(void);
void ex_timers(void);
void ex_motors(void);

/**
 * TPs (Trabajos prácticos)
 */
void tp_01(void);
void tp_02(void);
void tp_03(void);

#define HzFromCycles
#define PercentageFromCycles

#endif //ITBA_FIRMWARE_APPS_H
