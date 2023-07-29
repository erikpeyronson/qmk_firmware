#pragma once

#include "quantum.h"

enum Layers { Base = 0, Swe, Num, Sym, Nav, Etc };
enum TapDanceActions { TD_SWE = 0, TD_BASE };

typedef enum _RgbMode { EACH_KEY = 0, THUMBS_HINT, THUMBS_SOLID, OFF} RgbMode;
enum KeyCodes { MY_CYCLE_RGB_MODE = SAFE_RANGE };

typedef struct _my_state_t {
    RgbMode rgb_mode;
} my_state_t;

#define MY_LT(layer, kc) LT(layer, kc)
