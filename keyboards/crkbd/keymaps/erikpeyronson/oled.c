#include "quantum.h"
#include "logo.h"
#include "oled_driver.h"
#include "common.h"

#include "print.h"

#include <ctype.h>

#define OLED_CHARS_PER_LINE 6

char     my_key_name = ' ';
uint16_t my_last_keycode;

char keymap_chars[6][3][5];
// uint8_t  last_row;
// uint8_t  last_col;

static const char PROGMEM code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void my_set_keylog(uint16_t keycode, keyrecord_t *record) {
    my_key_name     = ' ';
    my_last_keycode = keycode;
    if (IS_QK_MOD_TAP(keycode)) {
        keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_LAYER_TAP(keycode)) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_MODS(keycode)) {
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    } else if (IS_QK_ONE_SHOT_MOD(keycode)) {
        keycode = 0xE0 + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0xF) + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0x10);
    }
    if (keycode > ARRAY_SIZE(code_to_name)) {
        return;
    }

    // update keylog
    my_key_name = pgm_read_byte(&code_to_name[keycode]);
    // last_row = record->event.key.row;
    // last_col = record->event.key.col;
}

void my_set_keymap_chars(const uint16_t keymaps[6][MATRIX_ROWS][MATRIX_COLS]) {
    uint8_t rows = 3;
    uint8_t cols = 6;
    for (uint8_t layer = 0; layer < 6; ++layer) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t k = 1; k < cols; k++) {
                // my_last_keycode = ;
                keypos_t keypos = {k, i};
                uint16_t kc     = keymap_key_to_keycode(layer, keypos);
                my_set_keylog(kc, NULL);
                keymap_chars[layer][i][k - 1] = my_key_name;
                // oled_write_char(my_key_name, false);
            }
        }
    }
}

    // static const char *depad_str(const char *depad_str, char depad_char) {
    //     while (*depad_str == depad_char)
    //         ++depad_str;
    //     return depad_str;
    // }

    static void my_oled_render_keylog(void) {
        // const char *last_row_str = get_u8_str(last_row, ' ');
        // oled_write(depad_str(last_row_str, ' '), false);
        // oled_write_P(PSTR("x"), false);
        // const char *last_col_str = get_u8_str(last_col, ' ');
        // oled_write(depad_str(last_col_str, ' '), false);
        // oled_write_P(PSTR(", k"), false);
        // const char *last_keycode_str = get_u16_str(last_keycode, ' ');
        // oled_write(depad_str(last_keycode_str, ' '), false);
        // oled_write_P(PSTR(":"), false);
        // oled_write_char(my_key_name, false);
        // oled_write_char('@', false);

        uint8_t current_layer = get_highest_layer(layer_state);

        uint8_t rows = 3;
        uint8_t cols = 5;
        for (size_t i = 0; i < rows; i++) {
            for (size_t k = 0; k < cols; k++) {
                // my_last_keycode = ;
                // my_set_keylog(keymaps[i][k], NULL);
                // oled_set_cursor(k, i);
                oled_write_char(keymap_chars[current_layer][i][k], false);
                // oled_write_char(my_key_name, false);
            }
        }
    }

    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        if (is_keyboard_master()) {
            rotation = OLED_ROTATION_270;
        }
        return rotation;
    }

    void oled_write_captalized(const char *str, bool invert) {
        for (uint8_t i = 0; i < strlen(str); ++i) {
            oled_write_char(toupper(str[i]), false);
        }
    }

    void oled_render_selection(const char *str, bool is_active) {
        if (is_active) {
            oled_write_char('*', false);
            oled_write_captalized(str, false);
        } else {
            oled_write_char(' ', false);
            oled_write(str, false);
        }

        if (strlen(str) < 4) {
            oled_advance_page(false);
        }
    }

    void oled_render_layers(void) {
        const char *layers[] = {
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
        if (!is_keyboard_master()) {
            oled_render_layer_state();
        } else {
            // my_oled_render_logo();
            my_oled_render_keylog();
        }

        return false;
    }
