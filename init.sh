#!/bin/bash

set -e

if [[ -z "$1" ]]; then
  echo "Usage: ./init.sh <project_name>"
  exit 1
fi

PROJECT_NAME=$1
BASE_DIR=$(cd "$(dirname "$0")" && pwd)
DEST_DIR="$PWD/$PROJECT_NAME"
TOP_CMAKELISTS="$PWD/CMakeLists.txt"
TEMPLATE_DIR="$BASE_DIR/template"

mkdir -p "$DEST_DIR"
cp "$TEMPLATE_DIR/main.c" "$DEST_DIR/main.c"
sed "s/{{project_name}}/$PROJECT_NAME/g" "$TEMPLATE_DIR/CMakeLists.txt" > "$DEST_DIR/CMakeLists.txt"

# Ensure top-level CMakeLists.txt exists
if [[ ! -f "$TOP_CMAKELISTS" ]]; then
  cat <<EOF > "$TOP_CMAKELISTS"
cmake_minimum_required(VERSION 3.13)
set(PICO_SDK_PATH "\${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk")
include(\${PICO_SDK_PATH}/external/pico_sdk_import.cmake")
project(pico_projects)
pico_sdk_init()
EOF
  echo "📄 Created top-level CMakeLists.txt"
fi

# Add add_subdirectory if not already included
if ! grep -Fxq "add_subdirectory($PROJECT_NAME)" "$TOP_CMAKELISTS"; then
  echo "add_subdirectory($PROJECT_NAME)" >> "$TOP_CMAKELISTS"
  echo "➕ Registered project in top-level CMakeLists.txt"
else
  echo "ℹ️ Project already registered in top-level CMakeLists.txt"
fi

echo "✅ Project '$PROJECT_NAME' created at $DEST_DIR"
