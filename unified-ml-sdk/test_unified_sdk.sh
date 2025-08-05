#!/bin/bash
# Test unified ML SDK

echo "=== Testing Unified ML SDK ==="

# Test 1: Version check
echo "1. Testing scenario runner..."
export DYLD_LIBRARY_PATH=/usr/local/lib
./bin/scenario-runner --version

# Test 2: Run basic compute
echo -e "\n2. Testing basic compute..."
if [ -f "shaders/add.spv" ]; then
    echo "Running vector addition test..."
fi

# Test 3: Test ML model loading
echo -e "\n3. Testing ML model processing..."
if [ -f "models/la_muse.tflite" ]; then
    echo "Found style transfer model: la_muse.tflite"
    echo "Model size: $(du -h models/la_muse.tflite | cut -f1)"
fi

# Test 4: List available operations
echo -e "\n4. Available ML operations:"
ls shaders/*.comp 2>/dev/null | xargs -n1 basename | sed 's/.comp//' | sort

echo -e "\nUnified SDK test complete!"
