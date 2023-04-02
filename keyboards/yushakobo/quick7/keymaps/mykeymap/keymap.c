#include QMK_KEYBOARD_H

#define RGB_MY_DEFAULT 0x40, 0x40, 0x40
#define HSV_MY_DEFAULT 0x0, 0x0, 0x80

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FUNC1
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    YUSHAURL = SAFE_RANGE
};

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
//    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD);
//    rgblight_setrgb_noeeprom(RGB_MY_DEFAULT);
    rgblight_sethsv_noeeprom(HSV_MY_DEFAULT);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        TO(0),     TO(1),      KC_MUTE,
        KC_PGUP,   KC_UP,      KC_PGDN,
        KC_LEFT,   KC_DOWN,    KC_RGHT
    ),
    [_FUNC1] = LAYOUT(
        KC_TRNS,   KC_TRNS, RGB_TOG,
        KC_HOME, KC_UP, KC_END,
        KC_LEFT, KC_DOWN, KC_RGHT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case YUSHAURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://yushakobo.jp/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case _FUNC1:
            if (index == 1) {
                if (clockwise) {
                    tap_code(KC_MS_WH_UP);
                } else {
                    tap_code(KC_MS_WH_DOWN);
                }
            }
            break;

        case _BASE:
        default:
            if (index == 1) {
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            }
            break;
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _FUNC1:
            rgblight_setrgb (RGB_ORANGE);
            break;
        case _BASE:
        default:
            rgblight_sethsv(HSV_MY_DEFAULT);
            break;
    }

    return state;
}
