#!/bin/bash
# Build script for ML SDK for Vulkan on macOS ARM64

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${GREEN}=== ML SDK for Vulkan macOS ARM64 Build Script ===${NC}"
echo -e "${GREEN}=== Building all components for native macOS ===${NC}"

# Get absolute paths
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SDK_ROOT="$SCRIPT_DIR"
VULKAN_ROOT="$(dirname "$SDK_ROOT")"

# Number of CPU cores
CPU_CORES=$(sysctl -n hw.ncpu)
echo -e "${BLUE}Using $CPU_CORES CPU cores for compilation${NC}"

# Check if separate component repos exist
echo -e "${YELLOW}Checking for separate component repositories...${NC}"

COMPONENTS=(
    "ai-ml-sdk-model-converter"
    "ai-ml-sdk-scenario-runner"
)

for component in "${COMPONENTS[@]}"; do
    if [ -d "$VULKAN_ROOT/$component" ]; then
        echo -e "${GREEN}✓ Found: $component${NC}"
    else
        echo -e "${RED}✗ Missing: $component${NC}"
    fi
done

# Build VGF Library first (it builds on macOS)
echo -e "${YELLOW}Building VGF Library...${NC}"
cd "$SDK_ROOT"
mkdir -p build-macos-vgf
cmake -S sw/vgf-lib -B build-macos-vgf -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DFLATBUFFERS_PATH="$SDK_ROOT/dependencies/flatbuffers" \
    -DJSON_PATH="$SDK_ROOT/dependencies/json"

ninja -C build-macos-vgf -j $CPU_CORES

echo -e "${GREEN}✓ VGF Library built successfully${NC}"

# Build SPIRV-Tools with official version
echo -e "${YELLOW}Building SPIRV-Tools...${NC}"
cd "$SDK_ROOT/dependencies/SPIRV-Tools"
mkdir -p build-macos
cmake -S . -B build-macos -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DSPIRV-Headers_SOURCE_DIR="$SDK_ROOT/dependencies/SPIRV-Headers"

ninja -C build-macos -j $CPU_CORES

echo -e "${GREEN}✓ SPIRV-Tools built successfully${NC}"

# Build glslang
echo -e "${YELLOW}Building glslang...${NC}"
cd "$SDK_ROOT/dependencies/glslang"
mkdir -p build-macos
cmake -S . -B build-macos -G Ninja \
    -DCMAKE_BUILD_TYPE=Release

ninja -C build-macos -j $CPU_CORES

echo -e "${GREEN}✓ glslang built successfully${NC}"

# Attempt to build Model Converter with patches
echo -e "${YELLOW}Attempting Model Converter build...${NC}"
if [ -d "$VULKAN_ROOT/ai-ml-sdk-model-converter" ]; then
    echo -e "${BLUE}Creating patched build script for Model Converter...${NC}"
    
    # Create a modified build script that works on macOS
    cat > "$SDK_ROOT/build_model_converter_macos.cmake" << 'EOF'
# Override platform check for macOS
set(CMAKE_SYSTEM_NAME "Linux" CACHE STRING "" FORCE)
set(CMAKE_SYSTEM_PROCESSOR "aarch64" CACHE STRING "" FORCE)

# Include the original CMakeLists
include(${CMAKE_CURRENT_LIST_DIR}/sw/model-converter/CMakeLists.txt)
EOF

    # Try building with overrides
    mkdir -p build-macos-modelconv
    cmake -S . -B build-macos-modelconv -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DMODEL_CONVERTER_APPLY_LLVM_PATCH=OFF \
        -DLLVM_PATH="$SDK_ROOT/dependencies/llvm-project" \
        -DVGF_LIB_PATH="$SDK_ROOT/sw/vgf-lib" \
        -DARGPARSE_PATH="$SDK_ROOT/dependencies/argparse" \
        -DFLATBUFFERS_PATH="$SDK_ROOT/dependencies/flatbuffers" \
        -DJSON_PATH="$SDK_ROOT/dependencies/json" \
        -DTOSA_MLIR_TRANSLATOR_PATH="$SDK_ROOT/dependencies/tosa_mlir_translator" \
        -C build_model_converter_macos.cmake || {
            echo -e "${RED}✗ Model Converter build failed (expected on macOS)${NC}"
        }
else
    echo -e "${RED}✗ Model Converter repo not found${NC}"
fi

# Summary
echo -e "${GREEN}=== Build Summary ===${NC}"
echo -e "${GREEN}Successfully built on macOS:${NC}"
echo "  - VGF Library (for reading/writing VGF files)"
echo "  - SPIRV-Tools (for SPIR-V manipulation)"
echo "  - glslang (for GLSL to SPIR-V compilation)"

echo -e "${YELLOW}Components requiring Linux:${NC}"
echo "  - Model Converter (TOSA to VGF conversion)"
echo "  - Scenario Runner (executing ML workloads)"
echo "  - Emulation Layer (ML API implementation)"

echo -e "${BLUE}Available tools:${NC}"
echo "  - VGF Dump: $SDK_ROOT/build-macos-vgf/vgf_dump/vgf_dump"
echo "  - flatc: $SDK_ROOT/build-macos-vgf/flatbuffers/flatc"
echo "  - spirv-opt: $SDK_ROOT/dependencies/SPIRV-Tools/build-macos/tools/spirv-opt"
echo "  - glslangValidator: $SDK_ROOT/dependencies/glslang/build-macos/StandAlone/glslangValidator"

echo -e "${YELLOW}Next steps:${NC}"
echo "1. Use Docker for full functionality: ./build_in_docker.sh"
echo "2. Or use VGF tools to inspect/manipulate VGF files on macOS"
echo "3. Convert models using Docker, then inspect locally"

# Create helper script for VGF operations
cat > "$SDK_ROOT/vgf_tools.sh" << 'EOFSCRIPT'
#!/bin/bash
# Helper script for VGF operations on macOS

SDK_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# VGF Dump
alias vgf-dump="$SDK_ROOT/build-macos-vgf/vgf_dump/vgf_dump"

# flatc
alias vgf-flatc="$SDK_ROOT/build-macos-vgf/flatbuffers/flatc"

echo "VGF Tools loaded. Available commands:"
echo "  vgf-dump <file.vgf>    - Dump VGF file contents"
echo "  vgf-flatc              - FlatBuffers compiler"
EOFSCRIPT

chmod +x "$SDK_ROOT/vgf_tools.sh"

echo -e "${GREEN}Created vgf_tools.sh - source it to use VGF tools${NC}"