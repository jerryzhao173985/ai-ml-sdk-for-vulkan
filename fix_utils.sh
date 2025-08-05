#!/bin/bash
# Fix utils.cpp issues

SDK_ROOT="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan"

echo "Fixing utils.cpp..."

# Fix ImageAspectFlagBits conversions
sed -i '' 's/return vk::ImageAspectFlagBits::/return static_cast<vk::ImageAspectFlags>(vk::ImageAspectFlagBits::/g' "$SDK_ROOT/sw/scenario-runner/src/utils.cpp"
sed -i '' 's/eDepth;/eDepth);/g' "$SDK_ROOT/sw/scenario-runner/src/utils.cpp"
sed -i '' 's/eColor;/eColor);/g' "$SDK_ROOT/sw/scenario-runner/src/utils.cpp"

# Fix ToFormatType calls
sed -i '' 's/vgflib::ToFormatType(format)/vgflib::ToFormatType(static_cast<VkFormat>(format))/g' "$SDK_ROOT/sw/scenario-runner/src/utils.cpp"

# Fix componentNumericFormat
sed -i '' 's/componentNumericFormat(/vk::componentNumericFormat(/g' "$SDK_ROOT/sw/scenario-runner/src/utils.cpp"

# Fix DeviceMemory constructor
sed -i '' 's/return vk::raii::DeviceMemory{ctx.device(), {size, index}};/return vk::raii::DeviceMemory{ctx.device(), vk::MemoryAllocateInfo{size, index}};/g' "$SDK_ROOT/sw/scenario-runner/src/utils.cpp"

echo "✓ Fixed utils.cpp"