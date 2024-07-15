#!/bin/bash

# Update and install dependencies
sudo apt update
sudo apt install -y python3 python3-venv python3-pip clang libsfml-dev

# Create virtual environment
python3 -m venv venv

# Activate virtual environment
source venv/bin/activate

# Install Python requirements

pip install -r requirements.txt
pip install pybind11

clear
echo "Setup complete for Linux."
