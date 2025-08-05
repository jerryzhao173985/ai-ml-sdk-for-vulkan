#!/bin/bash
# Build complete ARM ML SDK with all components

set -e

echo "=== Building Complete ARM ML SDK for Vulkan on macOS ==="
echo ""

# Paths
SDK_ROOT="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan"
BUILD_DIR="$SDK_ROOT/build-complete"

# Create build directory
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"

# Function to build component
build_component() {
    local name=$1
    local path=$2
    local extra_args=$3
    
    echo "=== Building $name ==="
    mkdir -p "$BUILD_DIR/$name"
    cd "$BUILD_DIR/$name"
    
    cmake "$path" \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_OSX_ARCHITECTURES=arm64 \
        $extra_args
    
    make -j4 || true
    
    echo "✓ $name build attempted"
    echo ""
}

# First, build dependencies if needed
echo "=== Checking dependencies ==="
cd "$SDK_ROOT/dependencies"

# Build SPIRV-Tools if not already built
if [ ! -f "SPIRV-Tools/build/tools/SPIRV-Tools" ]; then
    echo "Building ARM SPIRV-Tools..."
    cd SPIRV-Tools
    cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64 \
        -DSPIRV-Headers_SOURCE_DIR="../SPIRV-Headers"
    cmake --build build -j4
    cd ..
fi

# Now build all components
cd "$SDK_ROOT"

# 1. VGF Library
build_component "vgf" "$SDK_ROOT/sw/vgf-lib" \
    "-DJSON_PATH=$SDK_ROOT/dependencies/json \
     -DARGPARSE_PATH=$SDK_ROOT/dependencies/argparse \
     -DFLATBUFFERS_PATH=$SDK_ROOT/dependencies/flatbuffers"

# 2. Scenario Runner with ARM stubs
build_component "scenario-runner" "$SDK_ROOT/sw/scenario-runner" \
    "-DSPIRV_HEADERS_PATH=$SDK_ROOT/dependencies/SPIRV-Headers \
     -DSPIRV_TOOLS_PATH=$SDK_ROOT/dependencies/SPIRV-Tools \
     -DVULKAN_HEADERS_PATH=$SDK_ROOT/dependencies/Vulkan-Headers/include \
     -DGLSLANG_PATH=$SDK_ROOT/dependencies/glslang \
     -DARGPARSE_PATH=$SDK_ROOT/dependencies/argparse \
     -DJSON_PATH=$SDK_ROOT/dependencies/json \
     -DVGF_PATH=$BUILD_DIR/vgf"

# 3. Test components
echo "=== Testing built components ==="

# Test scenario runner
if [ -f "$BUILD_DIR/scenario-runner/scenario-runner" ]; then
    echo "Testing scenario-runner..."
    cd "$BUILD_DIR/scenario-runner"
    DYLD_LIBRARY_PATH=/usr/local/lib ./scenario-runner --version || true
fi

# Create test scenario
echo "=== Creating test scenario ==="
mkdir -p "$BUILD_DIR/test"
cd "$BUILD_DIR/test"

# Create a simple compute shader
cat > simple.comp << 'EOF'
#version 450

layout(local_size_x = 64) in;

layout(set = 0, binding = 0) buffer InputBuffer {
    float data[];
} input_buffer;

layout(set = 0, binding = 1) buffer OutputBuffer {
    float data[];
} output_buffer;

void main() {
    uint idx = gl_GlobalInvocationID.x;
    output_buffer.data[idx] = input_buffer.data[idx] * 2.0;
}
EOF

# Compile shader if glslangValidator is available
if command -v glslangValidator &> /dev/null; then
    echo "Compiling test shader..."
    glslangValidator -V simple.comp -o simple.spv
fi

# Create test scenario JSON
cat > test_scenario.json << 'EOF'
{
    "commands": [
        {
            "dispatch_compute": {
                "bindings": [
                    {
                        "id": 0,
                        "set": 0,
                        "resource_ref": "input"
                    },
                    {
                        "id": 1,
                        "set": 0,
                        "resource_ref": "output"
                    }
                ],
                "rangeND": [1024],
                "shader_ref": "compute_shader"
            }
        }
    ],
    "resources": [
        {
            "shader": {
                "entry": "main",
                "src": "simple.spv",
                "type": "SPIR-V",
                "uid": "compute_shader"
            }
        },
        {
            "buffer": {
                "shader_access": "readonly",
                "size": 4096,
                "uid": "input"
            }
        },
        {
            "buffer": {
                "shader_access": "writeonly",
                "size": 4096,
                "uid": "output"
            }
        }
    ]
}
EOF

echo ""
echo "=== Build Summary ==="
echo "Build directory: $BUILD_DIR"
echo ""
echo "Components built:"
find "$BUILD_DIR" -name "*.a" -o -name "scenario-runner" -o -name "*.dylib" | grep -v CMakeFiles | sort
echo ""
echo "To test the scenario runner:"
echo "cd $BUILD_DIR/scenario-runner"
echo "DYLD_LIBRARY_PATH=/usr/local/lib ./scenario-runner --help"