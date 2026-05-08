#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

const uint8_t DOUBLE_TAP_LAYER = 8;

typedef enum {
    TD_NONE,
    TD_HOLD,
    TD_SINGLE_TAP,
    TD_DOUBLE_TAP,
} td_state_t;

enum {
    X_LAYER,
    SOME_OTHER_DANCE
};

extern layer_state_t default_layer_state;

#define NO_ROW { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }

#define NO_LAYER {\
        NO_ROW, NO_ROW, NO_ROW, NO_ROW, NO_ROW, NO_ROW, NO_ROW, NO_ROW, NO_ROW, NO_ROW, NO_ROW, NO_ROW, NO_ROW, NO_ROW, NO_ROW, NO_ROW, \
    }

#define TRANS_ROW { KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, }
#define DL_KEYPAD_ROWS { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
            KC_F1, KC_F2, KC_F3, }, \
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
            KC_F4, KC_F5, KC_F6, }, \
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
            KC_F7, KC_F8, KC_F9, }, \
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
            KC_F10, KC_F11, KC_F12, }
#define XL_KEYPAD_ROWS { KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, \
            KC_1, KC_2, KC_3, }, \
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, \
            KC_4, KC_5, KC_6, }, \
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, \
            KC_7, KC_8, KC_9, }, \
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, \
            KC_BACKSPACE, KC_0, KC_ENTER, }

const uint16_t PROGMEM keymaps[DYNAMIC_KEYMAP_LAYER_COUNT][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        { KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_NO, KC_NO, 
            KC_NO, KC_NO, KC_NO, },
        { KC_Y, KC_U, KC_I, KC_O, KC_P, KC_EQUAL, KC_BACKSPACE, 
            KC_NO, KC_NO, KC_NO, },
        { KC_SEMICOLON, KC_H, KC_J, KC_K, KC_L, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, 
            KC_NO, KC_NO, KC_NO, },
        { KC_PAGE_UP, KC_SLASH, KC_N, KC_M, KC_COMMA, KC_ENTER, KC_HOME, 
            KC_NO, KC_NO, KC_NO, },
        { KC_RIGHT_SHIFT, KC_NO, KC_SPACE, KC_UP, KC_LEFT, KC_DOT, KC_END, 
            KC_NO, KC_NO, KC_NO, },
        { KC_RIGHT_ALT, KC_RIGHT_CTRL, KC_LANGUAGE_1, KC_DOWN, KC_RIGHT, KC_PAGE_DOWN, KC_NO,
            KC_NO, KC_NO, KC_NO, },

        { KC_NO, KC_NO, KC_2, KC_3, KC_4, KC_5, KC_6,
            KC_NO, KC_NO, KC_NO, },
        { KC_ESCAPE, KC_1, KC_W, KC_E, KC_R, KC_T, KC_BACKSLASH,
            KC_NO, KC_NO, KC_NO, },
        { KC_GRAVE, KC_Q, KC_S, KC_D, KC_F, KC_G, KC_QUOTE,
            KC_NO, KC_NO, KC_NO, },
        { KC_TAB, KC_A, KC_X, KC_C, KC_V, KC_B, KC_LEFT_GUI,
            KC_NO, KC_NO, KC_NO, },
        { KC_DELETE, KC_Z, KC_NO, KC_NO, KC_SPACE, KC_NO, KC_LEFT_SHIFT,
            KC_NO, KC_NO, KC_NO, },
        { KC_NO, KC_NO, KC_NO, TD(X_LAYER), KC_LANGUAGE_2, KC_LEFT_CTRL, KC_LEFT_ALT,
            KC_NO, KC_NO, KC_NO, },

        DL_KEYPAD_ROWS
    },
    [1] = {
        { KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_NO, KC_NO, 
            KC_NO, KC_NO, KC_NO, },
        { KC_Y, KC_U, KC_I, KC_O, KC_P, JP_YEN, KC_BACKSPACE, 
            KC_NO, KC_NO, KC_NO, },
        { JP_COLN, KC_H, KC_J, KC_K, KC_L, KC_LEFT_BRACKET, JP_RBRC, 
            KC_NO, KC_NO, KC_NO, },
        { KC_PAGE_UP, KC_SLASH, KC_N, KC_M, KC_COMMA, KC_ENTER, KC_HOME, 
            KC_NO, KC_NO, KC_NO, },
        { KC_RIGHT_SHIFT, KC_NO, KC_SPACE, KC_UP, KC_LEFT, KC_DOT, KC_END, 
            KC_NO, KC_NO, KC_NO, },
        { KC_LEFT_GUI, KC_RIGHT_CTRL, KC_LANGUAGE_1, KC_DOWN, KC_RIGHT, KC_PAGE_DOWN, KC_NO,
            KC_NO, KC_NO, KC_NO, },

        { KC_NO, KC_NO, KC_2, KC_3, KC_4, KC_5, KC_6,
            KC_NO, KC_NO, KC_NO, },
        { KC_ESCAPE, KC_1, KC_W, KC_E, KC_R, KC_T, JP_AT,
            KC_NO, KC_NO, KC_NO, },
        { JP_CIRC, KC_Q, KC_S, KC_D, KC_F, KC_G, JP_SCLN,
            KC_NO, KC_NO, KC_NO, },
        { KC_TAB, KC_A, KC_X, KC_C, KC_V, KC_B, JP_BSLS,
            KC_NO, KC_NO, KC_NO, },
        { KC_DELETE, KC_Z, KC_NO, KC_NO, KC_SPACE, KC_NO, KC_LEFT_SHIFT,
            KC_NO, KC_NO, KC_NO, },
        { KC_NO, KC_NO, KC_NO, TD(X_LAYER), KC_LANGUAGE_2, KC_LEFT_CTRL, KC_LEFT_ALT,
            KC_NO, KC_NO, KC_NO, },

        DL_KEYPAD_ROWS
    },
    [2] = {
        { KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_NO, KC_NO, 
            KC_NO, KC_NO, KC_NO, },
        { KC_Y, KC_U, KC_I, KC_O, KC_P, KC_EQUAL, KC_BACKSPACE, 
            KC_NO, KC_NO, KC_NO, },
        { KC_SEMICOLON, KC_H, KC_J, KC_K, KC_L, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, 
            KC_NO, KC_NO, KC_NO, },
        { KC_PAGE_UP, KC_SLASH, KC_N, KC_M, KC_COMMA, KC_ENTER, KC_HOME, 
            KC_NO, KC_NO, KC_NO, },
        { KC_RIGHT_SHIFT, KC_NO, KC_SPACE, KC_UP, KC_LEFT, KC_DOT, KC_END, 
            KC_NO, KC_NO, KC_NO, },
        { KC_RIGHT_ALT, KC_RIGHT_CTRL, KC_LANGUAGE_1, KC_DOWN, KC_RIGHT, KC_PAGE_DOWN, KC_NO,
            KC_NO, KC_NO, KC_NO, },

        { KC_NO, KC_NO, KC_2, KC_3, KC_4, KC_5, KC_6,
            KC_NO, KC_NO, KC_NO, },
        { KC_ESCAPE, KC_1, KC_W, KC_E, KC_R, KC_T, KC_BACKSLASH,
            KC_NO, KC_NO, KC_NO, },
        { KC_GRAVE, KC_Q, KC_S, KC_D, KC_F, KC_G, KC_QUOTE,
            KC_NO, KC_NO, KC_NO, },
        { KC_TAB, KC_A, KC_X, KC_C, KC_V, KC_B, KC_GLOBE,
            KC_NO, KC_NO, KC_NO, },
        { KC_DELETE, KC_Z, KC_NO, KC_NO, KC_SPACE, KC_NO, KC_LEFT_SHIFT,
            KC_NO, KC_NO, KC_NO, },
        { KC_NO, KC_NO, KC_NO, TD(X_LAYER), KC_LANGUAGE_2, KC_LEFT_GUI, KC_LEFT_ALT,
            KC_NO, KC_NO, KC_NO, },

        DL_KEYPAD_ROWS
    },
    [3] = {
        { KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_NO, KC_NO, 
            KC_NO, KC_NO, KC_NO, },
        { KC_Y, KC_U, KC_I, KC_O, KC_P, JP_YEN, KC_BACKSPACE, 
            KC_NO, KC_NO, KC_NO, },
        { JP_COLN, KC_H, KC_J, KC_K, KC_L, KC_LEFT_BRACKET, JP_RBRC, 
            KC_NO, KC_NO, KC_NO, },
        { KC_PAGE_UP, KC_SLASH, KC_N, KC_M, KC_COMMA, KC_ENTER, KC_HOME, 
            KC_NO, KC_NO, KC_NO, },
        { KC_RIGHT_SHIFT, KC_NO, KC_SPACE, KC_UP, KC_LEFT, KC_DOT, KC_END, 
            KC_NO, KC_NO, KC_NO, },
        { KC_GLOBE, KC_RIGHT_CTRL, KC_LANGUAGE_1, KC_DOWN, KC_RIGHT, KC_PAGE_DOWN, KC_NO,
            KC_NO, KC_NO, KC_NO, },

        { KC_NO, KC_NO, KC_2, KC_3, KC_4, KC_5, KC_6,
            KC_NO, KC_NO, KC_NO, },
        { KC_ESCAPE, KC_1, KC_W, KC_E, KC_R, KC_T, JP_AT,
            KC_NO, KC_NO, KC_NO, },
        { JP_CIRC, KC_Q, KC_S, KC_D, KC_F, KC_G, JP_SCLN,
            KC_NO, KC_NO, KC_NO, },
        { KC_TAB, KC_A, KC_X, KC_C, KC_V, KC_B, JP_BSLS,
            KC_NO, KC_NO, KC_NO, },
        { KC_DELETE, KC_Z, KC_NO, KC_NO, KC_SPACE, KC_NO, KC_LEFT_SHIFT,
            KC_NO, KC_NO, KC_NO, },
        { KC_NO, KC_NO, KC_NO, TD(X_LAYER), KC_LANGUAGE_2, KC_LEFT_GUI, KC_LEFT_ALT,
            KC_NO, KC_NO, KC_NO, },

        DL_KEYPAD_ROWS
    },
    [4] = {
        TRANS_ROW, TRANS_ROW, TRANS_ROW, TRANS_ROW, TRANS_ROW, TRANS_ROW, 

        TRANS_ROW,
        { KC_SYSTEM_SLEEP, KC_TRANSPARENT, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_MEDIA_PLAY_PAUSE, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_MUTE, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_SCROLL_LOCK, KC_PRINT_SCREEN, KC_APPLICATION, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},
        { KC_INSERT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, },
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_CAPS_LOCK, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},

        XL_KEYPAD_ROWS
    },
    [5] = {
        TRANS_ROW, TRANS_ROW, TRANS_ROW, 
        { KC_TRANSPARENT, KC_TRANSPARENT, JP_MHEN, JP_HENK, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, },
        TRANS_ROW,
        { KC_TRANSPARENT, KC_TRANSPARENT, JP_KANA, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, }, 

        TRANS_ROW,
        { KC_SYSTEM_SLEEP, KC_TRANSPARENT, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_MEDIA_PLAY_PAUSE, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_MUTE, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},
        { JP_ZKHK, KC_TRANSPARENT, KC_SCROLL_LOCK, KC_PRINT_SCREEN, KC_APPLICATION, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},
        { KC_INSERT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, },
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_CAPS_LOCK, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},

        XL_KEYPAD_ROWS
    },
    [6] = {
        TRANS_ROW, TRANS_ROW, TRANS_ROW, 
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_KP_ENTER, KC_TRANSPARENT, 
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, },
        TRANS_ROW, TRANS_ROW, 
        TRANS_ROW,
        { KC_SYSTEM_SLEEP, KC_TRANSPARENT, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_MEDIA_PLAY_PAUSE, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_MUTE, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_SYSTEM_DO_NOT_DISTURB, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},
        TRANS_ROW,
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_CAPS_LOCK, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},

        XL_KEYPAD_ROWS
    },
    [7] = {
        TRANS_ROW, TRANS_ROW, TRANS_ROW, 
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_KP_ENTER, KC_TRANSPARENT, 
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, },
        TRANS_ROW, TRANS_ROW, 
        TRANS_ROW,
        { KC_SYSTEM_SLEEP, KC_TRANSPARENT, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_MEDIA_PLAY_PAUSE, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_MUTE, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_SYSTEM_DO_NOT_DISTURB, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},
        TRANS_ROW,
        { KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_CAPS_LOCK, KC_TRANSPARENT, KC_TRANSPARENT,
            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT},

        XL_KEYPAD_ROWS
    },
    [8] = {
        TRANS_ROW, TRANS_ROW, TRANS_ROW, TRANS_ROW, TRANS_ROW, TRANS_ROW, 
        TRANS_ROW, TRANS_ROW, TRANS_ROW, TRANS_ROW, TRANS_ROW, TRANS_ROW,
        TRANS_ROW, TRANS_ROW, TRANS_ROW, TRANS_ROW, },
};

static uint8_t get_default_layer(void) {
    switch (default_layer_state) {
        case 1:
            return 0;
        case 2:
            return 1;
        case 4:
            return 2;
        case 8:
            return 3;
        default:
            return 0;
    }
}

static td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || state->pressed) {
            return TD_HOLD;
        } else {
            return TD_SINGLE_TAP;
        }
    } else if (state->count == 2) {
        if (state->interrupted || state->pressed) {
            return TD_HOLD;
        } else {
            return TD_DOUBLE_TAP;
        }
    } else {
        return TD_NONE;
    }
}

static td_state_t ld;

static void x_finished(tap_dance_state_t *state, void *user_data) {
    td_state_t cd = cur_dance(state);
    switch (cd) {
        case TD_SINGLE_TAP:
            layer_off(DOUBLE_TAP_LAYER);
            break;
        case TD_DOUBLE_TAP:
            layer_on(DOUBLE_TAP_LAYER);
            break;
        case TD_HOLD:
            layer_on(get_default_layer() + 4);
            break;
        default:
            break;
    }
    ld = cd;
}

static void x_reset(tap_dance_state_t *state, void *user_data) {
    switch (ld) {
        case TD_HOLD:
            // Why don't `layer_off(get_default_layer() + 4)`? Because default layer switch can be changed while holding.
            layer_off(4);
            layer_off(5);
            layer_off(6);
            layer_off(7);
            break;
        default:
            break;
    }
    ld = TD_NONE;
}

#ifdef VIAL_ENABLE
extern tap_dance_action_t tap_dance_actions[];
#else
tap_dance_action_t tap_dance_actions[16] = { };
#endif

void keyboard_post_init_user(void) {
    tap_dance_action_t ac = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset);
    tap_dance_actions[X_LAYER] = ac;
};
