#include QMK_KEYBOARD_H

#include "oled_driver.h"
#include "quantum.h"

enum Layers { Base = 0, Swe, Num, Sym, Nav, Etc };

enum TapDanceActions { TD_Q_SWE = 0, TD_Q_BASE };

#define MY_LT(layer, kc) LT(layer, kc)

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for W, twice for switch to swedish layer
    [TD_Q_SWE]  = ACTION_TAP_DANCE_LAYER_MOVE(KC_Q, Swe),
    [TD_Q_BASE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_Q, Base),
};

// void keyboard_post_init_user(void) {
//     rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
//     rgb_matrix_sethsv_noeeprom(HSV_OFF);
// }

// #ifdef RGB_MATRIX_ENABLE


// bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
//     for (uint8_t i = led_min; i < led_max; i++) {
//         switch(get_highest_layer(layer_state|default_layer_state)) {
//             case Base:
//                 rgb_matrix_set_color(i, RGB_WHITE);
//                 break;
//             case Swe:
//                 rgb_matrix_set_color(i, RGB_YELLOW);
//                 break;
//             case Num:
//                 rgb_matrix_set_color(i, RGB_RED);
//                 break;
//             case Sym:
//                 rgb_matrix_set_color(i, RGB_GOLD);
//                 break;
//             case Etc:
//                 rgb_matrix_set_color(i, RGB_BLUE);
//                 break;

//             default:
//                 break;
//         }
//     }
//     return false;
// }

// #endif

#include "keymap_out.h"
