#!/bin/bash
# Check ARM ML SDK official build status

echo "=== ARM ML SDK Build Status Check ==="
echo "Build directory: build-official"
echo ""

# Function to check component
check_component() {
    local name=$1
    local path=$2
    
    if [ -f "$path" ]; then
        echo "✅ $name: Built"
        ls -lh "$path"
    elif [ -d "$(dirname "$path")" ]; then
        echo "⏳ $name: In progress (directory exists)"
    else
        echo "❌ $name: Not built"
    fi
}

# Check each component
echo "=== Component Status ==="

# Find actual built files
SCENARIO_RUNNER=$(find build-official -name "scenario-runner" -type f 2>/dev/null | head -1)
MODEL_CONVERTER=$(find build-official -name "model-converter" -type f 2>/dev/null | head -1)
VGF_LIB=$(find build-official -name "libvgf.a" -o -name "libvgf.so" 2>/dev/null | head -1)
ML_EMULATION=$(find build-official -name "libml_emulation.a" -o -name "libml_emulation.so" 2>/dev/null | head -1)

if [ -n "$SCENARIO_RUNNER" ]; then
    check_component "Scenario Runner" "$SCENARIO_RUNNER"
else
    echo "❌ Scenario Runner: Not found"
fi

if [ -n "$MODEL_CONVERTER" ]; then
    check_component "Model Converter" "$MODEL_CONVERTER"
else
    echo "❌ Model Converter: Not found"
fi

if [ -n "$VGF_LIB" ]; then
    check_component "VGF Library" "$VGF_LIB"
else
    echo "❌ VGF Library: Not found"
fi

if [ -n "$ML_EMULATION" ]; then
    check_component "ML Emulation Layer" "$ML_EMULATION"
else
    echo "❌ ML Emulation Layer: Not found"
fi

echo ""
echo "=== Build Statistics ==="
echo "Total libraries built: $(find build-official -name "*.a" 2>/dev/null | wc -l)"
echo "LLVM libraries: $(find build-official/model-converter/llvm -name "*.a" 2>/dev/null | wc -l)"
echo "SPIRV libraries: $(find build-official -name "*SPIRV*.a" 2>/dev/null | wc -l)"

echo ""
echo "=== Recent Build Activity ==="
if [ -f "build-official.log" ]; then
    tail -10 build-official.log | grep -E "(Built target|Linking|Installing|error:|warning:)" | tail -5
fi