!/bin/bash
KBD=crkbd
VERSION=r2g
KEYMAP=erikpeyronson
REPO_ROOT=$(git rev-parse --show-toplevel)

SOURCE=$HOME/Downloads/$KEYMAP.json
DEST=$REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_in.json

if ! which qmk; then
    echo "Command 'qmk' not found, please install qmk"
    exit 1;
fi

if [ "$QMK_COMMAND" != "/usr/bin/qmk" ]; then
    read -p "Qmk not globally available, move $QMK_COMMAND to /usr/bin/qmk? (yes/no) " yn

    case $yn in
    	yes ) sudo mv $QMK_COMMAND /usr/bin;;
    	no ) echo exiting...;
    		exit;;
    	* ) echo invalid response;
    		exit 1;;
    esac
fi

QMK_COMMAND=/usr/bin/qmk

# Check if the "qmk" group exists. If not, create it.
if ! grep  -q "^qmk:" /etc/group; then
    echo -n "Creating group qmk ..."
    sudo groupadd qmk             || (echo "Failed to create group" && exit 1)
    sudo chgrp qmk "$QMK_COMMAND" || (echo "Failed change group permissions" && exit 1)
fi

# Add the current user to the "qmk" group if not already a member
if ! id -nG "$USER" | grep -qw "qmk"; then
    echo -n "Adding $USER to group qmk ..."
    sudo usermod -aG qmk "$USER" || (echo "failed to add $USER to group" && exit 1)
    newgrp qmk
    echo "User '$USER' added to the 'qmk' group."
    echo " done!"
fi

if [[ ! -f /etc/sudoers.d/qmk-console ]]; then
    # Set group ownership and permissions for the "qmk" command
    echo -n "Modify sudoers file to allow qmk console without password for every memver of the qmk group ..."
    # sudo echo '%erik ALL=NOPASSWD: /home/erik/.local/bin/qmk console' | sudo tee /etc/sudoers.d/qmk-console
    sudo echo '%qmk ALL=(ALL) NOPASSWD:/usr/bin/qmk console' | sudo tee /etc/sudoers.d/qmk-console
    sudo chmod 440 "/etc/sudoers.d/qmk-console" || (echo "Failed to set permission of sudoers file" && exit 1)
    echo " done!"
    echo "Setup complete, you should now be able to run sudo qmk console without password"
fi

mv $SOURCE $DEST
echo "Moved json keymap from $SOURCE to $DEST"

echo -n "Setting qmk defaults -kb $KBD/$VERSION -km $KEYMAP ..."
qmk config user.keymap=$KEYMAP
echo " done!"
qmk config user.keyboard=$KBD/$VERSION

qmk json2c -o $REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_out.h $REPO_ROOT/keyboards/$KBD/keymaps/$KEYMAP/keymap_in.json
qmk generate-compilation-database

