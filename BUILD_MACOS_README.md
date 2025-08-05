# ARM ML SDK for Vulkan - macOS ARM64 Build Guide

## Overview

This guide documents the successful build process for the ARM ML SDK for Vulkan on macOS ARM64 (Apple Silicon).

## Build Status

✅ **Successfully Built Components:**
- VGF Library
- Scenario Runner (with ARM extension stubs)
- SPIRV-Tools, SPIRV-Headers, glslang, SPIRV-Cross

⏳ **In Progress:**
- Model Converter (building LLVM - very slow)
- Emulation Layer (SPIRV-Tools compatibility issues)

## Prerequisites

1. **macOS ARM64** (tested on Mac M4 Max)
2. **Xcode Command Line Tools**
3. **CMake 3.25+**
4. **Python 3.10+**
5. **Vulkan SDK for macOS**
6. **Ninja** (optional, for faster builds)

## Quick Build

### Option 1: Official Build Script (Recommended)

```bash
cd /Users/jerry/Vulkan/ai-ml-sdk-for-vulkan

# Run the official build script
python3 ./scripts/build.py \
  --build-type Debug \
  --threads 4 \
  --vulkan-headers-path dependencies/Vulkan-Headers \
  --glslang-path dependencies/glslang \
  --spirv-headers-path dependencies/SPIRV-Headers \
  --spirv-tools-path dependencies/SPIRV-Tools \
  --spirv-cross-path dependencies/SPIRV-Cross \
  --external-llvm dependencies/llvm-project \
  --build-dir build-official
```

### Option 2: Custom Build Script

```bash
# Use the provided unified build script
./build_all_macos.sh
```

### Option 3: Manual Component Build

```bash
# Build scenario-runner only
cd sw/scenario-runner
mkdir build && cd build
cmake .. \
  -DCMAKE_BUILD_TYPE=Debug \
  -DSPIRV_HEADERS_PATH=/Users/jerry/Vulkan/dependencies/SPIRV-Headers \
  -DSPIRV_TOOLS_PATH=/Users/jerry/Vulkan/dependencies/SPIRV-Tools \
  -DVULKAN_HEADERS_PATH=/Users/jerry/Vulkan/dependencies/Vulkan-Headers/include \
  -DGLSLANG_PATH=/Users/jerry/Vulkan/dependencies/glslang
make -j4
```

## Running the Scenario Runner

```bash
cd sw/scenario-runner/build
DYLD_LIBRARY_PATH=/usr/local/lib ./scenario-runner --version
```

## Key Fixes Applied for macOS

1. **Vulkan Compatibility Layer** (`vulkan_full_compat.hpp`)
   - Created comprehensive compatibility header for macOS
   - Added RAII wrapper constructors for ARM extension types
   - Fixed namespace issues and type definitions

2. **C++ Compilation Fixes**
   - Fixed RAII object assignment issues using placement new pattern
   - Fixed container operations for non-copyable types
   - Fixed return type conversions for Vulkan handles
   - Fixed struct initialization for C API compatibility

3. **ARM Extension Functions**
   - Created stub implementations (`arm_extension_stubs.cpp`)
   - These stubs allow compilation but throw runtime errors if ML features are used
   - Full functionality requires the emulation layer

4. **Linking Issues**
   - Fixed SPIRV-Tools linking (changed from SPIRV-Tools-static to SPIRV-Tools)
   - Added Vulkan library linking for both scenario-runner and tools

## Known Issues and Limitations

1. **ARM ML Extensions**
   - Extension functions are stubbed out
   - ML workloads will throw runtime errors
   - Full functionality requires emulation layer

2. **Emulation Layer**
   - Build fails due to SPIRV-Tools compatibility issues
   - The ARM SDK version of SPIRV-Tools has custom modifications
   - Work needed to reconcile differences

3. **Model Converter**
   - Builds LLVM from source (very slow)
   - May take hours to complete
   - Consider using pre-built LLVM if available

## Directory Structure

```
ai-ml-sdk-for-vulkan/
├── sw/
│   ├── scenario-runner/     # ✅ Built
│   ├── emulation-layer/     # ❌ Build issues
│   ├── model-converter/     # ⏳ Building (slow)
│   └── vgf-lib/            # ✅ Built
├── dependencies/
│   ├── SPIRV-Headers/      # ✅ Built
│   ├── SPIRV-Tools/        # ✅ Built
│   ├── glslang/            # ✅ Built
│   ├── SPIRV-Cross/        # ✅ Built
│   └── llvm-project/       # ⏳ Building
├── build-official/         # Official build output
├── build_all_macos.sh      # Custom build script
├── test_build.sh           # Test script
└── monitor_build.sh        # Build monitor

```

## Testing

Run the test script to verify the build:

```bash
./test_build.sh
```

## Monitoring Build Progress

For long builds (especially model converter):

```bash
./monitor_build.sh build-official
```

## Troubleshooting

### "Library not loaded" Error
```bash
export DYLD_LIBRARY_PATH=/usr/local/lib
```

### SPIRV-Tools Errors
The ARM SDK uses a modified version of SPIRV-Tools. If you encounter build errors, use the pre-built version from the scenario-runner build.

### Slow Build
The model converter builds LLVM which can take hours. Consider:
- Using fewer threads if memory is limited
- Building in Release mode for faster runtime
- Using pre-built LLVM if available

## Next Steps

1. Complete emulation layer build (requires fixing SPIRV-Tools)
2. Complete model converter build (wait for LLVM)
3. Test with sample ML models
4. Create Docker image for reproducible builds

## Support

For issues specific to macOS builds:
- Check this README first
- Review the build logs in `build.log`
- File issues with macOS-specific tag

## Credits

Build fixes and macOS compatibility by Claude with assistance from the user.
Original ARM ML SDK by ARM Ltd.