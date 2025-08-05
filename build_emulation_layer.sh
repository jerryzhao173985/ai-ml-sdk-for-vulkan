#!/bin/bash

# Build the ML Emulation Layer for Vulkan on macOS

set -e

REPO_DIR="/Users/jerry/Vulkan"
EMULATION_LAYER_DIR="${REPO_DIR}/ai-ml-emulation-layer-for-vulkan"
BUILD_DIR="${EMULATION_LAYER_DIR}/build"

echo "=== Building ML Emulation Layer for Vulkan on macOS ARM64 ==="
echo "Platform: Mac M4 Max with 64GB RAM, 16 cores"
echo ""

# Check if emulation layer exists
if [ ! -d "${EMULATION_LAYER_DIR}" ]; then
    echo "Error: Emulation layer not found at ${EMULATION_LAYER_DIR}"
    exit 1
fi

# Clean previous build
if [ -d "${BUILD_DIR}" ]; then
    echo "Cleaning previous build..."
    rm -rf "${BUILD_DIR}"
fi

# Create build directory
mkdir -p "${BUILD_DIR}"

# Configure with CMake for macOS
echo "Configuring with CMake..."
cmake -B "${BUILD_DIR}" -S "${EMULATION_LAYER_DIR}" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_OSX_ARCHITECTURES=arm64 \
    -DGLSLANG_PATH="${REPO_DIR}/dependencies/glslang" \
    -DSPIRV_CROSS_PATH="${REPO_DIR}/dependencies/SPIRV-Cross" \
    -DSPIRV_HEADERS_PATH="${REPO_DIR}/dependencies/SPIRV-Headers" \
    -DSPIRV_TOOLS_PATH="${REPO_DIR}/dependencies/SPIRV-Tools" \
    -DVULKAN_HEADERS_PATH="${REPO_DIR}/dependencies/Vulkan-Headers" \
    -DVMEL_TESTS_ENABLE=OFF \
    -DVMEL_BUILD_DOCS=OFF

# Build with parallel jobs
echo ""
echo "Building with $(sysctl -n hw.ncpu) parallel jobs..."
cmake --build "${BUILD_DIR}" -j $(sysctl -n hw.ncpu)

# Install to deploy directory
DEPLOY_DIR="${EMULATION_LAYER_DIR}/deploy"
echo ""
echo "Installing to ${DEPLOY_DIR}..."
cmake --install "${BUILD_DIR}" --prefix "${DEPLOY_DIR}"

echo ""
echo "=== Build Complete ==="
echo "Emulation layer installed to: ${DEPLOY_DIR}"
echo ""
echo "To use the emulation layer, set these environment variables:"
echo "export DYLD_LIBRARY_PATH=\${DEPLOY_DIR}/lib:\$DYLD_LIBRARY_PATH"
echo "export VK_ADD_LAYER_PATH=\${DEPLOY_DIR}/share/vulkan/explicit_layer.d"
echo "export VK_INSTANCE_LAYERS=VK_LAYER_ML_Graph_Emulation:VK_LAYER_ML_Tensor_Emulation"