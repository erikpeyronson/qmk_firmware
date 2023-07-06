#include QMK_KEYBOARD_H

enum Layers{
  Base = 0,
  Swe,
  Num,
  Sym
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
