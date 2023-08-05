#include "quantum.h"
#include "process_tap_dance.h"
#include "erikpeyronson.h"
#include "tap_dance.h"

enum
{
  SINGLE_TAP        = 1,
  SINGLE_HOLD       = 2,
  DOUBLE_TAP        = 3,
  DOUBLE_HOLD       = 4,
  DOUBLE_SINGLE_TAP = 5, // send two single taps
  TRIPLE_TAP        = 6,
  TRIPLE_HOLD       = 7
};


static my_tap_t xtap_state = { .is_press_action = true, .state = 0 };

static int my_td_current_dance(tap_dance_state_t *state)
{
  if (state->count == 1)
    {
      if (state->interrupted || !state->pressed)
        return SINGLE_TAP;
      // key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
      else
        return SINGLE_HOLD;
    }
  else if (state->count == 2)
    {
      /*
       * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
       * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
       * keystrokes of the key, and not the 'double tap' action/macro.
       */
      if (state->interrupted)
        return DOUBLE_SINGLE_TAP;
      else if (state->pressed)
        return DOUBLE_HOLD;
      else
        return DOUBLE_TAP;
    }
  // Assumes no one is trying to type the same letter three times (at least not quickly).
  // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3)
    {
      if (state->interrupted || !state->pressed)
        return TRIPLE_TAP;
      else
        return TRIPLE_HOLD;
    }
  else
    return 8; // magic number. At some point this method will expand to work for more presses
}

void my_td_brackets_finished(tap_dance_state_t *state, void *user_data)
{
  bracket_info_t *bracket_info = (bracket_info_t *)user_data;

  xtap_state.state = my_td_current_dance(state);
  switch (xtap_state.state)
    {
      case SINGLE_TAP:
        if (bracket_info->is_shifted)
          {
            register_code(KC_LEFT_SHIFT);
          }
        register_code(bracket_info->kc_open);
        break;
      case SINGLE_HOLD:
        if (bracket_info->is_shifted)
          register_code(KC_LEFT_SHIFT);
        register_code(bracket_info->kc_open);
        register_code(bracket_info->kc_close);

        if (bracket_info->is_shifted)
          unregister_code(KC_LEFT_SHIFT);
        unregister_code(bracket_info->kc_open);
        unregister_code(bracket_info->kc_close);
        register_code(KC_LEFT);
        break;
      case DOUBLE_TAP:
        if (bracket_info->is_shifted)
          register_code(KC_LEFT_SHIFT);
        register_code(bracket_info->kc_close);
        break;
    }
}

void my_td_brackets_reset(tap_dance_state_t *state, void *user_data)
{
  bracket_info_t *bracket_info = (bracket_info_t *)user_data;
  switch (xtap_state.state)
    {
      case SINGLE_TAP:
        if (bracket_info->is_shifted)
          {
            unregister_code(KC_LEFT_SHIFT);
          }
        unregister_code(bracket_info->kc_open);
        break;
      case SINGLE_HOLD:
        unregister_code(KC_LEFT);
        break;
      case DOUBLE_TAP:
        if (bracket_info->is_shifted)
          {
            unregister_code(KC_LEFT_SHIFT);
          }
        unregister_code(bracket_info->kc_close);
        break;
    }
  xtap_state.state = 0;
}
