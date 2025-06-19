#
# SPDX-FileCopyrightText: Copyright 2024-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
# SPDX-License-Identifier: Apache-2.0
#
import sys

import numpy as np
from PIL import Image

_, filename1, filename2 = sys.argv
image1 = np.asarray(Image.open(filename1))
image2 = np.asarray(Image.open(filename2))
print(image1.shape, image2.shape)

err = np.sqrt((image1 - image2) ** 2).mean()
print("RMSE:", err)
if err > 10:
    print("Error too big")
    sys.exit(1)
