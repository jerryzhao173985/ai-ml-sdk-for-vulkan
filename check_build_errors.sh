#!/bin/bash
# Check detailed build errors

BUILD_ROOT="/Users/jerry/Vulkan/ml-sdk-macos-build"
cd "$BUILD_ROOT/scenario-runner"

echo "Checking detailed build errors..."
echo "================================"

# Try to build and capture specific errors
ninja -j16 2>&1 | grep -A5 -B5 "error:" | head -200