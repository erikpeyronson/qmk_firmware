#include QMK_KEYBOARD_H

#include "keyboard.h"
#include "oled_driver.h"
#include "quantum.h"

enum Layers { Base = 0, Swe, Num, Sym, Nav, Etc };

enum TapDanceActions { TD_Q_SWE = 0, TD_Q_BASE };

#define MY_LT(layer, kc) LT(layer, kc)

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for W, twice for switch to swedish layer
    [TD_Q_SWE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_Q, Swe),
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
  // for(int i = 0; i < 54; ++i) {
  //   rgb_matrix_set_color(i, RGB_WHITE);
  // }
  uint16_t layer = get_highest_layer(layer_state | default_layer_state);
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 12; ++col) {
      keypos_t current_key;  // {.col = col, .row = row};
      if (col > 5) {
        current_key.col = 11 - col;
      } else {
        current_key.col = col;
      }
      current_key.row = row;
      uint16_t kc = keymap_key_to_keycode(layer, current_key);

      if (kc != KC_NO && kc != KC_TRANSPARENT) {
        uint8_t led_index = led_mappings[row][col];
        // right hand
        if (col > 6) {
          led_index += 27;
        }
        struct ColorBinding* rgb = &layer_color_mappings[layer];
        rgb_matrix_set_color(led_index, rgb->red, rgb->green, rgb->blue);
      }
    }
  }
  // uint8_t led_index = led_mappings[0][0] + 27;
  // rgb_matrix_set_color(led_index, RGB_WHITE);
  return false;
}

#endif