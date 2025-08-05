#!/bin/bash
# Fix and continue ARM ML SDK build

set -e

echo "=== Fixing and continuing ARM ML SDK build ==="

# First, let's skip glslang standalone tools and continue with the rest
cd /Users/jerry/Vulkan/ai-ml-sdk-for-vulkan

# Continue the build, but skip certain problematic targets
echo "Continuing build with specific targets..."

# Build VGF library first
echo "Building VGF library..."
cmake --build build-official --target vgf -j 4 || true

# Build scenario runner  
echo "Building scenario runner..."
cmake --build build-official --target scenario-runner -j 4 || true

# Build emulation layer (without glslang standalone)
echo "Building emulation layer libraries..."
cmake --build build-official --target ml_emulation -j 4 || true

# Build model converter (after LLVM is done)
echo "Building model converter..."
cmake --build build-official --target model-converter -j 4 || true

echo ""
echo "=== Checking results ==="
./check_official_build.sh