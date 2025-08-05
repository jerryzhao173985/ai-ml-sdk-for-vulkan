# ML SDK for Vulkan® - Comprehensive Development Guide

## Table of Contents
1. [Overview](#overview)
2. [Architecture](#architecture)
3. [Components Deep Dive](#components-deep-dive)
4. [Development Workflow](#development-workflow)
5. [APIs Reference](#apis-reference)
6. [Practical Examples](#practical-examples)
7. [Advanced Topics](#advanced-topics)

## Overview

The ML SDK for Vulkan® is a comprehensive toolkit for deploying machine learning models using Vulkan's ML extensions. It provides a complete pipeline from model conversion to runtime execution.

### Key Features
- **TOSA to SPIR-V conversion**: Convert TOSA (Tensor Operator Set Architecture) models to Vulkan-compatible SPIR-V graphs
- **VGF Container Format**: Efficient packaging format for ML workloads including graphs, shaders, and constant data
- **Hardware Abstraction**: Run ML workloads on any Vulkan-capable GPU
- **Emulation Layer**: Software implementation for development and testing

### Use Cases
- Game AI inference (NPCs, procedural generation)
- Real-time image processing (filters, effects)
- Computer vision tasks (object detection, segmentation)
- Audio processing (noise reduction, voice synthesis)

## Architecture

### Component Hierarchy

```
ML SDK for Vulkan
├── Model Converter
│   ├── TOSA → SPIR-V Compiler
│   ├── Graph Optimizer
│   └── VGF Packager
├── VGF Library
│   ├── Encoder API
│   ├── Decoder API
│   └── VGF Dump Tool
├── Scenario Runner
│   ├── JSON Parser
│   ├── Vulkan Runtime
│   └── Test Framework
└── Emulation Layer
    ├── TOSA Implementation
    └── Vulkan Layer Interface
```

### Data Flow

```
Framework Model (PyTorch/TensorFlow)
       ↓ (Framework → TOSA converter)
    TOSA Model (.tosa)
       ↓ (Model Converter)
    VGF File (.vgf)
       ↓ (VGF Library)
   Vulkan API Calls
       ↓ (GPU/Emulation Layer)
    Inference Results
```

## Components Deep Dive

### 1. Model Converter

**Purpose**: Transforms TOSA models into Vulkan-compatible SPIR-V graphs packaged in VGF format.

**Key Features**:
- MLIR-based transformation pipeline
- Graph optimization passes
- Static shape inference
- Custom shader integration

**Command Line Usage**:
```bash
# Basic conversion
model-converter --input model.tosa --output model.vgf

# With optimization
model-converter --input model.tosa --output model.vgf --optimize

# With custom shaders
model-converter --input model.tosa --output model.vgf --shader custom.glsl

# Require static shapes
model-converter --input model.tosa --output model.vgf --require-static-shape
```

**Internal Pipeline**:
1. TOSA parsing and validation
2. MLIR lowering to intermediate representation
3. Graph optimization (fusion, constant folding)
4. SPIR-V code generation
5. VGF packaging with metadata

### 2. VGF Library

**Purpose**: Container format library for efficient storage and loading of ML workloads.

**VGF File Structure**:
```
VGF File
├── Header
│   ├── Magic Number
│   ├── Version
│   └── Metadata
├── Graph Section
│   ├── SPIR-V Modules
│   ├── Pipeline Layouts
│   └── Descriptor Sets
├── Constant Data
│   ├── Weights
│   └── Biases
└── Resources
    ├── Custom Shaders
    └── Configuration
```

**C++ API Example**:
```cpp
// Encoder
vgf::Encoder encoder;
encoder.addGraph(spirvModule, pipelineLayout);
encoder.addConstantData(weightsBuffer, weightsSize);
encoder.writeToFile("model.vgf");

// Decoder
vgf::Decoder decoder("model.vgf");
auto graph = decoder.getGraph(0);
auto constants = decoder.getConstantData();
// Use memory-mapped access for efficiency
auto mappedData = decoder.getMemoryMappedConstant(0);
```

**VGF Dump Tool**:
```bash
# Extract graph information
vgf_dump --input model.vgf --dump-graphs

# Generate scenario template
vgf_dump --input model.vgf --output scenario.json --scenario-template

# Extract specific resources
vgf_dump --input model.vgf --extract-resource 0 --output resource.bin
```

### 3. Scenario Runner

**Purpose**: Data-driven test and validation tool for ML workloads.

**Scenario JSON Format**:
```json
{
  "version": "1.0",
  "resources": {
    "input_image": {
      "image": {
        "dims": [1, 640, 480, 4],
        "format": "VK_FORMAT_R32G32B32A32_SFLOAT",
        "shader_access": "readonly",
        "src": "input.dds",
        "uid": "input_image"
      }
    },
    "input_tensor": {
      "tensor": {
        "dims": [1, 480, 640, 4],
        "format": "VK_FORMAT_R32_SFLOAT",
        "shader_access": "readonly",
        "alias_target": {
          "resource_ref": "input_image"
        },
        "uid": "input_tensor"
      }
    },
    "output_tensor": {
      "tensor": {
        "dims": [1, 476, 636, 1],
        "format": "VK_FORMAT_R32_SFLOAT",
        "shader_access": "writeonly",
        "src": "output.npy",
        "uid": "output_tensor"
      }
    }
  },
  "graphs": [
    {
      "graph_ref": "main_graph",
      "bindings": {
        "input_0": "input_tensor",
        "output_0": "output_tensor"
      }
    }
  ]
}
```

**Command Line Usage**:
```bash
# Run scenario
scenario-runner --scenario test.json

# With validation layers
scenario-runner --scenario test.json --enable-validation

# Specify device
scenario-runner --scenario test.json --device-index 1

# Performance profiling
scenario-runner --scenario test.json --profile
```

### 4. Emulation Layer

**Purpose**: Software implementation of Vulkan ML extensions for development and testing.

**Features**:
- TOSA-compliant operator implementations
- Vulkan layer mechanism integration
- Debugging and profiling support
- Platform-independent execution

**Usage**:
```bash
# Enable emulation layer
export VK_INSTANCE_LAYERS=VK_LAYER_ML_emulation

# Run with emulation
scenario-runner --scenario test.json
```

## Development Workflow

### Complete End-to-End Example

#### Step 1: Create PyTorch Model
```python
import torch
import torch.nn as nn
from executorch.backends.arm.arm_backend import ArmCompileSpecBuilder
from executorch.backends.arm.tosa_partitioner import TOSAPartitioner

class MyModel(nn.Module):
    def __init__(self):
        super().__init__()
        self.conv1 = nn.Conv2d(3, 64, 3, padding=1)
        self.pool = nn.MaxPool2d(2, 2)
        self.conv2 = nn.Conv2d(64, 128, 3, padding=1)
        
    def forward(self, x):
        x = torch.relu(self.conv1(x))
        x = self.pool(x)
        x = torch.relu(self.conv2(x))
        return x

# Export to TOSA
model = MyModel().eval()
example_input = torch.randn(1, 3, 224, 224)

compile_spec = (
    ArmCompileSpecBuilder()
    .tosa_compile_spec("TOSA-1.0+FP")
    .dump_intermediate_artifacts_to(".")
    .build()
)
partitioner = TOSAPartitioner(compile_spec)
exported_program = torch.export.export_for_training(model, (example_input,))
# This generates model.tosa
```

#### Step 2: Convert to VGF
```bash
# Convert TOSA to VGF
model-converter --input model.tosa --output model.vgf

# Generate scenario template
vgf_dump --input model.vgf --output scenario.json --scenario-template
```

#### Step 3: Prepare Input Data
```python
import numpy as np
# Save test input
test_input = np.random.randn(1, 3, 224, 224).astype(np.float32)
np.save("input.npy", test_input)
```

#### Step 4: Configure Scenario
Edit `scenario.json`:
- Replace `TEMPLATE_PATH_TENSOR_INPUT_0` with `input.npy`
- Replace `TEMPLATE_PATH_TENSOR_OUTPUT_0` with `output.npy`

#### Step 5: Run Inference
```bash
# Run on GPU
scenario-runner --scenario scenario.json

# Run with emulation layer
export VK_INSTANCE_LAYERS=VK_LAYER_ML_emulation
scenario-runner --scenario scenario.json
```

#### Step 6: Process Results
```python
# Load and visualize results
output = np.load("output.npy")
print(f"Output shape: {output.shape}")
```

## APIs Reference

### Model Converter API

**Command Line Interface**:
```bash
model-converter [OPTIONS]

Required:
  --input FILE          Input TOSA file
  --output FILE         Output VGF file

Optional:
  --optimize            Enable optimization passes
  --require-static-shape Require static tensor shapes
  --shader FILE         Add custom shader
  --verbose             Verbose output
  --help                Show help
```

### VGF Library C++ API

**Core Classes**:

```cpp
namespace vgf {

class Encoder {
public:
    // Add graph with SPIR-V module
    void addGraph(const uint32_t* spirv, size_t size, 
                  const PipelineLayout& layout);
    
    // Add constant data (weights, biases)
    uint32_t addConstantData(const void* data, size_t size);
    
    // Add custom shader
    void addShader(const char* name, const uint32_t* spirv, size_t size);
    
    // Write to file
    void writeToFile(const char* filename);
};

class Decoder {
public:
    // Open VGF file
    explicit Decoder(const char* filename);
    
    // Get graph by index
    Graph getGraph(uint32_t index);
    
    // Get constant data
    ConstantData getConstantData(uint32_t index);
    
    // Memory-mapped access
    const void* getMemoryMappedConstant(uint32_t index);
};

} // namespace vgf
```

### Scenario Runner API

**JSON Schema**:
```typescript
interface Scenario {
  version: string;
  resources: {
    [key: string]: Resource;
  };
  graphs: GraphExecution[];
}

interface Resource {
  tensor?: TensorResource;
  image?: ImageResource;
}

interface TensorResource {
  dims: number[];
  format: string;
  shader_access: "readonly" | "writeonly" | "readwrite";
  src?: string;
  alias_target?: { resource_ref: string };
  uid: string;
}

interface GraphExecution {
  graph_ref: string;
  bindings: { [key: string]: string };
}
```

## Practical Examples

### Example 1: Image Filtering (Sobel Edge Detection)

```python
# 1. Create Sobel filter model
class SobelFilter(nn.Module):
    def __init__(self):
        super().__init__()
        # Sobel X kernel
        self.conv_x = nn.Conv2d(1, 1, 3, bias=False, padding=1)
        self.conv_x.weight.data = torch.tensor([
            [[-1, 0, 1],
             [-2, 0, 2],
             [-1, 0, 1]]
        ]).float().unsqueeze(0).unsqueeze(0)
        
        # Sobel Y kernel
        self.conv_y = nn.Conv2d(1, 1, 3, bias=False, padding=1)
        self.conv_y.weight.data = torch.tensor([
            [[-1, -2, -1],
             [ 0,  0,  0],
             [ 1,  2,  1]]
        ]).float().unsqueeze(0).unsqueeze(0)
    
    def forward(self, x):
        gx = self.conv_x(x)
        gy = self.conv_y(x)
        return torch.sqrt(gx**2 + gy**2)
```

### Example 2: Multi-Input Model

```python
# Model with multiple inputs
class MultiInputModel(nn.Module):
    def __init__(self):
        super().__init__()
        self.branch1 = nn.Linear(128, 64)
        self.branch2 = nn.Conv2d(3, 32, 3)
        self.combine = nn.Linear(64 + 32*30*30, 10)
    
    def forward(self, x1, x2):
        b1 = torch.relu(self.branch1(x1))
        b2 = torch.relu(self.branch2(x2))
        b2_flat = b2.view(b2.size(0), -1)
        combined = torch.cat([b1, b2_flat], dim=1)
        return self.combine(combined)
```

### Example 3: Custom Shader Integration

```glsl
// custom_activation.comp
#version 450

layout(set = 0, binding = 0) readonly buffer InputBuffer {
    float data[];
} input_buffer;

layout(set = 0, binding = 1) writeonly buffer OutputBuffer {
    float data[];
} output_buffer;

layout(push_constant) uniform PushConstants {
    uint total_elements;
} pc;

// Custom activation function
float custom_activation(float x) {
    return x * smoothstep(0.0, 1.0, x);
}

void main() {
    uint idx = gl_GlobalInvocationID.x;
    if (idx >= pc.total_elements) return;
    
    output_buffer.data[idx] = custom_activation(input_buffer.data[idx]);
}
```

## Advanced Topics

### 1. Performance Optimization

**Graph Optimization Techniques**:
- Operator fusion (Conv + ReLU → ConvReLU)
- Constant folding
- Dead code elimination
- Memory layout optimization

**Runtime Optimization**:
- Batch processing
- Asynchronous execution
- Memory pooling
- Pipeline caching

### 2. Debugging Techniques

**Validation Layers**:
```bash
# Enable all validation
export VK_INSTANCE_LAYERS=VK_LAYER_KHRONOS_validation:VK_LAYER_ML_emulation

# Run with debugging
scenario-runner --scenario test.json --enable-validation --log-level debug
```

**Intermediate Outputs**:
```python
# Save intermediate tensors
compile_spec = (
    ArmCompileSpecBuilder()
    .tosa_compile_spec("TOSA-1.0+FP")
    .dump_intermediate_artifacts_to("./debug")
    .build()
)
```

### 3. Memory Management

**Tensor Aliasing**:
```json
{
  "resources": {
    "shared_memory": {
      "tensor": {
        "dims": [1, 1024, 1024, 4],
        "format": "VK_FORMAT_R32_SFLOAT",
        "uid": "shared_memory"
      }
    },
    "view1": {
      "tensor": {
        "alias_target": {
          "resource_ref": "shared_memory",
          "offset": 0,
          "size": 4194304
        },
        "uid": "view1"
      }
    }
  }
}
```

### 4. Platform-Specific Considerations

**Linux**:
```bash
# Check Vulkan installation
vulkaninfo | grep -i "ml"

# Set library path
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/ml-sdk/lib
```

**Windows**:
```powershell
# Enable long paths for deep directory structures
Set-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\FileSystem" `
                 -Name "LongPathsEnabled" -Value 1

# Set environment
$env:VK_LAYER_PATH = "C:\ml-sdk\layers"
```

### 5. Integration with Game Engines

**Unity Integration Example**:
```csharp
public class MLInference : MonoBehaviour {
    private VGFDecoder decoder;
    private VulkanContext vulkanContext;
    
    void Start() {
        // Load VGF file
        decoder = new VGFDecoder("model.vgf");
        
        // Create Vulkan resources
        var graph = decoder.GetGraph(0);
        vulkanContext.CreatePipeline(graph);
    }
    
    void Update() {
        // Run inference
        var input = GetInputTensor();
        var output = vulkanContext.RunInference(input);
        ProcessOutput(output);
    }
}
```

### 6. Custom Operators

**Implementing Custom TOSA Operators**:
```cpp
// In emulation layer
class CustomOperator : public TosaOperator {
public:
    Status execute(const std::vector<Tensor>& inputs,
                   std::vector<Tensor>& outputs) override {
        // Custom implementation
        const auto& input = inputs[0];
        auto& output = outputs[0];
        
        // Process data
        for (size_t i = 0; i < input.size(); ++i) {
            output[i] = customFunction(input[i]);
        }
        
        return Status::OK;
    }
};
```

## Best Practices

### 1. Model Design
- Use static shapes when possible for better optimization
- Minimize dynamic memory allocation
- Batch operations for efficiency
- Consider quantization for performance

### 2. Development Workflow
- Start with emulation layer for rapid prototyping
- Profile early and often
- Use validation layers during development
- Test on target hardware regularly

### 3. Deployment
- Package resources efficiently in VGF
- Use memory-mapped I/O for large constants
- Implement proper error handling
- Cache compiled pipelines

### 4. Testing
- Create comprehensive scenario files
- Test edge cases (empty inputs, large batches)
- Validate numerical accuracy
- Benchmark performance

## Troubleshooting

### Common Issues

**1. Model Conversion Fails**
```bash
# Check TOSA validity
tosa-checker --input model.tosa

# Use verbose mode
model-converter --input model.tosa --output model.vgf --verbose
```

**2. Runtime Errors**
```bash
# Enable detailed logging
export VK_LOADER_DEBUG=all
scenario-runner --scenario test.json --log-level trace
```

**3. Performance Issues**
```bash
# Profile execution
scenario-runner --scenario test.json --profile --output-stats stats.json

# Analyze bottlenecks
python analyze_performance.py stats.json
```

## Summary

The ML SDK for Vulkan provides a complete solution for deploying ML models on Vulkan-capable hardware. Key takeaways:

1. **Model Converter**: Transforms TOSA models to optimized SPIR-V graphs
2. **VGF Library**: Efficient container format with memory-mapped I/O support
3. **Scenario Runner**: Flexible testing framework with JSON configuration
4. **Emulation Layer**: Software fallback for development and testing

The SDK enables efficient ML inference in graphics applications, games, and embedded systems while leveraging existing Vulkan infrastructure and tooling.