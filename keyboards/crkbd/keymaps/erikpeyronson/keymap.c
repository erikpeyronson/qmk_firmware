#include QMK_KEYBOARD_H

#include "oled_driver.h"
#include "quantum.h"

enum Layers{
  Base = 0,
  Swe,
  Num,
  Sym,
  Nav,
  Etc
};

enum TapDanceActions {
  TD_Q_SWE = 0,
  TD_Q_BASE
};

#define MY_LT(layer, kc) LT(layer, kc)

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for W, twice for switch to swedish layer
    [TD_Q_SWE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_Q, Swe),
    [TD_Q_BASE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_Q, Base),
};

#include "keymap_out.h"
#include "logo.h"


__attribute__((weak)) const char* get_logo(uint16_t* size) {
  return NULL;
}

void oled_render_logo(void) {
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

bool oled_task_user(void) {

  oled_render_logo();
  return false;
}