#!/bin/bash
# Monitor ARM ML SDK build progress

BUILD_DIR="${1:-build-official}"

echo "=== ARM ML SDK Build Monitor ==="
echo "Build directory: $BUILD_DIR"
echo ""

while true; do
    clear
    echo "=== ARM ML SDK Build Progress ==="
    echo "Time: $(date)"
    echo ""
    
    # Check LLVM progress
    if [ -d "$BUILD_DIR/model-converter/llvm" ]; then
        LLVM_TARGETS=$(find "$BUILD_DIR/model-converter/llvm" -name "*.a" 2>/dev/null | wc -l)
        echo "LLVM Libraries built: $LLVM_TARGETS"
    fi
    
    # Check component status
    echo ""
    echo "Component Status:"
    
    # VGF Library
    if [ -f "$BUILD_DIR/vgf-lib/libvgf.a" ]; then
        echo "✓ VGF Library: Built"
    else
        echo "⏳ VGF Library: Building..."
    fi
    
    # Scenario Runner
    if [ -f "$BUILD_DIR/scenario-runner/scenario-runner" ]; then
        echo "✓ Scenario Runner: Built"
    elif [ -d "$BUILD_DIR/scenario-runner" ]; then
        echo "⏳ Scenario Runner: Building..."
    else
        echo "⏸  Scenario Runner: Not started"
    fi
    
    # Emulation Layer
    if [ -f "$BUILD_DIR/emulation-layer/libml_emulation.a" ] || [ -f "$BUILD_DIR/emulation-layer/libml_emulation.so" ]; then
        echo "✓ Emulation Layer: Built"
    elif [ -d "$BUILD_DIR/emulation-layer/tensor" ]; then
        echo "⏳ Emulation Layer: Building..."
    else
        echo "⏸  Emulation Layer: Not started"
    fi
    
    # Model Converter
    if [ -f "$BUILD_DIR/model-converter/model-converter" ]; then
        echo "✓ Model Converter: Built"
    elif [ -d "$BUILD_DIR/model-converter/llvm" ]; then
        echo "⏳ Model Converter: Building LLVM..."
    else
        echo "⏸  Model Converter: Not started"
    fi
    
    # Check build log
    if [ -f "build.log" ]; then
        echo ""
        echo "Recent build activity:"
        tail -5 build.log | sed 's/^/  /'
    fi
    
    # Check for errors
    if [ -f "build.log" ]; then
        ERRORS=$(grep -i "error:" build.log | tail -5)
        if [ ! -z "$ERRORS" ]; then
            echo ""
            echo "⚠️  Recent errors:"
            echo "$ERRORS" | sed 's/^/  /'
        fi
    fi
    
    echo ""
    echo "Press Ctrl+C to exit"
    sleep 10
done