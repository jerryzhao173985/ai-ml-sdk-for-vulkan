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
