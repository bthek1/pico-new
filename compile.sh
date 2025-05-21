#!/bin/bash

set -e

BUILD_DIR="build"
SDK_PATH="lib/pico-sdk"

# Check for optional --clean flag
CLEAN_BUILD=false
if [[ "$1" == "--clean" ]]; then
  CLEAN_BUILD=true
fi

# 🧩 Step 1: Ensure pico-sdk submodule is initialized
if [[ ! -f "$SDK_PATH/external/pico_sdk_import.cmake" ]]; then
  echo "📦 Initializing Pico SDK submodule..."
  git submodule update --init --recursive
else
  echo "✅ Pico SDK already initialized."
fi

# 🧹 Step 2: Optionally clean the build folder
if $CLEAN_BUILD; then
  echo "🧹 Cleaning $BUILD_DIR directory..."
  rm -rf "$BUILD_DIR"
fi

# 📂 Step 3: Create and enter build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# ⚙️ Step 4: Configure and build
echo "⚙️ Running cmake .."
cmake ..

echo "🛠️ Building project with make -j4"
make -j4

echo "✅ Build complete!"
