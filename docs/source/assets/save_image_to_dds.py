#
# SPDX-FileCopyrightText: Copyright 2024-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
# SPDX-License-Identifier: Apache-2.0
#
import subprocess
import sys

import numpy as np
from PIL import Image

# Read from command line arguments
if len(sys.argv) != 4:
    raise RuntimeError(
        f"Expected 4 command line arguments (including python file name), got {len(sys.argv)}"
    )
dds_exe_path = sys.argv[1]
image_in_path = sys.argv[2]
image_out_path = sys.argv[3]

# load .jpg image as NumPy array
img = np.asarray(Image.open(image_in_path))
print(img.dtype, img.shape)

height, width, channel = img.shape

# convert image data type to float32 and add alpha channel
img = img.astype("float32").reshape((-1, 3))
alpha = np.ones((img.shape[0], 1), dtype="float32") * 256
img = np.hstack((img, alpha))
print(img.dtype, img.shape)

# write DDS header into .dds file
subprocess.run(
    [
        dds_exe_path,
        "--action",
        "generate",
        "--height",
        str(height),
        "--width",
        str(width),
        "--element-dtype",
        "f32",
        "--element-size",
        "16",  # RGBA each takes 4 bytes
        "--format",
        "DXGI_FORMAT_R32G32B32A32_FLOAT",
        "--output",
        image_out_path,
        "--header-only",
    ],
    check=True,
)

# write image data into .dds file
with open(image_out_path, "ab") as file:
    file.write(img.tobytes())
