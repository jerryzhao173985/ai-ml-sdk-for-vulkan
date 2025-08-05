#!/bin/bash
# Fix vulkan_structs.hpp namespace issues

STRUCTS_FILE="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/dependencies/Vulkan-Headers/include/vulkan/vulkan_structs.hpp"

echo "Creating backup of vulkan_structs.hpp..."
cp "$STRUCTS_FILE" "$STRUCTS_FILE.backup"

echo "Fixing namespace issues in vulkan_structs.hpp..."

# Add namespace prefix to types
sed -i '' 's/\bDeviceAddress\b/vk::DeviceAddress/g' "$STRUCTS_FILE"
sed -i '' 's/\bDeviceSize\b/vk::DeviceSize/g' "$STRUCTS_FILE"
sed -i '' 's/\bFormat\b/vk::Format/g' "$STRUCTS_FILE"
sed -i '' 's/\bIndexType\b/vk::IndexType/g' "$STRUCTS_FILE"
sed -i '' 's/\bStructureType\b/vk::StructureType/g' "$STRUCTS_FILE"

# Fix specific cases where vk:: was already present
sed -i '' 's/vk::vk::/vk::/g' "$STRUCTS_FILE"

echo "✓ Fixed vulkan_structs.hpp namespace issues"