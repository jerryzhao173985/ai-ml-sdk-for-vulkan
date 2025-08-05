/*
 * SPDX-FileCopyrightText: Copyright 2024-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <string>

namespace mlsdk::vgf_dump::details {

const std::string version{R""""({
  "version": "f90fe30-dirty",
  "dependencies": [
    "argparse=v3.1",
    "nlohmann_json=v3.11.3"
  ]
})""""};

} // namespace mlsdk::vgf_dump::details
