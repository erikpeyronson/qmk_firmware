ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC +=  $(USER_PATH)/rgb.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += $(USER_PATH)/oled.c
endif

# ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
# 	SRC += $(USER_PATH)/tap_dance.c
# endif

SRC += erikpeyronson.c