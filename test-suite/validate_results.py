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
