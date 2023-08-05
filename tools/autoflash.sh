#!/bin/bash
KBD=crkbd
VERSION=r2g
KEYMAP=erikpeyronson
REPO_ROOT=$(git rev-parse --show-toplevel)

SOURCE=$HOME/Downloads/$KEYMAP.json
DEST=$REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_in.json

mv $SOURCE $DEST
echo "Moved $SOURCE to $DEST"
qmk config user.keymap=$KEYMAP
qmk config user.keyboard=$KBD
qmk json2c -o $REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_out.h $REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_in.json

