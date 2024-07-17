
#include "my_encoder.h"

bool my_encoder_scroll(bool clockwise) {
  clockwise ? tap_code(KC_WH_D) : tap_code(KC_WH_U);
  return false;
}

bool my_encoder_space(bool clockwise) {
  clockwise ? tap_code(KC_SPACE) : tap_code(KC_BACKSPACE);
  return false;
}


void my_encoder_clear_state(void) {

}