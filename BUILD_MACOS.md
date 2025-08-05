# Building ARM ML SDK on macOS ARM64

## Prerequisites
- macOS 11.0 or later
- Apple Silicon (M1/M2/M3/M4) or Intel Mac
- Xcode Command Line Tools
- CMake 3.20 or later
- Python 3.8 or later
- Vulkan SDK 1.3 or later

## Build Instructions

### 1. Clone with Dependencies
```bash
git clone --recursive https://github.com/jerryzhao173985/ai-ml-sdk-for-vulkan.git
cd ai-ml-sdk-for-vulkan
```

### 2. Setup Dependencies
```bash
./setup_dependencies.sh
```

### 3. Build
```bash
python3 ./scripts/build.py \
  --build-type Release \
  --threads 8 \
  --build-dir build-macos
```

### 4. Test
```bash
./build-macos/bin/scenario-runner --version
```

## Key Changes for macOS

1. **RAII Fixes**: Modified Vulkan C++ bindings for proper object lifetime
2. **Namespace Fixes**: Added explicit namespace qualifiers
3. **ARM Extensions**: Created stub implementations
4. **Build System**: Adapted for macOS toolchain

## Performance

Optimized for Apple Silicon with:
- FP16 arithmetic support
- Unified memory architecture
- Metal interoperability potential

## Troubleshooting

If you encounter build issues:
1. Ensure all submodules are updated
2. Check Vulkan SDK installation
3. Verify CMake version
4. See COMPLETE_JOURNEY_LOG.md for detailed fixes
