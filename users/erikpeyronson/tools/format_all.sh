#!/bin/bash

REPO_ROOT=$(git rev-parse --show-toplevel)

find $REPO_ROOT/keyboards/crkbd/keymaps/erikpeyronson/ -iname *.h -o -iname *.c | xargs clang-format -i
find $REPO_ROOT/users/erikpeyronson/ -iname *.h -o -iname *.c | xargs clang-format -i