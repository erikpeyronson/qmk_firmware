#include QMK_KEYBOARD_H

#include "keyboard.h"
#include "oled_driver.h"
#include "quantum.h"
#include "rgb.h"
#include "logo.h"
#include "common.h"

#define MY_LT(layer, kc) LT(layer, kc)

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for W, twice for switch to swedish layer
    [TD_SWE]  = ACTION_TAP_DANCE_LAYER_MOVE(KC_NO, Swe),
    [TD_BASE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_NO, Base),
};

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    my_rgb_init();
#endif

    // Customise these values to desired behaviour
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;
}
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    return true;
}

#include "keymap_out.h"