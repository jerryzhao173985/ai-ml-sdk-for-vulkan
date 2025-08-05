#!/bin/bash
# Create comprehensive benchmark suite

set -e

echo "=== Creating Performance Benchmark Suite ==="

BENCH_DIR="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/benchmarks"
mkdir -p "$BENCH_DIR"/{shaders,scenarios,results,scripts}

cd "$BENCH_DIR"

# Create compute-intensive shaders for benchmarking
cat > shaders/matrix_mult_naive.comp << 'EOF'
#version 450
layout(local_size_x = 16, local_size_y = 16) in;

layout(set = 0, binding = 0) readonly buffer MatA { float data[]; } a;
layout(set = 0, binding = 1) readonly buffer MatB { float data[]; } b;
layout(set = 0, binding = 2) writeonly buffer MatC { float data[]; } c;

layout(push_constant) uniform Constants {
    uint M, N, K;
} constants;

void main() {
    uint row = gl_GlobalInvocationID.y;
    uint col = gl_GlobalInvocationID.x;
    
    if (row >= constants.M || col >= constants.N) return;
    
    float sum = 0.0;
    for (uint i = 0; i < constants.K; i++) {
        sum += a.data[row * constants.K + i] * b.data[i * constants.N + col];
    }
    c.data[row * constants.N + col] = sum;
}
EOF

# Tiled matrix multiplication
cat > shaders/matrix_mult_tiled.comp << 'EOF'
#version 450
#define TILE_SIZE 16

layout(local_size_x = TILE_SIZE, local_size_y = TILE_SIZE) in;

layout(set = 0, binding = 0) readonly buffer MatA { float data[]; } a;
layout(set = 0, binding = 1) readonly buffer MatB { float data[]; } b;
layout(set = 0, binding = 2) writeonly buffer MatC { float data[]; } c;

layout(push_constant) uniform Constants {
    uint M, N, K;
} constants;

shared float tileA[TILE_SIZE][TILE_SIZE];
shared float tileB[TILE_SIZE][TILE_SIZE];

void main() {
    uint row = gl_WorkGroupID.y * TILE_SIZE + gl_LocalInvocationID.y;
    uint col = gl_WorkGroupID.x * TILE_SIZE + gl_LocalInvocationID.x;
    uint localRow = gl_LocalInvocationID.y;
    uint localCol = gl_LocalInvocationID.x;
    
    float sum = 0.0;
    
    for (uint t = 0; t < (constants.K + TILE_SIZE - 1) / TILE_SIZE; t++) {
        // Load tiles into shared memory
        uint aRow = row;
        uint aCol = t * TILE_SIZE + localCol;
        if (aRow < constants.M && aCol < constants.K) {
            tileA[localRow][localCol] = a.data[aRow * constants.K + aCol];
        } else {
            tileA[localRow][localCol] = 0.0;
        }
        
        uint bRow = t * TILE_SIZE + localRow;
        uint bCol = col;
        if (bRow < constants.K && bCol < constants.N) {
            tileB[localRow][localCol] = b.data[bRow * constants.N + bCol];
        } else {
            tileB[localRow][localCol] = 0.0;
        }
        
        barrier();
        
        // Compute partial dot product
        for (uint k = 0; k < TILE_SIZE; k++) {
            sum += tileA[localRow][k] * tileB[k][localCol];
        }
        
        barrier();
    }
    
    if (row < constants.M && col < constants.N) {
        c.data[row * constants.N + col] = sum;
    }
}
EOF

# Vector operations benchmark
cat > shaders/vector_ops.comp << 'EOF'
#version 450
layout(local_size_x = 256) in;

layout(set = 0, binding = 0) buffer Data { float data[]; } buf;

layout(push_constant) uniform Constants {
    uint size;
    uint operation; // 0=add, 1=mul, 2=fma, 3=complex
} constants;

void main() {
    uint idx = gl_GlobalInvocationID.x;
    if (idx >= constants.size) return;
    
    float x = buf.data[idx];
    
    switch (constants.operation) {
        case 0: // Add constant
            buf.data[idx] = x + 1.0;
            break;
        case 1: // Multiply
            buf.data[idx] = x * 2.0;
            break;
        case 2: // FMA
            buf.data[idx] = x * 2.0 + 1.0;
            break;
        case 3: // Complex operation
            buf.data[idx] = sqrt(abs(sin(x) * cos(x * 2.0))) + exp(-x * x);
            break;
    }
}
EOF

# Memory bandwidth test
cat > shaders/memory_bandwidth.comp << 'EOF'
#version 450
layout(local_size_x = 256) in;

layout(set = 0, binding = 0) readonly buffer Src { float data[]; } src;
layout(set = 0, binding = 1) writeonly buffer Dst { float data[]; } dst;

void main() {
    uint idx = gl_GlobalInvocationID.x;
    dst.data[idx] = src.data[idx];
}
EOF

# Compile shaders
echo "Compiling benchmark shaders..."
for shader in shaders/*.comp; do
    if command -v glslangValidator &> /dev/null; then
        glslangValidator -V "$shader" -o "${shader%.comp}.spv" 2>/dev/null || echo "Failed: $shader"
    fi
done

# Create benchmark runner script
cat > scripts/run_benchmarks.py << 'EOF'
#!/usr/bin/env python3
import subprocess
import time
import json
import numpy as np
import os
import sys
from datetime import datetime

SCENARIO_RUNNER = "/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/build-final/bin/scenario-runner"

class Benchmark:
    def __init__(self, name, scenario_file, sizes):
        self.name = name
        self.scenario_file = scenario_file
        self.sizes = sizes
        self.results = {}
    
    def run(self, iterations=5):
        print(f"\n{'='*60}")
        print(f"Benchmark: {self.name}")
        print(f"{'='*60}")
        
        for size in self.sizes:
            print(f"\nSize: {size}")
            times = []
            
            # Prepare data
            self.prepare_data(size)
            
            # Warm up
            self._run_scenario()
            
            # Benchmark runs
            for i in range(iterations):
                start = time.perf_counter()
                self._run_scenario()
                end = time.perf_counter()
                elapsed = (end - start) * 1000  # Convert to ms
                times.append(elapsed)
                print(f"  Run {i+1}: {elapsed:.2f} ms")
            
            avg_time = np.mean(times)
            std_time = np.std(times)
            
            self.results[size] = {
                'avg_ms': avg_time,
                'std_ms': std_time,
                'min_ms': min(times),
                'max_ms': max(times)
            }
            
            print(f"  Average: {avg_time:.2f} ± {std_time:.2f} ms")
            
            # Calculate throughput if applicable
            self.calculate_metrics(size, avg_time)
    
    def prepare_data(self, size):
        # Override in subclasses
        pass
    
    def calculate_metrics(self, size, time_ms):
        # Override in subclasses
        pass
    
    def _run_scenario(self):
        env = os.environ.copy()
        env['DYLD_LIBRARY_PATH'] = '/usr/local/lib'
        
        cmd = [SCENARIO_RUNNER, '--scenario', self.scenario_file, '--output', '.']
        subprocess.run(cmd, env=env, capture_output=True)

class MatrixMultBenchmark(Benchmark):
    def prepare_data(self, size):
        # Create square matrices
        A = np.random.randn(size, size).astype(np.float32)
        B = np.random.randn(size, size).astype(np.float32)
        np.save(f'../data/matrix_a_{size}.npy', A)
        np.save(f'../data/matrix_b_{size}.npy', B)
    
    def calculate_metrics(self, size, time_ms):
        # FLOPS = 2 * M * N * K for matrix multiplication
        flops = 2 * size * size * size
        gflops = (flops / 1e9) / (time_ms / 1000)
        print(f"  Performance: {gflops:.2f} GFLOPS")

class MemoryBandwidthBenchmark(Benchmark):
    def prepare_data(self, size):
        data = np.random.randn(size).astype(np.float32)
        np.save(f'../data/bandwidth_{size}.npy', data)
    
    def calculate_metrics(self, size, time_ms):
        # Bandwidth = 2 * size * sizeof(float) / time
        bytes_transferred = 2 * size * 4  # Read + Write, 4 bytes per float
        bandwidth_gb = (bytes_transferred / 1e9) / (time_ms / 1000)
        print(f"  Bandwidth: {bandwidth_gb:.2f} GB/s")

def main():
    print("ARM ML SDK Performance Benchmarks")
    print(f"Date: {datetime.now()}")
    print(f"Platform: macOS ARM64")
    
    # Check if scenario runner exists
    if not os.path.exists(SCENARIO_RUNNER):
        print(f"Error: Scenario runner not found at {SCENARIO_RUNNER}")
        sys.exit(1)
    
    benchmarks = [
        MatrixMultBenchmark(
            "Matrix Multiplication (Naive)",
            "../scenarios/matrix_mult_naive.json",
            [128, 256, 512, 1024]
        ),
        MatrixMultBenchmark(
            "Matrix Multiplication (Tiled)",
            "../scenarios/matrix_mult_tiled.json",
            [128, 256, 512, 1024]
        ),
        MemoryBandwidthBenchmark(
            "Memory Bandwidth",
            "../scenarios/memory_bandwidth.json",
            [1024*1024, 4*1024*1024, 16*1024*1024]  # 1MB, 4MB, 16MB
        )
    ]
    
    results = {}
    for bench in benchmarks:
        bench.run()
        results[bench.name] = bench.results
    
    # Save results
    with open('../results/benchmark_results.json', 'w') as f:
        json.dump({
            'date': str(datetime.now()),
            'platform': 'macOS ARM64',
            'results': results
        }, f, indent=2)
    
    print("\n" + "="*60)
    print("Benchmarks complete. Results saved to benchmark_results.json")

if __name__ == "__main__":
    main()
EOF

chmod +x scripts/run_benchmarks.py

# Create benchmark report generator
cat > scripts/generate_report.py << 'EOF'
#!/usr/bin/env python3
import json
import matplotlib.pyplot as plt
import numpy as np

def generate_report():
    with open('../results/benchmark_results.json', 'r') as f:
        data = json.load(f)
    
    print("# ARM ML SDK Benchmark Report")
    print(f"\nDate: {data['date']}")
    print(f"Platform: {data['platform']}")
    print("\n## Results Summary\n")
    
    for bench_name, results in data['results'].items():
        print(f"### {bench_name}")
        print("\n| Size | Avg Time (ms) | Std Dev | Performance |")
        print("|------|---------------|---------|-------------|")
        
        for size, metrics in results.items():
            print(f"| {size} | {metrics['avg_ms']:.2f} | ±{metrics['std_ms']:.2f} | - |")
        print()
    
    # Generate plots
    fig, axes = plt.subplots(2, 2, figsize=(12, 10))
    
    # Plot matrix multiplication comparison
    # ... plotting code ...
    
    plt.tight_layout()
    plt.savefig('../results/benchmark_plots.png')
    print("\nPlots saved to benchmark_plots.png")

if __name__ == "__main__":
    generate_report()
EOF

chmod +x scripts/generate_report.py

echo ""
echo "=== Benchmark Suite Created ==="
echo "Location: $BENCH_DIR"
echo ""
echo "To run benchmarks:"
echo "cd $BENCH_DIR/scripts"
echo "python3 run_benchmarks.py"
echo ""
echo "Note: Benchmarks require working Vulkan instance."
echo "Results will be saved in JSON format for analysis."