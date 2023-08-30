#pragma once

#include "quantum.h"

#ifdef OLED_ENABLE
void my_oled_init(const uint16_t keymaps[6][MATRIX_ROWS][MATRIX_COLS]);
void my_oled_screensaver(bool turn_on);
void my_oled_render_info(void);
#else
void my_oled_init(const uint16_t keymaps[6][MATRIX_ROWS][MATRIX_COLS]) {}
void my_oled_screensaver(bool turn_on) {}
void my_oled_render_info(void) {}
#endif