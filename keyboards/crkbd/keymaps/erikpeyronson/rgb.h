#pragma once

#include "common.h"

#ifdef RGB_MATRIX_ENABLE
void my_rgb_init(void);
void set_rgb_mode(enum RgbMode mode);
void my_next_rgb_mode(void);
void sync_rgb_mode(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data);
#else
void my_rgb_init(void) {}
void set_rgb_mode(enum RgbMode mode) {}
void my_next_rgb_mode(void) {}
void sync_rgb_mode(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {}
#endif