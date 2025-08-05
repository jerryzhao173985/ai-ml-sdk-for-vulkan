#!/bin/bash
# Create comprehensive test suite for ARM ML SDK

set -e

echo "=== Creating Comprehensive Test Suite ==="

# Paths
SDK_ROOT="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan"
TEST_SUITE="$SDK_ROOT/test-suite"
SCENARIO_RUNNER="$SDK_ROOT/build-final/bin/scenario-runner"

# Create test suite directory
rm -rf "$TEST_SUITE"
mkdir -p "$TEST_SUITE"/{shaders,scenarios,data,results}

cd "$TEST_SUITE"

# Function to create shader
create_shader() {
    local name=$1
    local code=$2
    
    echo "$code" > "shaders/${name}.comp"
    
    if command -v glslangValidator &> /dev/null; then
        glslangValidator -V "shaders/${name}.comp" -o "shaders/${name}.spv" 2>/dev/null || echo "Failed to compile $name"
    fi
}

# 1. Basic Math Operations
create_shader "add" '
#version 450
layout(local_size_x = 64) in;
layout(set = 0, binding = 0) readonly buffer A { float data[]; } a;
layout(set = 0, binding = 1) readonly buffer B { float data[]; } b;
layout(set = 0, binding = 2) writeonly buffer C { float data[]; } c;
void main() {
    uint idx = gl_GlobalInvocationID.x;
    c.data[idx] = a.data[idx] + b.data[idx];
}'

create_shader "multiply" '
#version 450
layout(local_size_x = 64) in;
layout(set = 0, binding = 0) readonly buffer A { float data[]; } a;
layout(set = 0, binding = 1) readonly buffer B { float data[]; } b;
layout(set = 0, binding = 2) writeonly buffer C { float data[]; } c;
void main() {
    uint idx = gl_GlobalInvocationID.x;
    c.data[idx] = a.data[idx] * b.data[idx];
}'

# 2. Matrix Operations
create_shader "matrix_multiply" '
#version 450
layout(local_size_x = 16, local_size_y = 16) in;
layout(set = 0, binding = 0) readonly buffer A { float data[]; } a;
layout(set = 0, binding = 1) readonly buffer B { float data[]; } b;
layout(set = 0, binding = 2) writeonly buffer C { float data[]; } c;
layout(push_constant) uniform PushConstants {
    uint M, N, K;
} pc;
void main() {
    uint row = gl_GlobalInvocationID.y;
    uint col = gl_GlobalInvocationID.x;
    if (row >= pc.M || col >= pc.N) return;
    
    float sum = 0.0;
    for (uint k = 0; k < pc.K; k++) {
        sum += a.data[row * pc.K + k] * b.data[k * pc.N + col];
    }
    c.data[row * pc.N + col] = sum;
}'

# 3. Convolution-like operation
create_shader "conv1d" '
#version 450
layout(local_size_x = 64) in;
layout(set = 0, binding = 0) readonly buffer Input { float data[]; } input;
layout(set = 0, binding = 1) readonly buffer Kernel { float data[]; } kernel;
layout(set = 0, binding = 2) writeonly buffer Output { float data[]; } output;
layout(push_constant) uniform PushConstants {
    uint input_size;
    uint kernel_size;
} pc;
void main() {
    uint idx = gl_GlobalInvocationID.x;
    if (idx >= pc.input_size - pc.kernel_size + 1) return;
    
    float sum = 0.0;
    for (uint k = 0; k < pc.kernel_size; k++) {
        sum += input.data[idx + k] * kernel.data[k];
    }
    output.data[idx] = sum;
}'

# 4. Activation functions
create_shader "relu" '
#version 450
layout(local_size_x = 64) in;
layout(set = 0, binding = 0) buffer Data { float data[]; } buf;
void main() {
    uint idx = gl_GlobalInvocationID.x;
    buf.data[idx] = max(0.0, buf.data[idx]);
}'

create_shader "sigmoid" '
#version 450
layout(local_size_x = 64) in;
layout(set = 0, binding = 0) buffer Data { float data[]; } buf;
void main() {
    uint idx = gl_GlobalInvocationID.x;
    buf.data[idx] = 1.0 / (1.0 + exp(-buf.data[idx]));
}'

# Create test data
cat > create_test_data.py << 'EOF'
import numpy as np
import json

# Create various test data
sizes = {
    "small": 1024,
    "medium": 4096,
    "large": 16384
}

# Basic arrays
for name, size in sizes.items():
    # Sequential data
    np.save(f"data/seq_{name}.npy", np.arange(size, dtype=np.float32))
    
    # Random data
    np.save(f"data/rand_{name}.npy", np.random.randn(size).astype(np.float32))
    
    # Ones
    np.save(f"data/ones_{name}.npy", np.ones(size, dtype=np.float32))
    
    # Constants
    np.save(f"data/const2_{name}.npy", np.full(size, 2.0, dtype=np.float32))

# Matrix data
for dim in [32, 64, 128]:
    np.save(f"data/matrix_a_{dim}.npy", np.random.randn(dim, dim).astype(np.float32))
    np.save(f"data/matrix_b_{dim}.npy", np.random.randn(dim, dim).astype(np.float32))

# Convolution data
np.save("data/conv_input.npy", np.random.randn(256).astype(np.float32))
np.save("data/conv_kernel_3.npy", np.array([0.25, 0.5, 0.25], dtype=np.float32))
np.save("data/conv_kernel_5.npy", np.array([0.1, 0.2, 0.4, 0.2, 0.1], dtype=np.float32))

print("Test data created successfully")
EOF

python3 create_test_data.py

# Create test scenarios
# 1. Basic addition
cat > scenarios/test_add.json << 'EOF'
{
    "commands": [{
        "dispatch_compute": {
            "bindings": [
                {"id": 0, "set": 0, "resource_ref": "input_a"},
                {"id": 1, "set": 0, "resource_ref": "input_b"},
                {"id": 2, "set": 0, "resource_ref": "output"}
            ],
            "rangeND": [1024],
            "shader_ref": "add_shader"
        }
    }],
    "resources": [
        {
            "shader": {
                "entry": "main",
                "src": "../shaders/add.spv",
                "type": "SPIR-V",
                "uid": "add_shader"
            }
        },
        {
            "buffer": {
                "shader_access": "readonly",
                "size": 4096,
                "src": "../data/seq_small.npy",
                "uid": "input_a"
            }
        },
        {
            "buffer": {
                "shader_access": "readonly",
                "size": 4096,
                "src": "../data/const2_small.npy",
                "uid": "input_b"
            }
        },
        {
            "buffer": {
                "dst": "../results/add_result.npy",
                "shader_access": "writeonly",
                "size": 4096,
                "uid": "output"
            }
        }
    ]
}
EOF

# 2. ReLU activation
cat > scenarios/test_relu.json << 'EOF'
{
    "commands": [{
        "dispatch_compute": {
            "bindings": [
                {"id": 0, "set": 0, "resource_ref": "data"}
            ],
            "rangeND": [1024],
            "shader_ref": "relu_shader"
        }
    }],
    "resources": [
        {
            "shader": {
                "entry": "main",
                "src": "../shaders/relu.spv",
                "type": "SPIR-V",
                "uid": "relu_shader"
            }
        },
        {
            "buffer": {
                "shader_access": "readwrite",
                "size": 4096,
                "src": "../data/rand_small.npy",
                "dst": "../results/relu_result.npy",
                "uid": "data"
            }
        }
    ]
}
EOF

# Create benchmark script
cat > run_benchmarks.sh << 'EOF'
#!/bin/bash
# Run performance benchmarks

SCENARIO_RUNNER="../build-final/bin/scenario-runner"
export DYLD_LIBRARY_PATH=/usr/local/lib

echo "=== ARM ML SDK Performance Benchmarks ==="
echo "Date: $(date)"
echo "Platform: macOS ARM64"
echo ""

# Function to run benchmark
benchmark() {
    local name=$1
    local scenario=$2
    local iterations=${3:-10}
    
    echo "Benchmark: $name"
    echo "Iterations: $iterations"
    
    # Warm up
    $SCENARIO_RUNNER --scenario "$scenario" --output . > /dev/null 2>&1
    
    # Time multiple runs
    start=$(date +%s.%N)
    for i in $(seq 1 $iterations); do
        $SCENARIO_RUNNER --scenario "$scenario" --output . > /dev/null 2>&1
    done
    end=$(date +%s.%N)
    
    # Calculate average
    duration=$(echo "$end - $start" | bc)
    avg=$(echo "scale=3; $duration / $iterations" | bc)
    
    echo "Average time: ${avg}s"
    echo ""
}

# Run benchmarks
cd scenarios
benchmark "Vector Addition (1K elements)" "test_add.json"
benchmark "ReLU Activation (1K elements)" "test_relu.json"

echo "Benchmarks complete"
EOF

chmod +x run_benchmarks.sh

# Create validation script
cat > validate_results.py << 'EOF'
#!/usr/bin/env python3
import numpy as np
import sys

def validate_add():
    a = np.load("data/seq_small.npy")
    b = np.load("data/const2_small.npy")
    result = np.load("results/add_result.npy")
    expected = a + b
    
    if np.allclose(result, expected, rtol=1e-5):
        print("✓ Addition test passed")
        return True
    else:
        print("✗ Addition test failed")
        print(f"  Expected: {expected[:5]}...")
        print(f"  Got: {result[:5]}...")
        return False

def validate_relu():
    original = np.load("data/rand_small.npy")
    result = np.load("results/relu_result.npy")
    expected = np.maximum(0, original)
    
    if np.allclose(result, expected, rtol=1e-5):
        print("✓ ReLU test passed")
        return True
    else:
        print("✗ ReLU test failed")
        return False

if __name__ == "__main__":
    print("=== Validating Results ===")
    tests = [validate_add, validate_relu]
    passed = sum(1 for test in tests if test())
    print(f"\nPassed {passed}/{len(tests)} tests")
    sys.exit(0 if passed == len(tests) else 1)
EOF

chmod +x validate_results.py

echo ""
echo "=== Test Suite Created ==="
echo "Location: $TEST_SUITE"
echo ""
echo "Contents:"
echo "- shaders/: GLSL compute shaders and compiled SPIR-V"
echo "- scenarios/: JSON scenario definitions"
echo "- data/: NumPy test data arrays"
echo "- results/: Output directory for results"
echo ""
echo "To run tests:"
echo "cd $TEST_SUITE/scenarios"
echo "DYLD_LIBRARY_PATH=/usr/local/lib $SCENARIO_RUNNER --scenario test_add.json --output ."
echo ""
echo "To run benchmarks:"
echo "cd $TEST_SUITE"
echo "./run_benchmarks.sh"