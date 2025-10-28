#!/bin/bash
# Build the project using Ninja

set -e

BUILD_DIR="build"
TARGET="${1:-all}"

# Check if build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    echo "Build directory not found. Running configure.sh first..."
    ./configure.sh
fi

# Build
if [ "$TARGET" = "all" ]; then
    echo "Building all targets..."
    ninja -C "$BUILD_DIR"
else
    echo "Building target: $TARGET"
    ninja -C "$BUILD_DIR" "$TARGET"
fi

echo ""
echo "Build complete!"
