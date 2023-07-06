#!/bin/bash

KBD=crkbd
VERSION=erik2g
KEYMAP=erikpeyronson
REPO_ROOT=$(git rev-parse --show-toplevel)

SOURCE=$HOME/Downloads/$KEYMAP.json
DEST=$REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_in.json

while true
do
  if [[ -f $SOURCE ]]; then
    mv $SOURCE $DEST
    echo "Moved $SOURCE to $DEST"
  else
    echo "Looking for $SOURCE"
  fi
  sleep 4
done