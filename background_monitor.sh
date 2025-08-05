#!/bin/bash
# Background build monitor for ARM ML SDK

BUILD_DIR="${1:-build-official}"
LOG_FILE="build_progress.log"

echo "Starting background monitor for $BUILD_DIR" > "$LOG_FILE"
echo "Started at: $(date)" >> "$LOG_FILE"

while true; do
    # Count LLVM files built
    LLVM_COUNT=$(find "$BUILD_DIR/model-converter/llvm" -name "*.a" 2>/dev/null | wc -l)
    
    # Check component status
    COMPONENTS=""
    
    if [ -f "$BUILD_DIR/vgf-lib/libvgf.a" ]; then
        COMPONENTS="$COMPONENTS VGF:✓"
    else
        COMPONENTS="$COMPONENTS VGF:⏳"
    fi
    
    if [ -f "$BUILD_DIR/scenario-runner/scenario-runner" ]; then
        COMPONENTS="$COMPONENTS SR:✓"
    else
        COMPONENTS="$COMPONENTS SR:⏳"
    fi
    
    if [ -f "$BUILD_DIR/emulation-layer/libml_emulation.a" ] || [ -f "$BUILD_DIR/emulation-layer/libml_emulation.so" ]; then
        COMPONENTS="$COMPONENTS EL:✓"
    else
        COMPONENTS="$COMPONENTS EL:⏳"
    fi
    
    if [ -f "$BUILD_DIR/model-converter/model-converter" ]; then
        COMPONENTS="$COMPONENTS MC:✓"
    else
        COMPONENTS="$COMPONENTS MC:⏳"
    fi
    
    # Write status
    echo "[$(date +%H:%M:%S)] LLVM libs: $LLVM_COUNT | $COMPONENTS" >> "$LOG_FILE"
    
    # Check if build is complete
    if [ -f "$BUILD_DIR/model-converter/model-converter" ] && [ -f "$BUILD_DIR/emulation-layer/libml_emulation.a" ]; then
        echo "BUILD COMPLETE at $(date)" >> "$LOG_FILE"
        break
    fi
    
    # Check for recent errors
    if [ -f "build-official.log" ]; then
        ERRORS=$(tail -100 build-official.log | grep -i "error:" | wc -l)
        if [ $ERRORS -gt 0 ]; then
            echo "[$(date +%H:%M:%S)] Found $ERRORS errors in recent log" >> "$LOG_FILE"
        fi
    fi
    
    sleep 30
done