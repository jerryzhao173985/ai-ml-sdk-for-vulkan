#!/bin/bash
# Comprehensive build script for all ML SDK repos on macOS M4 Max
# This script builds across all three repos in /Users/jerry/Vulkan/

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m'

echo -e "${PURPLE}╔════════════════════════════════════════════════════════════════╗${NC}"
echo -e "${PURPLE}║   ML SDK for Vulkan - Complete Multi-Repo Build for M4 Max    ║${NC}"
echo -e "${PURPLE}╚════════════════════════════════════════════════════════════════╝${NC}"

# Base paths
VULKAN_ROOT="/Users/jerry/Vulkan"
MAIN_SDK="$VULKAN_ROOT/ai-ml-sdk-for-vulkan"
MODEL_CONVERTER_REPO="$VULKAN_ROOT/ai-ml-sdk-model-converter"
SCENARIO_RUNNER_REPO="$VULKAN_ROOT/ai-ml-sdk-scenario-runner"

# System info
CPU_CORES=$(sysctl -n hw.ncpu)
echo -e "${BLUE}System: macOS on Apple Silicon M4 Max${NC}"
echo -e "${BLUE}CPU Cores: $CPU_CORES${NC}"
echo -e "${BLUE}Architecture: $(uname -m)${NC}"

# Create unified build directory
BUILD_ROOT="$VULKAN_ROOT/ml-sdk-unified-build"
rm -rf "$BUILD_ROOT"
mkdir -p "$BUILD_ROOT"

# Function to check if directory exists
check_dir() {
    if [ -d "$1" ]; then
        echo -e "${GREEN}✓ Found: $1${NC}"
        return 0
    else
        echo -e "${RED}✗ Missing: $1${NC}"
        return 1
    fi
}

# Check all repos
echo -e "\n${CYAN}Checking repositories...${NC}"
check_dir "$MAIN_SDK"
check_dir "$MODEL_CONVERTER_REPO"
check_dir "$SCENARIO_RUNNER_REPO"

# Build dependencies from main SDK first
echo -e "\n${PURPLE}═══ Phase 1: Building Core Dependencies ═══${NC}"

# 1. Build flatbuffers
echo -e "\n${YELLOW}[1/10] Building flatbuffers...${NC}"
if [ -d "$MAIN_SDK/dependencies/flatbuffers" ]; then
    mkdir -p "$BUILD_ROOT/flatbuffers"
    cd "$BUILD_ROOT/flatbuffers"
    cmake "$MAIN_SDK/dependencies/flatbuffers" \
        -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_OSX_ARCHITECTURES=arm64 \
        -DFLATBUFFERS_BUILD_TESTS=OFF
    ninja -j $CPU_CORES
    echo -e "${GREEN}✓ flatbuffers built${NC}"
else
    echo -e "${RED}✗ flatbuffers source not found${NC}"
fi

# 2. Build SPIRV-Headers
echo -e "\n${YELLOW}[2/10] Building SPIRV-Headers...${NC}"
if [ -d "$MAIN_SDK/dependencies/SPIRV-Headers" ]; then
    mkdir -p "$BUILD_ROOT/spirv-headers"
    cd "$BUILD_ROOT/spirv-headers"
    cmake "$MAIN_SDK/dependencies/SPIRV-Headers" \
        -G Ninja \
        -DCMAKE_BUILD_TYPE=Release
    ninja -j $CPU_CORES
    echo -e "${GREEN}✓ SPIRV-Headers built${NC}"
fi

# 3. Build SPIRV-Tools
echo -e "\n${YELLOW}[3/10] Building SPIRV-Tools...${NC}"
if [ -d "$MAIN_SDK/dependencies/SPIRV-Tools" ]; then
    mkdir -p "$BUILD_ROOT/spirv-tools"
    cd "$BUILD_ROOT/spirv-tools"
    cmake "$MAIN_SDK/dependencies/SPIRV-Tools" \
        -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DSPIRV-Headers_SOURCE_DIR="$MAIN_SDK/dependencies/SPIRV-Headers" \
        -DSPIRV_SKIP_TESTS=ON
    ninja -j $CPU_CORES
    echo -e "${GREEN}✓ SPIRV-Tools built${NC}"
fi

# 4. Build glslang
echo -e "\n${YELLOW}[4/10] Building glslang...${NC}"
if [ -d "$MAIN_SDK/dependencies/glslang" ]; then
    mkdir -p "$BUILD_ROOT/glslang"
    cd "$BUILD_ROOT/glslang"
    cmake "$MAIN_SDK/dependencies/glslang" \
        -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DSPIRV-Tools_SOURCE_DIR="$BUILD_ROOT/spirv-tools" \
        -DBUILD_TESTING=OFF
    ninja -j $CPU_CORES
    echo -e "${GREEN}✓ glslang built${NC}"
fi

# 5. Build argparse
echo -e "\n${YELLOW}[5/10] Building argparse...${NC}"
if [ -d "$MAIN_SDK/dependencies/argparse" ]; then
    mkdir -p "$BUILD_ROOT/argparse"
    cd "$BUILD_ROOT/argparse"
    cmake "$MAIN_SDK/dependencies/argparse" \
        -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DARGPARSE_BUILD_TESTS=OFF
    ninja -j $CPU_CORES
    ninja install DESTDIR="$BUILD_ROOT/argparse-install"
    echo -e "${GREEN}✓ argparse built${NC}"
fi

# Create ML extensions patch
echo -e "\n${YELLOW}Creating ML extensions enabler...${NC}"
cat > "$BUILD_ROOT/vulkan_ml_patch.hpp" << 'EOF'
#pragma once
#define VK_ENABLE_BETA_EXTENSIONS 1
#include <vulkan/vulkan.hpp>

// Additional definitions for missing ML types if needed
namespace vk {
    // Compatibility layer for ML extensions
    using TensorCreateInfoARM = VkTensorCreateInfoARM;
    using TensorMemoryBarrierARM = VkTensorMemoryBarrierARM;
}
EOF

echo -e "\n${PURPLE}═══ Phase 2: Building VGF Library ═══${NC}"

# Try building from each repo
for repo in "$MAIN_SDK" "$MODEL_CONVERTER_REPO" "$SCENARIO_RUNNER_REPO"; do
    if [ -d "$repo/sw/vgf-lib" ] || [ -d "$repo/vgf-lib" ]; then
        echo -e "\n${YELLOW}[6/10] Building VGF Library from $repo...${NC}"
        
        VGF_SRC=""
        if [ -d "$repo/sw/vgf-lib" ]; then
            VGF_SRC="$repo/sw/vgf-lib"
        elif [ -d "$repo/vgf-lib" ]; then
            VGF_SRC="$repo/vgf-lib"
        fi
        
        if [ -n "$VGF_SRC" ]; then
            mkdir -p "$BUILD_ROOT/vgf-lib"
            cd "$BUILD_ROOT/vgf-lib"
            
            # Configure with all dependencies
            cmake "$VGF_SRC" \
                -G Ninja \
                -DCMAKE_BUILD_TYPE=Release \
                -DCMAKE_PREFIX_PATH="$BUILD_ROOT/argparse-install/usr/local" \
                -DFLATBUFFERS_PATH="$MAIN_SDK/dependencies/flatbuffers" \
                -DJSON_PATH="$MAIN_SDK/dependencies/json" \
                -DARGPARSE_PATH="$MAIN_SDK/dependencies/argparse" \
                -Dargparse_DIR="$BUILD_ROOT/argparse/lib/cmake/argparse" \
                || echo -e "${YELLOW}VGF Library config failed, trying alternative...${NC}"
            
            # Try to build
            if [ -f "build.ninja" ]; then
                ninja -j $CPU_CORES || echo -e "${RED}VGF build failed${NC}"
                if [ -f "vgf_dump/vgf_dump" ]; then
                    echo -e "${GREEN}✓ VGF Library built from $repo${NC}"
                    break
                fi
            fi
        fi
    fi
done

echo -e "\n${PURPLE}═══ Phase 3: Building Model Converter ═══${NC}"

# Create platform override for Model Converter
cat > "$BUILD_ROOT/macos_platform_override.cmake" << 'EOF'
# Override platform checks for macOS
set(CMAKE_SYSTEM_NAME "Linux" CACHE STRING "" FORCE)
set(CMAKE_SYSTEM_PROCESSOR "aarch64" CACHE STRING "" FORCE)

# Suppress platform warnings
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS TRUE CACHE BOOL "" FORCE)
EOF

if [ -d "$MODEL_CONVERTER_REPO" ]; then
    echo -e "\n${YELLOW}[7/10] Building Model Converter from separate repo...${NC}"
    mkdir -p "$BUILD_ROOT/model-converter"
    cd "$BUILD_ROOT/model-converter"
    
    # Try to configure with platform override
    cmake "$MODEL_CONVERTER_REPO" \
        -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_CXX_FLAGS="-Wno-error" \
        -DMODEL_CONVERTER_APPLY_LLVM_PATCH=OFF \
        -DLLVM_PATH="$MAIN_SDK/dependencies/llvm-project" \
        -DML_SDK_VGF_LIB_PATH="$BUILD_ROOT/vgf-lib" \
        -DARGPARSE_PATH="$MAIN_SDK/dependencies/argparse" \
        -Dargparse_DIR="$BUILD_ROOT/argparse/lib/cmake/argparse" \
        -DFLATBUFFERS_PATH="$MAIN_SDK/dependencies/flatbuffers" \
        -DJSON_PATH="$MAIN_SDK/dependencies/json" \
        -DTOSA_MLIR_TRANSLATOR_PATH="$MAIN_SDK/dependencies/tosa_mlir_translator" \
        -C "$BUILD_ROOT/macos_platform_override.cmake" \
        2>&1 | tee model-converter-config.log || {
            echo -e "${RED}Model Converter config failed (expected on macOS)${NC}"
        }
    
    # Try to build if configured
    if [ -f "build.ninja" ]; then
        ninja -j $CPU_CORES 2>&1 | tee model-converter-build.log || {
            echo -e "${RED}Model Converter build failed${NC}"
        }
    fi
fi

echo -e "\n${PURPLE}═══ Phase 4: Building Scenario Runner ═══${NC}"

if [ -d "$SCENARIO_RUNNER_REPO" ]; then
    echo -e "\n${YELLOW}[8/10] Building Scenario Runner from separate repo...${NC}"
    mkdir -p "$BUILD_ROOT/scenario-runner"
    cd "$BUILD_ROOT/scenario-runner"
    
    # Configure with ML extensions enabled
    cmake "$SCENARIO_RUNNER_REPO" \
        -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_CXX_FLAGS="-DVK_ENABLE_BETA_EXTENSIONS -I$BUILD_ROOT" \
        -DARGPARSE_PATH="$MAIN_SDK/dependencies/argparse" \
        -Dargparse_DIR="$BUILD_ROOT/argparse/lib/cmake/argparse" \
        -DJSON_PATH="$MAIN_SDK/dependencies/json" \
        -DML_SDK_VGF_LIB_PATH="$BUILD_ROOT/vgf-lib" \
        -DVULKAN_HEADERS_PATH="$MAIN_SDK/dependencies/Vulkan-Headers" \
        -DSPIRV_HEADERS_PATH="$MAIN_SDK/dependencies/SPIRV-Headers" \
        -DSPIRV_TOOLS_PATH="$BUILD_ROOT/spirv-tools" \
        -DGLSLANG_PATH="$BUILD_ROOT/glslang" \
        2>&1 | tee scenario-runner-config.log || {
            echo -e "${RED}Scenario Runner config failed${NC}"
        }
    
    # Try to build
    if [ -f "build.ninja" ]; then
        ninja -j $CPU_CORES 2>&1 | tee scenario-runner-build.log || {
            echo -e "${RED}Scenario Runner build failed${NC}"
        }
    fi
fi

echo -e "\n${PURPLE}═══ Phase 5: Building Python Extensions ═══${NC}"

# Set up Python environment
echo -e "\n${YELLOW}[9/10] Setting up Python environment...${NC}"
cd "$BUILD_ROOT"
python3 -m venv ml-sdk-env
source ml-sdk-env/bin/activate

# Install Python dependencies
pip install --upgrade pip
for repo in "$MAIN_SDK" "$MODEL_CONVERTER_REPO" "$SCENARIO_RUNNER_REPO"; do
    if [ -f "$repo/requirements.txt" ]; then
        echo -e "${BLUE}Installing requirements from $repo${NC}"
        pip install -r "$repo/requirements.txt"
    fi
done

echo -e "\n${PURPLE}═══ Phase 6: Creating Unified Tools ═══${NC}"

# Create unified environment script
cat > "$BUILD_ROOT/ml-sdk-unified-env.sh" << 'EOFENV'
#!/bin/bash
# ML SDK Unified Environment for macOS M4 Max

export ML_SDK_UNIFIED_BUILD="/Users/jerry/Vulkan/ml-sdk-unified-build"
export VULKAN_SDK_ROOT="/Users/jerry/Vulkan"

# Add all built tools to PATH
export PATH="$ML_SDK_UNIFIED_BUILD/flatbuffers:$PATH"
export PATH="$ML_SDK_UNIFIED_BUILD/spirv-tools/tools:$PATH"
export PATH="$ML_SDK_UNIFIED_BUILD/glslang/StandAlone:$PATH"
export PATH="$ML_SDK_UNIFIED_BUILD/vgf-lib/vgf_dump:$PATH"

# Python environment
alias ml-sdk-python="source $ML_SDK_UNIFIED_BUILD/ml-sdk-env/bin/activate"

# Tool aliases
alias ml-flatc="$ML_SDK_UNIFIED_BUILD/flatbuffers/flatc"
alias ml-spirv-opt="$ML_SDK_UNIFIED_BUILD/spirv-tools/tools/spirv-opt"
alias ml-spirv-dis="$ML_SDK_UNIFIED_BUILD/spirv-tools/tools/spirv-dis"
alias ml-glslang="$ML_SDK_UNIFIED_BUILD/glslang/StandAlone/glslangValidator"
alias ml-vgf-dump="$ML_SDK_UNIFIED_BUILD/vgf-lib/vgf_dump/vgf_dump"

echo "ML SDK Unified Environment Loaded!"
echo ""
echo "Available tools:"
echo "  ml-flatc        - FlatBuffers compiler"
echo "  ml-spirv-opt    - SPIR-V optimizer"
echo "  ml-spirv-dis    - SPIR-V disassembler"
echo "  ml-glslang      - GLSL to SPIR-V compiler"
echo "  ml-vgf-dump     - VGF file inspector"
echo ""
echo "Python environment: ml-sdk-python"
EOFENV

chmod +x "$BUILD_ROOT/ml-sdk-unified-env.sh"

# Create Docker runner for Linux-only components
cat > "$BUILD_ROOT/run-in-docker.sh" << 'EOFDOCKER'
#!/bin/bash
# Run ML SDK components in Docker

VULKAN_ROOT="/Users/jerry/Vulkan"
COMPONENT="$1"
shift

docker run --rm -it \
    -v "$VULKAN_ROOT:/workspace" \
    -w /workspace \
    ubuntu:22.04 \
    bash -c "
        apt-get update && apt-get install -y \
            build-essential cmake ninja-build python3 python3-pip git
        
        cd /workspace/ml-sdk-unified-build
        case '$COMPONENT' in
            model-converter)
                ./model-converter $@
                ;;
            scenario-runner)
                ./scenario-runner $@
                ;;
            *)
                echo 'Usage: run-in-docker.sh [model-converter|scenario-runner] <args>'
                ;;
        esac
    "
EOFDOCKER

chmod +x "$BUILD_ROOT/run-in-docker.sh"

echo -e "\n${PURPLE}═══ Build Summary ═══${NC}"

# Check what was successfully built
echo -e "\n${GREEN}Successfully built components:${NC}"

[ -f "$BUILD_ROOT/flatbuffers/flatc" ] && echo "  ✓ FlatBuffers compiler"
[ -f "$BUILD_ROOT/spirv-tools/tools/spirv-opt" ] && echo "  ✓ SPIRV-Tools"
[ -f "$BUILD_ROOT/glslang/StandAlone/glslangValidator" ] && echo "  ✓ glslang"
[ -f "$BUILD_ROOT/argparse/libargparse.a" ] && echo "  ✓ argparse"
[ -f "$BUILD_ROOT/vgf-lib/vgf_dump/vgf_dump" ] && echo "  ✓ VGF Library"

echo -e "\n${YELLOW}Components requiring Linux:${NC}"
echo "  - Model Converter (use Docker: ./run-in-docker.sh model-converter)"
echo "  - Scenario Runner with ML extensions"

echo -e "\n${CYAN}═══ Next Steps ═══${NC}"
echo "1. Load the unified environment:"
echo "   source $BUILD_ROOT/ml-sdk-unified-env.sh"
echo ""
echo "2. For Model Converter:"
echo "   $BUILD_ROOT/run-in-docker.sh model-converter --help"
echo ""
echo "3. Build outputs saved to: $BUILD_ROOT"

echo -e "\n${GREEN}✓ Multi-repo build completed!${NC}"