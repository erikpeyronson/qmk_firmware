#include "keymap_helpers.h"
#include "tap_dance.h"

#define IS_KC_SHIFTED_SYMBOL(code) (keycode >> 8 & 0x02)

static const char PROGMEM code_to_name[60] = { ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' ' };

const char* layer_strings[] = {
  [LAYER_BASE] = "Base",
  [LAYER_SWE] = "Swe" ,
  [LAYER_NUM] = "Num" ,
  [LAYER_SYM] = "Sym" ,
  [LAYER_NAV] = "Nav" ,
  [LAYER_ETC] = "Etc"
};


const char* layer_to_string(layer_t layer) {
  return layer_strings[layer];
}

char keycode_to_char(uint16_t keycode, keyrecord_t *record)
{
  if (MY_IS_QK_TAP_DANCE(keycode))
    {
      uprintf("keycode in tapdance conversion: 0x%4x \n", keycode);
      keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
      uprintf("Basic keycode: 0x%04x \n", keycode);

      switch (keycode)
        {
          case TD_CURLY_BRACKETS:
            return '}';
          case TD_SQUARE_BRACKETS:
            return ']';
          case TD_PARENTESES:
            return ')';
          case TD_LTGT:
            return '>';
          default:
            return (char)0x07;
        }
    }

  if (IS_QK_MOD_TAP(keycode))
    {
      println("Mod tap");
      keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    }
  if (IS_KC_SHIFTED_SYMBOL(keycode))
    {
      println("Is shifted");
      switch (QK_MODS_GET_BASIC_KEYCODE(keycode))
        {
          case 0x1E:
            return '!';
          case 0x1F:
            return '@';
          case 0x20:
            return '#';
          case 0x21:
            return '$';
          case 0x22:
            return '%';
          case 0x23:
            return '^';
          case 0x24:
            return '&';
          case 0x25:
            return '*';
          case 0x26:
            return '(';
          case 0x27:
            return ')';
          case 0x2F:
            return '{';
          case 0x30:
            return '}';
        }
    }

  if (IS_QK_LAYER_TAP(keycode))
    {
      println("layer tap tap");
      keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    }

  if (IS_QK_MODS(keycode))
    {
      println("qk mods");
      keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    }
  if (IS_QK_ONE_SHOT_MOD(keycode))
    {
      println("one shot mod");
      keycode = 0xE0 + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0xF) + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0x10);
    }

  if (keycode == KC_TRANSPARENT)
    {
      return 0x1F;
    }

  if (keycode == KC_NO)
    {
      return 0x80;
    }

  switch (keycode)
    {
      case KC_KP_SLASH:
        return '/';
      case KC_KP_ASTERISK:
        return '*';
      case KC_KP_MINUS:
        return '-';
      case KC_KP_PLUS:
        return '+';
    }

  if (keycode > ARRAY_SIZE(code_to_name))
    {
      return (char)0x07;
    }
  // update keylog
  return pgm_read_byte(&code_to_name[keycode]);
}

int8_t get_layer_with_key(uint8_t layer, const keypos_t keypos)
{
  uint16_t kc = keymap_key_to_keycode(layer, keypos);

  while (layer > 0 && (kc == KC_TRANSPARENT || IS_LAYER_OFF(layer)))
    {
      layer--;
      kc = keymap_key_to_keycode(layer, keypos);
    }

  if (kc != KC_NO && kc != KC_TRANSPARENT)
    {
      return layer;
    }

  return -1;
}

bracket_info_t brackets[] = {
  [TD_CURLY_BRACKETS]  = { KC_LEFT_BRACKET, KC_RIGHT_BRACKET, true },
  [TD_SQUARE_BRACKETS] = { KC_LEFT_BRACKET, KC_RIGHT_BRACKET, false },
  [TD_PARENTESES]      = { KC_9, KC_0, true },
  [TD_LTGT]            = { KC_COMMA, KC_DOT, true },
};
