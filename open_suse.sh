#!/bin/bash

# Update package repositories
echo "Updating package repositories..."
sudo zypper refresh

# Install required development packages
echo "Installing required development packages..."
sudo zypper install -y wayland-devel wayland-protocols-devel libxkbcommon-devel libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel Mesa-libGL-devel

# Check if cmake is installed, install if missing
if ! command -v cmake &> /dev/null
then
    echo "CMake not found, installing..."
    sudo zypper install -y cmake
else
    echo "CMake is already installed."
fi

# Navigate to the project directory (modify this if necessary)
PROJECT_DIR="~/CmakeRayLibTemplate"
echo "Navigating to project directory: $PROJECT_DIR"
cd "$PROJECT_DIR" || { echo "Project directory not found!"; exit 1; }

# Run CMake and make
echo "Running CMake..."
cmake .

if [ $? -ne 0 ]; then
    echo "CMake configuration failed. Exiting..."
    exit 1
fi

echo "Building the project..."
make

if [ $? -eq 0 ]; then
    echo "Build completed successfully!"
else
    echo "Build failed. Please check the error messages above."
    exit 1
fi
