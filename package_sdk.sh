#!/bin/bash
# Package ARM ML SDK for distribution

set -e

echo "=== Packaging ARM ML SDK for macOS ARM64 ==="

# Variables
SDK_VERSION="1.0.0-macos-arm64"
PACKAGE_NAME="arm-ml-sdk-vulkan-${SDK_VERSION}"
PACKAGE_DIR="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/dist/${PACKAGE_NAME}"

# Clean and create package directory
rm -rf /Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/dist
mkdir -p "$PACKAGE_DIR"/{bin,lib,include,share,examples,docs}

# Copy binaries
echo "Copying binaries..."
cp build-final/bin/scenario-runner "$PACKAGE_DIR/bin/"

# Copy libraries
echo "Copying libraries..."
cp build-final/lib/libvgf.a "$PACKAGE_DIR/lib/"

# Copy headers (if available)
echo "Copying headers..."
mkdir -p "$PACKAGE_DIR/include/vgf"
# cp sw/vgf-lib/include/*.h "$PACKAGE_DIR/include/vgf/" 2>/dev/null || true

# Copy examples
echo "Copying examples..."
cp -r test-suite "$PACKAGE_DIR/examples/"
cp -r benchmarks "$PACKAGE_DIR/examples/"

# Copy documentation
echo "Creating documentation..."
cp *.md "$PACKAGE_DIR/docs/"

# Create launcher scripts
cat > "$PACKAGE_DIR/bin/run-scenario.sh" << 'EOF'
#!/bin/bash
# Launcher script for scenario runner
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export DYLD_LIBRARY_PATH=/usr/local/lib:$DYLD_LIBRARY_PATH
"$SCRIPT_DIR/scenario-runner" "$@"
EOF
chmod +x "$PACKAGE_DIR/bin/run-scenario.sh"

# Create setup script
cat > "$PACKAGE_DIR/setup.sh" << 'EOF'
#!/bin/bash
# Setup script for ARM ML SDK

echo "Setting up ARM ML SDK for Vulkan..."

# Add to PATH
SDK_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export PATH="$SDK_DIR/bin:$PATH"

# Check dependencies
echo "Checking dependencies..."

# Check Vulkan
if command -v vulkaninfo &> /dev/null; then
    echo "✓ Vulkan found"
else
    echo "✗ Vulkan not found. Please install Vulkan SDK"
fi

# Check glslang
if command -v glslangValidator &> /dev/null; then
    echo "✓ glslang found"
else
    echo "✗ glslang not found. Please install glslang"
fi

# Check Python
if command -v python3 &> /dev/null; then
    echo "✓ Python 3 found"
else
    echo "✗ Python 3 not found"
fi

echo ""
echo "Setup complete. You can now use:"
echo "  run-scenario.sh - Run Vulkan scenarios"
echo ""
echo "Examples are in: $SDK_DIR/examples"
EOF
chmod +x "$PACKAGE_DIR/setup.sh"

# Create README
cat > "$PACKAGE_DIR/README.md" << EOF
# ARM ML SDK for Vulkan - macOS ARM64 Edition

Version: ${SDK_VERSION}

## Contents

- **bin/**: Executables
  - scenario-runner: Main Vulkan scenario execution engine
  - run-scenario.sh: Convenience launcher script

- **lib/**: Libraries
  - libvgf.a: Vulkan Graph Format library

- **examples/**: Example code and benchmarks
  - test-suite/: Basic compute shader examples
  - benchmarks/: Performance benchmarks

- **docs/**: Documentation
  - Complete build reports and guides

## Quick Start

1. Run the setup script:
   \`\`\`bash
   ./setup.sh
   \`\`\`

2. Test the installation:
   \`\`\`bash
   bin/run-scenario.sh --version
   \`\`\`

3. Run an example:
   \`\`\`bash
   cd examples/test-suite/scenarios
   ../../bin/run-scenario.sh --scenario test_add.json
   \`\`\`

## Requirements

- macOS 12.0+ on Apple Silicon (M1/M2/M3/M4)
- Vulkan SDK with MoltenVK
- Python 3.8+ (for test scripts)

## Limitations

- ARM ML extensions (VK_ARM_tensors, VK_ARM_data_graph) are stubbed
- Model converter not included (TOSA compatibility issues)
- Emulation layer not included (SPIRV-Tools compatibility)

## Support

This is an unofficial macOS port. For official ARM ML SDK:
https://github.com/ARM-software/ml-sdk-for-vulkan

Built with ❤️ on macOS ARM64
EOF

# Create archive
echo ""
echo "Creating archive..."
cd /Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/dist
tar -czf "${PACKAGE_NAME}.tar.gz" "$PACKAGE_NAME"

# Create installer package (optional)
cat > create_pkg.sh << 'EOF'
#!/bin/bash
# Create macOS installer package
pkgbuild --root "$PACKAGE_NAME" \
         --identifier "com.arm.ml-sdk-vulkan" \
         --version "$SDK_VERSION" \
         --install-location "/usr/local/arm-ml-sdk" \
         "${PACKAGE_NAME}.pkg"
EOF

echo ""
echo "=== Packaging Complete ==="
echo "Package: /Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/dist/${PACKAGE_NAME}.tar.gz"
echo "Size: $(du -h "${PACKAGE_NAME}.tar.gz" | cut -f1)"
echo ""
echo "To distribute:"
echo "1. Upload ${PACKAGE_NAME}.tar.gz"
echo "2. Users extract and run ./setup.sh"