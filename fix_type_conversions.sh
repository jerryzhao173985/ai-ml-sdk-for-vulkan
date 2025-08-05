#!/bin/bash
# Fix type conversion issues in Scenario Runner

SDK_ROOT="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan"

echo "Fixing type conversion issues..."

# Fix barrier.cpp enum conversions
sed -i '' 's/vk::StructureType::/static_cast<VkStructureType>(vk::StructureType::/g' "$SDK_ROOT/sw/scenario-runner/src/barrier.cpp"
sed -i '' 's/vk::ImageAspectFlagBits::/static_cast<VkImageAspectFlags>(vk::ImageAspectFlagBits::/g' "$SDK_ROOT/sw/scenario-runner/src/barrier.cpp"
sed -i '' 's/convertImageLayout(/static_cast<VkImageLayout>(convertImageLayout(/g' "$SDK_ROOT/sw/scenario-runner/src/barrier.cpp"

# Add closing parentheses for the casts
sed -i '' 's/eImageMemoryBarrier2;/eImageMemoryBarrier2);/g' "$SDK_ROOT/sw/scenario-runner/src/barrier.cpp"
sed -i '' 's/eTensorMemoryBarrierARM;/eTensorMemoryBarrierARM);/g' "$SDK_ROOT/sw/scenario-runner/src/barrier.cpp"
sed -i '' 's/eMemoryBarrier;/eMemoryBarrier);/g' "$SDK_ROOT/sw/scenario-runner/src/barrier.cpp"
sed -i '' 's/eBufferMemoryBarrier2;/eBufferMemoryBarrier2);/g' "$SDK_ROOT/sw/scenario-runner/src/barrier.cpp"
sed -i '' 's/eColor;/eColor);/g' "$SDK_ROOT/sw/scenario-runner/src/barrier.cpp"
sed -i '' 's/oldLayout));/oldLayout)));/g' "$SDK_ROOT/sw/scenario-runner/src/barrier.cpp"
sed -i '' 's/newLayout));/newLayout)));/g' "$SDK_ROOT/sw/scenario-runner/src/barrier.cpp"

# Fix dds_reader.cpp format conversion
sed -i '' 's/vgflib::ToFormatType(vkFormat)/vgflib::ToFormatType(static_cast<VkFormat>(vkFormat))/g' "$SDK_ROOT/sw/scenario-runner/src/dds_reader.cpp"

echo "✓ Fixed type conversions"