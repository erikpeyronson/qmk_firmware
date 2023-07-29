#pragma once

#include "quantum.h"

#define IS_KC_SHIFTED_SYMBOL(code) (keycode >> 8 & 0x02)

static const char PROGMEM code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

char keycode_to_char(uint16_t keycode, keyrecord_t *record) {
    if (IS_KC_SHIFTED_SYMBOL(keycode)) {
        switch (QK_MODS_GET_BASIC_KEYCODE(keycode)) {
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
        }
    }

    if (IS_QK_MOD_TAP(keycode)) {
        keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
        uprintf("mod tap: %x \n\n", keycode);
    }

    if (IS_QK_LAYER_TAP(keycode)) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
        uprintf("layer tap after: %x \n\n", keycode);
    }

    if (IS_QK_MODS(keycode)) {
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    }
    if (IS_QK_ONE_SHOT_MOD(keycode)) {
        keycode = 0xE0 + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0xF) + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0x10);
    }

    if (keycode == KC_TRANSPARENT) {
        return 0x1F;
    }

    if (keycode == KC_NO) {
        return 0x80;
    }

    if (keycode > ARRAY_SIZE(code_to_name)) {
        return (char)0x09;
    }
    // update keylog
    return pgm_read_byte(&code_to_name[keycode]);
}