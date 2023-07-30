#ifndef KEYMAP_HELPERS_H
#define KEYMAP_HELPERS_H


#include "quantum.h"
#include "common.h"

#define IS_KC_SHIFTED_SYMBOL(code) (keycode >> 8 & 0x02)
#define MY_IS_QK_TAP_DANCE(code) ((keycode & 0xFF00) == (QK_TAP_DANCE & 0xFF00))

char   keycode_to_char(uint16_t keycode, keyrecord_t *record);
int8_t get_layer_with_key(uint8_t layer, const keypos_t keypos);

typedef struct {
    uint16_t kc_open;
    uint16_t kc_close;
    bool     is_shifted;
} bracket_info_t;

extern bracket_info_t brackets[4];

#endif // !KEYMAP_HELPERS_H