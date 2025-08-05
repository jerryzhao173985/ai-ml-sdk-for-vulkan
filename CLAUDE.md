# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

The ML SDK for Vulkan® is an SDK to facilitate the development of projects using the ML extensions for Vulkan®. It consists of four main components that can be built together or individually:

1. **VGF Library** - A container format for ML use cases with C++ encoder/decoder API
2. **Model Converter** - Converts TOSA models to SPIR-V™ graphs and packages into VGF files
3. **Scenario Runner** - Data-driven test and validation tool for ML workloads
4. **Emulation Layer** - TOSA compliant compute-based implementation of graph/tensor extensions

## Build Commands

### Build all components:
```bash
./scripts/build.py
```

### Build with documentation:
```bash
./scripts/build.py --doc
```

### Build with custom component paths:
```bash
./scripts/build.py --vgf-lib $PATH_TO_VGF_LIB --model-converter $PATH_TO_MODEL_CONVERTER
```

### Build with installation to specific location:
```bash
./scripts/build.py --install /path/to/install
```

### Create distributable package:
```bash
./scripts/build.py --package
```

### Common build options:
- `--build-type` - Set build type (Release/Debug/RelWithDebInfo)
- `--threads` - Number of build threads
- `--skip-llvm-patch` - Skip applying LLVM patches
- `--prefix-path` - Additional CMake prefix paths

## Development Environment

### Python Requirements
- Python 3.10+ required
- Install tooling dependencies: `pip install -r tooling-requirements.txt`
- Code formatting: Uses Black with Python 3.10 target

### Build System Requirements
- CMake 3.25+
- C/C++17 compiler (GCC, Clang on Linux, MSVC on Windows)
- Flatbuffers flatc compiler
- Doxygen 1.9.1+ (for documentation)

## Project Architecture

### Component Dependencies
- VGF Library is required by both Model Converter and Scenario Runner
- Components can be built independently but have strict dependencies
- All components depend on various third-party libraries (LLVM, TOSA, Vulkan headers, etc.)

### Directory Structure
```
/
├── scripts/           # Build and utility scripts
├── docs/             # Documentation sources
├── cmake/            # CMake modules and configurations
├── sw/               # Component source directories (when cloned)
│   ├── vgf-lib/
│   ├── model-converter/
│   ├── scenario-runner/
│   └── emulation-layer/
└── dependencies/     # Third-party dependencies (when cloned)
```

### Key Scripts
- `scripts/build.py` - Main build orchestration script
- `scripts/run_model_e2e.py` - End-to-end model testing
- `scripts/compare_numpy.py` - Compare numpy arrays
- `scripts/dump_numpy.py` - Dump numpy data
- `scripts/check_images_closeby.py` - Image comparison utility

## Testing

Tests are built as part of the component builds when GoogleTest is available. Each component has its own test suite that can be run after building.

## Important Notes

1. **Out-of-source builds required** - The build system enforces out-of-source builds
2. **Sparse checkout support** - Missing components are skipped during build
3. **Memory-mapped file support** - VGF Library supports efficient runtime file access
4. **No Vulkan API calls in VGF Library** - Integration must handle all Vulkan API interactions

## Common Development Tasks

When working on ML SDK for Vulkan:
1. Always run the build script from the repository root
2. Use the `--help` flag to see all available options for build.py
3. Check component-specific documentation in their respective repositories
4. Use the Scenario Runner for testing ML workloads before integration
5. Use the VGF Dump Tool for debugging VGF files