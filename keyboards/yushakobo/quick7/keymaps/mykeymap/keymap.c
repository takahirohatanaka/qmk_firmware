/* Copyright 2020 yushakobo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FUNC1,
    _LIGHTROOM
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    YUSHAURL = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    // [_BASE] = LAYOUT(
    //     KC_MUTE,   MO(_FUNC1), RGB_MOD,
    //     S(KC_TAB), KC_UP,      KC_TAB,
    //     KC_LEFT,   KC_DOWN,    KC_RGHT
    // ),
    // [_FUNC1] = LAYOUT(
    //     RESET,   KC_TRNS, RGB_TOG,
    //     KC_HOME, KC_VOLU, KC_END,
    //     KC_MPRV, KC_VOLD, KC_MNXT
    // )

    // my layer is here
    [_BASE] = LAYOUT(
        KC_ESC, TG(_LIGHTROOM), KC_MUTE,
        KC_PGUP, KC_UP, KC_PGDOWN,
        KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [_FUNC1] = LAYOUT(
        KC_TRNS, KC_H, KC_TRNS,
        KC_D, KC_E, KC_F,
        KC_A, KC_B, KC_TRNS
    ),
    [_LIGHTROOM] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_D, KC_E, KC_F,
        LCMD(KC_Z), LCMD(LSFT(KC_Z)), KC_BSLASH
    ),
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

void encoder_update_user(uint8_t index, bool clockwise) {
    // Right encoder
    if (index == 1) {
        if(layer_state_is(_LIGHTROOM)) {
            if (clockwise) {
                tap_code(KC_DOWN);
            } else {
                tap_code(KC_UP);
            }

            return;
        }

        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _FUNC1:
        rgblight_setrgb (RGB_ORANGE);
        break;
    case _LIGHTROOM:
        rgblight_setrgb (RGB_TEAL);
        break;
    case _BASE:
    default:
        rgblight_setrgb(0x40, 0x40, 0x40);
        break;
    }

  return state;
}
