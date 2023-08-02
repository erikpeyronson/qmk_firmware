RGBLIGHT_ENABLE = no

CAPS_WORD_ENABLE = yes

CONSOLE_ENABLE = no

SRC += keymap_helpers.c

# Optional features
RGB_MATRIX_ENABLE = yes
OLED_ENABLE = yes

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC +=  rgb.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled.c
endif

# Possible to disable but obviously keymap doesnt make much sense without it
TAP_DANCE_ENABLE = yes
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += tap_dance.c
endif