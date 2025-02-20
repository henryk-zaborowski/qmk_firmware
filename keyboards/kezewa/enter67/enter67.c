/*
 * Copyright 2024 Henryk Zaborowski (henryk-zaborowski)
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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  {   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14 },
  {  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29 },
  {  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41, NO_LED,  42,  43 },
  {  44, NO_LED,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57 },
  {  58,  59,  60,  61, 62, 63, NO_LED, NO_LED, NO_LED,  64,  65, NO_LED,  66,  67,  68 }
}, {
    // Esc, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace, Ins
    {   0,   0 }, {  15,   0 }, {  30,   0 }, {  45,   0 }, {  60,   0 }, {  75,   0 }, {  90,   0 }, { 105,   0 }, { 120,   0 }, { 135,   0 }, { 150,   0 }, { 165,   0 }, { 180,   0 }, { 202,   0 }, { 225,   0 },
    // Tab, Q, W, E, R, T, Y, U, I, O, P, [, ],  , Del
    {   7,  16 }, {  22,  16 }, {  37,  16 }, {  52,  16 }, {  67,  16 }, {  82,  16 }, {  97,  16 }, { 112,  16 }, { 127,  16 }, { 142,  16 }, { 157,  16 }, { 172,  16 }, { 187,  16 }, { 206,  16 }, { 225,  16 },
    // Capslock, A, S, D, F, G, H, J, K, L, ;, ', Return, Page Up
    {  11,  32 }, {  26,  32 }, {  41,  32 }, {  56,  32 }, {  71,  32 }, {  86,  32 }, { 101,  32 }, { 116,  32 }, { 131,  32 }, { 146,  32 }, { 161,  32 }, { 176,  32 }, { 198,  32 }, { 225,  32 },
    // LShift, Z, X, C, V, B, N, M, ,, ., /, Shift, Up, Page Down
    {  18,  48 }, {  30,  48 }, {  45,  48 }, {  60,  48 }, {  75,  48 }, {  90,  48 }, { 105,  48 }, { 120,  48 }, { 135,  48 }, { 150,  48 }, { 165,  48 }, { 191,  48 }, { 210,  48 }, { 225,  48 },
    // Ctrl, GUI, Alt, LSpace, Space, RSpace, RAlt, FN, Left, Down, Right
    {   3,  64 }, {  22,  64 }, {  30,  64 }, {  68,  64 }, {  92,  64 }, { 110,  64 }, { 135,  64 }, { 153,  64 }, { 195,  64 }, { 210,  64 }, { 225,  64 }
}, {
    // Esc, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace, Ins
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    // Tab, Q, W, E, R, T, Y, U, I, O, P, [, ],  , Del
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    // Capslock, A, S, D, F, G, H, J, K, L, ;, ', Return, Page Up
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    // LShift, Z, X, C, V, B, N, M, ,, ., /, Shift, Up, Page Down
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
    // Ctrl, GUI, Alt, Space, RAlt, FN, Left, Down, Right
    1, 1, 1, 4, 4, 4, 1, 1, 1, 1, 1
} };

void suspend_power_down_kb(void)
{
    rgb_matrix_set_color_all(0, 0, 0);
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void)
{
    rgb_matrix_set_suspend_state(false);
}

void suspend_power_down_user(void) {
    rgb_matrix_set_color_all(0, 0, 0);
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
        rgb_matrix_set_suspend_state(false);
}
#endif

#if defined(RGB_MATRIX_ENABLE) && defined(CAPS_LOCK_LED_INDEX)

    bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
        if (!process_record_user(keycode, record)) {
            return false;
        }
        switch (keycode) {
        #ifdef RGB_MATRIX_ENABLE
            case RGB_TOG:
                if (record->event.pressed) {
                    switch (rgb_matrix_get_flags()) {
                        case LED_FLAG_ALL: {
                            rgb_matrix_set_flags(LED_FLAG_NONE);
                            rgb_matrix_set_color_all(0, 0, 0);
                        } break;
                        default: {
                            rgb_matrix_set_flags(LED_FLAG_ALL);
                        } break;
                    }
                }
                if (!rgb_matrix_is_enabled()) {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable();
                }
                return false;
        #endif
        }
        return true;
    }

    bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
        if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
            return false;
        }

        if (host_keyboard_led_state().caps_lock) {
            RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 255, 255, 255);
        } else {
            if (!rgb_matrix_get_flags()) {
                RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 0, 0, 0);
            }
        }
        return true;
    }

#endif
