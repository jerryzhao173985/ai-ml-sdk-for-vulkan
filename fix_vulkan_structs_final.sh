#!/bin/bash
# Final comprehensive fix for vulkan_structs.hpp

STRUCTS_FILE="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/dependencies/Vulkan-Headers/include/vulkan/vulkan_structs.hpp"

echo "Applying final fixes to vulkan_structs.hpp..."

# Fix remaining GeometryTypeKHR references
sed -i '' 's/( GeometryTypeKHR /( vk::GeometryTypeKHR /g' "$STRUCTS_FILE"
sed -i '' 's/: GeometryTypeKHR::/: vk::GeometryTypeKHR::/g' "$STRUCTS_FILE"

# Fix GeometryFlagsKHR references
sed -i '' 's/( GeometryFlagsKHR /( vk::GeometryFlagsKHR /g' "$STRUCTS_FILE"

# Fix member variable declarations
sed -i '' 's/^    GeometryTypeKHR /    vk::GeometryTypeKHR /g' "$STRUCTS_FILE"
sed -i '' 's/^    GeometryFlagsKHR /    vk::GeometryFlagsKHR /g' "$STRUCTS_FILE"

# Fix parameter types
sed -i '' 's/& setGeometryType( GeometryTypeKHR /\& setGeometryType( vk::GeometryTypeKHR /g' "$STRUCTS_FILE"
sed -i '' 's/& setFlags( GeometryFlagsKHR /\& setFlags( vk::GeometryFlagsKHR /g' "$STRUCTS_FILE"

# Fix any double vk:: that might have been created
sed -i '' 's/vk::vk::/vk::/g' "$STRUCTS_FILE"

echo "✓ Applied final fixes to vulkan_structs.hpp"