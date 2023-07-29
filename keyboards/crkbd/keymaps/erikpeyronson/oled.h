#pragma once

#include "quantum.h"

void my_get_tap_code(uint16_t keycode, keyrecord_t *record);
void my_set_keymap_chars(const uint16_t keymaps[6][MATRIX_ROWS][MATRIX_COLS]);
uint16_t my_get_tapped_kc(uint16_t keycode);