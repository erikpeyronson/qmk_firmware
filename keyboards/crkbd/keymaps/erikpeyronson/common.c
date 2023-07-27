#include "common.h"

static const char * const PROGMEM LAYER_STRINGS[] = {
    FOREACH_LAYER(GENERATE_STRING)
};

const char *layer_to_string(enum Layers layer) {
  return LAYER_STRINGS[layer];
}