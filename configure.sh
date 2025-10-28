#!/bin/bash
# Configure the build system with CMake and Ninja

set -e

# Default values
BUILD_TYPE="${1:-Debug}"
BUILD_DIR="build"

# Check if Ninja is available
if ! command -v ninja &> /dev/null; then
    echo "Error: Ninja build system not found. Please install ninja-build package."
    echo "On Ubuntu/Debian: sudo apt install ninja-build"
    echo "On Fedora: sudo dnf install ninja-build"
    exit 1
fi

# Check CMake version
CMAKE_VERSION=$(cmake --version | head -n1 | cut -d' ' -f3)
CMAKE_MAJOR=$(echo $CMAKE_VERSION | cut -d'.' -f1)
CMAKE_MINOR=$(echo $CMAKE_VERSION | cut -d'.' -f2)

if [ $CMAKE_MAJOR -lt 3 ] || ([ $CMAKE_MAJOR -eq 3 ] && [ $CMAKE_MINOR -lt 28 ]); then
    echo "Error: CMake 3.28 or higher is required for C++20 module support."
    echo "Current version: $CMAKE_VERSION"
    exit 1
fi

# Check compiler support
CXX_COMPILER="${CXX:-g++}"
if command -v "$CXX_COMPILER" &> /dev/null; then
    CXX_VERSION=$($CXX_COMPILER --version | head -n1)
    echo "Using C++ compiler: $CXX_VERSION"
else
    echo "Warning: C++ compiler $CXX_COMPILER not found."
fi

echo "Configuring build with:"
echo "  Build type: $BUILD_TYPE"
echo "  Build directory: $BUILD_DIR"
echo "  Generator: Ninja"

# Create build directory
mkdir -p "$BUILD_DIR"

# Configure with CMake
cmake -S . -B "$BUILD_DIR" \
    -G Ninja \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

echo ""
echo "Configuration complete!"
echo ""
echo "To build all targets, run:"
echo "  ninja -C $BUILD_DIR"
echo ""
echo "To build a specific day, run:"
echo "  ninja -C $BUILD_DIR day01"
echo ""
echo "To clean the build, run:"
echo "  ninja -C $BUILD_DIR clean"
