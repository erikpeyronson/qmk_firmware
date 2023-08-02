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
#ifdef RGB_MATRIX_ENABLE
    my_rgb_init();
#endif

    // Customise these values to desired behaviour
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    transaction_register_rpc(SYNC_RGB_MODE, sync_rgb_mode);
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

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for W, twice for switch to swedish layer
    [TD_SWE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_NO, Swe), [TD_BASE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_NO, Base), [TD_CURLY_BRACKETS] = MY_ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_curly_bracked_finished, td_curly_bracketd_reset, (void *)&brackets[TD_CURLY_BRACKETS]), [TD_SQUARE_BRACKETS] = MY_ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_curly_bracked_finished, td_curly_bracketd_reset, (void *)&brackets[TD_SQUARE_BRACKETS]), [TD_PARENTESES] = MY_ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_curly_bracked_finished, td_curly_bracketd_reset, (void *)&brackets[TD_PARENTESES]), [TD_LTGT] = MY_ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_curly_bracked_finished, td_curly_bracketd_reset, (void *)&brackets[TD_LTGT]),
};
