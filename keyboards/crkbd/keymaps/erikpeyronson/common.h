#pragma once

#include "quantum.h"

typedef enum
{
  TD_CURLY_BRACKETS = 0,
  TD_SQUARE_BRACKETS,
  TD_PARENTESES,
  TD_LTGT,
  TD_SWE,
  TD_BASE
} TapDanceActions;

typedef enum
{
  Base = 0,
  Swe,
  Num,
  Sym,
  Nav,
  Etc
} Layer;

#define RGB_KEYCODE_OFFSET SAFE_RANGE
#define TAP_DANCE_KEYCODE_OFFSET SAFE_RANGE + 0xFF

#define MY_LT(layer, kc) LT(layer, kc)

typedef struct
{
  bool is_press_action;
  int  state;
} tap;

enum
{
  SINGLE_TAP        = 1,
  SINGLE_HOLD       = 2,
  DOUBLE_TAP        = 3,
  DOUBLE_HOLD       = 4,
  DOUBLE_SINGLE_TAP = 5, // send two single taps
  TRIPLE_TAP        = 6,
  TRIPLE_HOLD       = 7
};