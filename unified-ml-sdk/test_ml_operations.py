#!/usr/bin/env python3
"""Test all ML operations"""

import numpy as np
import subprocess
import os

def test_operation(op_name, scenario_path):
    """Test a single ML operation"""
    print(f"Testing {op_name}...", end=" ")
    
    if not os.path.exists(scenario_path):
        print("SKIP (scenario not found)")
        return False
    
    # Run scenario
    result = subprocess.run([
        "./bin/scenario-runner",
        "--scenario", scenario_path,
        "--output", "results/"
    ], capture_output=True, env={"DYLD_LIBRARY_PATH": "/usr/local/lib"})
    
    if result.returncode == 0:
        print("PASS")
        return True
    else:
        print("FAIL")
        print(result.stderr.decode())
        return False

def main():
    print("=== Testing ML Operations ===")
    
    operations = [
        ("Convolution", "scenarios/ml_ops/test_conv2d.json"),
        ("Matrix Multiply", "scenarios/ml_ops/test_matmul.json"),
        ("Max Pooling", "scenarios/ml_ops/test_maxpool.json"),
        ("ReLU", "scenarios/ml_ops/test_relu.json"),
        ("Batch Norm", "scenarios/ml_ops/test_batchnorm.json")
    ]
    
    passed = 0
    total = len(operations)
    
    for op_name, scenario in operations:
        if test_operation(op_name, scenario):
            passed += 1
    
    print(f"\nResults: {passed}/{total} tests passed")
    
    # Test with real model
    print("\nTesting with real ML model:")
    if os.path.exists("models/la_muse.tflite"):
        print("Style transfer model found")
        # Would run actual inference here

if __name__ == "__main__":
    main()
