#!/bin/bash
# ML SDK for Vulkan Environment Setup Script

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Set up environment variables
export ML_SDK_ROOT="$SCRIPT_DIR"
export ML_SDK_BUILD_DIR="$ML_SDK_ROOT/build"

# Add binaries to PATH
export PATH="$ML_SDK_BUILD_DIR/model-converter:$PATH"
export PATH="$ML_SDK_BUILD_DIR/scenario-runner:$PATH"
export PATH="$ML_SDK_BUILD_DIR/vgf_dump:$PATH"

# Library paths (for macOS)
export DYLD_LIBRARY_PATH="$ML_SDK_BUILD_DIR/lib:$DYLD_LIBRARY_PATH"

# Vulkan layer path for emulation
export VK_LAYER_PATH="$ML_SDK_BUILD_DIR/emulation-layer/layers:$VK_LAYER_PATH"

# Python path for model converter modules
export PYTHONPATH="$ML_SDK_BUILD_DIR/model-converter/python:$PYTHONPATH"

echo "ML SDK for Vulkan environment configured!"
echo ""
echo "Available tools:"
echo "  - model-converter: Convert TOSA models to VGF format"
echo "  - scenario-runner: Run ML scenarios"
echo "  - vgf_dump: Inspect and extract VGF files"
echo ""
echo "To enable emulation layer:"
echo "  export VK_INSTANCE_LAYERS=VK_LAYER_ML_emulation"
echo ""
echo "Build directory: $ML_SDK_BUILD_DIR"