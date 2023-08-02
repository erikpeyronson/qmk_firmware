#pragma once

#include "quantum.h"

enum TapDanceActions { TD_CURLY_BRACKETS = 0, TD_SQUARE_BRACKETS, TD_PARENTESES, TD_LTGT, TD_SWE, TD_BASE };

enum Layers { Base = 0, Swe, Num, Sym, Nav, Etc };

typedef enum _RgbMode { EACH_KEY = 0, THUMBS_HINT, THUMBS_SOLID, OFF } RgbMode;

enum KeyCodes { MY_CYCLE_RGB_MODE = SAFE_RANGE, MY_SEND_CURLY_BRACKETS, MY_SEND_SQUARE_BRACKETS, MY_SEND_PARENTHESES, MY_SEND_LT_GT };

typedef struct _my_state_t {
    RgbMode rgb_mode;
} my_state_t;

#define MY_LT(layer, kc) LT(layer, kc)

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};