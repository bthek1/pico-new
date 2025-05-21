#!/bin/bash

set -e

DEFAULT_PROJECT="oscilloscope"
PROJECT_NAME="${1:-$DEFAULT_PROJECT}"
BUILD_DIR="build/$PROJECT_NAME"
MOUNT_POINT=$(find /media/$USER -type d -name "RPI-RP2" 2>/dev/null | head -n 1)

UF2_FILE="$BUILD_DIR/$PROJECT_NAME.uf2"

if [[ ! -f "$UF2_FILE" ]]; then
  echo "❌ .uf2 file not found for project '$PROJECT_NAME'. Have you run make?"
  exit 1
fi

if [[ -z "$MOUNT_POINT" ]]; then
  echo "❌ Pico not found. Please plug in your Pico in BOOTSEL mode."
  exit 1
fi

echo "🚀 Flashing $UF2_FILE to $MOUNT_POINT..."
cp "$UF2_FILE" "$MOUNT_POINT"
echo "✅ Flash complete!"
