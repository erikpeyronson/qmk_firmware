#ifndef KEYMAP_HELPERS_H
#define KEYMAP_HELPERS_H

#include "quantum.h"
#include "common.h"

#ifdef OLED_ENABLE
#include "oled.h"
#endif

#ifdef RGB_MATRIX_ENABLE
#include "rgb.h"
#endif

// custom macros
#define IS_KC_SHIFTED_SYMBOL(code) (keycode >> 8 & 0x02)
#define MY_IS_QK_TAP_DANCE(code) ((keycode & 0xFF00) == (QK_TAP_DANCE & 0xFF00))

#undef KC_COPY
#define KC_COPY LCTL(KC_C)
#undef KC_CUT
#define KC_CUT LCTL(KC_X)
#undef KC_PSTE
#define KC_PSTE LCTL(KC_X)

enum custom_keycodes {

  ONENOTE_HAND= SAFE_RANGE,
  ONENOTE_ARROW,

  ONENOTE_NEXT_PEN,
  ONENOTE_PREVIOUS_PEN,

  ONENOTE_ZOOM_IN,
  ONENOTE_ZOOM_OUT,
  ONENOTE_FULL_SCREEN,
};

// Custom helper functions used by rgb/oled. Can be overridden in keymap
char        keycode_to_char(uint16_t keycode, keyrecord_t *record);
const char *layer_to_string(uint8_t layer);
int8_t      get_layer_with_key(uint8_t layer, const keypos_t keypos);

typedef struct
{
  uint16_t kc_open;
  uint16_t kc_close;
  bool     is_shifted;
} bracket_info_t;

extern bracket_info_t brackets[4];
extern const char    *layer_strings[];

#endif // !KEYMAP_HELPERS_H