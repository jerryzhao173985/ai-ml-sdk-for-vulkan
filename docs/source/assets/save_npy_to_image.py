#
# SPDX-FileCopyrightText: Copyright 2024 Arm Limited and/or its affiliates <open-source-office@arm.com>
# SPDX-License-Identifier: Apache-2.0
#
import numpy as np
from PIL import Image

grayscale = np.load("output.npy")[0, :, :, 0]
grayscale = np.interp(grayscale, (np.min(grayscale), np.max(grayscale)), (0.0, 256.0))
im = Image.fromarray(grayscale.astype("uint8"))
im.save("output.jpg")
