#!/bin/bash
# Clean and rebuild with updated compatibility header

BUILD_ROOT="/Users/jerry/Vulkan/ml-sdk-macos-build"
SDK_ROOT="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan"

echo "Cleaning object files..."
rm -rf "$BUILD_ROOT/scenario-runner/src/CMakeFiles/ScenarioRunnerLib.dir/"*.o

echo "Rebuilding Scenario Runner..."
cd "$BUILD_ROOT/scenario-runner"
ninja -j16 2>&1 | tee build.log | grep -E "(Building|error:|FAILED:|Linking)" | head -100