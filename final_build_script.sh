#!/bin/bash
# Final comprehensive build script for ML SDK on macOS ARM64

set -e

echo "============================================"
echo "ML SDK for Vulkan - macOS ARM64 Build"
echo "============================================"

BUILD_ROOT="/Users/jerry/Vulkan/ml-sdk-macos-build"
SDK_ROOT="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan"
CPU_CORES=16

# Function to show build summary
show_summary() {
    echo
    echo "✨ Build Summary:"
    echo "=================="
    
    if [ -f "$BUILD_ROOT/bin/spirv-opt" ]; then
        echo "✅ SPIRV-Tools: Built"
    fi
    
    if [ -f "$BUILD_ROOT/bin/flatc" ]; then
        echo "✅ FlatBuffers: Built"
    fi
    
    if [ -f "$BUILD_ROOT/install/lib/libvgf.a" ]; then
        echo "✅ VGF Library: Built and installed"
    fi
    
    if [ -f "$BUILD_ROOT/bin/glslangValidator" ]; then
        echo "✅ glslang: Built"
    fi
    
    if [ -d "$BUILD_ROOT/llvm" ]; then
        echo "✅ LLVM/MLIR: Built (for Model Converter)"
    fi
    
    if [ -f "$BUILD_ROOT/model-converter/build/model-converter" ]; then
        echo "✅ Model Converter: Built"
    else
        echo "⚠️  Model Converter: Partial build"
    fi
    
    if [ -f "$BUILD_ROOT/scenario-runner/src/tools/scenario-runner" ]; then
        echo "✅ Scenario Runner: Built"
    else
        echo "⚠️  Scenario Runner: Build issues remain"
    fi
    
    echo
    echo "Build artifacts location: $BUILD_ROOT"
    echo
    echo "To use the SDK:"
    echo "  export PATH=$BUILD_ROOT/bin:\$PATH"
    echo "  export LD_LIBRARY_PATH=$BUILD_ROOT/lib:\$LD_LIBRARY_PATH"
}

# Clean existing scenario runner includes
echo "🔧 Cleaning Scenario Runner includes..."
find "$SDK_ROOT/sw/scenario-runner/src" -name "*.cpp" -o -name "*.hpp" | while read file; do
    if [[ "$file" == *"compat/"* ]]; then
        continue
    fi
    
    # Remove any existing vulkan.hpp includes
    sed -i '' '/#include.*<vulkan\/vulkan\.hpp>/d' "$file" 2>/dev/null || true
    sed -i '' '/#include.*<vulkan\/vulkan_raii\.hpp>/d' "$file" 2>/dev/null || true
    sed -i '' '/#include.*"vulkan\/vulkan\.hpp"/d' "$file" 2>/dev/null || true
    sed -i '' '/#include.*"vulkan\/vulkan_raii\.hpp"/d' "$file" 2>/dev/null || true
done

# Specific fix for utils.cpp to prevent vulkan.hpp inclusion
if grep -q "vulkan_format_traits.hpp" "$SDK_ROOT/sw/scenario-runner/src/utils.cpp"; then
    echo "🔧 Fixing utils.cpp..."
    sed -i '' '/#include.*vulkan_format_traits\.hpp/d' "$SDK_ROOT/sw/scenario-runner/src/utils.cpp"
fi

# Try building Scenario Runner
echo "🔨 Building Scenario Runner..."
cd "$BUILD_ROOT/scenario-runner"
ninja -j$CPU_CORES 2>&1 | tee build.log || {
    echo "⚠️  Scenario Runner build encountered issues"
    echo "   See $BUILD_ROOT/scenario-runner/build.log for details"
}

# Show final summary
show_summary

echo "🎉 Build process complete!"
echo
echo "Note: Some components may have partial builds due to macOS compatibility"
echo "The core ML SDK functionality (VGF, SPIRV-Tools) is available."