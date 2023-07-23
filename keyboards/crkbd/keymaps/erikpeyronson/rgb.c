#ifdef RGB_MATRIX_ENABLE

#include "rgb.h"

#include "rgb_matrix.h"

struct ColorBinding {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
};

struct ColorBinding layer_color_mappings[] = {{RGB_WHITE}, {RGB_YELLOW}, {RGB_BLUE}, {RGB_GREEN}, {RGB_PINK}, {RGB_RED}};


void my_rgb_init(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}


bool rgb_matrix_indicators_user() {
    uint16_t layer = get_highest_layer(layer_state | default_layer_state);

    uint8_t low, high;

    if (is_keyboard_master()) {
      low = 0;
      high = 4;
    } else
    {
      low = 4 ;
      high = 8;
    }

      for (int row = low; row < high; ++row) {
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