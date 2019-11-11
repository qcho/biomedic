#include "../apps.h"

enum Command {
    ECHO='e',
    GET_='g',
    CHG_='c',
    SET_='s',
    _STATE = 's',
    _FREQ ='f',
    _DC = 'd'
};

typedef enum Error {
    UNKNOWN_COMMAND = -1,
    INVALID_CHG_INDEX = -2,
    MALFORMED_CHG_DC = -3,
    MALFORMED_CHG_FREQ = -4,
    INVALID_SET_DC_VALUE = -5,
    MALFORMED_SET_DC = -6,
} Error_t;

typedef struct tp_02_state {
    bool echo_mode;
    uint8_t duty_enabled_index;
    uint8_t duty_options[3];
    uint8_t freq_enabled_index;
    uint16_t freq_options[3];
} tp_02_state_t;

void print_prompt(const tp_02_state_t state) {
    printf("\n\n");
    printf("i Frequency\tDuty-cycle\n");
    for (int i = 0; i < 3; i++) {
        printf("%u %c %5uHz\t%c %5u%%\n",
                i,
                state.freq_enabled_index == i ? '>' : ' ',
                state.freq_options[i],
                state.duty_enabled_index == i ? '>' : ' ',
                state.duty_options[i]
                );
    }
    printf("echo_mode is %s\n", state.echo_mode ? "ON" : "OFF");
    printf("Press button or type a command: ");
}

void print_error(const Error_t error, const char *extra) {
    char *msg, *hint = "";
    switch (error) {
        case UNKNOWN_COMMAND:
            msg= "Unknown command";
            hint = "Usage: \n \
 echo             echo-mode on/off.\n \
 get_state        prints current freq & dc.\n \
 chg_freq[0..2]   changes frequency within 3 presets in Hz.\n \
 chg_dc[0..2]     changes duty-cycle whithin 3 presets in %.\n \
 set_dc[0..100]   changes current duty-cycle to other %.\n \
";
            break;
        case INVALID_CHG_INDEX:
            msg = "Invalid Change Index";
            hint = "Usage: chg_***[0..2]";
            break;
        case MALFORMED_CHG_DC:
            msg = "Malformed Change Duty-Cycle";
            hint = "Usage: chg_dc[0..2]";
            break;
        case MALFORMED_CHG_FREQ:
            msg = "Malformed Change Frequency";
            hint = "Usage: chg_freq[0..2]";
            break;
        case INVALID_SET_DC_VALUE:
            msg = "Invalid Set Duty-Cycle value";
            hint = "Usage: set_dc[0..100]";
            break;
        case MALFORMED_SET_DC:
            msg = "Malformed Set Duty-Cycle";
            hint = "Usage: set_dc[0..100]";
            break;
        default:
            msg = "Unknown error";
            break;
    }
    printf("Error[%i]: %s '%s', %s\n", error, msg, extra, hint);
}

bool chg_dc(tp_02_state_t *state, const char * line) {
    const char *line_args = line + strlen("chg_dc");
    if (line_args[0] == '[' && line_args[2] == ']') {
        if (line_args[1] >= '0' && line_args[1] <= '2') {
            state->duty_enabled_index = cti(line_args[1]);
        } else {
            print_error(INVALID_CHG_INDEX, line_args);
            return false;
        }
    } else {
        print_error(MALFORMED_CHG_DC, line);
        return false;
    }
    return true;
}

bool chg_freq(tp_02_state_t *state, const char * line) {
    const char *line_args = line + strlen("chg_freq");
    if (line_args[0] == '[' && line_args[2] == ']') {
        if (line_args[1] >= '0' && line_args[1] <= '2') {
            state->freq_enabled_index = cti(line_args[1]);
        } else {
            print_error(INVALID_CHG_INDEX, line_args);
            return false;
        }
    } else {
        print_error(MALFORMED_CHG_FREQ, line);
        return false;
    }
    return true;
}

bool set_dc(tp_02_state_t *state, const char * line) {
    const char *line_args = line + strlen("set_dc");
    if (strcmp("[reset]",line_args) == 0) { // set_dc[reset]
        state->duty_options[0] = DC_L;
        state->duty_options[1] = DC_M;
        state->duty_options[2] = DC_H;
        printf("dc values reseted\n");
    } else {
        uint8_t new_dc = -1;
        if (line_args[0] == '[' && line_args[2] == ']') { // set_dc[x]
            new_dc = cti(line_args[1]);
        } else if (line_args[0] == '[' && line_args[3] == ']') { // set_dc[xx]
            new_dc = cti(line_args[2]) + cti(line_args[1]) * 10;
        } else if (line_args[0] == '[' && line_args[4] == ']') { // set_dc[xxx]
            new_dc = cti(line_args[3]) + cti(line_args[2]) * 10 + cti(line_args[1]) * 100;
        }
        if (new_dc >= 0 && new_dc <= 100) {
            state->duty_options[state->duty_enabled_index] = new_dc;
        } else {
            print_error(INVALID_SET_DC_VALUE, line_args);
            return false;
        };
    }
    return true;
}

void rot_dc(tp_02_state_t *state) {
    state->duty_enabled_index = (state->duty_enabled_index + 1) % 3;
    led_duty_cycle_set_percentage(state->duty_options[state->duty_enabled_index]);
}

void rot_freq(tp_02_state_t *state) {
    state->freq_enabled_index = (state->freq_enabled_index + 1) % 3;
    led_frequency_set_hertz(state->freq_options[state->freq_enabled_index]);
}

void tp_02(void) {
    /**
     * From TP01
     */
    DDR_OUTPUT(B, PB7);
    DDR_INPUT(D, PD7);
    uint8_t button_history = 0;
    long press_cycles = 0;

    led_init();
    /**
     * From TP01
    */

    tp_02_state_t state = {
            .echo_mode = false,
            .duty_enabled_index = 0,
            .duty_options = {DC_L, DC_M, DC_H},
            .freq_enabled_index = 0,
            .freq_options = {FREQ_L, FREQ_M, FREQ_H},
            };
    char line[80];
    print_prompt(state);
    for(;;) {
        if (serial_incomming_data()) {
            fgets(line, 80, stdin);
            strtok(line, "\r\n");

            if (!state.echo_mode) {
                // Print command after [ENTER] since it's not being echoed
                printf("%s\n", line);
            }
            switch (line[0]) {
                case ECHO:
                    stdin = state.echo_mode ? &serial_input : &serial_input_echo;
                    state.echo_mode = !state.echo_mode;
                    break;
                case GET_:
                    switch (line[4]) {
                        case _STATE:
                            printf("Frequency: %uHz. Duty-Cycle: %u%%.",
                                   led_frequency_get_hertz(),
                                   led_duty_cycle_get_percentage());
                            break;
                        default:
                            print_error(UNKNOWN_COMMAND, line);
                            break;
                    }
                    break;
                case CHG_:
                    switch (line[4]) {
                        case _DC:
                            if (chg_dc(&state, line)) {
                                led_duty_cycle_set_percentage(state.duty_options[state.duty_enabled_index]);
                                printf("dc changed\n");
                            }
                            break;
                        case _FREQ:
                            if (chg_freq(&state, line)) {
                                led_frequency_set_hertz(state.freq_options[state.freq_enabled_index]);
                                printf("freq changed\n");
                            }
                            break;
                        default:
                            print_error(UNKNOWN_COMMAND, line);
                            break;
                    }
                    break;
                case SET_:
                    switch (line[4]) {
                        case _DC:
                            if (set_dc(&state, line)) {
                                led_duty_cycle_set_percentage(state.duty_options[state.duty_enabled_index]);
                                printf("freq set\n");
                            }
                            break;
                        default:
                            print_error(UNKNOWN_COMMAND, line);
                            break;
                    }
                    break;
                default:
                    print_error(UNKNOWN_COMMAND, line);
                    break;
            }
            print_prompt(state);
        } else {
            /**
            * From TP01
            */
            button_update(&button_history, PIN_IS_HIGH(D, PD7));

            if (button_is_down(&button_history)) {
                press_cycles++;
            }

            if (button_is_released(&button_history)) {
                if (press_cycles > CYCLES_IN_SECOND) {
                    rot_freq(&state);
                    printf("LONG PRESS (%lu c): changed frequency.\n", press_cycles);
                } else {
                    rot_dc(&state);
                    printf("QUICK PRESS (%lu c): changed duty_cycle.\n", press_cycles);
                }
                print_prompt(state);
                press_cycles = 0;
            }
            /**
            * From TP01
            */
        }
    }
}
