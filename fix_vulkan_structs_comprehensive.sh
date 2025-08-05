#!/bin/bash
# Comprehensive fix for vulkan_structs.hpp namespace issues

STRUCTS_FILE="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/dependencies/Vulkan-Headers/include/vulkan/vulkan_structs.hpp"

echo "Creating backup of vulkan_structs.hpp..."
cp "$STRUCTS_FILE" "$STRUCTS_FILE.backup2"

echo "Fixing namespace issues in vulkan_structs.hpp..."

# Create a temporary file
TMP_FILE="${STRUCTS_FILE}.tmp"

# Process the file line by line to ensure we don't double-prefix
awk '
{
    # Skip lines that already have vk:: prefix or are inside string literals
    if ($0 ~ /vk::DeviceAddress/ || $0 ~ /vk::DeviceSize/ || $0 ~ /vk::Format/ || 
        $0 ~ /vk::IndexType/ || $0 ~ /vk::StructureType/ || $0 ~ /"/) {
        print $0
    }
    # Add vk:: prefix to standalone type names
    else {
        line = $0
        # Only replace if not part of a larger identifier
        gsub(/\<DeviceAddress\>/, "vk::DeviceAddress", line)
        gsub(/\<DeviceSize\>/, "vk::DeviceSize", line)
        gsub(/\<Format\>/, "vk::Format", line)
        gsub(/\<IndexType\>/, "vk::IndexType", line)
        gsub(/\<StructureType\>/, "vk::StructureType", line)
        print line
    }
}
' "$STRUCTS_FILE" > "$TMP_FILE"

# Move the temporary file back
mv "$TMP_FILE" "$STRUCTS_FILE"

echo "✓ Fixed vulkan_structs.hpp namespace issues comprehensively"