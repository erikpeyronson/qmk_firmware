#pragma once

#include "common.h"

enum RgbKeyCodes
{
  MY_CYCLE_RGB_MODE = RGB_KEYCODE_OFFSET
};

typedef enum _RgbMode
{
  EACH_KEY = 0,
  THUMBS_HINT,
  THUMBS_SOLID,
  OFF
} RgbMode;

typedef struct _my_state_t
{
  RgbMode rgb_mode;
} my_state_t;

#ifdef RGB_MATRIX_ENABLE
void    my_rgb_init(void);
void    my_rgb_set_mode(RgbMode mode);
RgbMode my_rgb_get_mode(void);
void    my_rgb_next_mode(void);
void    my_rgb_sync_state(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data);

#else
void my_rgb_init(void)
{
}
void my_rgb_set_mode(RgbMode mode)
{
}
RgbMode my_rgb_get_mode(void)
{
  return OFF;
}
void my_rgb_next_mode(void)
{
}
void my_rgb_sync_state(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data)
{
}
#endif