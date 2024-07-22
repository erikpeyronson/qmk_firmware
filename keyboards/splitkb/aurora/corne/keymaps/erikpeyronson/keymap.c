#include QMK_KEYBOARD_H

#include "common.h"
#include "erikpeyronson.h"
#include "keymap_out.h"
#include "logo.h"
#include "oled.h"
#include "quantum.h"
#include "rgb.h"

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_BASE] = {{QK_REPEAT_KEY, QK_ALT_REPEAT_KEY},
                    {QK_REPEAT_KEY, QK_ALT_REPEAT_KEY}},
    [LAYER_SWE] = {{QK_REPEAT_KEY, QK_ALT_REPEAT_KEY},
                   {QK_REPEAT_KEY, QK_ALT_REPEAT_KEY}},
    [LAYER_OSM] = {{KC_WH_D, KC_WH_U}, {KC_WH_D, KC_WH_U}},
    [LAYER_NUM] = {{MY_ALT_TAB_NAV, MY_ALT_TAB_NAV_REVERSE},
                   {MY_ALT_TAB_NAV, MY_ALT_TAB_NAV_REVERSE}},
    [LAYER_SYM] = {{MY_CTRL_TAB_NAV, MY_CTRL_TAB_NAV_REVERSE},
                   {MY_CTRL_TAB_NAV, MY_CTRL_TAB_NAV_REVERSE}},
    [LAYER_NAV] = {{KC_WH_D, KC_WH_U}, {KC_WH_D, KC_WH_U}},
    [LAYER_ETC] = {{KC_NO, KC_NO}, {KC_NO, KC_NO}}};

#endif

static bool ctrl_enabled = false;
static bool alt_enabled = false;

void start_ctrl_timer(void) {
  if (!ctrl_enabled) {
    register_code(KC_LCTL);
    ctrl_enabled = true;
  }
}

void stop_ctrl_timer(void) {
  if (ctrl_enabled) {
    unregister_code(KC_LCTL);
    ctrl_enabled = false;
  }
}

void start_alt_timer(void) {
  if (!alt_enabled) {
    register_code(KC_LALT);
    alt_enabled = true;
  }
}

void stop_alt_timer(void) {
  if (alt_enabled) {
    unregister_code(KC_LALT);
    alt_enabled = false;
  }
}

// clang-format off
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for W, twice for switch to swedish layer
    [TD_SWE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_MINUS, LAYER_SWE),
    [TD_BASE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_NO, LAYER_BASE),
    [TD_BASE_TILDE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_TILD, LAYER_BASE),
};
// clang-format on

const char *layer_strings[] = {
    [LAYER_BASE] = "Base", [LAYER_OSM] = "Osm", [LAYER_SWE] = "Swe",
    [LAYER_NUM] = "Num",   [LAYER_SYM] = "Sym", [LAYER_NAV] = "Nav",
    [LAYER_ETC] = "Etc",
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable = true;
  debug_matrix = false;
  debug_keyboard = false;
  debug_mouse = false;

  my_rgb_init();
  my_oled_init(keymaps);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
  uprintf(
      "KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: "
      "%u, count: %u\n\n",
      keycode, record->event.key.col, record->event.key.row,
      record->event.pressed, record->event.time, record->tap.interrupted,
      record->tap.count);

#endif

  switch (keycode) {
    // ONENOTE macros
    case ONENOTE_HAND:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("d") "y");
      }
      break;
    case ONENOTE_ARROW:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("d") "t");
      }
      break;

    case ONENOTE_NEXT_PEN:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("d") "g" SS_TAP(X_RIGHT) SS_TAP(X_ENTER));
      }
      break;
    case ONENOTE_PREVIOUS_PEN:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("d") "g" SS_TAP(X_LEFT) SS_TAP(X_ENTER));
      }
      break;
    case ONENOTE_ZOOM_IN:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("w") "e");
      }
      break;
    case ONENOTE_ZOOM_OUT:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("w") "w");
      }
      break;
    case ONENOTE_FULL_SCREEN:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("d") "f");
      }
      break;

      // Custom navigation

    case MY_CTRL_TAB_NAV:
      if (record->event.pressed) {
        start_ctrl_timer();
        tap_code(KC_TAB);
      }
      return false;
    case MY_CTRL_TAB_NAV_REVERSE:
      if (record->event.pressed) {
        uprintf("control tab reverse\n");
        start_ctrl_timer();
        tap_code16(S(KC_TAB));
      }
      return false;
    case MY_ALT_TAB_NAV:
      if (record->event.pressed) {
        start_alt_timer();
        tap_code(KC_TAB);
      }
      return false;
    case MY_ALT_TAB_NAV_REVERSE:
      if (record->event.pressed) {
        start_alt_timer();
        tap_code16(S(KC_TAB));
      }
      return false;
  }
  stop_ctrl_timer();
  stop_alt_timer();

  if (!my_rgb_process_record(keycode, record)) return false;
  return true;
}

static bool is_idle = false;

void housekeeping_task_user(void) {
  static RgbMode old_rgb_mode;
  uint32_t idle_time = last_input_activity_elapsed();

  if (!is_idle && idle_time > MY_OLED_SCREENSAVER_TIMEOUT) {
    old_rgb_mode = my_rgb_get_mode();
    my_rgb_set_mode(OFF);
    my_oled_screensaver(true);
    is_idle = true;
  } else if (is_idle && idle_time < MY_OLED_SCREENSAVER_TIMEOUT) {
    my_oled_screensaver(false);
    my_rgb_set_mode(old_rgb_mode);
    is_idle = false;
  }

  if (idle_time > MY_NAVIGATION_MOD_TIMEOUT) {
    stop_ctrl_timer();
    stop_alt_timer();
  }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  return false;
}
