// SPIRV-Tools compatibility functions for macOS
// Provides stub implementations for missing ARM-specific functions

#include "spirv-tools/optimizer.hpp"

#ifdef SPIRV_TOOLS_MACOS_COMPAT

namespace spvtools {
namespace opt {

// Stub for missing ARM-specific function
void spvValidatorOptionsSetAllowOffsetTextureOperand(spv_validator_options options, bool allow) {
    // This is an ARM-specific extension validation
    // On macOS, we'll just ignore it as MoltenVK doesn't support it anyway
    (void)options;
    (void)allow;
}

// Additional stubs for ARM ML extensions
void CreateGraphShapePass() {
    // No-op on macOS
}

} // namespace opt
} // namespace spvtools

#endif // SPIRV_TOOLS_MACOS_COMPAT