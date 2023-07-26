#include "quantum.h"
#include "logo.h"
#include "oled_driver.h"
#include "common.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

static void oled_render_layer_state(void) {
    uint8_t layer = get_highest_layer(layer_state);

    switch (layer) {
        case Base:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case Swe:
            oled_write_ln_P(PSTR("Swe"), false);
            break;
        case Num:
            oled_write_ln_P(PSTR("Num"), false);
            break;
        case Sym:
            oled_write_ln_P(PSTR("Sym"), false);
            break;
        case Nav:
            oled_write_ln_P(PSTR("Nav"), false);
            break;
        case Etc:
            oled_write_ln_P(PSTR("Etc"), false);
            break;
    }

    led_t led_config = host_keyboard_led_state();

    oled_write_ln_P(PSTR(""), false);

    if (led_config.caps_lock) {
        oled_write_ln_P(PSTR("CAPS"), false);
    } else if (is_caps_word_on()) {
        oled_write_ln_P(PSTR("WORD"), false);
    } else {
        oled_write_ln_P(PSTR(""), false);
    }

  // oled_scroll_right();
}

void my_oled_render_logo(void) {
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

bool oled_task_user(void) {
    // if (is_keyboard_master()) {
    oled_render_layer_state();
    // } else {
    //     my_oled_render_logo();
    // }
    return false;
}