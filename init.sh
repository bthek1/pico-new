#!/bin/bash

set -e

if [[ -z "$1" ]]; then
  echo "Usage: ./init.sh <project_name>"
  exit 1
fi

PROJECT_NAME=$1
BASE_DIR=$(dirname "$0")
DEST_DIR="$PWD/$PROJECT_NAME"

mkdir -p "$DEST_DIR"
cp "$BASE_DIR/template/main.c" "$DEST_DIR/main.c"

# Replace placeholder in CMakeLists
sed "s/{{project_name}}/$PROJECT_NAME/g" "$BASE_DIR/template/CMakeLists.txt" > "$DEST_DIR/CMakeLists.txt"

echo "✅ Project '$PROJECT_NAME' created at $DEST_DIR"
