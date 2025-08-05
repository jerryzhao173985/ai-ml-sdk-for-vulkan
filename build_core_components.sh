#!/bin/bash
# Build only core components directly

echo "ML SDK for Vulkan - Core Components Build"
echo "========================================"
echo "Building: VGF Library, Model Converter, Scenario Runner"
echo ""

NUM_CORES=$(sysctl -n hw.ncpu)
BUILD_DIR="build-core"

# Clean
rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR

echo "Building with $NUM_CORES cores..."
echo ""

# Build VGF Library first
echo "1/3: Building VGF Library..."
cd sw/vgf-lib
mkdir -p build
cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DJSON_PATH="$PWD/../../dependencies/json"
    
ninja -C build -j $NUM_CORES
if [ $? -ne 0 ]; then
    echo "VGF Library build failed!"
    exit 1
fi
cd ../..

# Build Model Converter
echo ""
echo "2/3: Building Model Converter..."
cd sw/model-converter
mkdir -p build
cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DLLVM_PATH="$PWD/../../dependencies/llvm-project" \
    -DTOSA_MLIR_TRANSLATOR_PATH="$PWD/../../dependencies/tosa_mlir_translator" \
    -DML_SDK_VGF_LIB_PATH="$PWD/../vgf-lib" \
    -DMODEL_CONVERTER_APPLY_LLVM_PATCH=OFF \
    -DLLVM_PARALLEL_COMPILE_JOBS=$NUM_CORES \
    -DLLVM_PARALLEL_LINK_JOBS=$((NUM_CORES/2))
    
ninja -C build -j $NUM_CORES
if [ $? -ne 0 ]; then
    echo "Model Converter build failed!"
    exit 1
fi
cd ../..

# Build Scenario Runner
echo ""
echo "3/3: Building Scenario Runner..."
cd sw/scenario-runner
mkdir -p build
cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DML_SDK_VGF_LIB_PATH="$PWD/../vgf-lib" \
    -DVULKAN_HEADERS_PATH="$PWD/../../dependencies/Vulkan-Headers" \
    -DGLSLANG_PATH="$PWD/../../dependencies/glslang" \
    -DSPIRV_HEADERS_PATH="$PWD/../../dependencies/SPIRV-Headers" \
    -DSPIRV_TOOLS_PATH="$PWD/../../dependencies/SPIRV-Tools" \
    -DSPIRV_CROSS_PATH="$PWD/../../dependencies/SPIRV-Cross"
    
ninja -C build -j $NUM_CORES
if [ $? -ne 0 ]; then
    echo "Scenario Runner build failed!"
    exit 1
fi
cd ../..

echo ""
echo "========================================"
echo "Build completed successfully!"
echo ""
echo "Binaries location:"
echo "  VGF Library: sw/vgf-lib/build/"
echo "  Model Converter: sw/model-converter/build/"
echo "  Scenario Runner: sw/scenario-runner/build/"
echo ""
echo "To use the tools, add them to your PATH or use full paths."