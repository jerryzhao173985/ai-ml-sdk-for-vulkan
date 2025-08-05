# Unified ARM ML SDK for Vulkan on macOS

## Overview

This unified SDK combines all available components from the ARM ML SDK ecosystem, optimized for Apple Silicon.

## Components

- **Scenario Runner**: Execute Vulkan compute workloads
- **VGF Library**: Handle Vulkan Graph Format
- **ML Models**: Pre-trained TensorFlow Lite models
- **Optimized Shaders**: TOSA operations and custom kernels
- **Tools**: ML pipeline builder, profiler, and demos

## Quick Start

1. Run a basic test:
   ```bash
   ./test_unified_sdk.sh
   ```

2. Run ML inference:
   ```bash
   ./tools/run_ml_demo.sh models/la_muse.tflite
   ```

3. Profile performance:
   ```bash
   cd tools
   python3 profile_performance.py
   ```

## Available ML Operations

- Convolution (conv2d, depthwise_conv2d)
- Pooling (maxpool2d, avgpool2d)
- Activation (relu, sigmoid, tanh)
- Element-wise (add, multiply, subtract)
- Reduction (reduce_sum, reduce_mean)
- Matrix operations (matmul, transpose)

## Performance Optimization

This SDK is optimized for Apple Silicon with:
- 16-bit float support
- Shared memory tiling
- Metal Performance Shaders integration
- Unified memory architecture benefits

## Creating Custom ML Pipelines

```python
from create_ml_pipeline import MLPipelineBuilder

builder = MLPipelineBuilder()
builder.load_tflite_model("model.tflite")
builder.generate_vulkan_scenario("output.json")
```

## Limitations

- ARM tensor extensions are emulated
- Some TOSA operations not fully implemented
- Model converter requires manual pipeline creation

