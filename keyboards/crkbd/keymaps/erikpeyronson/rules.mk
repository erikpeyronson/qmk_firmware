RGBLIGHT_ENABLE = no

TAP_DANCE_ENABLE = yes
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

