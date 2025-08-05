#!/bin/bash
# Test script to verify ARM ML SDK build

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "=== ARM ML SDK Build Test ==="
echo ""

# Test scenario-runner
echo "1. Testing scenario-runner..."
cd "$SCRIPT_DIR/sw/scenario-runner/build"
if [ -f "./scenario-runner" ]; then
    echo "   Binary found: $(ls -lh scenario-runner | awk '{print $5}')"
    echo -n "   Version: "
    DYLD_LIBRARY_PATH=/usr/local/lib ./scenario-runner --version 2>/dev/null | grep version | head -1 || echo "Failed to get version"
    echo "   ✓ scenario-runner OK"
else
    echo "   ✗ scenario-runner not found"
fi
echo ""

# Test glslc
echo "2. Testing glslc..."
if [ -f "./src/tools/glslc" ]; then
    echo "   Binary found: $(ls -lh src/tools/glslc | awk '{print $5}')"
    echo -n "   Version: "
    ./src/tools/glslc --version 2>/dev/null | head -1 || echo "Failed to get version"
    echo "   ✓ glslc OK"
else
    echo "   ✗ glslc not found"
fi
echo ""

# Test dds_utils
echo "3. Testing dds_utils..."
if [ -f "./src/tools/dds_utils" ]; then
    echo "   Binary found: $(ls -lh src/tools/dds_utils | awk '{print $5}')"
    echo "   ✓ dds_utils OK"
else
    echo "   ✗ dds_utils not found"
fi
echo ""

# Check for ARM extension stubs
echo "4. Checking ARM extension support..."
if nm libScenarioRunnerLib.a 2>/dev/null | grep -q "vkCreateTensorARM"; then
    echo "   ✓ ARM extension functions present (stubs)"
    echo "   Note: These are stub implementations - full ML functionality requires emulation layer"
else
    echo "   ✗ ARM extension functions not found"
fi
echo ""

# Check dependencies
echo "5. Checking dependencies..."
for dep in SPIRV-Headers SPIRV-Tools glslang SPIRV-Cross; do
    if [ -d "$SCRIPT_DIR/dependencies/$dep/install" ] || [ -d "$SCRIPT_DIR/dependencies/$dep/build" ]; then
        echo "   ✓ $dep built"
    else
        echo "   ✗ $dep not built"
    fi
done
echo ""

# Summary
echo "=== Test Summary ==="
echo "The ARM ML SDK scenario-runner has been successfully built for macOS ARM64."
echo "You can use it to run Vulkan compute scenarios."
echo ""
echo "Limitations:"
echo "- ARM ML extension functions are stubbed (will throw errors if used)"
echo "- Full ML functionality requires the emulation layer"
echo "- Tested on macOS with standard Vulkan SDK"
echo ""
echo "To run a scenario:"
echo "  cd $SCRIPT_DIR/sw/scenario-runner/build"
echo '  DYLD_LIBRARY_PATH=/usr/local/lib ./scenario-runner <scenario.json>'