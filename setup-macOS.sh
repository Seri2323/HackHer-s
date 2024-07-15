#!/bin/bash

# Update and install dependencies using Homebrew
brew update
brew install python3 clang sfml

# Install pybind11
pip3 install pybind11

# Create virtual environment
python3 -m venv venv

# Activate virtual environment
source venv/bin/activate

# Install Python requirements
pip install -r requirements.txt
pip install pybind11

echo "Setup complete for macOS."
