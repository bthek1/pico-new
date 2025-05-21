#!/bin/bash

set -e

BUILD_DIR="build"

# Check for optional --clean flag
CLEAN_BUILD=false
if [[ "$1" == "--clean" ]]; then
  CLEAN_BUILD=true
fi

if $CLEAN_BUILD; then
  echo "🧹 Cleaning $BUILD_DIR directory..."
  rm -rf "$BUILD_DIR"
fi

# Ensure build directory exists
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "⚙️ Running cmake .."
cmake ..

echo "🛠️ Building project with make -j4"
make -j4

echo "✅ Build complete!"
