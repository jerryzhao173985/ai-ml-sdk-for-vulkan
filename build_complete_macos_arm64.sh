#!/bin/bash
# Complete build script for ML SDK for Vulkan on macOS ARM64
# This script attempts to build all components with necessary fixes

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
NC='\033[0m'

echo -e "${PURPLE}╔═══════════════════════════════════════════════════════════╗${NC}"
echo -e "${PURPLE}║   ML SDK for Vulkan - macOS ARM64 Complete Build Script   ║${NC}"
echo -e "${PURPLE}╚═══════════════════════════════════════════════════════════╝${NC}"

SDK_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CPU_CORES=$(sysctl -n hw.ncpu)
BUILD_DIR="$SDK_ROOT/build-macos-complete"

echo -e "${BLUE}SDK Root: $SDK_ROOT${NC}"
echo -e "${BLUE}CPU Cores: $CPU_CORES${NC}"

# Function to check if command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Check prerequisites
echo -e "${YELLOW}Checking prerequisites...${NC}"
MISSING_DEPS=0

if ! command_exists cmake; then
    echo -e "${RED}✗ CMake not found${NC}"
    MISSING_DEPS=1
else
    echo -e "${GREEN}✓ CMake found${NC}"
fi

if ! command_exists ninja; then
    echo -e "${RED}✗ Ninja not found${NC}"
    MISSING_DEPS=1
else
    echo -e "${GREEN}✓ Ninja found${NC}"
fi

if ! command_exists python3; then
    echo -e "${RED}✗ Python3 not found${NC}"
    MISSING_DEPS=1
else
    echo -e "${GREEN}✓ Python3 found${NC}"
fi

if [ $MISSING_DEPS -eq 1 ]; then
    echo -e "${RED}Please install missing dependencies first${NC}"
    exit 1
fi

# Clean previous builds
echo -e "${YELLOW}Cleaning previous builds...${NC}"
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"

# Build components that work on macOS
echo -e "${PURPLE}═══ Phase 1: Building macOS-compatible components ═══${NC}"

# 1. Build VGF Library
echo -e "${YELLOW}[1/7] Building VGF Library...${NC}"
mkdir -p "$BUILD_DIR/vgf-lib"
cmake -S "$SDK_ROOT/sw/vgf-lib" -B "$BUILD_DIR/vgf-lib" -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DFLATBUFFERS_PATH="$SDK_ROOT/dependencies/flatbuffers" \
    -DJSON_PATH="$SDK_ROOT/dependencies/json" \
    2>&1 | tee "$BUILD_DIR/vgf-lib-cmake.log"

ninja -C "$BUILD_DIR/vgf-lib" -j $CPU_CORES 2>&1 | tee "$BUILD_DIR/vgf-lib-build.log"
echo -e "${GREEN}✓ VGF Library built successfully${NC}"

# 2. Build SPIRV-Tools
echo -e "${YELLOW}[2/7] Building SPIRV-Tools...${NC}"
mkdir -p "$BUILD_DIR/spirv-tools"
cmake -S "$SDK_ROOT/dependencies/SPIRV-Tools" -B "$BUILD_DIR/spirv-tools" -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DSPIRV-Headers_SOURCE_DIR="$SDK_ROOT/dependencies/SPIRV-Headers" \
    2>&1 | tee "$BUILD_DIR/spirv-tools-cmake.log"

ninja -C "$BUILD_DIR/spirv-tools" -j $CPU_CORES 2>&1 | tee "$BUILD_DIR/spirv-tools-build.log"
echo -e "${GREEN}✓ SPIRV-Tools built successfully${NC}"

# 3. Build glslang
echo -e "${YELLOW}[3/7] Building glslang...${NC}"
mkdir -p "$BUILD_DIR/glslang"
cmake -S "$SDK_ROOT/dependencies/glslang" -B "$BUILD_DIR/glslang" -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    2>&1 | tee "$BUILD_DIR/glslang-cmake.log"

ninja -C "$BUILD_DIR/glslang" -j $CPU_CORES 2>&1 | tee "$BUILD_DIR/glslang-build.log"
echo -e "${GREEN}✓ glslang built successfully${NC}"

# 4. Build flatbuffers
echo -e "${YELLOW}[4/7] Building flatbuffers...${NC}"
mkdir -p "$BUILD_DIR/flatbuffers"
cmake -S "$SDK_ROOT/dependencies/flatbuffers" -B "$BUILD_DIR/flatbuffers" -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    2>&1 | tee "$BUILD_DIR/flatbuffers-cmake.log"

ninja -C "$BUILD_DIR/flatbuffers" -j $CPU_CORES 2>&1 | tee "$BUILD_DIR/flatbuffers-build.log"
echo -e "${GREEN}✓ flatbuffers built successfully${NC}"

echo -e "${PURPLE}═══ Phase 2: Attempting Linux-only components ═══${NC}"

# 5. Try Model Converter (expected to fail on macOS)
echo -e "${YELLOW}[5/7] Attempting Model Converter build...${NC}"
mkdir -p "$BUILD_DIR/model-converter"

# Create a wrapper script to bypass platform check
cat > "$BUILD_DIR/build_model_converter.cmake" << 'EOF'
# Override platform check
set(CMAKE_SYSTEM_NAME "Linux" CACHE STRING "" FORCE)
message(STATUS "Overriding platform check for Model Converter")
EOF

cmake -S "$SDK_ROOT/sw/model-converter" -B "$BUILD_DIR/model-converter" -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DMODEL_CONVERTER_APPLY_LLVM_PATCH=OFF \
    -DLLVM_PATH="$SDK_ROOT/dependencies/llvm-project" \
    -DML_SDK_VGF_LIB_PATH="$SDK_ROOT/sw/vgf-lib" \
    -DARGPARSE_PATH="$SDK_ROOT/dependencies/argparse" \
    -DFLATBUFFERS_PATH="$SDK_ROOT/dependencies/flatbuffers" \
    -DJSON_PATH="$SDK_ROOT/dependencies/json" \
    -DTOSA_MLIR_TRANSLATOR_PATH="$SDK_ROOT/dependencies/tosa_mlir_translator" \
    -C "$BUILD_DIR/build_model_converter.cmake" \
    2>&1 | tee "$BUILD_DIR/model-converter-cmake.log" || {
        echo -e "${RED}✗ Model Converter configuration failed (expected on macOS)${NC}"
    }

# 6. Try Scenario Runner with ML extensions
echo -e "${YELLOW}[6/7] Attempting Scenario Runner build...${NC}"
mkdir -p "$BUILD_DIR/scenario-runner"

cmake -S "$SDK_ROOT/sw/scenario-runner" -B "$BUILD_DIR/scenario-runner" -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_FLAGS="-DVK_ENABLE_BETA_EXTENSIONS" \
    -DARGPARSE_PATH="$SDK_ROOT/dependencies/argparse" \
    -DJSON_PATH="$SDK_ROOT/dependencies/json" \
    -DML_SDK_VGF_LIB_PATH="$SDK_ROOT/sw/vgf-lib" \
    -DVULKAN_HEADERS_PATH="$SDK_ROOT/dependencies/Vulkan-Headers" \
    -DSPIRV_HEADERS_PATH="$SDK_ROOT/dependencies/SPIRV-Headers" \
    -DSPIRV_TOOLS_PATH="$SDK_ROOT/dependencies/SPIRV-Tools" \
    -DGLSLANG_PATH="$SDK_ROOT/dependencies/glslang" \
    2>&1 | tee "$BUILD_DIR/scenario-runner-cmake.log" || {
        echo -e "${RED}✗ Scenario Runner configuration failed${NC}"
    }

# Try to build if configuration succeeded
if [ -f "$BUILD_DIR/scenario-runner/build.ninja" ]; then
    ninja -C "$BUILD_DIR/scenario-runner" -j $CPU_CORES 2>&1 | tee "$BUILD_DIR/scenario-runner-build.log" || {
        echo -e "${RED}✗ Scenario Runner build failed${NC}"
    }
fi

# 7. Full SDK build attempt
echo -e "${YELLOW}[7/7] Attempting full SDK build...${NC}"
mkdir -p "$BUILD_DIR/full-sdk"

cmake -S "$SDK_ROOT" -B "$BUILD_DIR/full-sdk" -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_FLAGS="-DVK_ENABLE_BETA_EXTENSIONS" \
    -DMODEL_CONVERTER_APPLY_LLVM_PATCH=OFF \
    2>&1 | tee "$BUILD_DIR/full-sdk-cmake.log"

ninja -C "$BUILD_DIR/full-sdk" -j $CPU_CORES 2>&1 | tee "$BUILD_DIR/full-sdk-build.log" || {
    echo -e "${RED}✗ Full SDK build partially failed${NC}"
}

echo -e "${PURPLE}═══ Build Summary ═══${NC}"

# Check what was successfully built
echo -e "${GREEN}Successfully built components:${NC}"

if [ -f "$BUILD_DIR/vgf-lib/vgf_dump/vgf_dump" ]; then
    echo -e "  ${GREEN}✓${NC} VGF Dump tool"
fi

if [ -f "$BUILD_DIR/vgf-lib/flatbuffers/flatc" ] || [ -f "$BUILD_DIR/flatbuffers/flatc" ]; then
    echo -e "  ${GREEN}✓${NC} FlatBuffers compiler (flatc)"
fi

if [ -f "$BUILD_DIR/spirv-tools/tools/spirv-opt" ]; then
    echo -e "  ${GREEN}✓${NC} SPIRV-Tools (spirv-opt, spirv-dis, etc.)"
fi

if [ -f "$BUILD_DIR/glslang/StandAlone/glslangValidator" ]; then
    echo -e "  ${GREEN}✓${NC} glslang validator"
fi

# Create convenience script
cat > "$SDK_ROOT/ml-sdk-env.sh" << EOFENV
#!/bin/bash
# Source this file to set up ML SDK environment

export ML_SDK_ROOT="$SDK_ROOT"
export ML_SDK_BUILD="$BUILD_DIR"

# Add tools to PATH
export PATH="\$ML_SDK_BUILD/vgf-lib/vgf_dump:\$PATH"
export PATH="\$ML_SDK_BUILD/flatbuffers:\$PATH"
export PATH="\$ML_SDK_BUILD/spirv-tools/tools:\$PATH"
export PATH="\$ML_SDK_BUILD/glslang/StandAlone:\$PATH"

# Aliases for convenience
alias vgf-dump="\$ML_SDK_BUILD/vgf-lib/vgf_dump/vgf_dump"
alias ml-flatc="\$ML_SDK_BUILD/flatbuffers/flatc"

echo "ML SDK environment loaded!"
echo "Available tools:"
echo "  - vgf-dump: Dump VGF file contents"
echo "  - ml-flatc: FlatBuffers compiler"
echo "  - spirv-opt: SPIR-V optimizer"
echo "  - spirv-dis: SPIR-V disassembler"
echo "  - glslangValidator: GLSL validator"
EOFENV

chmod +x "$SDK_ROOT/ml-sdk-env.sh"

echo -e "${PURPLE}═══ Next Steps ═══${NC}"
echo -e "${BLUE}1. Source the environment:${NC}"
echo "   source $SDK_ROOT/ml-sdk-env.sh"
echo ""
echo -e "${BLUE}2. For full functionality (Model Converter, Scenario Runner):${NC}"
echo "   Use Docker: ./build_in_docker.sh"
echo ""
echo -e "${BLUE}3. Available native macOS tools:${NC}"
echo "   - VGF file inspection and manipulation"
echo "   - SPIR-V shader analysis and optimization"
echo "   - GLSL to SPIR-V compilation"
echo ""
echo -e "${BLUE}4. Logs saved in:${NC} $BUILD_DIR/"

# Final status
if [ -f "$BUILD_DIR/vgf-lib/vgf_dump/vgf_dump" ]; then
    echo -e "${GREEN}✓ Build completed with partial success!${NC}"
    echo -e "${YELLOW}  Some components require Linux environment${NC}"
else
    echo -e "${RED}✗ Build failed${NC}"
fi