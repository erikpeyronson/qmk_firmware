#!/bin/bash
KBD=crkbd
VERSION=erik2g
KEYMAP=erikpeyronson
REPO_ROOT=$(git rev-parse --show-toplevel)

qmk json2c -o $REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_out.h $REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_in.json
qmk compile -kb $KBD/$VERSION -km $KEYMAP
