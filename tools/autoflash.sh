#!/bin/bash
KBD=crkbd
VERSION=r2g
KEYMAP=erikpeyronson
REPO_ROOT=$(git rev-parse --show-toplevel)

SOURCE=$HOME/Downloads/$KEYMAP.json
DEST=$REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_in.json

while true; do
  mv $SOURCE $DEST
  echo "Moved $SOURCE to $DEST"
  qmk json2c -o $REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_out.h $REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_in.json

  qmk flash -kb $KBD/$VERSION -km $KEYMAP
done
# echo "Put second half in bootloader mode"
# qmk flash -kb $KBD/$VERSION -km $KEYMAP
