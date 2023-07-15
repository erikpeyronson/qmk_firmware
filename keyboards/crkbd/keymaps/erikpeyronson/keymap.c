#include QMK_KEYBOARD_H

#include "oled_driver.h"
#include "quantum.h"
#include "keyboard.h"

enum Layers { Base = 0, Swe, Num, Sym, Nav, Etc };

enum TapDanceActions { TD_Q_SWE = 0, TD_Q_BASE };

#define MY_LT(layer, kc) LT(layer, kc)

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for W, twice for switch to swedish layer
    [TD_Q_SWE]  = ACTION_TAP_DANCE_LAYER_MOVE(KC_Q, Swe),
    [TD_Q_BASE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_Q, Base),
};

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

#include "keymap_out.h"

#ifdef RGB_MATRIX_ENABLE

const int led_count = 46 + 7;

int leds[] = {6, 6, 17, 18, 29, 30, 36, 37, 38, 41, 44, 45, 46};

// clang-format off
uint8_t led_mappings[4][6] = {
  {24, 23, 18, 17, 10, 9 },
  {25, 22, 19, 16, 11, 8 },
  {26, 21, 20, 15, 12, 7 },
  {0,  0,  0,  14, 13,  6},
};
// clang-format on

struct ColorBinding {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
};

struct ColorBinding layer_color_mappings[] = {
    {RGB_OFF}, {RGB_YELLOW}, {RGB_BLUE}, {RGB_GREEN}, {RGB_PINK},
};

bool rgb_matrix_indicators_user() {
    uint16_t layer = get_highest_layer(layer_state | default_layer_state);
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 6; ++col) {
            keypos_t current_key; // {.col = col, .row = row};
            current_key.col = col;
            current_key.row = row;
            uint16_t kc = keymap_key_to_keycode(layer, current_key);
            if (kc != KC_NO && kc != KC_TRANSPARENT) {
                struct ColorBinding* rgb = &layer_color_mappings[layer];
                rgb_matrix_set_color(led_mappings[row][col], rgb->red, rgb->green, rgb->blue);
            }
        }
    }
    return false;

    // switch (get_highest_layer(layer_state | default_layer_state)) {
    //     case Swe:
    //         for (int row = 0; row < 4; ++row) {
    //             for (int col = 0; col < 6; ++col) {
    //                 uint16_t kc = keymaps[Swe][row][col];
    //                 if (kc != KC_NO) {
    //                     rgb_matrix_set_color(led_mappings[row][col], RGB_YELLOW);
    //                 }
    //             }
    //         }
    //         break;
    //     case Num:
    //         for (int row = 0; row < 4; ++row) {
    //             for (int col = 0; col < 6; ++col) {
    //                 uint16_t kc = keymaps[Num][row][col];
    //                 if (kc != KC_NO) {
    //                     rgb_matrix_set_color(led_mappings[row][col], RGB_BLUE);
    //                 }
    //             }
    //         }
    //         break;
    //     case Sym:
    //         for (int row = 0; row < 4; ++row) {
    //             for (int col = 0; col < 6; ++col) {
    //                 uint16_t kc = keymaps[Sym][row][col];
    //                 if (kc != KC_NO) {
    //                     rgb_matrix_set_color(led_mappings[row][col], RGB_RED);
    //                 }
    //             }
    //         }

    //         break;
    //     case Nav:
    //         for (int row = 0; row < 4; ++row) {
    //             for (int col = 0; col < 6; ++col) {
    //                 uint16_t kc = keymaps[Nav][row][col];
    //                 if (kc != KC_NO) {
    //                     rgb_matrix_set_color(led_mappings[row][col], RGB_RED);
    //                 }
    //             }
    //         }
    //         // rgb_matrix_set_color(i, RGB_BLUE);
    //         break;

    //     default:
    //         break;
    // }
    // return false;
}

#endif
