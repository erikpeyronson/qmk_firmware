#include QMK_KEYBOARD_H

enum Layers{
  Base = 0,
  Swe,
  Num,
  Sym
};

#define MY_LT(layer, kc) LT(layer, kc)

#include "keymap_out.h"

