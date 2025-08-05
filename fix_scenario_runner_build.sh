#!/bin/bash
# Fix Scenario Runner build issues for macOS

SDK_ROOT="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan"
BUILD_ROOT="/Users/jerry/Vulkan/ml-sdk-macos-build"

echo "Fixing Scenario Runner build issues..."

# 1. Fix numpy.cpp type mismatches
echo "Fixing numpy.cpp type mismatches..."
cat > "$SDK_ROOT/sw/scenario-runner/src/numpy_compat.patch" << 'EOF'
--- a/sw/scenario-runner/src/numpy.cpp
+++ b/sw/scenario-runner/src/numpy.cpp
@@ -19,6 +19,11 @@
 
 namespace {
 
+// Overload for size_t
+std::string shape_to_str(const std::vector<size_t> &shape) {
+    std::vector<uint64_t> shape64(shape.begin(), shape.end());
+    return shape_to_str(shape64);
+}
 std::string shape_to_str(const std::vector<uint64_t> &shape) {
     std::ostringstream out;
     out << "(";
@@ -97,6 +102,12 @@
     return info.str();
 }
 
+// Overload for uint64_t
+void write_header(std::ostream &out, const std::vector<uint64_t> &shape, const std::string &dtype) {
+    std::vector<size_t> shape_size(shape.begin(), shape.end());
+    write_header(out, shape_size, dtype);
+}
+
 void write_header(std::ostream &out, const std::vector<size_t> &shape, const std::string &dtype) {
     std::ostringstream header_dict;
     header_dict << "{'descr': '" << dtype << "', 'fortran_order': False, ";
EOF

patch -p1 -d "$SDK_ROOT" < "$SDK_ROOT/sw/scenario-runner/src/numpy_compat.patch" || true

# 2. Fix glslang missing headers
echo "Fixing glslang headers..."
if [ ! -d "$BUILD_ROOT/install/include/glslang/StandAlone" ]; then
    echo "Copying missing StandAlone headers..."
    mkdir -p "$BUILD_ROOT/install/include/glslang/StandAlone"
    cp -r "$SDK_ROOT/dependencies/glslang/StandAlone"/*.h "$BUILD_ROOT/install/include/glslang/StandAlone/" 2>/dev/null || true
fi

# 3. Create better ML extensions compatibility header
echo "Creating improved ML extensions header..."
cat > "$SDK_ROOT/sw/scenario-runner/src/compat/vulkan_ml_compat.hpp" << 'EOF'
#pragma once

// Define beta extensions before including headers
#ifndef VK_ENABLE_BETA_EXTENSIONS
#define VK_ENABLE_BETA_EXTENSIONS 1
#endif

// Force use of SDK headers with ML extensions
#include "vulkan/vulkan_core.h"
#include "vulkan/vulkan_beta.h"

// Don't include system vulkan.hpp - it conflicts with SDK version
#ifdef VULKAN_HPP
#error "System vulkan.hpp already included - ML extensions require SDK headers"
#endif

// Create minimal C++ bindings for ML extensions
namespace vk {
    // Basic handle types
    struct TensorARM { 
        VkTensorARM handle; 
        operator VkTensorARM() const { return handle; }
    };
    
    struct TensorViewARM { 
        VkTensorViewARM handle;
        operator VkTensorViewARM() const { return handle; }
    };
    
    // Enums
    enum class TensorTilingARM : uint32_t {
        eOptimal = VK_TENSOR_TILING_OPTIMAL_ARM,
        eLinear = VK_TENSOR_TILING_LINEAR_ARM
    };
    
    enum class TensorUsageFlagBitsARM : VkTensorUsageFlagsARM {
        eShader = VK_TENSOR_USAGE_SHADER_BIT_ARM,
        eTransferSrc = VK_TENSOR_USAGE_TRANSFER_SRC_BIT_ARM,
        eTransferDst = VK_TENSOR_USAGE_TRANSFER_DST_BIT_ARM,
        eDataGraph = VK_TENSOR_USAGE_DATA_GRAPH_BIT_ARM
    };
    
    using TensorUsageFlagsARM = VkTensorUsageFlagsARM;
    using TensorCreateFlagsARM = VkTensorCreateFlagsARM;
    
    // Structure types
    namespace StructureType {
        static constexpr VkStructureType eTensorCreateInfoARM = VK_STRUCTURE_TYPE_TENSOR_CREATE_INFO_ARM;
        static constexpr VkStructureType eTensorMemoryBarrierARM = VK_STRUCTURE_TYPE_TENSOR_MEMORY_BARRIER_ARM;
        static constexpr VkStructureType eBindTensorMemoryInfoARM = VK_STRUCTURE_TYPE_BIND_TENSOR_MEMORY_INFO_ARM;
    }
    
    // Access flags
    namespace AccessFlagBits2 {
        static constexpr VkAccessFlags2 eDataGraphWriteARM = VK_ACCESS_2_DATA_GRAPH_WRITE_BIT_ARM;
        static constexpr VkAccessFlags2 eDataGraphReadARM = VK_ACCESS_2_DATA_GRAPH_READ_BIT_ARM;
    }
    
    // Pipeline stages
    namespace PipelineStageFlagBits2 {
        static constexpr VkPipelineStageFlags2 eDataGraphARM = VK_PIPELINE_STAGE_2_DATA_GRAPH_BIT_ARM;
    }
    
    // Image layouts
    namespace ImageLayout {
        static constexpr VkImageLayout eTensorAliasingARM = VK_IMAGE_LAYOUT_TENSOR_ALIASING_ARM;
    }
    
    // Structure wrappers
    struct TensorCreateInfoARM : VkTensorCreateInfoARM {
        TensorCreateInfoARM() {
            sType = VK_STRUCTURE_TYPE_TENSOR_CREATE_INFO_ARM;
            pNext = nullptr;
        }
    };
    
    struct TensorMemoryBarrierARM : VkTensorMemoryBarrierARM {
        TensorMemoryBarrierARM() {
            sType = VK_STRUCTURE_TYPE_TENSOR_MEMORY_BARRIER_ARM;
            pNext = nullptr;
        }
    };
    
    struct BindTensorMemoryInfoARM : VkBindTensorMemoryInfoARM {
        BindTensorMemoryInfoARM() {
            sType = VK_STRUCTURE_TYPE_BIND_TENSOR_MEMORY_INFO_ARM;
            pNext = nullptr;
        }
    };
    
    // RAII namespace for device operations
    namespace raii {
        class Device {
            VkDevice device;
        public:
            Device(VkDevice d) : device(d) {}
            operator VkDevice() const { return device; }
            
            void bindTensorMemoryARM(uint32_t bindInfoCount, const VkBindTensorMemoryInfoARM* pBindInfos) {
                vkBindTensorMemoryARM(device, bindInfoCount, pBindInfos);
            }
        };
    }
}

// Include minimal vulkan.hpp functionality needed
#include <vector>
#include <string>
#include <array>

namespace vk {
    // ArrayProxy replacement
    template<typename T>
    class ArrayProxy {
        const T* ptr;
        std::size_t count;
    public:
        ArrayProxy(const T& single) : ptr(&single), count(1) {}
        ArrayProxy(const std::vector<T>& vec) : ptr(vec.data()), count(vec.size()) {}
        ArrayProxy(const T* data, std::size_t size) : ptr(data), count(size) {}
        
        const T* data() const { return ptr; }
        std::size_t size() const { return count; }
        const T* begin() const { return ptr; }
        const T* end() const { return ptr + count; }
    };
    
    // Common types
    using Device = VkDevice;
    using DeviceMemory = VkDeviceMemory;
    using DeviceSize = VkDeviceSize;
    using Format = VkFormat;
    using SharingMode = VkSharingMode;
    
    static constexpr SharingMode SharingModeExclusive = VK_SHARING_MODE_EXCLUSIVE;
    static constexpr SharingMode SharingModeConcurrent = VK_SHARING_MODE_CONCURRENT;
}
EOF

# 4. Update includes in scenario runner files
echo "Updating includes..."
find "$SDK_ROOT/sw/scenario-runner/src" -name "*.cpp" -o -name "*.hpp" | while read file; do
    # Skip our compatibility files
    if [[ "$file" == *"vulkan_ml_compat.hpp"* ]] || [[ "$file" == *"ml_extensions.hpp"* ]]; then
        continue
    fi
    
    # Replace vulkan includes with our compatibility header
    sed -i.bak 's|#include.*"compat/ml_extensions.hpp"|#include "compat/vulkan_ml_compat.hpp"|g' "$file"
    sed -i.bak 's|#include.*<vulkan/vulkan_raii.hpp>|#include "compat/vulkan_ml_compat.hpp"|g' "$file"
    sed -i.bak 's|#include.*<vulkan/vulkan.hpp>|#include "compat/vulkan_ml_compat.hpp"|g' "$file"
    
    # Clean up backup files
    rm -f "$file.bak"
done

echo "✓ Scenario Runner fixes applied"