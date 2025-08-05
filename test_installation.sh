#!/bin/bash
# Test ML SDK for Vulkan Installation

echo "Testing ML SDK for Vulkan installation..."
echo "========================================"

# Source the environment
source "$(dirname "$0")/setup_environment.sh"

echo ""
echo "Checking for built binaries..."

# Check for model-converter
if [ -f "$ML_SDK_BUILD_DIR/model-converter/model-converter" ]; then
    echo "✓ model-converter found"
    "$ML_SDK_BUILD_DIR/model-converter/model-converter" --help > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo "  └─ model-converter is executable"
    else
        echo "  └─ ERROR: model-converter is not working properly"
    fi
else
    echo "✗ model-converter not found"
fi

# Check for scenario-runner
if [ -f "$ML_SDK_BUILD_DIR/scenario-runner/scenario-runner" ]; then
    echo "✓ scenario-runner found"
    "$ML_SDK_BUILD_DIR/scenario-runner/scenario-runner" --help > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo "  └─ scenario-runner is executable"
    else
        echo "  └─ ERROR: scenario-runner is not working properly"
    fi
else
    echo "✗ scenario-runner not found"
fi

# Check for vgf_dump
if [ -f "$ML_SDK_BUILD_DIR/vgf-lib/vgf_dump/vgf_dump" ]; then
    echo "✓ vgf_dump found"
    "$ML_SDK_BUILD_DIR/vgf-lib/vgf_dump/vgf_dump" --help > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo "  └─ vgf_dump is executable"
    else
        echo "  └─ ERROR: vgf_dump is not working properly"
    fi
else
    echo "✗ vgf_dump not found"
fi

# Check for emulation layer
if [ -d "$ML_SDK_BUILD_DIR/emulation-layer/layers" ]; then
    echo "✓ Emulation layer directory found"
    if [ -f "$ML_SDK_BUILD_DIR/emulation-layer/layers/VkLayer_ML_emulation.json" ]; then
        echo "  └─ Emulation layer manifest found"
    else
        echo "  └─ WARNING: Emulation layer manifest not found"
    fi
else
    echo "✗ Emulation layer directory not found"
fi

echo ""
echo "Checking Vulkan installation..."
which vulkaninfo > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "✓ Vulkan is installed"
    vulkaninfo --summary 2>/dev/null | grep -q "apiVersion" && echo "  └─ Vulkan is working"
else
    echo "⚠ Vulkan tools not found in PATH (vulkaninfo)"
    echo "  You may need to install the Vulkan SDK"
fi

echo ""
echo "========================================"
echo "Test complete!"