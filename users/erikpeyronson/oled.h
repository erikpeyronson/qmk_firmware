#pragma once

#include "quantum.h"

#ifdef OLED_ENABLE
void my_oled_init(const uint16_t keymaps[6][MATRIX_ROWS][MATRIX_COLS]);
void my_oled_screensaver(bool turn_on);
void my_oled_render_info(void);
void my_oled_osl_changed(uint8_t);
void my_oled_locked_mods_changed(uint8_t mods);
void my_oled_oneshot_mods_changed(uint8_t mods);
#else
void my_oled_init(const uint16_t keymaps[6][MATRIX_ROWS][MATRIX_COLS]) {}
void my_oled_screensaver(bool turn_on) {}
void my_oled_render_info(void) {}
void my_oled_osl_changed(uint8_t layers) {}
void my_oled_locked_mods_changed(uint8_t mods) {}
void my_oled_oneshot_mods_changed(uint8_t mods) {}
#endif