/*
 * SPDX-FileCopyrightText: Copyright 2024-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#pragma once

#include <string>

namespace mlsdk::model_converter::details {

const std::string version{R""""({
  "version": "d990f8a-dirty",
  "dependencies": [
    "argparse=v3.1",
    "flatbuffers=v23.5.26",
    "LLVM=18.1.4",
    "MLIR=18.1.4",
    "VGF=f90fe30-dirty"
  ]
})""""};

} // namespace mlsdk::model_converter::details
