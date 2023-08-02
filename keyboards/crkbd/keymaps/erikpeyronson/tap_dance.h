#pragma once

#include "quantum.h"

// enum TapDanceKeyCodes { MY_SEND_CURLY_BRACKETS = TAP_DANCE_KEYCODE_OFFSET, MY_SEND_SQUARE_BRACKETS, MY_SEND_PARENTHESES, MY_SEND_LT_GT };

#ifdef TAP_DANCE_ENABLE
#define MY_ACTION_TAP_DANCE_FN_ADVANCED(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, my_user_data) \
        { .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = my_user_data}
#else

#define TD(arg) KC_NO

#endif

