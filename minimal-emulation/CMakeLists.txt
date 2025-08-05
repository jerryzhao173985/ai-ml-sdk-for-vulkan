cmake_minimum_required(VERSION 3.20)
project(MinimalEmulation)

set(CMAKE_CXX_STANDARD 17)

find_package(Vulkan REQUIRED)

add_library(minimal_emulation SHARED
    src/tensor_emulation.cpp
    src/graph_emulation.cpp
)

target_include_directories(minimal_emulation PUBLIC
    ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(minimal_emulation
    ${Vulkan_LIBRARIES}
)

# Create layer JSON
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/VkLayer_ARM_emulation.json.in
    ${CMAKE_CURRENT_BINARY_DIR}/VkLayer_ARM_emulation.json
    @ONLY
)
