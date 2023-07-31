#pragma once

#include "quantum.h"

#ifdef OLED_ENABLE
void my_oled_init(const uint16_t keymaps[6][MATRIX_ROWS][MATRIX_COLS]);
#else
void my_oled_init(const uint16_t keymaps[6][MATRIX_ROWS][MATRIX_COLS]) {}
#endif