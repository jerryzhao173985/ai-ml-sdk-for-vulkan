#!/bin/bash
# Ultra-fast build script using Ninja for ML SDK for Vulkan

echo "ML SDK for Vulkan - Ninja Build (Maximum Performance)"
echo "===================================================="
echo "System: 16 cores, 64GB RAM"
echo "Build system: Ninja (optimal for parallel builds)"
echo ""

# Set build directory
BUILD_DIR="build-ninja"

# Get number of cores
NUM_CORES=$(sysctl -n hw.ncpu)
echo "Using $NUM_CORES parallel jobs"

# Clean previous build
echo "Cleaning previous build..."
rm -rf $BUILD_DIR

# Create build directory
mkdir -p $BUILD_DIR

# Configure with Ninja generator
echo ""
echo "Configuring with Ninja generator..."
echo ""

cmake -S . -B $BUILD_DIR -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DARGPARSE_PATH="$PWD/dependencies/argparse" \
    -DFLATBUFFERS_PATH="$PWD/dependencies/flatbuffers" \
    -DJSON_PATH="$PWD/dependencies/json" \
    -DGLSLANG_PATH="$PWD/dependencies/glslang" \
    -DSPIRV_HEADERS_PATH="$PWD/dependencies/SPIRV-Headers" \
    -DSPIRV_TOOLS_PATH="$PWD/dependencies/SPIRV-Tools" \
    -DSPIRV_CROSS_PATH="$PWD/dependencies/SPIRV-Cross" \
    -DVULKAN_HEADERS_PATH="$PWD/dependencies/Vulkan-Headers" \
    -DLLVM_PATH="$PWD/dependencies/llvm-project" \
    -DTOSA_MLIR_TRANSLATOR_PATH="$PWD/dependencies/tosa_mlir_translator" \
    -DML_SDK_MODEL_CONVERTER_PATH="$PWD/sw/model-converter" \
    -DML_SDK_SCENARIO_RUNNER_PATH="$PWD/sw/scenario-runner" \
    -DML_SDK_VGF_LIB_PATH="$PWD/sw/vgf-lib" \
    -DML_SDK_EMULATION_LAYER_PATH="$PWD/sw/emulation-layer" \
    -DMODEL_CONVERTER_APPLY_LLVM_PATCH=OFF \
    -DLLVM_PARALLEL_COMPILE_JOBS=$NUM_CORES \
    -DLLVM_PARALLEL_LINK_JOBS=$((NUM_CORES/2))

if [ $? -ne 0 ]; then
    echo "Configuration failed!"
    exit 1
fi

# Build with Ninja
echo ""
echo "Building with Ninja using $NUM_CORES jobs..."
echo "This should be significantly faster than Make"
echo ""

# Use caffeinate on macOS to prevent sleep during build
time caffeinate -dis ninja -C $BUILD_DIR -j $NUM_CORES

# Check if build succeeded
if [ $? -eq 0 ]; then
    echo ""
    echo "===================================================="
    echo "Build completed successfully!"
    echo ""
    echo "Build time is shown above"
    echo ""
    echo "Next steps:"
    echo "1. Update setup_environment.sh to use build-ninja directory"
    echo "2. source ./setup_environment.sh"
    echo "3. ./test_installation.sh"
    
    # Update the BUILD_DIR in setup_environment.sh
    sed -i '' 's|build|build-ninja|g' setup_environment.sh
    echo ""
    echo "setup_environment.sh has been updated to use build-ninja directory"
else
    echo ""
    echo "===================================================="
    echo "Build failed. Check the output above for errors."
    exit 1
fi