# macOS Development Guide for ML SDK for Vulkan

## Overview

The ML SDK for Vulkan is primarily designed for Linux and Windows platforms. This guide provides solutions for macOS developers who want to work with this SDK.

## Current Limitations on macOS

1. **Build System**: The build scripts explicitly check for platform and reject Darwin (macOS)
2. **ML Extensions**: Vulkan C++ headers don't properly expose ARM ML extensions on macOS
3. **Dependencies**: Some dependencies (like ARM's SPIRV-Tools fork) have incomplete implementations

## Working Components on macOS

The following components can be built and used natively on macOS:

### 1. VGF Library
- Purpose: Read/write VGF (Vulkan Graph Format) container files
- Status: ✅ Builds successfully
- Use case: Inspect and manipulate VGF files without running them

### 2. SPIRV-Tools (Official Khronos Version)
- Purpose: SPIR-V manipulation and optimization
- Status: ✅ Builds successfully with official repo
- Use case: Analyze and transform SPIR-V shaders

### 3. glslang
- Purpose: GLSL to SPIR-V compilation
- Status: ✅ Builds successfully
- Use case: Compile GLSL shaders to SPIR-V

## Recommended Development Approaches

### Option 1: Docker-based Development (Recommended)

Use the provided Docker container for full SDK functionality:

```bash
# Build and run using the provided script
./build_in_docker.sh

# Or manually:
docker build -t ml-sdk-vulkan-builder -f docker/Dockerfile docker/
docker run --rm -it -v "$(pwd):/workspace" -w /workspace ml-sdk-vulkan-builder
```

Inside the container:
```bash
./scripts/build.py --threads $(nproc) --build-type Release
```

### Option 2: Virtual Machine

Install Ubuntu 22.04 in a VM (VMware Fusion, Parallels, or UTM) and develop there.

### Option 3: Remote Development

Use VS Code Remote Development or similar tools to develop on a Linux machine while working from macOS.

## Native macOS Partial Build

For components that do work on macOS:

```bash
# Setup
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt

# Configure (partial build)
cmake -S . -B build-macos -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_FLAGS="-DVK_ENABLE_BETA_EXTENSIONS"

# Build (will partially succeed)
ninja -C build-macos -j $(sysctl -n hw.ncpu)
```

## Using VGF Tools on macOS

After building, you can use:

```bash
# Dump VGF file contents
./build-macos/vgf-lib/vgf_dump/vgf_dump <path_to_vgf_file>

# Use flatc for FlatBuffers operations
./build-macos/vgf-lib/flatbuffers/flatc
```

## Python Development

The Python tools for model conversion can be partially used:

```python
import vgf_utils
# Use VGF utilities for file inspection and manipulation
```

## Troubleshooting

### Issue: "Unsupported host platform Darwin"
**Solution**: Use Docker or modify build scripts (not recommended)

### Issue: Missing vk::TensorARM types
**Solution**: The Vulkan ML extensions require proper header generation. Use Linux environment.

### Issue: SPIRV-Tools ML extensions missing
**Solution**: Use the official Khronos SPIRV-Tools for basic functionality

## Example Workflow

1. **Develop models on macOS** using PyTorch/TensorFlow
2. **Convert models in Docker** container
3. **Inspect VGF files** using native macOS tools
4. **Test on target platform** (Linux/Android device)

## Quick Docker Commands

```bash
# Interactive development
docker run --rm -it -v "$(pwd):/workspace" -w /workspace ml-sdk-vulkan-builder bash

# Build specific component
docker run --rm -v "$(pwd):/workspace" -w /workspace ml-sdk-vulkan-builder \
  ./sw/model-converter/scripts/build.py

# Run model converter
docker run --rm -v "$(pwd):/workspace" -w /workspace ml-sdk-vulkan-builder \
  ./build/sw/model-converter/model-converter --help
```

## Contributing

When contributing to the SDK from macOS:
1. Develop and test in Docker/Linux environment
2. Ensure changes work on officially supported platforms
3. Don't add macOS-specific code without discussion