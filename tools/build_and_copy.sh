#!/bin/bash
KBD=crkbd
VERSION=erik2g
KEYMAP=erikpeyronson
qmk compile -kb $KBD/$VERSION -km $KEYMAP


mv /mnt/c/Users/erikp/OneDrive/Dokument/keyboard/firmware/${KBD}_${VERSION}_${KEYMAP}.hex /mnt/c/Users/erikp/OneDrive/Dokument/keyboard/firmware/${KBD}_${VERSION}_${KEYMAP}.hex.bak
cp $(git rev-parse --show-toplevel)/${KBD}_${VERSION}_${KEYMAP}.hex /mnt/c/Users/erikp/OneDrive/Dokument/keyboard/firmware