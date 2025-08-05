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
