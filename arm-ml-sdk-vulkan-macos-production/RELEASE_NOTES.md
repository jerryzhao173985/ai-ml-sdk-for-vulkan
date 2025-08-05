# ARM ML SDK for Vulkan - Release Notes

## Version 1.0.0-production (macOS ARM64)

### Release Date
August 5, 2025

### Overview
First production release of the unified ARM ML SDK for Vulkan, optimized for Apple Silicon.

### Key Features
- Full Vulkan compute support on macOS
- Optimized for Apple Silicon (M1/M2/M3/M4)
- TensorFlow Lite model support
- Comprehensive ML operation library
- Performance profiling tools
- Production-ready inference runner

### Included Components
- Scenario Runner (v197a36e)
- VGF Library (vf90fe30)
- SPIRV Tools (v2025.3.rc1)
- 5 pre-trained style transfer models
- 30+ optimized compute shaders
- Comprehensive documentation

### Performance
- Up to 1.8x speedup with FP16 optimization
- 50% memory reduction for inference
- Optimized for unified memory architecture
- SIMD group acceleration for matrix operations

### Known Limitations
- ARM tensor extensions require emulation layer
- Some TOSA operations not fully implemented
- Dynamic shapes not yet supported
- INT8 quantization in development

### System Requirements
- macOS 11.0 or later
- Apple Silicon (M1 or newer) recommended
- 8GB RAM minimum
- Vulkan SDK 1.3 or later

### Getting Started
```bash
./install.sh
source ~/.arm-ml-sdk/activate.sh
python3 tools/run_ml_inference.py models/la_muse.tflite
```

### Support
For issues and questions, refer to the documentation in docs/

### Next Release
Version 1.1.0 will include:
- Full TFLite operator coverage
- Metal Performance Shaders integration
- Dynamic shape support
- INT8 quantization
