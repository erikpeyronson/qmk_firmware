#include QMK_KEYBOARD_H

#include "keyboard.h"
#include "oled.h"
#include "quantum.h"
#include "transactions.h"

#include "rgb.h"
#include "logo.h"
#include "common.h"

#include "oled.h"
#include "keymap_helpers.h"
#include "tap_dance.h"

#include "keymap_out.h"

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;


    my_rgb_init();
    my_oled_init(keymaps);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE

    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);

    uprintf("Character reprentation: %c \n\n", keycode_to_char(keycode, NULL));
#endif

    switch (keycode) {
#ifdef RGB_MATRIX_ENABLE
        case MY_CYCLE_RGB_MODE: {
            if (record->event.pressed) {
                my_next_rgb_mode();
            } else {
                // Do something else when release
                return false; // Skip all further processing of this key
            }
        }
#endif
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // my_set_keymap_chars(keymaps);
    return state;
}
