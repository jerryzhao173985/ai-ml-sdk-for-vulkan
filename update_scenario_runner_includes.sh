#!/bin/bash
# Update all Scenario Runner source files to use the comprehensive compatibility header

SR_SRC="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan/sw/scenario-runner/src"

echo "Updating Scenario Runner includes to use vulkan_full_compat.hpp..."

# Find all C++ source and header files
find "$SR_SRC" -name "*.cpp" -o -name "*.hpp" | while read file; do
    # Skip our compatibility files
    if [[ "$file" == *"compat/"* ]]; then
        continue
    fi
    
    # Create backup
    cp "$file" "$file.bak" 2>/dev/null || true
    
    # Replace all vulkan includes with our full compatibility header
    sed -i '' 's|#include "compat/ml_extensions.hpp"|#include "compat/vulkan_full_compat.hpp"|g' "$file"
    sed -i '' 's|#include "compat/vulkan_ml_compat.hpp"|#include "compat/vulkan_full_compat.hpp"|g' "$file"
    sed -i '' 's|#include <vulkan/vulkan_raii.hpp>|#include "compat/vulkan_full_compat.hpp"|g' "$file"
    sed -i '' 's|#include <vulkan/vulkan.hpp>|#include "compat/vulkan_full_compat.hpp"|g' "$file"
    sed -i '' 's|#include "vulkan/vulkan_raii.hpp"|#include "compat/vulkan_full_compat.hpp"|g' "$file"
    sed -i '' 's|#include "vulkan/vulkan.hpp"|#include "compat/vulkan_full_compat.hpp"|g' "$file"
    
    # Clean up backup if no changes were made
    if cmp -s "$file" "$file.bak" 2>/dev/null; then
        rm -f "$file.bak"
    fi
done

# Special fix for commands.hpp that already has vulkan_types_compat.hpp
sed -i '' 's|#include "vulkan_types_compat.hpp"|#include "compat/vulkan_full_compat.hpp"|g' "$SR_SRC/commands.hpp"

echo "✓ Include updates complete"