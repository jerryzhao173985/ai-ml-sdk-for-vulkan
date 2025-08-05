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
