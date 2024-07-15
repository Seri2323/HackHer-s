#!/bin/bash

# Goto virtual environment
source venv/bin/activate

# Change directory to build and run the program
cd build
./Santra

echo "Program execution complete."
cd ..

