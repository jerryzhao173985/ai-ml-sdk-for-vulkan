#!/bin/bash
# Script to fix Scenario Runner ML types for macOS

SDK_ROOT="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan"
SR_SRC="$SDK_ROOT/sw/scenario-runner/src"

echo "Fixing Scenario Runner ML types..."

# Create a compatibility header that maps types
cat > "$SR_SRC/vulkan_ml_compat.hpp" << 'EOF'
#pragma once

#define VK_ENABLE_BETA_EXTENSIONS 1
#include <vulkan/vulkan.h>

// Create namespace aliases for missing C++ types
namespace vk {
    // Basic type mappings
    using Device = VkDevice;
    using Format = VkFormat;
    using DeviceMemory = VkDeviceMemory;
    using DeviceSize = VkDeviceSize;
    
    // ML extension types
    struct TensorARM {
        VkTensorARM handle;
        operator VkTensorARM() const { return handle; }
    };
    
    struct TensorViewARM {
        VkTensorViewARM handle;
        operator VkTensorViewARM() const { return handle; }
    };
    
    struct TensorCreateInfoARM : VkTensorCreateInfoARM {
        TensorCreateInfoARM(VkTensorCreateFlagsARM flags, 
                           const VkTensorDescriptionARM* desc,
                           VkSharingMode mode) {
            sType = VK_STRUCTURE_TYPE_TENSOR_CREATE_INFO_ARM;
            pNext = nullptr;
            this->flags = flags;
            pDescription = desc;
            sharingMode = mode;
            queueFamilyIndexCount = 0;
            pQueueFamilyIndices = nullptr;
        }
    };
    
    struct TensorDescriptionARM : VkTensorDescriptionARM {
        TensorDescriptionARM(VkTensorTilingARM til, VkFormat fmt, 
                            uint32_t dimCount, const int64_t* dims,
                            const int64_t* strides, VkTensorUsageFlagsARM use) {
            tiling = til;
            format = fmt;
            dimensionCount = dimCount;
            pDimensions = dims;
            pStrides = strides;
            usage = use;
        }
    };
    
    struct TensorMemoryBarrierARM : VkTensorMemoryBarrierARM {
        TensorMemoryBarrierARM() {
            sType = VK_STRUCTURE_TYPE_TENSOR_MEMORY_BARRIER_ARM;
            pNext = nullptr;
        }
    };
    
    struct BindTensorMemoryInfoARM : VkBindTensorMemoryInfoARM {
        BindTensorMemoryInfoARM(VkTensorARM t, VkDeviceMemory m, VkDeviceSize o) {
            sType = VK_STRUCTURE_TYPE_BIND_TENSOR_MEMORY_INFO_ARM;
            pNext = nullptr;
            tensor = t;
            memory = m;
            memoryOffset = o;
        }
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
    using TensorViewCreateFlagsARM = VkTensorViewCreateFlagsARM;
    
    // Structure type constants
    namespace StructureType {
        static constexpr VkStructureType eTensorCreateInfoARM = VK_STRUCTURE_TYPE_TENSOR_CREATE_INFO_ARM;
        static constexpr VkStructureType eTensorMemoryBarrierARM = VK_STRUCTURE_TYPE_TENSOR_MEMORY_BARRIER_ARM;
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
    
    // RAII namespace
    namespace raii {
        class Device {
            VkDevice device;
        public:
            Device(VkDevice d) : device(d) {}
            
            // ML extension functions
            void bindTensorMemoryARM(const BindTensorMemoryInfoARM& info) {
                vkBindTensorMemoryARM(device, 1, &info);
            }
            
            VkMemoryRequirements2 getTensorMemoryRequirementsARM(const VkTensorMemoryRequirementsInfoARM& info) {
                VkMemoryRequirements2 reqs = {};
                reqs.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
                vkGetDeviceTensorMemoryRequirementsARM(device, &info, &reqs);
                return reqs;
            }
        };
        
        class TensorARM {
            VkDevice device;
            VkTensorARM tensor;
        public:
            TensorARM(const Device& d, const TensorCreateInfoARM& info) {
                device = d;
                vkCreateTensorARM(device, &info, nullptr, &tensor);
            }
            ~TensorARM() {
                if (tensor) vkDestroyTensorARM(device, tensor, nullptr);
            }
            operator VkTensorARM() const { return tensor; }
            VkTensorARM operator*() const { return tensor; }
        };
        
        class TensorViewARM {
            VkDevice device;
            VkTensorViewARM view;
        public:
            TensorViewARM(const Device& d, const VkTensorViewCreateInfoARM& info) {
                device = d;
                vkCreateTensorViewARM(device, &info, nullptr, &view);
            }
            ~TensorViewARM() {
                if (view) vkDestroyTensorViewARM(device, view, nullptr);
            }
            operator VkTensorViewARM() const { return view; }
            VkTensorViewARM operator*() const { return view; }
        };
    }
    
    // Helper to create ArrayProxy
    template<typename T>
    class ArrayProxy {
        const T* data;
        size_t size;
    public:
        ArrayProxy(const T& single) : data(&single), size(1) {}
        ArrayProxy(const std::vector<T>& vec) : data(vec.data()), size(vec.size()) {}
        const T* begin() const { return data; }
        const T* end() const { return data + size; }
        size_t size() const { return size; }
    };
}

// Now include the standard Vulkan headers
#include <vulkan/vulkan.hpp>
EOF

# Replace includes in all source files
find "$SR_SRC" -name "*.cpp" -o -name "*.hpp" | while read file; do
    # Skip our compat file
    if [[ "$file" == *"vulkan_ml_compat.hpp"* ]]; then
        continue
    fi
    
    # Create backup
    cp "$file" "$file.bak"
    
    # Replace vulkan includes
    sed -i '' '/#include.*vulkan.*raii\.hpp/c\
#include "vulkan_ml_compat.hpp"' "$file"
    
    sed -i '' '/#include.*<vulkan\/vulkan.*hpp>/c\
#include "vulkan_ml_compat.hpp"' "$file"
done

echo "✓ Scenario Runner types fixed for macOS"