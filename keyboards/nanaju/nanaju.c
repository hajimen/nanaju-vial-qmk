/*
    Copyright (C) 2025 NAKAZATO Hajime

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"
#include "matrix.h"
#include "usb_device_state.h"
#include "qa_test.h"
#include QMK_KEYBOARD_H
extern uint16_t PROGMEM keymaps[DYNAMIC_KEYMAP_LAYER_COUNT][MATRIX_ROWS][MATRIX_COLS];

static pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#ifndef MATRIX_INPUT_PRESSED_STATE
#    define MATRIX_INPUT_PRESSED_STATE 0
#endif

void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter);

static inline void gpio_atomic_set_pin_output_low(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_low(pin);
    }
}

static inline void gpio_atomic_set_pin_input_high(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_input_high(pin);
    }
}

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return (gpio_read_pin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
}

static bool select_col(uint8_t col) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
        gpio_atomic_set_pin_output_low(pin);
        return true;
    }
    return false;
}

static void unselect_col(uint8_t col) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
        gpio_atomic_set_pin_input_high(pin);
    }
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        unselect_col(x);
    }
}

void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
    bool key_pressed = false;

    // Select col
    if (!select_col(current_col)) { // select col
        return;                     // skip NO_PIN col
    }
    matrix_output_select_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Check row pin state
        if (readMatrixPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= row_shifter;
            key_pressed = true;
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~row_shifter;
        }
    }

    // Unselect col
    unselect_col(current_col);
    matrix_output_unselect_delay(current_col, key_pressed); // wait for all Row signals to go HIGH
}

static bool is_conduct_test = false;
static matrix_row_t conduct_matrix[MATRIX_ROWS];
static bool blink_on = false;
static bool multi_blink_on = false;
static bool key_pressed = false;
static bool multi_key_pressed = false;
static int blink_count = 0;
static int max_blink_count = 255;
static virtual_timer_t repeat_vt;
#define REPEAT_MS 50
static uint8_t conduct_test_row_from = 0;
static uint8_t conduct_test_row_to = MATRIX_ROWS;

static void __not_in_flash_func(repeat_callback)(virtual_timer_t *vtp, void *p) {
    if (multi_key_pressed) {
        writePin(CONDUCT_TEST_LED, multi_blink_on);
    } else {
        writePin(CONDUCT_TEST_LED, blink_on || key_pressed);
    }

    blink_count = (blink_count + 1) % (max_blink_count * 2);
    blink_on = (blink_count < max_blink_count);
    multi_blink_on = (blink_count != 0);
}

static bool is_qa_test = false;

void matrix_init_kb(void) {
    gpio_atomic_set_pin_output_low(CONDUCT_TEST_LED);

    if (check_qa_fixture()) {
        is_qa_test = true;
        gpio_set_pin_input_high(ROTARY_R2);
        return;
    }

    unselect_cols();
    gpio_atomic_set_pin_input_high(ROTARY_C);
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            gpio_atomic_set_pin_input_high(row_pins[x]);
        }
    }

    matrix_scan();
    wait_ms(DEBOUNCE);
    matrix_scan();

    /* To enter conduct test mode, just one key should be pressed. */
    int n_pressed = 0;
    for (uint8_t row_idx = 0; row_idx < MATRIX_ROWS; row_idx ++) {
        matrix_row_t row = matrix_get_row(row_idx);
        if (row) {
            for (uint8_t col_idx = 0; col_idx < MATRIX_COLS; col_idx ++) {
                if ((row & (1 << col_idx))) {
                    n_pressed ++;
                }
            }
        }
    }

    if (n_pressed == 1) {
        is_conduct_test = matrix_get_row(CONDUCT_TEST_ROW) & (1 << CONDUCT_TEST_COL);
    }
#ifdef TEST_FIXTURE
    is_conduct_test = true;
#endif
    if (is_conduct_test) {
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
            matrix_row_t r = { 0 };
            for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
                if (keymaps[0][row_index][col_index]) {
                    r |= (1 << col_index);
                }
            }
            conduct_matrix[row_index] = r;
        }
        chVTObjectInit(&repeat_vt);
        chVTSetContinuous(&repeat_vt, TIME_MS2I(REPEAT_MS), repeat_callback, NULL);
    }
}

#define INVALID_DEFAULT_LAYER 255  // 255 never occurs. Always run set_single_default_layer(layer) after boot.
static uint8_t default_layer = INVALID_DEFAULT_LAYER;

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    if (((layer_state_t)1 << default_layer) != state) {
        default_layer = INVALID_DEFAULT_LAYER;
    }
    return default_layer_state_set_user(state);
}

bool matrix_scan_custom(matrix_row_t raw_matrix[]) {

    if (is_qa_test) {
        gpio_set_pin_input_high(ROTARY_R1);
    }
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    gpio_atomic_set_pin_output_low(ROTARY_C);
    matrix_output_select_delay();
    uint8_t layer = (1 - readMatrixPin(ROTARY_R1)) * 2 + (1 - readMatrixPin(ROTARY_R2));
    if (layer != default_layer) {
        default_layer = layer;
        set_single_default_layer(layer);
#ifdef TEST_FIXTURE
        if (layer == 0) {
            conduct_test_row_from = 0;
            conduct_test_row_to = 12;
        } else {
            conduct_test_row_from = 12;
            conduct_test_row_to = MATRIX_ROWS;
        }
#endif
    }
    gpio_atomic_set_pin_input_high(ROTARY_C);
    matrix_output_select_delay();

    if (is_qa_test) {
        gpio_set_pin_output(ROTARY_R1);
        gpio_write_pin(ROTARY_R1, 1);
        writePin(CONDUCT_TEST_LED, default_layer % 2);
        return false;
    }

    // Set col, read rows
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++, row_shifter <<= 1) {
        matrix_read_rows_on_col(curr_matrix, current_col, row_shifter);
    }

    if (is_conduct_test) {
        const int time_map[] = {2, 3, 5, 8};
        max_blink_count = time_map[default_layer];
        bool kp = false;
        bool mkp = false;
        for (uint8_t row_index = conduct_test_row_from; row_index < conduct_test_row_to; row_index++) {
            matrix_row_t row = curr_matrix[row_index];
            if (row) {
                for (uint8_t col_idx = 0; col_idx < MATRIX_COLS; col_idx ++) {
                    if ((row & (1 << col_idx))) {
                        if (!kp) {
                            kp = true;
                        } else {
                            mkp = true;
                        }
                    }
                }
            }
        }
        key_pressed = kp;
        multi_key_pressed = mkp;
        if (mkp) {
            return false;
        }

        bool still = false;
        for (uint8_t row_index = conduct_test_row_from; row_index < conduct_test_row_to; row_index++) {
            conduct_matrix[row_index] &= (~curr_matrix[row_index]);
            still = still || conduct_matrix[row_index];
        }
        if (!key_pressed && !still) {
            key_pressed = false;
            is_conduct_test = false;
            blink_on = false;
            chVTReset(&repeat_vt);
            writePin(CONDUCT_TEST_LED, false);
        }

        return false;
    }

    bool changed = memcmp(raw_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) memcpy(raw_matrix, curr_matrix, sizeof(curr_matrix));

    return changed;
}

#ifdef RAW_ENABLE
/*
macOS Globe key shortcuts (Globe + N etc.) require NKRO because
Consumer Page (Globe key) and Keyboard/Keypad Page
both should be sent from the same endpoint.
We can use KEYBOARD_SHARED_EP for the purpose but some bizzare hosts
may not work with it.
*/
void notify_usb_device_state_change_kb(struct usb_device_state usb_device_state) {
    if (!is_conduct_test && usb_device_state.configure_state == USB_DEVICE_STATE_CONFIGURED) {
        keymap_config.nkro = (usb_device_state.protocol == USB_PROTOCOL_REPORT);
    }
    notify_usb_device_state_change_user(usb_device_state);
}
#endif
