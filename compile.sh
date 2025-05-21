#!/bin/bash

set -e

BUILD_DIR="build"
SDK_PATH="lib/pico-sdk"

# Check for optional --clean flag
CLEAN_BUILD=false
if [[ "$1" == "--clean" ]]; then
  CLEAN_BUILD=true
fi

# 🧰 Step 0: Check and install system dependencies only if missing
REQUIRED_PKGS=(cmake gcc-arm-none-eabi build-essential libnewlib-arm-none-eabi)
MISSING_PKGS=()

echo "🔍 Checking system dependencies..."

for pkg in "${REQUIRED_PKGS[@]}"; do
  if ! dpkg -s "$pkg" &> /dev/null; then
    MISSING_PKGS+=("$pkg")
  fi
done

if [ ${#MISSING_PKGS[@]} -ne 0 ]; then
  echo "📦 Missing packages: ${MISSING_PKGS[*]}"
  echo "🔧 Installing missing packages..."
  sudo apt update
  sudo apt install -y "${MISSING_PKGS[@]}"
else
  echo "✅ All required packages are already installed."
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
