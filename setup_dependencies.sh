#!/bin/bash

# Setup and build dependencies for ML SDK on macOS

set -e

REPO_DIR="/Users/jerry/Vulkan"
DEPS_DIR="${REPO_DIR}/dependencies"

echo "=== Setting up ML SDK Dependencies for macOS ARM64 ==="
echo ""

# Create dependencies directory
mkdir -p "${DEPS_DIR}"

# Function to clone or update a repository
clone_or_update() {
    local name=$1
    local url=$2
    local branch=$3
    local dir="${DEPS_DIR}/${name}"
    
    if [ -d "${dir}" ]; then
        echo "Updating ${name}..."
        cd "${dir}"
        git fetch origin
        git checkout "${branch}"
        git pull origin "${branch}"
        cd -
    else
        echo "Cloning ${name}..."
        git clone --depth 1 --branch "${branch}" "${url}" "${dir}"
    fi
}

# Clone dependencies according to manifest
echo "Cloning Vulkan and SPIR-V dependencies..."

# Dependencies for emulation layer
clone_or_update "glslang" "https://github.com/KhronosGroup/glslang.git" "main"
clone_or_update "SPIRV-Cross" "https://github.com/KhronosGroup/SPIRV-Cross.git" "main"
clone_or_update "SPIRV-Headers" "https://github.com/arm/SPIRV-Headers.git" "staging"
clone_or_update "SPIRV-Tools" "https://github.com/arm/SPIRV-Tools.git" "staging"
clone_or_update "Vulkan-Headers" "https://github.com/KhronosGroup/Vulkan-Headers.git" "main"

# Common dependencies
clone_or_update "googletest" "https://github.com/google/googletest.git" "v1.17.0"
clone_or_update "argparse" "https://github.com/p-ranav/argparse.git" "v3.1"
clone_or_update "flatbuffers" "https://github.com/google/flatbuffers.git" "v23.5.26"
clone_or_update "json" "https://github.com/nlohmann/json.git" "v3.11.3"
clone_or_update "pybind11" "https://github.com/pybind/pybind11.git" "v2.13.6"

echo ""
echo "Building SPIRV-Tools first..."
cd "${DEPS_DIR}/SPIRV-Tools"
if [ ! -d "build" ]; then
    cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64 \
        -DSPIRV-Headers_SOURCE_DIR="${DEPS_DIR}/SPIRV-Headers"
    cmake --build build -j $(sysctl -n hw.ncpu)
fi

echo ""
echo "Building glslang..."
cd "${DEPS_DIR}/glslang"
# Update glslang sources first to get SPIRV-Tools
if [ -f "update_glslang_sources.py" ]; then
    python3 update_glslang_sources.py || true
fi
if [ ! -d "build" ]; then
    cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64 \
        -DENABLE_OPT=OFF \
        -DALLOW_EXTERNAL_SPIRV_TOOLS=ON \
        -DSPIRV_TOOLS_DIR="${DEPS_DIR}/SPIRV-Tools"
    cmake --build build -j $(sysctl -n hw.ncpu)
fi

echo ""
echo "Building SPIRV-Cross..."
cd "${DEPS_DIR}/SPIRV-Cross"
if [ ! -d "build" ]; then
    cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64
    cmake --build build -j $(sysctl -n hw.ncpu)
fi

echo ""
echo "Installing Vulkan-Headers..."
cd "${DEPS_DIR}/Vulkan-Headers"
if [ ! -d "build" ]; then
    cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64
    cmake --build build
    cmake --install build --prefix "${DEPS_DIR}/Vulkan-Headers/install"
fi

echo ""
echo "Building googletest..."
cd "${DEPS_DIR}/googletest"
if [ ! -d "build" ]; then
    cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64
    cmake --build build -j $(sysctl -n hw.ncpu)
fi

echo ""
echo "=== Dependencies Setup Complete ==="