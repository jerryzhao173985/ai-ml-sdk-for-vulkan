/*
 * SPDX-FileCopyrightText: Copyright 2024-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <string>

namespace mlsdk::scenariorunner::details {

const std::string version{R""""({
  "version": "197a36e",
  "dependencies": [
    "argparse=v3.1",
    "glslang=0d614c24",
    "nlohmann_json=v3.11.3",
    "SPIRV-Headers=de1807b",
    "SPIRV-Tools=4ed8384f",
    "VGF=f90fe30",
    "VulkanHeaders=a01329f"
  ]
})""""};

} // namespace mlsdk::scenariorunner::details
