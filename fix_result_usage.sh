#!/bin/bash
# Fix Result::eSuccess usage to ResultValue::eSuccess

SDK_ROOT="/Users/jerry/Vulkan/ai-ml-sdk-for-vulkan"

echo "Fixing Result usage..."

# Fix in pipeline.hpp
sed -i '' 's/vk::Result::eSuccess/vk::ResultValue::eSuccess/g' "$SDK_ROOT/sw/scenario-runner/src/pipeline.hpp"
sed -i '' 's/vk::Result::eIncomplete/vk::ResultValue::eIncomplete/g' "$SDK_ROOT/sw/scenario-runner/src/pipeline.hpp"

echo "✓ Fixed Result usage"