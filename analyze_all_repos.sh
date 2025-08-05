#!/bin/bash
# Analyze all compiled Vulkan AI SDK repositories

echo "=== Analyzing All Vulkan AI SDK Components ==="
echo ""

VULKAN_ROOT="/Users/jerry/Vulkan"
REPORT_FILE="$VULKAN_ROOT/ai-ml-sdk-for-vulkan/COMPLETE_SDK_ANALYSIS.md"

# Start report
cat > "$REPORT_FILE" << 'EOF'
# Complete Vulkan AI SDK Analysis Report

## Available Repositories and Components

EOF

# Function to analyze repository
analyze_repo() {
    local repo_path=$1
    local repo_name=$(basename "$repo_path")
    
    echo "Analyzing: $repo_name"
    echo "### $repo_name" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    
    # Check for built artifacts
    echo "**Built Artifacts:**" >> "$REPORT_FILE"
    find "$repo_path" -name "*.a" -o -name "*.so" -o -name "*.dylib" -o -name "*.exe" -o -type f -perm +111 2>/dev/null | grep -E "(build|lib|bin)" | grep -v CMakeFiles | head -10 >> "$REPORT_FILE" 2>/dev/null || echo "- None found" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    
    # Check for models
    echo "**ML Models/Data:**" >> "$REPORT_FILE"
    find "$repo_path" -name "*.tflite" -o -name "*.onnx" -o -name "*.pb" -o -name "*.vgf" -o -name "*.tosa" 2>/dev/null | head -5 >> "$REPORT_FILE" 2>/dev/null || echo "- None found" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    
    # Check for shaders
    echo "**Shaders:**" >> "$REPORT_FILE"
    find "$repo_path" -name "*.spv" -o -name "*.comp" -o -name "*.glsl" 2>/dev/null | grep -v CMakeFiles | head -5 >> "$REPORT_FILE" 2>/dev/null || echo "- None found" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    
    # Check for scenarios
    echo "**Scenarios/Tests:**" >> "$REPORT_FILE"
    find "$repo_path" -name "*.json" -path "*/scenario*" -o -name "*.json" -path "*/test*" 2>/dev/null | grep -v CMakeFiles | head -5 >> "$REPORT_FILE" 2>/dev/null || echo "- None found" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    echo "---" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
}

# Analyze main SDK
analyze_repo "$VULKAN_ROOT/ai-ml-sdk-for-vulkan"

# Analyze individual component repos
for repo in "$VULKAN_ROOT"/ai-ml-*; do
    if [ -d "$repo" ] && [ "$repo" != "$VULKAN_ROOT/ai-ml-sdk-for-vulkan" ]; then
        analyze_repo "$repo"
    fi
done

# Analyze other relevant repos
analyze_repo "$VULKAN_ROOT/ComputeLibrary"
analyze_repo "$VULKAN_ROOT/ML-examples"
analyze_repo "$VULKAN_ROOT/MoltenVK"

# Check dependencies
echo "" >> "$REPORT_FILE"
echo "## Compiled Dependencies" >> "$REPORT_FILE"
echo "" >> "$REPORT_FILE"

for dep in "$VULKAN_ROOT/dependencies"/*; do
    if [ -d "$dep/build" ]; then
        echo "- $(basename $dep): ✓ Built" >> "$REPORT_FILE"
    fi
done

echo "" >> "$REPORT_FILE"
echo "Report saved to: $REPORT_FILE"
cat "$REPORT_FILE"