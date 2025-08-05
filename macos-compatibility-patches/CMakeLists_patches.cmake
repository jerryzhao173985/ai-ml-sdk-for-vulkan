# CMake patches for macOS compatibility

# Function to patch Model Converter for macOS
function(patch_model_converter_for_macos)
    # Override platform checks
    if(APPLE)
        message(STATUS "Applying macOS compatibility patches for Model Converter")
        
        # Don't use Linux-specific toolchain files
        unset(CMAKE_TOOLCHAIN_FILE)
        
        # Set macOS-specific flags
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++" PARENT_SCOPE)
        
        # Disable platform warnings
        add_compile_definitions(PLATFORM_MACOS_OVERRIDE=1)
    endif()
endfunction()

# Function to patch Scenario Runner for macOS
function(patch_scenario_runner_for_macos)
    if(APPLE)
        message(STATUS "Applying macOS compatibility patches for Scenario Runner")
        
        # Add ML extensions wrapper include path
        include_directories(${CMAKE_CURRENT_SOURCE_DIR}/macos-compatibility-patches)
        
        # Add preprocessor definitions
        add_compile_definitions(
            VK_ENABLE_BETA_EXTENSIONS=1
            USE_VULKAN_ML_EXTENSIONS_WRAPPER=1
        )
        
        # Link against MoltenVK if available
        find_library(MOLTENVK_LIB MoltenVK)
        if(MOLTENVK_LIB)
            message(STATUS "Found MoltenVK: ${MOLTENVK_LIB}")
            link_libraries(${MOLTENVK_LIB})
        endif()
    endif()
endfunction()

# Function to fix SPIRV-Tools compatibility
function(fix_spirv_tools_for_macos)
    if(APPLE)
        # Use official SPIRV-Tools instead of ARM fork
        set(USE_OFFICIAL_SPIRV_TOOLS ON PARENT_SCOPE)
        
        # Add missing function stubs
        add_compile_definitions(SPIRV_TOOLS_MACOS_COMPAT=1)
    endif()
endfunction()

# Function to handle missing dependencies gracefully
function(handle_missing_dependencies)
    if(APPLE)
        # Create dummy targets for missing components
        if(NOT TARGET argparse::argparse)
            add_library(argparse::argparse INTERFACE IMPORTED)
        endif()
        
        # Set fallback paths
        if(NOT EXISTS ${FLATBUFFERS_PATH})
            message(WARNING "FlatBuffers not found, using system version")
            find_package(flatbuffers QUIET)
        endif()
    endif()
endfunction()