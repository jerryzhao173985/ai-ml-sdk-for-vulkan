#!/bin/bash
# Fix and build emulation layer with proper dependencies

set -e

echo "=== Building ARM ML Emulation Layer for Vulkan ==="

# Set paths
SDK_ROOT="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan"
EMULATION_ROOT="/Users/jerry/Vulkan/ai-ml-emulation-layer-for-vulkan"
DEPS_ROOT="/Users/jerry/Vulkan/dependencies"

# First, let's build the emulation layer separately
cd "$EMULATION_ROOT"

# Clean previous attempts
rm -rf build
mkdir build
cd build

# Configure with proper paths
cmake .. \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_OSX_ARCHITECTURES=arm64 \
  -DSPIRV_HEADERS_PATH="$DEPS_ROOT/SPIRV-Headers" \
  -DSPIRV_TOOLS_PATH="$DEPS_ROOT/SPIRV-Tools" \
  -DGLSLANG_PATH="$DEPS_ROOT/glslang" \
  -DSPIRV_CROSS_PATH="$DEPS_ROOT/SPIRV-Cross" \
  -DVULKAN_HEADERS_PATH="$DEPS_ROOT/Vulkan-Headers/include" \
  -DGTEST_PATH="$DEPS_ROOT/googletest" \
  -DBUILD_TESTS=OFF

# Build
echo "Building emulation layer..."
make -j4 || true

# Check what was built
echo ""
echo "=== Checking build results ==="
find . -name "*.a" -o -name "*.so" -o -name "*.dylib" | sort

# If that fails, try building just the core libraries
if [ ! -f "libml_emulation.a" ]; then
    echo ""
    echo "=== Trying to build core components only ==="
    
    # Build tensor layer
    make -j4 tensor || true
    
    # Build graph layer
    make -j4 graph || true
fi

echo ""
echo "=== Build complete ==="