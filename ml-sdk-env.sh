#!/bin/bash
# Source this file to set up ML SDK environment

export ML_SDK_ROOT="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan"
export ML_SDK_BUILD="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/build-macos-complete"

# Add tools to PATH
export PATH="$ML_SDK_BUILD/vgf-lib/vgf_dump:$PATH"
export PATH="$ML_SDK_BUILD/flatbuffers:$PATH"
export PATH="$ML_SDK_BUILD/spirv-tools/tools:$PATH"
export PATH="$ML_SDK_BUILD/glslang/StandAlone:$PATH"

# Aliases for convenience
alias vgf-dump="$ML_SDK_BUILD/vgf-lib/vgf_dump/vgf_dump"
alias ml-flatc="$ML_SDK_BUILD/flatbuffers/flatc"

echo "ML SDK environment loaded!"
echo "Available tools:"
echo "  - vgf-dump: Dump VGF file contents"
echo "  - ml-flatc: FlatBuffers compiler"
echo "  - spirv-opt: SPIR-V optimizer"
echo "  - spirv-dis: SPIR-V disassembler"
echo "  - glslangValidator: GLSL validator"
