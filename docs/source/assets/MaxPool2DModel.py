#!/usr/bin/env python3
#
# SPDX-FileCopyrightText: Copyright 2024-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
# SPDX-License-Identifier: Apache-2.0
#
import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from executorch.backends.arm.arm_backend import ArmCompileSpecBuilder
from executorch.backends.arm.tosa_partitioner import TOSAPartitioner
from executorch.exir import EdgeCompileConfig
from executorch.exir import to_edge_transform_and_lower

# Define model
class MaxPoolModel(nn.Module):
    def __init__(self):
        super(MaxPoolModel, self).__init__()
        self.pool = nn.MaxPool2d(kernel_size=2, stride=2)

    def forward(self, x):
        x = self.pool(x)
        return x


# Generate test input
example_input = torch.randn(1, 3, 64, 64)
np.save("input-0.npy", example_input.numpy())

model = MaxPoolModel().eval()

# Save model intermediates
compile_spec = (
    ArmCompileSpecBuilder()
    .tosa_compile_spec("TOSA-1.0+FP")
    .dump_intermediate_artifacts_to(".")
    .build()
)
partitioner = TOSAPartitioner(compile_spec)

exported_program = torch.export.export_for_training(model, (example_input,))

to_edge_transform_and_lower(
    exported_program,
    partitioner=[partitioner],
    compile_config=EdgeCompileConfig(
        _check_ir_validity=False,
    ),
)
