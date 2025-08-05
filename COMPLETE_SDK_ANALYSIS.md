# Complete Vulkan AI SDK Analysis Report

## Available Repositories and Components

### ai-ml-sdk-for-vulkan

**Built Artifacts:**
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/scripts/build.py
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/scripts/build.py.bak
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/build/llvm/bin/llvm-min-tblgen
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/build/llvm/bin/mlir-tblgen
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/build/llvm/bin/mlir-linalg-ods-yaml-gen
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/build/llvm/bin/update_core_linalg_named_ops.sh
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/build/llvm/bin/llvm-lit
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/build/llvm/lib/libMLIRDestinationStyleOpInterface.a
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/build/llvm/lib/libLLVMAnalysis.a
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/build/llvm/lib/libMLIRPass.a

**ML Models/Data:**
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/dependencies/llvm-project/llvm/unittests/Analysis/Inputs/ir2native_x86_64_model/model.tflite
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/dependencies/tosa_mlir_translator/third_party/serialization_lib/test/examples/test_add_1x4x4x4_f32.tosa

**Shaders:**
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/scenario-runner/src/tests/resources/shaders/test_tensor_aliasing/copy_img_shader.comp
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/scenario-runner/src/tests/resources/shaders/test_tensor_aliasing/copy_tensor_shader.comp
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/scenario-runner/src/tests/resources/shaders/test_tensor_aliasing/plus_ten_tensor.comp
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/scenario-runner/src/tests/resources/shaders/test_spec_const/uint_shader.comp
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/scenario-runner/src/tests/resources/shaders/test_spec_const/float_shader.comp

**Scenarios/Tests:**
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/test/json/rescale.json
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/test/json/double_custom.json
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/test/json/add.json
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/test/json/custom.json
/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/model-converter/test/json/rescale_input_signed.json

---

### ai-ml-emulation-layer-for-vulkan

**Built Artifacts:**
/Users/jerry/Vulkan/ai-ml-emulation-layer-for-vulkan/build/spirv-cross/libspirv-cross-glsl.a
/Users/jerry/Vulkan/ai-ml-emulation-layer-for-vulkan/build/spirv-cross/libspirv-cross-core.a
/Users/jerry/Vulkan/ai-ml-emulation-layer-for-vulkan/build/spirv-tools/source/libSPIRV-Tools.a
/Users/jerry/Vulkan/ai-ml-emulation-layer-for-vulkan/build/glslang/glslang/libglslang-default-resource-limits.a
/Users/jerry/Vulkan/ai-ml-emulation-layer-for-vulkan/build/lib/libgtest_main.a
/Users/jerry/Vulkan/ai-ml-emulation-layer-for-vulkan/build/lib/libgtest.a

**ML Models/Data:**

**Shaders:**
/Users/jerry/Vulkan/ai-ml-emulation-layer-for-vulkan/graph/tosa/mul.comp
/Users/jerry/Vulkan/ai-ml-emulation-layer-for-vulkan/graph/tosa/conv2d.comp
/Users/jerry/Vulkan/ai-ml-emulation-layer-for-vulkan/graph/tosa/rfft2d.comp
/Users/jerry/Vulkan/ai-ml-emulation-layer-for-vulkan/graph/tosa/select.comp
/Users/jerry/Vulkan/ai-ml-emulation-layer-for-vulkan/graph/tosa/tile.comp

**Scenarios/Tests:**

---

### ai-ml-sdk-manifest

**Built Artifacts:**

**ML Models/Data:**

**Shaders:**

**Scenarios/Tests:**

---

### ai-ml-sdk-model-converter

**Built Artifacts:**
/Users/jerry/Vulkan/ai-ml-sdk-model-converter/scripts/build.py

**ML Models/Data:**

**Shaders:**

**Scenarios/Tests:**
/Users/jerry/Vulkan/ai-ml-sdk-model-converter/test/json/rescale.json
/Users/jerry/Vulkan/ai-ml-sdk-model-converter/test/json/double_custom.json
/Users/jerry/Vulkan/ai-ml-sdk-model-converter/test/json/add.json
/Users/jerry/Vulkan/ai-ml-sdk-model-converter/test/json/custom.json
/Users/jerry/Vulkan/ai-ml-sdk-model-converter/test/json/rescale_input_signed.json

---

### ai-ml-sdk-scenario-runner

**Built Artifacts:**
/Users/jerry/Vulkan/ai-ml-sdk-scenario-runner/scripts/build.py

**ML Models/Data:**

**Shaders:**
/Users/jerry/Vulkan/ai-ml-sdk-scenario-runner/src/tests/resources/shaders/test_tensor_aliasing/copy_img_shader.comp
/Users/jerry/Vulkan/ai-ml-sdk-scenario-runner/src/tests/resources/shaders/test_tensor_aliasing/copy_tensor_shader.comp
/Users/jerry/Vulkan/ai-ml-sdk-scenario-runner/src/tests/resources/shaders/test_tensor_aliasing/plus_ten_tensor.comp
/Users/jerry/Vulkan/ai-ml-sdk-scenario-runner/src/tests/resources/shaders/test_spec_const/uint_shader.comp
/Users/jerry/Vulkan/ai-ml-sdk-scenario-runner/src/tests/resources/shaders/test_spec_const/float_shader.comp

**Scenarios/Tests:**
/Users/jerry/Vulkan/ai-ml-sdk-scenario-runner/src/tests/resources/scenarios/test_pipeline_cache/enable_pipeline_cache.json
/Users/jerry/Vulkan/ai-ml-sdk-scenario-runner/src/tests/resources/scenarios/test_tensor_aliasing/image_to_tensor_aliasing_no_compute.json
/Users/jerry/Vulkan/ai-ml-sdk-scenario-runner/src/tests/resources/scenarios/test_tensor_aliasing/image_to_tensor_aliasing_no_compute_8bit.json
/Users/jerry/Vulkan/ai-ml-sdk-scenario-runner/src/tests/resources/scenarios/test_tensor_aliasing/image_to_tensor_aliasing_copy_tensor_shader_copy_image_shader.json
/Users/jerry/Vulkan/ai-ml-sdk-scenario-runner/src/tests/resources/scenarios/test_tensor_aliasing/image_to_tensor_aliasing_copy_image_shader_copy_tensor_shader.json

---

### ai-ml-sdk-vgf-library

**Built Artifacts:**
/Users/jerry/Vulkan/ai-ml-sdk-vgf-library/scripts/build.py
/Users/jerry/Vulkan/ai-ml-sdk-vgf-library/scripts/generate_helpers.py
/Users/jerry/Vulkan/ai-ml-sdk-vgf-library/.git/hooks/commit-msg.sample
/Users/jerry/Vulkan/ai-ml-sdk-vgf-library/.git/hooks/pre-rebase.sample
/Users/jerry/Vulkan/ai-ml-sdk-vgf-library/.git/hooks/sendemail-validate.sample
/Users/jerry/Vulkan/ai-ml-sdk-vgf-library/.git/hooks/pre-commit.sample
/Users/jerry/Vulkan/ai-ml-sdk-vgf-library/.git/hooks/applypatch-msg.sample
/Users/jerry/Vulkan/ai-ml-sdk-vgf-library/.git/hooks/fsmonitor-watchman.sample
/Users/jerry/Vulkan/ai-ml-sdk-vgf-library/.git/hooks/pre-receive.sample
/Users/jerry/Vulkan/ai-ml-sdk-vgf-library/.git/hooks/prepare-commit-msg.sample

**ML Models/Data:**

**Shaders:**

**Scenarios/Tests:**

---

### ComputeLibrary

**Built Artifacts:**
/Users/jerry/Vulkan/ComputeLibrary/third_party/kleidiai/docker/build_linux_bootloader.sh

**ML Models/Data:**

**Shaders:**

**Scenarios/Tests:**

---

### ML-examples

**Built Artifacts:**

**ML Models/Data:**
/Users/jerry/Vulkan/ML-examples/armnn-style-transfer-android/app/assets/la_muse.tflite
/Users/jerry/Vulkan/ML-examples/armnn-style-transfer-android/app/assets/udnie.tflite
/Users/jerry/Vulkan/ML-examples/armnn-style-transfer-android/app/assets/mirror.tflite
/Users/jerry/Vulkan/ML-examples/armnn-style-transfer-android/app/assets/des_glaneuses.tflite
/Users/jerry/Vulkan/ML-examples/armnn-style-transfer-android/app/assets/wave_crop.tflite

**Shaders:**

**Scenarios/Tests:**

---

### MoltenVK

**Built Artifacts:**
/Users/jerry/Vulkan/MoltenVK/Scripts/create_dylib_xros.sh
/Users/jerry/Vulkan/MoltenVK/Scripts/package_dylibs.sh
/Users/jerry/Vulkan/MoltenVK/Scripts/copy_ext_lib_to_staging.sh
/Users/jerry/Vulkan/MoltenVK/Scripts/create_ext_lib_xcframeworks.sh
/Users/jerry/Vulkan/MoltenVK/Scripts/package_ext_libs_finish.sh
/Users/jerry/Vulkan/MoltenVK/Scripts/copy_lib_to_staging.sh

**ML Models/Data:**

**Shaders:**

**Scenarios/Tests:**

---


## Compiled Dependencies

- glslang: ✓ Built
- googletest: ✓ Built
- SPIRV-Cross: ✓ Built
- SPIRV-Tools: ✓ Built
- Vulkan-Headers: ✓ Built

