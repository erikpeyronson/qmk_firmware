#include "quantum.h"
#include "logo.h"
#include "oled_driver.h"
#include "common.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
      rotation = OLED_ROTATION_270;
    }
    return rotation;
}

static void oled_render_layer_state(void) {
    oled_clear();
    uint8_t current_layer = get_highest_layer(layer_state);

    char* const layers[] = {
        "Bas", "Swe", "Num", "Sym", "Nav", "Etc",
    };

    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("-----"), false);

    for (enum Layers layer = Base; layer < Etc; ++layer) {
        if (current_layer == layer) {
            oled_write_char('#', false);
        } else {
            // const char layer_number = (char)layer + '0';
            // oled_write(&layer_number, false);
            oled_write_char(' ', false);
        }

        oled_write_char(' ', false);
        oled_write(layers[layer], false);
    }

    oled_write_P(PSTR("-----"), false);

    led_t led_config = host_keyboard_led_state();
    if (led_config.caps_lock) {
        oled_write_P(PSTR("CAPS "), false);
    } else if (is_caps_word_on()) {
        oled_write_P(PSTR("WORD "), false);
    } else {
        oled_advance_page(true);
    }
    oled_write_ln_P(PSTR("-----"), false);
}

void my_oled_render_logo(void) {
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
      oled_render_layer_state();
    } else {
        my_oled_render_logo();
    }
    return false;
}