#!/bin/bash
# Fix Vulkan ML Extensions for macOS ARM64

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${GREEN}=== Fixing Vulkan ML Extensions for macOS ===${NC}"

SDK_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
VULKAN_HEADERS="$SDK_ROOT/dependencies/Vulkan-Headers"

# Create a patch to enable ML extensions in C++ headers
echo -e "${YELLOW}Creating Vulkan ML extensions enabler...${NC}"

# Create a header that force-enables ML extensions
cat > "$SDK_ROOT/vulkan_ml_enabled.hpp" << 'EOF'
#pragma once

// Force enable beta extensions for ML support
#ifndef VK_ENABLE_BETA_EXTENSIONS
#define VK_ENABLE_BETA_EXTENSIONS
#endif

// Include Vulkan with ML extensions
#include <vulkan/vulkan.hpp>

// Verify ML extensions are available
static_assert(VK_ARM_TENSORS_SPEC_VERSION >= 1, "ARM tensor extensions not available");

// Helper macros for ML extensions
#define VK_ML_ENABLED 1

// Additional type aliases for easier use
namespace vkml {
    using Tensor = VkTensorARM;
    using TensorView = VkTensorViewARM;
    using TensorCreateInfo = VkTensorCreateInfoARM;
    using TensorViewCreateInfo = VkTensorViewCreateInfoARM;
    using TensorMemoryBarrier = VkTensorMemoryBarrierARM;
}
EOF

# Create a CMake module to properly configure ML extensions
cat > "$SDK_ROOT/cmake/VulkanMLExtensions.cmake" << 'EOF'
# Enable Vulkan ML Extensions for macOS

# Add compile definitions
add_compile_definitions(VK_ENABLE_BETA_EXTENSIONS)

# Find Vulkan
find_package(Vulkan REQUIRED)

# Create an interface library for ML extensions
add_library(VulkanMLExtensions INTERFACE)
target_compile_definitions(VulkanMLExtensions INTERFACE VK_ENABLE_BETA_EXTENSIONS)
target_include_directories(VulkanMLExtensions INTERFACE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(VulkanMLExtensions INTERFACE Vulkan::Vulkan)

# Function to enable ML extensions for a target
function(enable_vulkan_ml_extensions TARGET)
    target_link_libraries(${TARGET} PRIVATE VulkanMLExtensions)
    target_compile_definitions(${TARGET} PRIVATE VK_ENABLE_BETA_EXTENSIONS)
endfunction()
EOF

# Create a test program to verify ML extensions work
echo -e "${YELLOW}Creating ML extensions test program...${NC}"

mkdir -p "$SDK_ROOT/test-ml-extensions"

cat > "$SDK_ROOT/test-ml-extensions/test_ml_extensions.cpp" << 'EOF'
#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.hpp>
#include <iostream>
#include <vector>

int main() {
    std::cout << "Testing Vulkan ML Extensions..." << std::endl;
    
    // Check if types are available
    std::cout << "VK_ARM_TENSORS_SPEC_VERSION: " << VK_ARM_TENSORS_SPEC_VERSION << std::endl;
    std::cout << "VK_ARM_TENSORS_EXTENSION_NAME: " << VK_ARM_TENSORS_EXTENSION_NAME << std::endl;
    
    // Test creating structures (compile-time check)
    VkTensorCreateInfoARM tensorInfo{};
    tensorInfo.sType = VK_STRUCTURE_TYPE_TENSOR_CREATE_INFO_ARM;
    
    VkTensorMemoryBarrierARM barrier{};
    barrier.sType = VK_STRUCTURE_TYPE_TENSOR_MEMORY_BARRIER_ARM;
    
    // Check C++ types
    try {
        vk::TensorCreateInfoARM cppTensorInfo{};
        cppTensorInfo.sType = vk::StructureType::eTensorCreateInfoARM;
        std::cout << "✓ C++ ML extension types are available!" << std::endl;
    } catch (...) {
        std::cout << "✗ C++ ML extension types not available" << std::endl;
        return 1;
    }
    
    // List required extensions
    std::vector<const char*> requiredExtensions = {
        VK_ARM_TENSORS_EXTENSION_NAME,
        VK_ARM_DATA_GRAPH_EXTENSION_NAME
    };
    
    std::cout << "\nRequired ML extensions:" << std::endl;
    for (const auto& ext : requiredExtensions) {
        std::cout << "  - " << ext << std::endl;
    }
    
    std::cout << "\n✓ ML extensions test passed!" << std::endl;
    return 0;
}
EOF

cat > "$SDK_ROOT/test-ml-extensions/CMakeLists.txt" << 'EOF'
cmake_minimum_required(VERSION 3.25)
project(VulkanMLExtensionsTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable ML extensions
add_compile_definitions(VK_ENABLE_BETA_EXTENSIONS)

# Find Vulkan
find_package(Vulkan REQUIRED)

# Create test executable
add_executable(test_ml_extensions test_ml_extensions.cpp)
target_include_directories(test_ml_extensions PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(test_ml_extensions PRIVATE Vulkan::Vulkan)
target_compile_definitions(test_ml_extensions PRIVATE VK_ENABLE_BETA_EXTENSIONS)
EOF

# Build the test
echo -e "${YELLOW}Building ML extensions test...${NC}"
cd "$SDK_ROOT/test-ml-extensions"
mkdir -p build
cmake -S . -B build -G Ninja
ninja -C build

# Run the test
echo -e "${YELLOW}Running ML extensions test...${NC}"
./build/test_ml_extensions || {
    echo -e "${RED}ML extensions test failed${NC}"
}

# Create a patched scenario runner build
echo -e "${YELLOW}Creating patched Scenario Runner build configuration...${NC}"

cat > "$SDK_ROOT/build_scenario_runner_macos.sh" << 'EOFSCRIPT'
#!/bin/bash
# Build Scenario Runner with ML extensions enabled

SDK_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Configure with ML extensions enabled
cmake -S sw/scenario-runner -B build-macos-scenario -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_FLAGS="-DVK_ENABLE_BETA_EXTENSIONS -I$SDK_ROOT" \
    -DARGPARSE_PATH="$SDK_ROOT/dependencies/argparse" \
    -DJSON_PATH="$SDK_ROOT/dependencies/json" \
    -DML_SDK_VGF_LIB_PATH="$SDK_ROOT/sw/vgf-lib" \
    -DVULKAN_HEADERS_PATH="$SDK_ROOT/dependencies/Vulkan-Headers" \
    -DSPIRV_HEADERS_PATH="$SDK_ROOT/dependencies/SPIRV-Headers" \
    -DSPIRV_TOOLS_PATH="$SDK_ROOT/dependencies/SPIRV-Tools" \
    -DGLSLANG_PATH="$SDK_ROOT/dependencies/glslang"

# Build
ninja -C build-macos-scenario -j $(sysctl -n hw.ncpu)
EOFSCRIPT

chmod +x "$SDK_ROOT/build_scenario_runner_macos.sh"

echo -e "${GREEN}=== ML Extensions Fix Complete ===${NC}"
echo -e "${BLUE}Created:${NC}"
echo "  - vulkan_ml_enabled.hpp - Header with ML extensions enabled"
echo "  - cmake/VulkanMLExtensions.cmake - CMake module for ML extensions"
echo "  - test-ml-extensions/ - Test program to verify ML extensions"
echo "  - build_scenario_runner_macos.sh - Build script for Scenario Runner"

echo -e "${YELLOW}To use ML extensions in your code:${NC}"
echo '  #define VK_ENABLE_BETA_EXTENSIONS'
echo '  #include <vulkan/vulkan.hpp>'
echo '  // or'
echo '  #include "vulkan_ml_enabled.hpp"'