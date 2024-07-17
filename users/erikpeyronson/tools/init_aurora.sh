!/bin/bash
KBD=splitkb/aurora
VERSION=corne
KEYMAP=erikpeyronson
REPO_ROOT=$(git rev-parse --show-toplevel)

SOURCE=$HOME/Downloads/$KEYMAP.json
DEST=$REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_in.json

mv $SOURCE $DEST
echo "Moved json keymap from $SOURCE to $DEST"

echo -n "Setting qmk defaults -kb $KBD/$VERSION -km $KEYMAP ..."
qmk config user.keymap=$KEYMAP
echo " done!"
qmk config user.keyboard=$KBD/$VERSION

qmk json2c -o $REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_out.h $REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_in.json
qmk generate-compilation-database

