#include QMK_KEYBOARD_H

#include "keyboard.h"
#include "oled_driver.h"
#include "quantum.h"
#include "transactions.h"
#include "process_tap_dance.h"

#include "rgb.h"
#include "logo.h"
#include "common.h"

#include "oled.h"
#include "keymap_helpers.h"

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
    my_set_keymap_chars(keymaps);
}

void send_closed_braces(char open, char close) {
    // println("Function called");
    // SEND_STRING("{}" SS_TAP(X_LEFT));
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
                // Do something elhjse when release
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

int cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        else
            return SINGLE_HOLD;
    } else if (state->count == 2) {
        /*
         * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
         * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
         * keystrokes of the key, and not the 'double tap' action/macro.
         */
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TRIPLE_TAP;
        else
            return TRIPLE_HOLD;
    } else
        return 8; // magic number. At some point this method will expand to work for more presses
}

static tap xtap_state = {.is_press_action = true, .state = 0};

void td_curly_bracked_finished(tap_dance_state_t *state, void *user_data) {
    bracket_info_t *bracket_info = (bracket_info_t *)user_data;

    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:
            if (bracket_info->is_shifted) {
                register_code(KC_LEFT_SHIFT);
            }
            register_code(bracket_info->kc_open);
            break;
        case SINGLE_HOLD:
            if (bracket_info->is_shifted) register_code(KC_LEFT_SHIFT);
            register_code(bracket_info->kc_open);
            register_code(bracket_info->kc_close);

            if (bracket_info->is_shifted) unregister_code(KC_LEFT_SHIFT);
            unregister_code(bracket_info->kc_open);
            unregister_code(bracket_info->kc_close);
            register_code(KC_LEFT);
            break;
        case DOUBLE_TAP:
            if (bracket_info->is_shifted) register_code(KC_LEFT_SHIFT);
            register_code(bracket_info->kc_close);
            break;
    }
}

void td_curly_bracketd_reset(tap_dance_state_t *state, void *user_data) {
    bracket_info_t *bracket_info = (bracket_info_t *)user_data;
    switch (xtap_state.state) {
        case SINGLE_TAP:
            if (bracket_info->is_shifted) {
                unregister_code(KC_LEFT_SHIFT);
            }
            unregister_code(bracket_info->kc_open);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LEFT);
            break;
        case DOUBLE_TAP:
            if (bracket_info->is_shifted) {
                unregister_code(KC_LEFT_SHIFT);
            }
            unregister_code(bracket_info->kc_close);
            break;
    }
    xtap_state.state = 0;
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for W, twice for switch to swedish layer
    [TD_SWE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_NO, Swe), [TD_BASE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_NO, Base), [TD_CURLY_BRACKETS] = MY_ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_curly_bracked_finished, td_curly_bracketd_reset, (void *)&brackets[TD_CURLY_BRACKETS]), [TD_SQUARE_BRACKETS] = MY_ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_curly_bracked_finished, td_curly_bracketd_reset, (void *)&brackets[TD_SQUARE_BRACKETS]), [TD_PARENTESES] = MY_ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_curly_bracked_finished, td_curly_bracketd_reset, (void *)&brackets[TD_PARENTESES]), [TD_LTGT] = MY_ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_curly_bracked_finished, td_curly_bracketd_reset, (void *)&brackets[TD_LTGT]),
};
