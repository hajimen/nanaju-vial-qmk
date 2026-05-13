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
#include "qa_test.h"
#include QMK_KEYBOARD_H

#define R1 GP18
#define R2 GP19
#define R3 GP20
#define R4 GP22

#define C1 GP23
#define C2 GP24
#define C3 GP25

#define M0 GP0
#define M1 GP1
#define M2 GP2
#define M3 GP3
#define M4 GP4
#define M5 GP5
#define M6 GP6
#define M7 GP7
#define M8 GP8
#define M9 GP9
#define M10 GP10
#define M11 GP11
#define M12 GP12
#define M13 GP13
#define M14 GP14
#define M15 GP15
#define M16 GP29
#define M17 GP28
#define M18 GP27
#define M19 GP26

static bool check_conduct(pin_t left, pin_t right, const pin_t *group, int n_group) {
    for (int i = 0; i < n_group; i ++) {
        gpio_set_pin_input_low(group[i]);
    }
    gpio_set_pin_output(right);
    gpio_write_pin(right, 1);

    wait_ms(1);

    if (!gpio_read_pin(left)) {
        return false;
    }

    for (int i = 0; i < n_group; i ++) {
        pin_t gp = group[i];
        if (gp == left || gp == right) {
            continue;
        }
        if (gpio_read_pin(gp)) {
            // Wrong conduct
            return false;
        }
    }

    // Check by reverse direction
    gpio_set_pin_input_low(right);
    gpio_set_pin_output(left);
    gpio_write_pin(left, 1);

    wait_ms(1);

    if (!gpio_read_pin(right)) {
        return false;
    }
    for (int i = 0; i < n_group; i ++) {
        pin_t gp = group[i];
        if (gp == left || gp == right) {
            continue;
        }
        if (gpio_read_pin(gp)) {
            // Wrong conduct
            return false;
        }
    }
    return true;
}

static bool check_p_conduct(pin_t left, pin_t right) {
    const pin_t group[] = {R1, R2, R3, R4, C1, C2, C3};
    return check_conduct(left, right, group, sizeof(group) / sizeof(pin_t));
}

static bool check_m_conduct(pin_t left, pin_t right) {
    const pin_t group[] = {M0, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11, M12, M13, M14, M15, M16, M17, M18, M19};
    return check_conduct(left, right, group, sizeof(group) / sizeof(pin_t));
}

bool check_qa_fixture(void) {
    gpio_set_pin_input(ROTARY_C);

    gpio_set_pin_input(C1);
    gpio_set_pin_input(C2);
    gpio_set_pin_input(C3);

    gpio_set_pin_output(R2);
    gpio_write_pin(R2, 1);
    gpio_set_pin_output(R3);
    gpio_write_pin(R3, 1);
    gpio_set_pin_output(R4);
    gpio_write_pin(R4, 1);

    wait_ms(1);

    if (!gpio_read_pin(C1) && !gpio_read_pin(C2) && !gpio_read_pin(C3)) {
        return false;
    }

    gpio_set_pin_input(R2);
    gpio_set_pin_input(R3);
    gpio_set_pin_input(R4);

    gpio_set_pin_output(C1);
    gpio_write_pin(C1, 1);
    gpio_set_pin_output(C2);
    gpio_write_pin(C2, 1);
    gpio_set_pin_output(C3);
    gpio_write_pin(C3, 1);

    wait_ms(1);

    if (!gpio_read_pin(R2) && !gpio_read_pin(R3) && !gpio_read_pin(R4)) {
        return false;
    }

    bool ok = true;
    const pin_t p_pairs[][2] = {{C1, R2}, {C2, R3}, {C3, R4}};
    for (int i = 0; i < sizeof(p_pairs) / sizeof(pin_t[2]); i ++) {
        if (!check_p_conduct(p_pairs[i][0], p_pairs[i][1])) {
            ok = false;
            break;
        }
    }
    if (ok) {
        // LED on
        gpio_set_pin_output(R1);
        gpio_write_pin(R1, 1);
    }

    ok = true;
    const pin_t m_pairs[][2] = {{M1, M2}, {M3, M5}, {M6, M7}, {M9, M10}, {M11, M13}, {M14, M15}, {M16, M17}, {M18, M19}};
    for (int i = 0; i < sizeof(m_pairs) / sizeof(pin_t[2]); i ++) {
        if (!check_m_conduct(m_pairs[i][0], m_pairs[i][1])) {
            ok = false;
            break;
        }
    }
    if (ok) {
        const pin_t leds[] = {M0, M4, M8, M12};
        for (int i = 0; i < sizeof(leds) / sizeof(pin_t); i ++) {
            // LED on
            gpio_set_pin_output(leds[i]);
            gpio_write_pin(leds[i], 1);
        }
    }

    return true;
}
