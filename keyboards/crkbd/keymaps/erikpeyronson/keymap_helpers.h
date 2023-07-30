#pragma once

#include "quantum.h"

#define IS_KC_SHIFTED_SYMBOL(code) (keycode >> 8 & 0x02)

char keycode_to_char(uint16_t keycode, keyrecord_t *record);
int8_t get_layer_with_key(uint8_t layer, const keypos_t keypos);