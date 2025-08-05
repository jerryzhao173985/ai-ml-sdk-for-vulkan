#!/bin/bash
# SPDX-FileCopyrightText: Copyright 2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
# SPDX-License-Identifier: Apache-2.0

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}ML SDK for Vulkan - Docker Build Script${NC}"
echo "========================================"

# Check if Docker is installed
if ! command -v docker &> /dev/null; then
    echo -e "${RED}Error: Docker is not installed. Please install Docker first.${NC}"
    exit 1
fi

# Build the Docker image
echo -e "${YELLOW}Building Docker image...${NC}"
docker build -t ml-sdk-vulkan-builder -f docker/Dockerfile docker/

# Get the number of CPU cores
if [[ "$OSTYPE" == "darwin"* ]]; then
    CPU_CORES=$(sysctl -n hw.ncpu)
else
    CPU_CORES=$(nproc)
fi

echo -e "${GREEN}Using $CPU_CORES CPU cores for compilation${NC}"

# Run the build inside Docker
echo -e "${YELLOW}Running build inside Docker container...${NC}"
docker run --rm -it \
    -v "$(pwd):/workspace" \
    -w /workspace \
    -e "BUILD_THREADS=$CPU_CORES" \
    ml-sdk-vulkan-builder \
    bash -c "
        echo 'Setting up Python virtual environment...'
        python3 -m venv /tmp/venv
        source /tmp/venv/bin/activate
        
        echo 'Installing Python dependencies...'
        pip install --upgrade pip
        pip install -r requirements.txt
        pip install -r tooling-requirements.txt
        
        echo 'Building ML SDK with all components...'
        ./scripts/build.py \\
            --build-type Release \\
            --threads $CPU_CORES \\
            --build-dir build-docker \\
            --with-spirv-tools \\
            --with-glslang \\
            --with-scenario-runner \\
            --with-model-converter \\
            --with-emulation-layer \\
            --with-vgf-library
        
        echo 'Build completed!'
        echo 'Build artifacts are in: build-docker/'
    "

echo -e "${GREEN}Docker build completed successfully!${NC}"
echo "Build outputs are available in: build-docker/"

# Optional: Copy important artifacts to host-specific directory
if [ ! -d "artifacts" ]; then
    mkdir -p artifacts
fi

echo -e "${YELLOW}Extracting key artifacts...${NC}"
docker run --rm \
    -v "$(pwd):/workspace" \
    -w /workspace \
    ml-sdk-vulkan-builder \
    bash -c "
        if [ -d build-docker ]; then
            # Copy executables
            find build-docker -name 'model-converter' -type f -executable -exec cp {} artifacts/ \;
            find build-docker -name 'scenario-runner' -type f -executable -exec cp {} artifacts/ \;
            find build-docker -name 'vgf-viewer' -type f -executable -exec cp {} artifacts/ \;
            find build-docker -name 'vgf-dump' -type f -executable -exec cp {} artifacts/ \;
            
            # Copy libraries
            find build-docker -name '*.so' -exec cp {} artifacts/ \;
            find build-docker -name '*.a' -exec cp {} artifacts/ \;
            
            echo 'Artifacts copied to artifacts/ directory'
        fi
    "

echo -e "${GREEN}All done! Key artifacts are available in the 'artifacts' directory.${NC}"