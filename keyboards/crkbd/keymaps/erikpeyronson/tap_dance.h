#pragma once

#ifdef TAP_DANCE_ENABLE
#include "quantum.h"

#define MY_ACTION_TAP_DANCE_FN_ADVANCED(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, my_user_data) \
        { .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = my_user_data}

void td_curly_bracked_finished(tap_dance_state_t *state, void *user_data);
void td_curly_bracketd_reset(tap_dance_state_t *state, void *user_data);
#endif

