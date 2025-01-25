#!/bin/bash

# Check if a file is provided
if [ $# -eq 0 ]; then
  echo "Usage: $0 <cpp_file>"
  exit 1
fi

CPP_FILE="$1"

# Check if the file exists
if [ ! -f "$CPP_FILE" ]; then
  echo "Error: File '$CPP_FILE' not found."
  exit 1
fi

# Create a temporary file for the compiled binary
TEMP_BINARY=$(mktemp)

# Compile the C++ file with LeetCode-like settings
clang++-19 \
  -std=c++23 \
  -stdlib=libstdc++ \
  -Wall -Wextra \
  -O2 \
  -fsanitize=address \
  "$CPP_FILE" -o "$TEMP_BINARY" \
  -lfmt # Link to fmt library

# Check if the compilation succeeded
if [ $? -ne 0 ]; then
  echo "Compilation failed."
  rm -f "$TEMP_BINARY"
  exit 1
fi

# Run the compiled binary
echo "Running....."
"$TEMP_BINARY"

# Clean up the temporary binary
rm -f "$TEMP_BINARY"
