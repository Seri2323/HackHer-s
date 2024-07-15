#!/bin/bash

read -p "Are you on Linux or macOS? (linux/macos): " OS

# Create build directory if it doesn't exist
mkdir -p build
cd src

if [ "$OS" == "linux" ]; then
    # Compile the code for Linux
    clang++ main.cpp startWindow/justForgeStarter.cpp utilities/justForgeAnimator.cpp dash/dash.cpp utilities/justForgeMouse.cpp mainScreen/mainScreen.cpp dataCard/dataCard.cpp -o ../build/Santra -std=c++17 -Isrc -I/usr/include/python3.11 -I/usr/include/pybind11 -lpython3.11 -lsfml-graphics -lsfml-window -lsfml-system
elif [ "$OS" == "macos" ]; then
    # Get the SFML and pybind11 installation paths
    SFML_PATH=$(brew --prefix sfml)

    # Compile the code for macOS
    clang++ main.cpp startWindow/justForgeStarter.cpp utilities/justForgeAnimator.cpp dash/dash.cpp utilities/justForgeMouse.cpp mainScreen/mainScreen.cpp dataCard/dataCard.cpp -o ../build/Santra -std=c++17 -Isrc -I${SFML_PATH}/include -L${SFML_PATH}/lib -lsfml-graphics -lsfml-window -lsfml-system
else
    echo "Unsupported OS. Please specify 'linux' or 'macos'. If windows use chocolatey or link SFML and Python.h"
    exit 1
fi

# Move back to root directory
cd ..
clear
echo "Build complete."