#include "quantum.h"
#include "logo.h"

void my_oled_render_logo(void) {
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

bool oled_task_user(void) {
  my_oled_render_logo();
  return false;
}