#include "quantum.h"
#include "logo.h"
#include "oled_driver.h"
#include "common.h"

#include "print.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        rotation = OLED_ROTATION_270;
    }
    return rotation;
}

void oled_render_selection(const char* str, bool is_active) {
    if (is_active) {
        oled_write_char('#', false);
    } else {
        oled_write_char(' ', false);
    }

    oled_write(str, false);
    if (strlen(str) < 4) {
        oled_advance_page(false);
    }
}

void oled_render_layers(void) {
    const char* layers[] = {
        "Base", "Swed", "Numb", "Symb", "Nav", "Etc",
    };
    uint8_t current_layer = get_highest_layer(layer_state);

    for (uint8_t layer = 0; layer < 6; ++layer) {
        oled_render_selection(layers[layer], (current_layer == layer));
    }
}

void oled_render_locks(void) {
    led_t led_config = host_keyboard_led_state();
    oled_render_selection("Word", is_caps_word_on());
    oled_render_selection("Caps", led_config.caps_lock);
    oled_render_selection("Scrl", led_config.num_lock);
    oled_render_selection("Num", led_config.num_lock);
}

static void oled_render_layer_state(void) {
    oled_clear();

    oled_write_P(PSTR("-----"), false);
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("-----"), false);

    oled_render_layers();

    oled_write_P(PSTR("-----"), false);
    oled_write_P(PSTR("LOCKS"), false);
    oled_write_P(PSTR("-----"), false);

    oled_render_locks();

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