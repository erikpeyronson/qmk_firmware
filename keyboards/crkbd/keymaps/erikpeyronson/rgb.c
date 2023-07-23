#ifdef RGB_MATRIX_ENABLE

// clang-format off
#include "rgb.h"
#include "rgb_matrix.h"
#include "common.h"
// clang-format on

struct ColorBinding {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
};

void my_rgb_init(void) {
    // Turn all leds off during startup
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

struct ColorBinding get_color(uint16_t layer) {
    switch (layer) {
        case Base:
            return (struct ColorBinding){RGB_WHITE};
        case Swe:
            return (struct ColorBinding){RGB_YELLOW};
        case Num:
            return (struct ColorBinding){RGB_BLUE};
        case Sym:
            return (struct ColorBinding){RGB_GREEN};
        case Nav:
            return (struct ColorBinding){RGB_ORANGE};
        case Etc:
            return (struct ColorBinding){RGB_RED};
        default:
            return (struct ColorBinding){RGB_OFF};
    }
}

int8_t get_layer_with_binding(uint8_t layer, const keypos_t keypos) {
    uint16_t kc = keymap_key_to_keycode(layer, keypos);

    while (layer > 0 && (kc == KC_TRANSPARENT || IS_LAYER_OFF(layer))) {
        layer--;
        kc = keymap_key_to_keycode(layer, keypos);
    }

    if (kc != KC_NO && kc != KC_TRANSPARENT) {
        return layer;
    }

    return -1;
}

bool rgb_matrix_indicators_user() {
    uint16_t current_layer = get_highest_layer(layer_state | default_layer_state);
    uint8_t  first_row, last_row;

    // To save some clock cycles let each half light its own leds rather than
    // both sides lighting all
    if (is_keyboard_master()) {
        first_row = 0;
        last_row  = 4;
    } else {
        first_row = 4;
        last_row  = 8;
    }

    for (int row = first_row; row < last_row; ++row) {
        for (int col = 0; col < 6; ++col) {
            keypos_t            current_key = {.col = col, .row = row};
            uint8_t             led_index   = g_led_config.matrix_co[row][col];
            uint8_t             layer       = get_layer_with_binding(current_layer, current_key);
            struct ColorBinding rgb         = get_color(layer);

            rgb_matrix_set_color(led_index, rgb.red, rgb.green, rgb.blue);
        }
    }
    return false;
}

#endif