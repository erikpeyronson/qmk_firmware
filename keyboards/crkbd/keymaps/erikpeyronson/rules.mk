RGBLIGHT_ENABLE = no

TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes

CONSOLE_ENABLE = yes
RGB_MATRIX_ENABLE = no
OLED_ENABLE = yes

SRC += keymap_helpers.c

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC +=  rgb.c
endif

SRC += oled.c

