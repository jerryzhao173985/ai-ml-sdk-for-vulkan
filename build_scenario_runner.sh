#!/bin/bash
# Build Scenario Runner with fixed compatibility header

set -e

BUILD_ROOT="/Users/jerry/Vulkan/ml-sdk-macos-build"
SDK_ROOT="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan"

echo "Building Scenario Runner with updated compatibility header..."

cd "$BUILD_ROOT/scenario-runner"
ninja -j16 2>&1 | head -100 || true

# Check if the build succeeded
if [ -f "$BUILD_ROOT/scenario-runner/src/tools/scenario-runner" ]; then
    echo "✅ Scenario Runner built successfully!"
else
    echo "⚠️  Scenario Runner build still has issues"
    echo "Checking for error patterns..."
    grep -E "(error:|FAILED:)" build.log 2>/dev/null | head -10 || true
fi