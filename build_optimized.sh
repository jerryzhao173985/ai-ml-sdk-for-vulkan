#!/bin/bash
# Optimized build script for ML SDK for Vulkan

echo "ML SDK for Vulkan - Optimized Build"
echo "==================================="
echo "System: 16 cores, 64GB RAM"
echo ""

# Set build directory
BUILD_DIR="build"

# Get number of cores
NUM_CORES=$(sysctl -n hw.ncpu)
echo "Using $NUM_CORES parallel jobs"

# Set up build environment for maximum performance
export MAKEFLAGS="-j$NUM_CORES"
export CMAKE_BUILD_PARALLEL_LEVEL=$NUM_CORES

# For LLVM specifically, use more aggressive settings
export LLVM_PARALLEL_COMPILE_JOBS=$NUM_CORES
export LLVM_PARALLEL_LINK_JOBS=$((NUM_CORES/2))  # Link jobs use more memory

# Clean previous build
echo "Cleaning previous build..."
rm -rf $BUILD_DIR

# Create build directory
mkdir -p $BUILD_DIR

# Run build with all optimizations
echo ""
echo "Starting optimized build with $NUM_CORES threads..."
echo "This should take approximately 15-30 minutes on your system"
echo ""

# Use caffeinate on macOS to prevent sleep during build
caffeinate -dis python3 ./scripts/build.py \
    --build-dir $BUILD_DIR \
    --threads $NUM_CORES \
    --skip-llvm-patch \
    --build-type Release

# Check if build succeeded
if [ $? -eq 0 ]; then
    echo ""
    echo "==================================="
    echo "Build completed successfully!"
    echo ""
    echo "Next steps:"
    echo "1. source ./setup_environment.sh"
    echo "2. ./test_installation.sh"
else
    echo ""
    echo "==================================="
    echo "Build failed. Check the output above for errors."
    exit 1
fi