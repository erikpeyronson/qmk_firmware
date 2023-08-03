#pragma once

#include "quantum.h"

#ifdef OLED_ENABLE
void my_oled_init(const uint16_t keymaps[6][MATRIX_ROWS][MATRIX_COLS]);
bool oled_screen_saver(bool turn_on);
void oled_render_info(void);
void screen_saver(bool active);
#else
void my_oled_init(const uint16_t keymaps[6][MATRIX_ROWS][MATRIX_COLS]) {}
bool oled_screen_saver(void) {}
void oled_render_info(void) {}
#endif