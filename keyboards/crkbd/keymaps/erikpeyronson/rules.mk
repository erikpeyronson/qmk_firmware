RGBLIGHT_ENABLE = no

CAPS_WORD_ENABLE = yes


SRC += keymap_helpers.c

# Optional features

# CONSOLE_ENABLE = yes
# RGB_MATRIX_ENABLE = no
CONSOLE_ENABLE = no
RGB_MATRIX_ENABLE = yes

OLED_ENABLE = yes

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC +=  rgb.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled.c
endif
	# SRC += oled.c

# Possible to disable but obviously keymap doesnt make much sense without it
TAP_DANCE_ENABLE = yes
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += tap_dance.c
endif