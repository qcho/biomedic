# Installation (OSX)
* The project uses `CMake` for management.
    * The CMAKE is customized for `AVR Atmega128` micro-controller.
* Needs:
    * `brew install cmake avr-gcc avrdude`
    * For serial comms: [CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)
* Recommended but not needed:
    * `brew install platformio`

# Decisions
* Tried to make C++17 code but I wasn't able to do it because of this issues:
    * No support for `std::` in `gcc-avr`: this makes simple things like working with streams not supported by default.
    * No support for `FDEV_SETUP_STREAM` to allow usage of `<stdio.h>` functions.
    * No support for `std::variant` for better state-machines.
* `src/driver` folder contains all drivers.
* `src/core/common.h` contains helper macros for bit operations.
* `src/apps` folder contains some examples `ex_**` and the tps`tp_**`.
* `doc/` contains board documentation.

# Apps
## TPs

### tp_01(): GPIO - RTI
 * The button drivers maintains the history of a word (`uint8_t`) of the last bits.
    * This allows proper debouncing of physical inconsistencies for any type of button.
    * Allows handling of press and release events.
 * quick-press a button to change duty_cycle (dim the led)
 * long-press a button to change frequency (blink)
 * It's implemented using two Timers and the Atmega128 feature
 * of OutputCompare Modulator (OCM1C2) to mix the two into one signal
 * OC1C 16 bit timer is used for blinking. Mode: Fast PWM (non-inverting)
 * OC2 8 bit timer is used for dimming. Mode: Fast PWM (inverting)
 * Serial events showing what has happened:
 ```sh
LONG PRESS (378696 c): changed frequency to 8Hz
QUICK PRESS (8084 c): changed duty_cycle to 50%
LONG PRESS (402930 c): changed frequency to 1Hz
QUICK PRESS (22010 c): changed duty_cycle to 94%
QUICK PRESS (22057 c): changed duty_cycle to 0%
LONG PRESS (316915 c): changed frequency to 2Hz
LONG PRESS (333678 c): changed frequency to 8Hz
QUICK PRESS (18483 c): changed duty_cycle to 50%
QUICK PRESS (22653 c): changed duty_cycle to 94%
QUICK PRESS (19914 c): changed duty_cycle to 0%
QUICK PRESS (31178 c): changed duty_cycle to 50%
QUICK PRESS (26451 c): changed duty_cycle to 94%
```
 
### tp_02(): UART
 * WIP
### tp_03(): ADT
 * WIP

## Examples
### ex_blink()
* Simple blink

### ex_button();
* Simple button driver test.
* Pressing button turns on/off led
* Also some serial events are shown including long-presses

### ex_serial();
* Simple serial driver test.

### ex_timers();
* Simple pwm timers example with lights and serial events.


# Windows (not tested) requirements
- Compiler: AVR
- WinAVR: Makefile
- USBASP [HW]
- AURDUDE