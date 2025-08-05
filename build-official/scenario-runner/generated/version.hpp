/*
 * SPDX-FileCopyrightText: Copyright 2024-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <string>

namespace mlsdk::scenariorunner::details {

const std::string version{R""""({
  "version": "197a36e-dirty",
  "dependencies": [
    "argparse=v3.1",
    "glslang=0d614c24-dirty",
    "nlohmann_json=v3.11.3",
    "SPIRV-Headers=vulkan-sdk-1.4.321.0-7-g97e96f9",
    "SPIRV-Tools=v2025.3.rc1-36-g3aeaaa08",
    "VGF=f90fe30-dirty",
    "VulkanHeaders=a01329f-dirty"
  ]
})""""};

} // namespace mlsdk::scenariorunner::details
