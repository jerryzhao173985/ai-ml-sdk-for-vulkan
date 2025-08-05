#pragma once

// Vulkan ML Extensions Compatibility Wrapper for macOS
// This header provides the missing ML extension types for macOS builds

#define VK_ENABLE_BETA_EXTENSIONS 1

#include <vulkan/vulkan.h>

// If the C++ types are not available, create compatibility wrappers
#ifndef VULKAN_HPP_DISABLE_ENHANCED_MODE

namespace vk {

// Forward declarations for missing types on macOS
#ifndef VK_ARM_tensors
    using TensorARM = VkTensorARM;
    using TensorViewARM = VkTensorViewARM;
    using TensorCreateInfoARM = VkTensorCreateInfoARM;
    using TensorViewCreateInfoARM = VkTensorViewCreateInfoARM;
    using TensorMemoryBarrierARM = VkTensorMemoryBarrierARM;
    using TensorDescriptionARM = VkTensorDescriptionARM;
    using TensorMemoryRequirementsInfoARM = VkTensorMemoryRequirementsInfoARM;
    using BindTensorMemoryInfoARM = VkBindTensorMemoryInfoARM;
    using TensorUsageFlagsARM = VkTensorUsageFlagsARM;
    using TensorCreateFlagsARM = VkTensorCreateFlagsARM;
    using TensorViewCreateFlagsARM = VkTensorViewCreateFlagsARM;
    using TensorTilingARM = VkTensorTilingARM;
    using TensorCopyARM = VkTensorCopyARM;
    using CopyTensorInfoARM = VkCopyTensorInfoARM;
    
    // Enum mappings
    enum class TensorUsageFlagBitsARM : VkTensorUsageFlagsARM {
        eShader = VK_TENSOR_USAGE_SHADER_BIT_ARM,
        eTransferSrc = VK_TENSOR_USAGE_TRANSFER_SRC_BIT_ARM,
        eTransferDst = VK_TENSOR_USAGE_TRANSFER_DST_BIT_ARM,
        eDataGraph = VK_TENSOR_USAGE_DATA_GRAPH_BIT_ARM
    };
    
    enum class TensorTilingARM : uint32_t {
        eOptimal = VK_TENSOR_TILING_OPTIMAL_ARM,
        eLinear = VK_TENSOR_TILING_LINEAR_ARM
    };
    
    // Structure type extensions
    namespace StructureType {
        static constexpr VkStructureType eTensorCreateInfoARM = VK_STRUCTURE_TYPE_TENSOR_CREATE_INFO_ARM;
        static constexpr VkStructureType eTensorMemoryBarrierARM = VK_STRUCTURE_TYPE_TENSOR_MEMORY_BARRIER_ARM;
        static constexpr VkStructureType eTensorViewCreateInfoARM = VK_STRUCTURE_TYPE_TENSOR_VIEW_CREATE_INFO_ARM;
        static constexpr VkStructureType eTensorMemoryRequirementsInfoARM = VK_STRUCTURE_TYPE_TENSOR_MEMORY_REQUIREMENTS_INFO_ARM;
        static constexpr VkStructureType eBindTensorMemoryInfoARM = VK_STRUCTURE_TYPE_BIND_TENSOR_MEMORY_INFO_ARM;
    }
    
    // Access flags
    namespace AccessFlagBits2 {
        static constexpr VkAccessFlags2 eDataGraphWriteARM = VK_ACCESS_2_DATA_GRAPH_WRITE_BIT_ARM;
        static constexpr VkAccessFlags2 eDataGraphReadARM = VK_ACCESS_2_DATA_GRAPH_READ_BIT_ARM;
    }
    
    // Pipeline stage flags
    namespace PipelineStageFlagBits2 {
        static constexpr VkPipelineStageFlags2 eDataGraphARM = VK_PIPELINE_STAGE_2_DATA_GRAPH_BIT_ARM;
    }
    
    // Image layout
    namespace ImageLayout {
        static constexpr VkImageLayout eTensorAliasingARM = VK_IMAGE_LAYOUT_TENSOR_ALIASING_ARM;
    }
    
    // RAII wrappers for macOS
    namespace raii {
        class TensorARM {
            VkDevice device;
            VkTensorARM tensor;
            
        public:
            TensorARM(const vk::Device& dev, const VkTensorCreateInfoARM& createInfo) : device(dev) {
                vkCreateTensorARM(device, &createInfo, nullptr, &tensor);
            }
            
            ~TensorARM() {
                if (tensor) {
                    vkDestroyTensorARM(device, tensor, nullptr);
                }
            }
            
            operator VkTensorARM() const { return tensor; }
            VkTensorARM operator*() const { return tensor; }
        };
        
        class TensorViewARM {
            VkDevice device;
            VkTensorViewARM tensorView;
            
        public:
            TensorViewARM(const vk::Device& dev, const VkTensorViewCreateInfoARM& createInfo) : device(dev) {
                vkCreateTensorViewARM(device, &createInfo, nullptr, &tensorView);
            }
            
            ~TensorViewARM() {
                if (tensorView) {
                    vkDestroyTensorViewARM(device, tensorView, nullptr);
                }
            }
            
            operator VkTensorViewARM() const { return tensorView; }
            VkTensorViewARM operator*() const { return tensorView; }
        };
    }
#endif // VK_ARM_tensors

} // namespace vk

#endif // VULKAN_HPP_DISABLE_ENHANCED_MODE

// Helper macros for easier migration
#define VK_ML_EXTENSIONS_AVAILABLE 1

// Include standard Vulkan C++ header after our definitions
#include <vulkan/vulkan.hpp>