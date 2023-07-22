#include QMK_KEYBOARD_H

#include "keyboard.h"
#include "oled_driver.h"
#include "quantum.h"

enum Layers { Base = 0, Swe, Num, Sym, Nav, Etc };

enum TapDanceActions { TD_SWE = 0, TD_BASE };

#define MY_LT(layer, kc) LT(layer, kc)

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for W, twice for switch to swedish layer
    [TD_SWE]  = ACTION_TAP_DANCE_LAYER_MOVE(KC_NO, Swe),
    [TD_BASE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_NO, Base),
};

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);

    // Customise these values to desired behaviour
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;
}
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    return true;
}

#include "keymap_out.h"

#ifdef RGB_MATRIX_ENABLE

const int led_count = 46 + 7;

// int leds[] = {6, 6, 17, 18, 29, 30, 36, 37, 38, 41, 44, 45, 46};

struct ColorBinding {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
};

struct ColorBinding layer_color_mappings[] = {{RGB_WHITE}, {RGB_YELLOW}, {RGB_BLUE}, {RGB_GREEN}, {RGB_PINK}, {RGB_RED}};

bool rgb_matrix_indicators_user() {
    uint16_t layer = get_highest_layer(layer_state | default_layer_state);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 6; ++col) {
            keypos_t current_key   = {.col = col, .row = row};
            uint8_t  current_layer = layer;
            uint16_t kc            = keymap_key_to_keycode(current_layer, current_key);

            while (true) {
                kc = keymap_key_to_keycode(current_layer, current_key);
                if (current_layer > 0 && (kc == KC_TRANSPARENT || IS_LAYER_OFF(current_layer))) {
                    current_layer--;
                } else {
                    break;
                }
            }

            if (kc != KC_NO && kc != KC_TRANSPARENT) {
                uint8_t              led_index = g_led_config.matrix_co[row][col];
                struct ColorBinding* rgb       = &layer_color_mappings[current_layer];
                rgb_matrix_set_color(led_index, rgb->red, rgb->green, rgb->blue);
            }
        }
    }
    return false;
}

#endif