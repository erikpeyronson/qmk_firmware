#include QMK_KEYBOARD_H

#include "quantum.h"

#include "rgb.h"
#include "logo.h"
#include "common.h"

#include "oled.h"
#include "erikpeyronson.h"
#include "tap_dance.h"

#include "keymap_out.h"

// clang-format off
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for W, twice for switch to swedish layer
    [TD_SWE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_MINUS, LAYER_SWE),
    [TD_BASE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_NO, LAYER_BASE),
    [TD_BASE_TILDE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_TILD, LAYER_BASE),
    [TD_CURLY_BRACKETS] = MY_ACTION_TAP_DANCE_FN_ADVANCED(NULL, my_td_brackets_finished, my_td_brackets_reset, (void *)&brackets[TD_CURLY_BRACKETS]),
    [TD_SQUARE_BRACKETS] = MY_ACTION_TAP_DANCE_FN_ADVANCED(NULL, my_td_brackets_finished, my_td_brackets_reset, (void *)&brackets[TD_SQUARE_BRACKETS]),
    [TD_PARENTESES] = MY_ACTION_TAP_DANCE_FN_ADVANCED(NULL, my_td_brackets_finished, my_td_brackets_reset, (void *)&brackets[TD_PARENTESES]),
    [TD_LTGT] = MY_ACTION_TAP_DANCE_FN_ADVANCED(NULL, my_td_brackets_finished, my_td_brackets_reset, (void *)&brackets[TD_LTGT]),
};
// clang-format on

const char *layer_strings[] = {
    [LAYER_BASE] = "Base",
    [LAYER_OSM]  = "Osm",
    [LAYER_SWE]  = "Swe",
    [LAYER_NUM]  = "Num",
    [LAYER_SYM]  = "Sym",
    [LAYER_NAV]  = "Nav",
    [LAYER_ETC]  = "Etc",
};

void keyboard_post_init_user(void)
{
  // Customise these values to desired behaviour
  debug_enable   = false;
  debug_matrix   = false;
  debug_keyboard = false;
  debug_mouse    = false;

  my_rgb_init();
  my_oled_init(keymaps);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  // If console is enabled, it will print the matrix position and status of each
  // key pressed
#ifdef CONSOLE_ENABLE

  uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: "
          "%u, count: %u\n\n",
      keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time,
      record->tap.interrupted, record->tap.count);

  uprintf("Character reprentation: %c \n\n", keycode_to_char(keycode, NULL));
#endif

  if (!my_rgb_process_record(keycode, record)) return false;
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state)
{
  // my_set_keymap_chars(keymaps);
  return state;
}

static bool is_idle = false;

void housekeeping_task_user(void)
{
  static RgbMode old_rgb_mode;
  uint32_t       idle_time = last_input_activity_elapsed();

  if (!is_idle && idle_time > MY_OLED_SCREENSAVER_TIMEOUT)
    {
      old_rgb_mode = my_rgb_get_mode();
      my_rgb_set_mode(OFF);
      my_oled_screensaver(true);
      is_idle = true;
    }
  else if (is_idle && idle_time < MY_OLED_SCREENSAVER_TIMEOUT)
    {
      my_oled_screensaver(false);
      my_rgb_set_mode(old_rgb_mode);
      is_idle = false;
    }
}

void oneshot_layer_changed_user(uint8_t mods) { my_oled_osl_changed(mods); }

void oneshot_locked_mods_changed_user(uint8_t mods) { my_oled_locked_mods_changed(mods); }

void oneshot_mods_changed_user(uint8_t mods) {
  my_oled_oneshot_mods_changed(mods);
}