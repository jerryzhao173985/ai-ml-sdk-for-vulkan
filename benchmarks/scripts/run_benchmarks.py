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
