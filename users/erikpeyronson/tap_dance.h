#pragma once

#include "quantum.h"

#ifdef TAP_DANCE_ENABLE
#define MY_ACTION_TAP_DANCE_FN_ADVANCED(                                                                               \
    user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, my_user_data)                              \
  {                                                                                                                    \
    .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = my_user_data          \
  }

typedef struct
{
  bool is_press_action;
  int  state;
} my_tap_t;

void my_td_brackets_finished(tap_dance_state_t *state, void *user_data);
void my_td_brackets_reset(tap_dance_state_t *state, void *user_data);
#else
void my_td_brackets_finished(tap_dance_state_t *state, void *user_data) {}
void my_td_brackets_reset(tap_dance_state_t *state, void *user_data) {}
#endif
