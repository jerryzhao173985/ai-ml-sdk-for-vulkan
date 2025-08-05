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
