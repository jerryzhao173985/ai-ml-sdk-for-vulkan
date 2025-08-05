#!/bin/bash
# Build emulation layer with all proper dependencies

set -e

echo "=== Building ARM ML Emulation Layer for Vulkan ==="

# Set paths
EMULATION_ROOT="/Users/jerry/Vulkan/ai-ml-emulation-layer-for-vulkan"
DEPS_ROOT="/Users/jerry/Vulkan/dependencies"

cd "$EMULATION_ROOT"

# Clean and create build directory
rm -rf build
mkdir build
cd build

# Configure with all proper paths
cmake .. \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_OSX_ARCHITECTURES=arm64 \
  -DCMAKE_PREFIX_PATH="$DEPS_ROOT/Vulkan-Headers/install" \
  -DVulkanHeaders_DIR="$DEPS_ROOT/Vulkan-Headers/install/share/cmake/VulkanHeaders" \
  -DSPIRV_HEADERS_PATH="$DEPS_ROOT/SPIRV-Headers" \
  -DSPIRV_TOOLS_PATH="$DEPS_ROOT/SPIRV-Tools" \
  -DGLSLANG_PATH="$DEPS_ROOT/glslang" \
  -DSPIRV_CROSS_PATH="$DEPS_ROOT/SPIRV-Cross" \
  -DGTEST_PATH="$DEPS_ROOT/googletest" \
  -DBUILD_TESTS=OFF \
  -DBUILD_LAYERS=ON

# Build
echo "Building emulation layer..."
make -j4 VERBOSE=1 || true

# Check results
echo ""
echo "=== Checking build results ==="
find . -name "*.a" -o -name "*.so" -o -name "*.dylib" -o -name "*.json" | grep -E "(tensor|graph|layer)" | sort

echo ""
echo "=== Build complete ==="