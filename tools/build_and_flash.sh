#!/bin/bash
KBD=crkbd
VERSION=erik2g
KEYMAP=erikpeyronson
REPO_ROOT=$(git rev-parse --show-toplevel)

SOURCE=$HOME/Downloads/$KEYMAP.json
DEST=$REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_in.json

if [[ -f $SOURCE ]]; then
  mv $SOURCE $DEST
  echo "Moved $SOURCE to $DEST"
fi

qmk json2c -o $REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_out.h $REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_in.json
qmk compile -kb $KBD/$VERSION -km $KEYMAP

echo "Put first half in bootloader mode"
qmk flash -kb $KBD/$VERSION -km $KEYMAP
# echo "Put second half in bootloader mode"
# qmk flash -kb $KBD/$VERSION -km $KEYMAP
