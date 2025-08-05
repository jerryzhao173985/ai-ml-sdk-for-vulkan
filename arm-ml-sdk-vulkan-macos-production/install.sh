#!/bin/bash
# Install ARM ML SDK for Vulkan

echo "=== ARM ML SDK for Vulkan Installer ==="
echo ""

# Check platform
if [[ "$OSTYPE" != "darwin"* ]]; then
    echo "Error: This SDK is built for macOS ARM64"
    exit 1
fi

# Check architecture
if [[ "$(uname -m)" != "arm64" ]]; then
    echo "Warning: This SDK is optimized for Apple Silicon (ARM64)"
    echo "Performance may be reduced on other architectures"
fi

# Set installation directory
INSTALL_DIR="${1:-$HOME/.arm-ml-sdk}"

echo "Installing to: $INSTALL_DIR"
echo ""

# Create installation directory
mkdir -p "$INSTALL_DIR"

# Copy files
echo "Copying SDK files..."
cp -r . "$INSTALL_DIR/"

# Set up environment
echo ""
echo "Setting up environment..."

# Create activation script
cat > "$INSTALL_DIR/activate.sh" << 'ACTIVATE'
#!/bin/bash
# Activate ARM ML SDK environment

export ARM_ML_SDK_ROOT="$(dirname "${BASH_SOURCE[0]}")"
export PATH="$ARM_ML_SDK_ROOT/bin:$ARM_ML_SDK_ROOT/tools:$PATH"
export DYLD_LIBRARY_PATH="/usr/local/lib:$DYLD_LIBRARY_PATH"

echo "ARM ML SDK activated"
echo "SDK root: $ARM_ML_SDK_ROOT"
ACTIVATE

chmod +x "$INSTALL_DIR/activate.sh"

# Create uninstall script
cat > "$INSTALL_DIR/uninstall.sh" << 'UNINSTALL'
#!/bin/bash
# Uninstall ARM ML SDK

echo "Uninstalling ARM ML SDK..."
SDK_DIR="$(dirname "${BASH_SOURCE[0]}")"
rm -rf "$SDK_DIR"
echo "ARM ML SDK uninstalled"
UNINSTALL

chmod +x "$INSTALL_DIR/uninstall.sh"

echo ""
echo "=== Installation Complete ==="
echo ""
echo "To use the SDK:"
echo "  source $INSTALL_DIR/activate.sh"
echo ""
echo "To run ML inference:"
echo "  python3 $INSTALL_DIR/tools/run_ml_inference.py <model.tflite>"
echo ""
echo "To uninstall:"
echo "  $INSTALL_DIR/uninstall.sh"
