#!/bin/bash

if [[ $PWD != *"esp-gui-lib/iconconvert"* ]] || [[ $0 != *"build.sh"* ]]; then
    echo "This script must be run from the iconconvert directory"
    exit 1
fi


# check if qmake is installed
if ! command -v qmake; then
    echo "Qmake is not installed"
    exit 1
fi

# check if make is installed
if ! command -v make; then
    echo "Make is not installed"
    exit 1
fi

mkdir -p build
cd build || exit 1
qmake ..
make
cd ..
