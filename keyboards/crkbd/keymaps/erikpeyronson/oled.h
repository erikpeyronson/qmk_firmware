#pragma once

#include "quantum.h"

void my_set_keylog(uint16_t keycode, keyrecord_t *record);
void my_set_keymap_chars(const uint16_t keymaps[6][MATRIX_ROWS][MATRIX_COLS]);
