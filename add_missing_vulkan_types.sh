#!/bin/bash
# Add missing Vulkan types to compatibility header

COMPAT_HPP="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/scenario-runner/src/compat/vulkan_full_compat.hpp"

# Add missing enum types after the existing enums
sed -i '' '/using Result = VkResult;/a\
    using Filter = VkFilter;\
    using SamplerMipmapMode = VkSamplerMipmapMode;\
    using SamplerAddressMode = VkSamplerAddressMode;\
    using BorderColor = VkBorderColor;\
    using ImageTiling = VkImageTiling;\
    using ImageType = VkImageType;\
    using ComponentSwizzle = VkComponentSwizzle;\
    using ImageViewType = VkImageViewType;\
    using CompareOp = VkCompareOp;\
    using PipelineBindPoint = VkPipelineBindPoint;\
    using DescriptorUpdateTemplate = VkDescriptorUpdateTemplate;\
    using ShaderStageFlags = VkShaderStageFlags;' "$COMPAT_HPP"

echo "✓ Added missing Vulkan enum types"