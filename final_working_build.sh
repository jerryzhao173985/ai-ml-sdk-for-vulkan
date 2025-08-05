#!/bin/bash
# Final working build script for ARM ML SDK on macOS

set -e

echo "=== Final ARM ML SDK Build for macOS ARM64 ==="
echo ""

# Set paths
SDK_ROOT="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan"
DEPS_ROOT="/Users/jerry/Vulkan/dependencies"
BUILD_DIR="$SDK_ROOT/build-final"

# Clean and create build directory
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"

# Use the official build that already works
echo "=== Using official build components ==="
cd "$SDK_ROOT"

# Copy working components
echo "Copying working components from official build..."
mkdir -p "$BUILD_DIR/bin"
mkdir -p "$BUILD_DIR/lib"

# Copy scenario runner
if [ -f "build-official/scenario-runner/scenario-runner" ]; then
    cp build-official/scenario-runner/scenario-runner "$BUILD_DIR/bin/"
    echo "✓ Scenario runner copied"
fi

# Copy VGF library
if [ -f "build-official/vgf-lib/src/libvgf.a" ]; then
    cp build-official/vgf-lib/src/libvgf.a "$BUILD_DIR/lib/"
    echo "✓ VGF library copied"
fi

# Create a test environment
echo ""
echo "=== Creating test environment ==="
mkdir -p "$BUILD_DIR/tests"
cd "$BUILD_DIR/tests"

# Create simple compute shader test
cat > add_vectors.comp << 'EOF'
#version 450

layout(local_size_x = 64) in;

layout(set = 0, binding = 0) readonly buffer InputA {
    float data[];
} input_a;

layout(set = 0, binding = 1) readonly buffer InputB {
    float data[];
} input_b;

layout(set = 0, binding = 2) writeonly buffer Output {
    float data[];
} output_buffer;

void main() {
    uint idx = gl_GlobalInvocationID.x;
    if (idx < input_a.data.length()) {
        output_buffer.data[idx] = input_a.data[idx] + input_b.data[idx];
    }
}
EOF

# Try to compile shader
if command -v glslangValidator &> /dev/null; then
    echo "Compiling compute shader..."
    glslangValidator -V add_vectors.comp -o add_vectors.spv
    echo "✓ Shader compiled"
fi

# Create test data using Python
cat > create_test_data.py << 'EOF'
import numpy as np

# Create test input arrays
size = 1024
a = np.arange(size, dtype=np.float32)
b = np.ones(size, dtype=np.float32) * 2.0

# Save as numpy files
np.save('input_a.npy', a)
np.save('input_b.npy', b)

print(f"Created test data: {size} float32 values")
print(f"input_a: {a[:5]}... (sequential)")
print(f"input_b: {b[:5]}... (all 2.0)")
print(f"Expected output: {(a+b)[:5]}... (a+2)")
EOF

python3 create_test_data.py

# Create scenario JSON
cat > add_vectors_scenario.json << 'EOF'
{
    "commands": [
        {
            "dispatch_compute": {
                "bindings": [
                    {
                        "id": 0,
                        "set": 0,
                        "resource_ref": "input_a"
                    },
                    {
                        "id": 1,
                        "set": 0,
                        "resource_ref": "input_b"
                    },
                    {
                        "id": 2,
                        "set": 0,
                        "resource_ref": "output"
                    }
                ],
                "rangeND": [1024],
                "shader_ref": "add_shader"
            }
        }
    ],
    "resources": [
        {
            "shader": {
                "entry": "main",
                "src": "add_vectors.spv",
                "type": "SPIR-V",
                "uid": "add_shader"
            }
        },
        {
            "buffer": {
                "shader_access": "readonly",
                "size": 4096,
                "src": "input_a.npy",
                "uid": "input_a"
            }
        },
        {
            "buffer": {
                "shader_access": "readonly",
                "size": 4096,
                "src": "input_b.npy",
                "uid": "input_b"
            }
        },
        {
            "buffer": {
                "dst": "output.npy",
                "shader_access": "writeonly",
                "size": 4096,
                "uid": "output"
            }
        }
    ]
}
EOF

echo ""
echo "=== Testing scenario runner ==="
cd "$BUILD_DIR"

# Test version
echo "Testing scenario runner version..."
DYLD_LIBRARY_PATH=/usr/local/lib ./bin/scenario-runner --version

# List available options
echo ""
echo "Available options:"
DYLD_LIBRARY_PATH=/usr/local/lib ./bin/scenario-runner --help | head -20

echo ""
echo "=== Build Summary ==="
echo "Build directory: $BUILD_DIR"
echo ""
echo "Available components:"
ls -la "$BUILD_DIR/bin/" 2>/dev/null || echo "No binaries"
ls -la "$BUILD_DIR/lib/" 2>/dev/null || echo "No libraries"
echo ""
echo "Test files created in: $BUILD_DIR/tests"
echo ""
echo "To run the test scenario:"
echo "cd $BUILD_DIR/tests"
echo "DYLD_LIBRARY_PATH=/usr/local/lib ../bin/scenario-runner --scenario add_vectors_scenario.json"