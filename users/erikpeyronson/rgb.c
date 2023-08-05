#ifdef RGB_MATRIX_ENABLE

// clang-format off
#include "rgb.h"
#include "rgb_matrix.h"
#include "common.h"
#include "transactions.h"
#include "erikpeyronson.h"
// clang-format on

RgbMode current_mode = EACH_KEY;

typedef struct
{
  uint16_t red;
  uint16_t green;
  uint16_t blue;
} rgb_color_t;

typedef struct
{
  int rgb_mode;
} rgb_state_t;

void my_rgb_init(void)
{
  // Turn all leds off during startup
  rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
  rgb_matrix_sethsv_noeeprom(HSV_OFF);
  transaction_register_rpc(SYNC_RGB_MODE, my_rgb_sync_state);
}

// clang-format off
static rgb_color_t layer_colors[] = {
  [LAYER_BASE] = { RGB_WHITE  },
  [LAYER_SWE]  = { RGB_YELLOW },
  [LAYER_NUM]  = { RGB_BLUE   },
  [LAYER_SYM]  = { RGB_GREEN  },
  [LAYER_NAV]  = { RGB_ORANGE },
  [LAYER_ETC]  = { RGB_RED    },
  [LAYER_END]  = { RGB_OFF    },
};
// clang-format on

rgb_color_t get_color(uint16_t layer)
{

  if (layer > LAYER_END)
    {
      layer = LAYER_END;
    }

  return layer_colors[layer];
}

void each_key(void)
{
  uint16_t current_layer = get_highest_layer(layer_state | default_layer_state);
  uint8_t  first_row, last_row;

  // To save some clock cycles let each half light its own leds rather than
  // both sides lighting all
  if (is_keyboard_master())
    {
      first_row = 0;
      last_row  = 4;
    }
  else
    {
      first_row = 4;
      last_row  = 8;
    }

  for (int row = first_row; row < last_row; ++row)
    {
      for (int col = 0; col < 6; ++col)
        {
          keypos_t    current_key = { .col = col, .row = row };
          uint8_t     led_index   = g_led_config.matrix_co[row][col];
          uint8_t     layer       = get_layer_with_key(current_layer, current_key);
          rgb_color_t rgb         = get_color(layer);

          rgb_matrix_set_color(led_index, rgb.red, rgb.green, rgb.blue);
        }
    }
}

void thumbs_only(void)
{
  uint16_t current_layer = get_highest_layer(layer_state | default_layer_state);

  // let each half light their own
  uint8_t row;
  if (is_keyboard_master())
    {
      row = 3;
    }
  else
    {
      row = 7;
    }

  // thumb key indexes
  uint8_t first_column = 3;
  uint8_t last_column  = 5;

  for (uint8_t col = first_column; col < last_column + 1; ++col)
    {
      keypos_t    current_key = { .col = col, .row = row };
      rgb_color_t rgb;

      uint8_t led_index = g_led_config.matrix_co[row][col];

      // If we are on the base layer use the target layer, otherwise just
      // display which layer we are at
      if (current_layer == LAYER_BASE)
        {
          uint16_t kc           = keymap_key_to_keycode(0, current_key);
          uint8_t  target_layer = QK_LAYER_TAP_GET_LAYER(kc);
          rgb                   = get_color(target_layer);
        }
      else if (current_layer == LAYER_SWE && is_keyboard_left())
        {
          rgb = (rgb_color_t){ RGB_BLUE };
        }
      else
        {
          rgb = get_color(current_layer);
        }

      rgb_matrix_set_color(led_index, rgb.red, rgb.green, rgb.blue);
    }
}

void thumbs_solid(void)
{
  uint16_t current_layer = get_highest_layer(layer_state | default_layer_state);

  // let each half light their own
  uint8_t row;
  if (is_keyboard_master())
    {
      row = 3;
    }
  else
    {
      row = 7;
    }

  // thumb key indexes
  uint8_t     first_column = 3;
  uint8_t     last_column  = 5;
  rgb_color_t rgb;
  if (current_layer == LAYER_SWE && is_keyboard_left())
    {
      rgb = (rgb_color_t){ RGB_BLUE };
    }
  else
    {
      rgb = get_color(current_layer);
    }

  for (uint8_t col = first_column; col < last_column + 1; ++col)
    {
      uint8_t led_index = g_led_config.matrix_co[row][col];
      rgb_matrix_set_color(led_index, rgb.red, rgb.green, rgb.blue);
    }
}

bool rgb_matrix_indicators_user()
{
  switch (current_mode)
    {
      case EACH_KEY:
        each_key();
        break;
      case THUMBS_HINT:
        thumbs_only();
        break;
      case THUMBS_SOLID:
        thumbs_solid();
        break;
      default:
        break;
    }
  return false;
}

void my_rgb_set_mode(RgbMode mode)
{
  current_mode = mode;
}
RgbMode my_rgb_get_mode(void)
{
  return current_mode;
}

void my_rgb_next_mode(void)
{
  if (current_mode++ >= OFF)
    {
      current_mode = 0;
    }
  rgb_state_t m2s = { current_mode };
  transaction_rpc_exec(SYNC_RGB_MODE, sizeof(m2s), &m2s, 0, NULL);
}

void my_rgb_sync_state(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data)
{
  const rgb_state_t *m2s = (const rgb_state_t *)in_data;
  current_mode           = m2s->rgb_mode;
}

#endif