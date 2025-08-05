#!/bin/bash
# ARM ML SDK for Vulkan - Complete Build Script for macOS ARM64
# This script builds all components in the correct dependency order

set -e  # Exit on error

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_TYPE="${BUILD_TYPE:-Debug}"
JOBS="${JOBS:-8}"

echo "=== ARM ML SDK for Vulkan Build Script ==="
echo "Platform: macOS ARM64"
echo "Build Type: $BUILD_TYPE"
echo "Parallel Jobs: $JOBS"
echo ""

# Function to build a component
build_component() {
    local name=$1
    local src_dir=$2
    local build_dir=$3
    local cmake_args=$4
    
    echo "=== Building $name ==="
    echo "Source: $src_dir"
    echo "Build: $build_dir"
    
    mkdir -p "$build_dir"
    cd "$build_dir"
    
    echo "Configuring..."
    cmake "$src_dir" -DCMAKE_BUILD_TYPE=$BUILD_TYPE $cmake_args
    
    echo "Building..."
    make -j$JOBS
    
    if [ -f Makefile ]; then
        echo "Installing..."
        make install || true
    fi
    
    echo "✓ $name built successfully"
    echo ""
}

# 1. Build SPIRV-Headers
echo "Step 1/6: SPIRV-Headers"
if [ ! -f "$SCRIPT_DIR/dependencies/SPIRV-Headers/install/lib/cmake/SPIRV-Headers/SPIRV-HeadersConfig.cmake" ]; then
    build_component "SPIRV-Headers" \
        "$SCRIPT_DIR/dependencies/SPIRV-Headers" \
        "$SCRIPT_DIR/dependencies/SPIRV-Headers/build" \
        "-DCMAKE_INSTALL_PREFIX=$SCRIPT_DIR/dependencies/SPIRV-Headers/install"
else
    echo "✓ SPIRV-Headers already built"
fi

# 2. Build SPIRV-Tools
echo "Step 2/6: SPIRV-Tools"
if [ ! -f "$SCRIPT_DIR/dependencies/SPIRV-Tools/install/lib/libSPIRV-Tools.a" ]; then
    build_component "SPIRV-Tools" \
        "$SCRIPT_DIR/dependencies/SPIRV-Tools" \
        "$SCRIPT_DIR/dependencies/SPIRV-Tools/build" \
        "-DCMAKE_INSTALL_PREFIX=$SCRIPT_DIR/dependencies/SPIRV-Tools/install \
         -DSPIRV-Headers_SOURCE_DIR=$SCRIPT_DIR/dependencies/SPIRV-Headers \
         -DSPIRV_SKIP_TESTS=ON"
else
    echo "✓ SPIRV-Tools already built"
fi

# 3. Build glslang
echo "Step 3/6: glslang"
if [ ! -f "$SCRIPT_DIR/dependencies/glslang/install/lib/libglslang.a" ]; then
    build_component "glslang" \
        "$SCRIPT_DIR/dependencies/glslang" \
        "$SCRIPT_DIR/dependencies/glslang/build" \
        "-DCMAKE_INSTALL_PREFIX=$SCRIPT_DIR/dependencies/glslang/install \
         -DSPIRV-Tools_DIR=$SCRIPT_DIR/dependencies/SPIRV-Tools/install/lib/cmake/SPIRV-Tools \
         -DSPIRV-Headers_DIR=$SCRIPT_DIR/dependencies/SPIRV-Headers/install/share/cmake/SPIRV-Headers"
else
    echo "✓ glslang already built"
fi

# 4. Build SPIRV-Cross
echo "Step 4/6: SPIRV-Cross"
if [ ! -f "$SCRIPT_DIR/dependencies/SPIRV-Cross/install/lib/libspirv-cross-core.a" ]; then
    build_component "SPIRV-Cross" \
        "$SCRIPT_DIR/dependencies/SPIRV-Cross" \
        "$SCRIPT_DIR/dependencies/SPIRV-Cross/build" \
        "-DCMAKE_INSTALL_PREFIX=$SCRIPT_DIR/dependencies/SPIRV-Cross/install"
else
    echo "✓ SPIRV-Cross already built"
fi

# 5. Build scenario-runner
echo "Step 5/6: scenario-runner"
build_component "scenario-runner" \
    "$SCRIPT_DIR/sw/scenario-runner" \
    "$SCRIPT_DIR/sw/scenario-runner/build" \
    "-DSPIRV_HEADERS_PATH=$SCRIPT_DIR/dependencies/SPIRV-Headers \
     -DSPIRV_TOOLS_PATH=$SCRIPT_DIR/dependencies/SPIRV-Tools \
     -DVULKAN_HEADERS_PATH=$SCRIPT_DIR/dependencies/Vulkan-Headers/include \
     -DGLSLANG_PATH=$SCRIPT_DIR/dependencies/glslang"

# 6. Try to build emulation-layer (may fail due to SPIRV-Tools issues)
echo "Step 6/7: emulation-layer (optional)"
echo "Note: This may fail due to SPIRV-Tools compatibility issues"
build_component "emulation-layer" \
    "$SCRIPT_DIR/sw/emulation-layer" \
    "$SCRIPT_DIR/sw/emulation-layer/build" \
    "-DVulkanHeaders_DIR=$SCRIPT_DIR/dependencies/Vulkan-Headers/install/share/cmake/VulkanHeaders \
     -DSPIRV-Headers_DIR=$SCRIPT_DIR/dependencies/SPIRV-Headers/install/share/cmake/SPIRV-Headers \
     -DSPIRV_TOOLS_PATH=$SCRIPT_DIR/dependencies/SPIRV-Tools \
     -Dspirv_cross_core_DIR=$SCRIPT_DIR/dependencies/SPIRV-Cross/install/share/spirv_cross_core/cmake \
     -Dspirv_cross_glsl_DIR=$SCRIPT_DIR/dependencies/SPIRV-Cross/install/share/spirv_cross_glsl/cmake \
     -Dspirv_cross_reflect_DIR=$SCRIPT_DIR/dependencies/SPIRV-Cross/install/share/spirv_cross_reflect/cmake \
     -DGLSLANG_PATH=$SCRIPT_DIR/dependencies/glslang" || echo "⚠️  Emulation layer build failed (expected)"

# 7. Build model-converter (optional - builds LLVM, very slow)
echo "Step 7/7: model-converter (optional - very slow)"
echo "Note: This builds LLVM and takes a long time"
if command -v ninja &> /dev/null; then
    BUILD_CMD="ninja"
else
    BUILD_CMD="make"
fi

mkdir -p "$SCRIPT_DIR/sw/model-converter/build"
cd "$SCRIPT_DIR/sw/model-converter/build"
cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE
echo "Building with $BUILD_CMD (this will take a while)..."
$BUILD_CMD -j2 || echo "⚠️  Model converter build incomplete (LLVM build is very slow)"

echo ""
echo "=== Build Summary ==="
echo "✓ Dependencies built successfully"
echo "✓ scenario-runner built successfully"
echo ""
echo "To run scenario-runner:"
echo "  cd $SCRIPT_DIR/sw/scenario-runner/build"
echo "  DYLD_LIBRARY_PATH=/usr/local/lib ./scenario-runner --version"
echo ""
echo "Note: ARM ML extension functions require the emulation layer which may not have built successfully."
echo "Non-ML Vulkan scenarios should work fine."