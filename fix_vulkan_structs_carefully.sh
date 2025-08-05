#!/bin/bash
# More careful fix for vulkan_structs.hpp

STRUCTS_FILE="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/dependencies/Vulkan-Headers/include/vulkan/vulkan_structs.hpp"

echo "Fixing namespace issues in vulkan_structs.hpp carefully..."

# Fix DeviceAddress references
sed -i '' 's/( DeviceAddress /( vk::DeviceAddress /g' "$STRUCTS_FILE"
sed -i '' 's/& setDeviceAddress( DeviceAddress /\& setDeviceAddress( vk::DeviceAddress /g' "$STRUCTS_FILE"

# Fix StructureType references  
sed -i '' 's/static VULKAN_HPP_CONST_OR_CONSTEXPR StructureType /static VULKAN_HPP_CONST_OR_CONSTEXPR vk::StructureType /g' "$STRUCTS_FILE"
sed -i '' 's/= StructureType::/= vk::StructureType::/g' "$STRUCTS_FILE"

# Fix DeviceSize references
sed -i '' 's/( DeviceSize /( vk::DeviceSize /g' "$STRUCTS_FILE" 
sed -i '' 's/& setStride( DeviceSize /\& setStride( vk::DeviceSize /g' "$STRUCTS_FILE"

# Fix Format references
sed -i '' 's/( Format /( vk::Format /g' "$STRUCTS_FILE"
sed -i '' 's/& setVertexFormat( Format /\& setVertexFormat( vk::Format /g' "$STRUCTS_FILE"
sed -i '' 's/= Format::/= vk::Format::/g' "$STRUCTS_FILE"

# Fix IndexType references
sed -i '' 's/( IndexType /( vk::IndexType /g' "$STRUCTS_FILE"
sed -i '' 's/& setIndexType( IndexType /\& setIndexType( vk::IndexType /g' "$STRUCTS_FILE"
sed -i '' 's/= IndexType::/= vk::IndexType::/g' "$STRUCTS_FILE"

# Fix Bool32 references
sed -i '' 's/( Bool32 /( vk::Bool32 /g' "$STRUCTS_FILE"
sed -i '' 's/& setArrayOfPointers( Bool32 /\& setArrayOfPointers( vk::Bool32 /g' "$STRUCTS_FILE"

# Fix tuple references
sed -i '' 's/<StructureType const/<vk::StructureType const/g' "$STRUCTS_FILE"
sed -i '' 's/<DeviceSize const/<vk::DeviceSize const/g' "$STRUCTS_FILE"

# Fix member variable types
sed -i '' 's/^    StructureType /    vk::StructureType /g' "$STRUCTS_FILE"
sed -i '' 's/^    DeviceSize /    vk::DeviceSize /g' "$STRUCTS_FILE"
sed -i '' 's/^    Format /    vk::Format /g' "$STRUCTS_FILE"
sed -i '' 's/^    IndexType /    vk::IndexType /g' "$STRUCTS_FILE"
sed -i '' 's/^    Bool32 /    vk::Bool32 /g' "$STRUCTS_FILE"

# Fix template specializations - comment them out for now
sed -i '' 's/^  template <>$/  \/\/ template <>/g' "$STRUCTS_FILE"
sed -i '' 's/^  struct CppType</  \/\/ struct CppType</g' "$STRUCTS_FILE"
sed -i '' 's/^    using Type = /  \/\/   using Type = /g' "$STRUCTS_FILE"
sed -i '' 's/^  };$/  \/\/ };/g' "$STRUCTS_FILE"

echo "✓ Fixed vulkan_structs.hpp namespace issues"