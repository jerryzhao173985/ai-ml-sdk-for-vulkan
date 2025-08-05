# ML SDK for Vulkan - Build Instructions

## Build Status
The ML SDK for Vulkan is currently building. This is a large project that includes LLVM and will take some time to complete.

## Build Command Used
```bash
python3 ./scripts/build.py --build-dir build --threads 4 --skip-llvm-patch
```

Note: The `--skip-llvm-patch` flag was used because the LLVM patch failed to apply on the current version.

## Post-Build Setup

Once the build completes, follow these steps:

### 1. Set up the environment
```bash
source ./setup_environment.sh
```

### 2. Test the installation
```bash
./test_installation.sh
```

### 3. Enable the emulation layer (optional)
```bash
export VK_INSTANCE_LAYERS=VK_LAYER_ML_emulation
```

## Built Components

The following components are being built:
- **VGF Library**: Container format for ML workloads
- **Model Converter**: TOSA to VGF converter
- **Scenario Runner**: Test runner for ML scenarios
- **Emulation Layer**: Software implementation of Vulkan ML extensions

## Build Output Location

All build artifacts will be in the `build/` directory:
- `build/model-converter/model-converter` - Model conversion tool
- `build/scenario-runner/scenario-runner` - Scenario execution tool
- `build/vgf-lib/vgf_dump/vgf_dump` - VGF inspection tool
- `build/emulation-layer/layers/` - Vulkan emulation layer

## Troubleshooting

If the build fails:
1. Check that all dependencies are properly initialized:
   ```bash
   cd dependencies/glslang && git submodule update --init --recursive
   cd ../tosa_mlir_translator && git submodule update --init --recursive
   ```

2. Ensure you have sufficient disk space (the build requires several GB)

3. If LLVM build fails, you can try using a pre-built LLVM:
   ```bash
   python3 ./scripts/build.py --external-llvm /path/to/llvm --skip-llvm-patch
   ```

## Next Steps

After successful build:
1. Review the [ML_SDK_COMPREHENSIVE_GUIDE.md](ML_SDK_COMPREHENSIVE_GUIDE.md) for detailed usage
2. Try the tutorials in `docs/source/tutorial.rst`
3. Run example models from the documentation

## Common Issues

- **Memory**: Building LLVM requires significant RAM (8GB+ recommended)
- **Time**: Full build can take 30-60 minutes depending on your system
- **macOS**: Ensure Xcode command line tools are installed
- **Vulkan**: Install Vulkan SDK for full functionality