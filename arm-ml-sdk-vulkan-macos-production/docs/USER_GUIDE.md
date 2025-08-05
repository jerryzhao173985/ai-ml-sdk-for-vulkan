# ARM ML SDK for Vulkan - User Guide

## Table of Contents
1. [Installation](#installation)
2. [Quick Start](#quick-start)
3. [Running ML Models](#running-ml-models)
4. [Performance Optimization](#performance-optimization)
5. [API Reference](#api-reference)
6. [Troubleshooting](#troubleshooting)

## Installation

```bash
# Install to default location
./install.sh

# Or specify custom location
./install.sh /path/to/install

# Activate SDK
source ~/.arm-ml-sdk/activate.sh
```

## Quick Start

### Running Your First Model

```bash
# Run style transfer on an image
python3 tools/run_ml_inference.py models/la_muse.tflite --input image.jpg

# Run with random input
python3 tools/run_ml_inference.py models/la_muse.tflite

# Benchmark performance
python3 tools/run_ml_inference.py models/la_muse.tflite --benchmark
```

### Using the Scenario Runner

```bash
# Run a Vulkan compute scenario
scenario-runner --scenario my_scenario.json --output results/

# Get version information
scenario-runner --version
```

## Running ML Models

### Supported Models

The SDK includes pre-converted style transfer models:
- `la_muse.tflite` - Impressionist style transfer
- `udnie.tflite` - Fauvist style transfer
- `wave_crop.tflite` - Japanese wave style
- `mirror.tflite` - Mirror effect
- `des_glaneuses.tflite` - Millet painting style

### Custom Models

To run your own TensorFlow Lite models:

```python
from tools.run_ml_inference import MLInferenceRunner

runner = MLInferenceRunner()
runner.run_inference("my_model.tflite", input_data)
```

## Performance Optimization

### Apple Silicon Optimizations

The SDK automatically applies these optimizations on Apple Silicon:
- FP16 arithmetic for 2x memory reduction
- SIMD group operations for matrix multiplication
- Shared memory tiling for reduced memory bandwidth
- Unified memory architecture benefits

### Performance Tips

1. **Use FP16 when possible**: Provides ~1.8x speedup
2. **Batch operations**: Process multiple inputs together
3. **Profile your workload**: Use the benchmark tools
4. **Monitor memory usage**: Apple Silicon has unified memory

## API Reference

### MLInferenceRunner

```python
class MLInferenceRunner:
    def run_inference(model_path, input_data, output_path=None):
        """
        Run ML inference on input data
        
        Args:
            model_path: Path to TFLite model
            input_data: NumPy array or path to input
            output_path: Optional output directory
            
        Returns:
            bool: Success status
        """
```

### Scenario Format

```json
{
    "commands": [{
        "dispatch_compute": {
            "shader_ref": "shader_id",
            "rangeND": [x, y, z],
            "bindings": [...]
        }
    }],
    "resources": [...]
}
```

## Troubleshooting

### Common Issues

1. **"Scenario runner not found"**
   - Ensure SDK is activated: `source activate.sh`

2. **"Library not loaded"**
   - Set library path: `export DYLD_LIBRARY_PATH=/usr/local/lib`

3. **Performance issues**
   - Check Activity Monitor for GPU usage
   - Use FP16 mode for better performance
   - Reduce batch size if memory limited

### Getting Help

- Check examples in `examples/` directory
- Run tools with `--help` flag
- Review benchmark results for optimization ideas

## Advanced Usage

### Creating Custom Pipelines

See `examples/custom_pipeline.py` for creating custom ML pipelines.

### Integration with Metal

The SDK can be integrated with Metal Performance Shaders for hybrid compute.

## License

This SDK is provided under the ARM ML SDK license terms.
