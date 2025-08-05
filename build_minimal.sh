#!/bin/bash
# Minimal build - only essential components

echo "ML SDK for Vulkan - Minimal Build (VGF, Model Converter, Scenario Runner)"
echo "========================================================================"

NUM_CORES=$(sysctl -n hw.ncpu)
BUILD_DIR="build-minimal"

# Clean
rm -rf $BUILD_DIR

# Create minimal CMakeLists.txt that excludes emulation layer
cat > CMakeLists.minimal.txt << 'EOF'
cmake_minimum_required(VERSION 3.25)

project(MLSdkForVulkan
    DESCRIPTION "ML SDK for Vulkan®")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "${CMAKE_PROJECT_NAME} requires an out of source build.")
endif()

# Path to ML SDK for Vulkan® root
set(ML_SDK_FOR_VULKAN_PATH           "${CMAKE_CURRENT_LIST_DIR}" CACHE PATH "Path to ML SDK for Vulkan®")

# Third party dependencies
set(ARGPARSE_PATH                    "${ML_SDK_FOR_VULKAN_PATH}/dependencies/argparse" CACHE PATH "Path to Argparse")
set(CATCH2_PATH                      "${ML_SDK_FOR_VULKAN_PATH}/dependencies/Catch2" CACHE PATH "Path to Catch2")
set(FLATBUFFERS_PATH                 "${ML_SDK_FOR_VULKAN_PATH}/dependencies/flatbuffers" CACHE PATH "Path to FlatBuffers")
set(JSON_PATH                        "${ML_SDK_FOR_VULKAN_PATH}/dependencies/json" CACHE PATH "Path to JSON")
set(LLVM_PATH                        "${ML_SDK_FOR_VULKAN_PATH}/dependencies/llvm-project" CACHE PATH "Path to LLVM")
set(TOSA_MLIR_TRANSLATOR_PATH        "${ML_SDK_FOR_VULKAN_PATH}/dependencies/tosa_mlir_translator" CACHE PATH "Path to TOSA MLIR Translator")

# Khronos dependencies
set(GLSLANG_PATH                     "${ML_SDK_FOR_VULKAN_PATH}/dependencies/glslang" CACHE PATH "Path to GLSLang")
set(SPIRV_HEADERS_PATH               "${ML_SDK_FOR_VULKAN_PATH}/dependencies/SPIRV-Headers" CACHE PATH "Path to SPIRV Headers")
set(SPIRV_CROSS_PATH                 "${ML_SDK_FOR_VULKAN_PATH}/dependencies/SPIRV-Cross" CACHE PATH "Path to SPIRV Cross")
set(SPIRV_TOOLS_PATH                 "${ML_SDK_FOR_VULKAN_PATH}/dependencies/SPIRV-Tools" CACHE PATH "Path to SPIRV Tools")
set(VULKAN_HEADERS_PATH              "${ML_SDK_FOR_VULKAN_PATH}/dependencies/Vulkan-Headers" CACHE PATH "Path to Vulkan Headers")

# SDK components
set(ML_SDK_VGF_LIB_PATH              "${ML_SDK_FOR_VULKAN_PATH}/sw/vgf-lib" CACHE PATH "Path to the ML SDK VGF Library")
set(ML_SDK_MODEL_CONVERTER_PATH      "${ML_SDK_FOR_VULKAN_PATH}/sw/model-converter" CACHE PATH "Path to the ML SDK Model Converter")
set(ML_SDK_SCENARIO_RUNNER_PATH      "${ML_SDK_FOR_VULKAN_PATH}/sw/scenario-runner" CACHE PATH "Path to the ML SDK Scenario Runner")

# Only add the components we need
if(EXISTS "${ML_SDK_VGF_LIB_PATH}/CMakeLists.txt")
    message(STATUS "Including VGF Library")
    add_subdirectory("${ML_SDK_VGF_LIB_PATH}" vgf-lib)
endif()

if(EXISTS "${ML_SDK_MODEL_CONVERTER_PATH}/CMakeLists.txt")
    message(STATUS "Including Model Converter")
    add_subdirectory("${ML_SDK_MODEL_CONVERTER_PATH}" model-converter)
endif()

if(EXISTS "${ML_SDK_SCENARIO_RUNNER_PATH}/CMakeLists.txt")
    message(STATUS "Including Scenario Runner")
    add_subdirectory("${ML_SDK_SCENARIO_RUNNER_PATH}" scenario-runner)
endif()
EOF

# Configure and build
echo "Configuring with Ninja..."
cmake -S . -B $BUILD_DIR -G Ninja \
    -C CMakeLists.minimal.txt \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DMODEL_CONVERTER_APPLY_LLVM_PATCH=OFF \
    -DLLVM_PARALLEL_COMPILE_JOBS=$NUM_CORES \
    -DLLVM_PARALLEL_LINK_JOBS=$((NUM_CORES/2)) \
    -DLLVM_ENABLE_LTO=OFF \
    -DLLVM_ENABLE_ASSERTIONS=OFF \
    -DLLVM_BUILD_TESTS=OFF \
    -DLLVM_BUILD_EXAMPLES=OFF \
    -DLLVM_BUILD_BENCHMARKS=OFF \
    -DLLVM_TARGETS_TO_BUILD="AArch64"

if [ $? -ne 0 ]; then
    echo "Configuration failed!"
    exit 1
fi

echo ""
echo "Building with $NUM_CORES cores..."
time caffeinate -dis ninja -C $BUILD_DIR -j $NUM_CORES

if [ $? -eq 0 ]; then
    echo ""
    echo "========================================================================"
    echo "Build completed successfully!"
    echo ""
    echo "Built components:"
    ls -la $BUILD_DIR/*/model-converter 2>/dev/null && echo "  ✓ model-converter"
    ls -la $BUILD_DIR/*/scenario-runner 2>/dev/null && echo "  ✓ scenario-runner"
    ls -la $BUILD_DIR/*/vgf_dump/vgf_dump 2>/dev/null && echo "  ✓ vgf_dump"
    echo ""
    
    # Create setup script for this build
    cat > setup_minimal.sh << 'EOF'
#!/bin/bash
export ML_SDK_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export ML_SDK_BUILD_DIR="$ML_SDK_ROOT/build-minimal"

# Add binaries to PATH
export PATH="$ML_SDK_BUILD_DIR/model-converter:$PATH"
export PATH="$ML_SDK_BUILD_DIR/scenario-runner:$PATH"
export PATH="$ML_SDK_BUILD_DIR/vgf-lib/vgf_dump:$PATH"

echo "ML SDK for Vulkan (minimal build) environment configured!"
echo "Available tools: model-converter, scenario-runner, vgf_dump"
EOF
    chmod +x setup_minimal.sh
    
    echo "To use: source ./setup_minimal.sh"
else
    echo "Build failed!"
    exit 1
fi