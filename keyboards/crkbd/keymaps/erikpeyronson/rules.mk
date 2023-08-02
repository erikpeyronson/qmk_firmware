RGBLIGHT_ENABLE = no


CAPS_WORD_ENABLE = yes

CONSOLE_ENABLE = no
RGB_MATRIX_ENABLE = yes

SRC += keymap_helpers.c

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC +=  rgb.c
endif

OLED_ENABLE = yes
ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled.c
endif


TAP_DANCE_ENABLE = yes
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += tap_dance.c
endif