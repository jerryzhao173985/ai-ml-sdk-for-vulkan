#pragma once
#include <map>
#include <string_view>
namespace {
constexpr std::string_view argmaxGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_T %in_t%
#define TYPE_IN %in_t_type%

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    uint axis;
    uint nanMode;
} pushConstants;

layout(constant_id = 0) const uint32_t RANK_IN = RANK_MAX;
layout(constant_id = 1) const uint32_t RANK_OUT = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<int32_t, RANK_OUT> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_T, RANK_IN> inputData;

void main() {
    uint[RANK_OUT] index;
    getIndex(outputData, index);

    uint[RANK_IN] inputIndex;
    for (uint i = 0; i < pushConstants.axis; i++) {
        inputIndex[i] = index[i];
    }

    for (uint i = pushConstants.axis; i < RANK_OUT; i++) {
        inputIndex[i + 1] = index[i];
    }

    IN_T maxValue = IN_T(%in_t_lowest%);
    int32_t maxIndex = 0;

    uint[RANK_IN] inputShape;
    getShape(inputShape, inputData);

    for (int32_t i = 0; i < inputShape[pushConstants.axis]; i++) {
        inputIndex[pushConstants.axis] = i;
        IN_T value;
        tensorReadARM(inputData, inputIndex, value);

        #if IS_FLOAT(TYPE_IN)
        if (isnan(value)) {
            if (pushConstants.nanMode == NAN_MODE_IGNORE) {
                continue;
            }
            maxIndex = i;
            break;
        }
        #endif

        if (value > maxValue) {
            maxValue = value;
            maxIndex = i;
        }
    }

    tensorWriteARM(outputData, index, maxIndex);
}
)"
;
constexpr std::string_view arithmetic_right_shiftGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2024 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    uint round;
} pushConstants;

layout(constant_id = 0) const uint32_t RANK_IN = RANK_MAX;
layout(constant_id = 1) const uint32_t RANK_OUT = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, RANK_OUT> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, RANK_IN> inputData1;
layout(set = 2, binding = 0) uniform tensorARM<IN_OUT_T, RANK_IN> inputData2;

void main() {
    uint[RANK_OUT] index;
    getIndex(outputData, index);

    uint[RANK_IN] inputTensor1;
    getShape(inputTensor1, inputData1);
    uint[RANK_IN] inputTensor2;
    getShape(inputTensor2, inputData2);

    uint[RANK_IN] coords1;
    applyBroadcast(inputTensor1, index, coords1);
    uint[RANK_IN] coords2;
    applyBroadcast(inputTensor2, index, coords2);

    IN_OUT_T value1;
    tensorReadARM(inputData1, coords1, value1);
    IN_OUT_T value2;
    tensorReadARM(inputData2, coords2, value2);

    IN_OUT_T result = value1 >> value2;

    const bool round = pushConstants.round != 0;
    if (round && value2 > 0) {
        if (((value1 >> IN_OUT_T(value2 - 1)) & 1) != 0) {
            result++;
        }
    }
    tensorWriteARM(outputData, index, result);
}
)"
;
constexpr std::string_view avgpool2dGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%
#define TYPE_IN_OUT %in_out_t_type%
#define ACC_T %acc_t%
#define MIN %in_out_t_lowest%
#define MAX %in_out_t_max%

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    int32_t kernel[2];
    int32_t stride[2];
    int32_t pad[4];
    int32_t inputZeroPoint;
    int32_t outputZeroPoint;
} pushConstants;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, 4> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, 4> inputData;

void main() {
    uint[4] index;
    getIndex4(outputData, index);

    uint on = index[0];
    uint oy = index[1];
    uint ox = index[2];
    uint oc = index[3];

    ACC_T acc = ACC_T(0);
    uint32_t count = uint32_t(0);

    uint iy = oy * pushConstants.stride[0] - pushConstants.pad[0];
    uint ix = ox * pushConstants.stride[1] - pushConstants.pad[2];

    for (uint ky = 0; ky < pushConstants.kernel[0]; ky++) {
        for (uint kx = 0; kx < pushConstants.kernel[1]; kx++) {
            uint y = iy + ky;
            uint x = ix + kx;

            if (y < tensorSizeARM(inputData, 1) && x < tensorSizeARM(inputData, 2)) {
                uint[4] index = uint[](on, y, x, oc);
                IN_OUT_T value;
                tensorReadARM(inputData, index, value);

                acc += ACC_T(value) - ACC_T(pushConstants.inputZeroPoint);
                count++;
            }
        }
    }

#if IS_FLOAT(TYPE_IN_OUT)
    acc /= ACC_T(count);
#else
    // Divide and round
    ACC_T round = acc < 0 ? -ACC_T(count >> 1) : ACC_T(count >> 1);
    acc = (acc + round) / ACC_T(count);

    // Add output zero point
    acc += ACC_T(pushConstants.outputZeroPoint);

    // Clamp to output range
    acc = clamp(acc, MIN, MAX);
#endif

    tensorWriteARM(outputData, index, IN_OUT_T(acc));
}
)"
;
constexpr std::string_view castGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_T %in_t%
#define OUT_T %out_t%
#define TYPE_IN %in_t_type%
#define TYPE_OUT %out_t_type%
#define TYPE_IN_MIN %in_t_lowest%
#define TYPE_IN_MAX %in_t_max%
#define TYPE_OUT_MIN %out_t_lowest%
#define TYPE_OUT_MAX %out_t_max%

layout(local_size_x = %warpX%) in;

layout(constant_id = 0) const uint32_t RANK = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<OUT_T, RANK> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_T, RANK> inputData;

void main() {
    uint[RANK] index;
    getIndex(outputData, index);

    IN_T value;
    tensorReadARM(inputData, index, value);

#if IS_BOOL(TYPE_OUT)
    OUT_T outValue = OUT_T(value);
#elif IS_FLOAT(TYPE_OUT)
    #if IS_BOOL(TYPE_IN)
        OUT_T outValue = OUT_T(value ? 1.0 : 0.0);
    #else
        OUT_T outValue = OUT_T(0.0);
        if (TYPE_IN_MIN < TYPE_OUT_MIN && TYPE_IN_MAX > TYPE_OUT_MAX) {
            if (value > IN_T(TYPE_OUT_MAX)) {
                outValue = OUT_T(1.0 / 0.0); // +Inf
            } else if (value < IN_T(TYPE_OUT_MIN)) {
                outValue = OUT_T(-1.0 / 0.0); // -Inf
            } else {
                outValue = OUT_T(value);
            }
        } else {
            outValue = OUT_T(value);
        }
    #endif
#else
    #if IS_BOOL(TYPE_IN)
        OUT_T outValue = OUT_T(value ? 1 : 0);
    #elif IS_FLOAT(TYPE_IN)
        OUT_T outValue = OUT_T(clamp(round(double(value)), TYPE_OUT_MIN, TYPE_OUT_MAX));
    #else
        OUT_T outValue = OUT_T(value);
    #endif
#endif

    tensorWriteARM(outputData, index, outValue);
}
)"
;
constexpr std::string_view clampGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%
#define TYPE_IN_OUT %in_out_t_type%

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    double min;
    double max;
    uint nanMode;
} pushConstants;

layout(constant_id = 0) const uint32_t RANK = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, RANK> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, RANK> inputData;

void main() {
    uint[RANK] index;
    getIndex(outputData, index);

    IN_OUT_T value;
    tensorReadARM(inputData, index, value);

#if IS_FLOAT(TYPE_IN_OUT)
    // In the NaN ignoring mode, if the input is a NaN, the output is the specified minimum value.
    if (isnan(value) && (pushConstants.nanMode == NAN_MODE_IGNORE)) {
        value = IN_OUT_T(pushConstants.min);
    }
#endif

    // In the NaN propagating mode, if the input is a NaN, the output must be a NaN.
    value = isnan(float(value)) ? value : clamp(value, IN_OUT_T(pushConstants.min), IN_OUT_T(pushConstants.max));
    tensorWriteARM(outputData, index, value);
}
)"
;
constexpr std::string_view concatGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2024 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    uint32_t axis;
    uint32_t offset;
} pushConstants;

layout(constant_id = 0) const uint32_t RANK = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, RANK> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, RANK> inputData;

void main() {
    uint[RANK] index;
    getIndex(inputData, index);

    uint[RANK] outputIndex;
    for (uint i = 0; i < outputIndex.length(); i++) {
        outputIndex[i] = index[i];
    }

    outputIndex[pushConstants.axis] += pushConstants.offset;

    IN_OUT_T value;
    tensorReadARM(inputData, index, value);
    tensorWriteARM(outputData, outputIndex, value);
}
)"
;
constexpr std::string_view conv2dGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_T %in_t%
#define OUT_T %out_t%
#define WEIGHT_T %weight_t%
#define TYPE_ACC %acc_t_type%
#define ACC_T %acc_t%

#if TYPE_ACC == TYPE_INT64
    #define VEC4 dvec4
#elif TYPE_ACC == TYPE_INT32
    #define VEC4 ivec4
#else
    #define VEC4 vec4
#endif

layout(local_size_x = %warpX%, local_size_y = %warpY%, local_size_z = %warpZ%) in;

layout(push_constant) uniform PushConstants {
    int32_t inputZeroPoint;
    int32_t weightZeroPoint;
    int32_t pad[4];
    int32_t stride[2];
    int32_t dilation[2];
} pushConstants;

layout(set = 0, binding = 0) uniform tensorARM<OUT_T, 4> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_T, 4> inputData;
layout(set = 2, binding = 0) uniform tensorARM<WEIGHT_T, 4> weightsData;
layout(set = 3, binding = 0) uniform tensorARM<OUT_T, 1> biasesData;

void main() {
    ACC_T acc[4] = {ACC_T(0), ACC_T(0), ACC_T(0), ACC_T(0)};
    uint batches = tensorSizeARM(outputData, 0);
    uint n = gl_GlobalInvocationID.x % batches;
    uint ox = gl_GlobalInvocationID.x / batches;
    uint oy = gl_GlobalInvocationID.y;
    uint oc = gl_GlobalInvocationID.z * 4;
    uint[4] ocs = {oc, oc + 1, oc + 2, oc + 3};

    if (oy >= tensorSizeARM(outputData, 1) ||
        ox >= tensorSizeARM(outputData, 2) ||
        oc >= tensorSizeARM(outputData, 3)) {
        return;
    }

    uint iy = oy * pushConstants.stride[0] - pushConstants.pad[0];
    uint ix = ox * pushConstants.stride[1] - pushConstants.pad[2];

    for (uint ky = 0; ky < tensorSizeARM(weightsData, 1); ky++) {
        for (uint kx = 0; kx < tensorSizeARM(weightsData, 2); kx++) {
            uint y = iy + ky * pushConstants.dilation[0];
            uint x = ix + kx * pushConstants.dilation[1];

            if (y < tensorSizeARM(inputData, 1) && x < tensorSizeARM(inputData, 2)) {
                const uint IC = tensorSizeARM(inputData, 3);
                for (uint ic = 0; ic < IC; ic += 4) {
                    IN_T tempValue[4];
                    tensorReadARM(inputData, uint[](n, y, x, ic), tempValue);
                    VEC4 value = VEC4(ACC_T(tempValue[0]), ACC_T(tempValue[1]), ACC_T(tempValue[2]), ACC_T(tempValue[3]));

                    WEIGHT_T weight[4][4];
                    tensorReadARM(weightsData, uint[](ocs[0], ky, kx, ic), weight[0]);
                    tensorReadARM(weightsData, uint[)"
R"(](ocs[1], ky, kx, ic), weight[1]);
                    tensorReadARM(weightsData, uint[](ocs[2], ky, kx, ic), weight[2]);
                    tensorReadARM(weightsData, uint[](ocs[3], ky, kx, ic), weight[3]);

                    VEC4 outValue = value - pushConstants.inputZeroPoint;
                    VEC4 outWeight0 = VEC4(ACC_T(weight[0][0]), ACC_T(weight[0][1]), ACC_T(weight[0][2]), ACC_T(weight[0][3])) - pushConstants.weightZeroPoint;
                    VEC4 outWeight1 = VEC4(ACC_T(weight[1][0]), ACC_T(weight[1][1]), ACC_T(weight[1][2]), ACC_T(weight[1][3])) - pushConstants.weightZeroPoint;
                    VEC4 outWeight2 = VEC4(ACC_T(weight[2][0]), ACC_T(weight[2][1]), ACC_T(weight[2][2]), ACC_T(weight[2][3])) - pushConstants.weightZeroPoint;
                    VEC4 outWeight3 = VEC4(ACC_T(weight[3][0]), ACC_T(weight[3][1]), ACC_T(weight[3][2]), ACC_T(weight[3][3])) - pushConstants.weightZeroPoint;

                    VEC4 mul0 = outValue * outWeight0;
                    VEC4 mul1 = outValue * outWeight1;
                    VEC4 mul2 = outValue * outWeight2;
                    VEC4 mul3 = outValue * outWeight3;
                    for (uint idx = 0; idx < 4 && ic + idx < IC; ++idx) {
                        acc[0] += ACC_T(mul0[idx]);
                        acc[1] += ACC_T(mul1[idx]);
                        acc[2] += ACC_T(mul2[idx]);
                        acc[3] += ACC_T(mul3[idx]);
                    }
                }
            }
        }
    }

    if (tensorSizeARM(biasesData, 0) == 1) {
        OUT_T bias;
        tensorReadARM(biasesData, uint[](0), bias);
        acc[0] += ACC_T(bias);
        acc[1] += ACC_T(bias);
        acc[2] += ACC_T(bias);
        acc[3] += ACC_T(bias);
    } else {
        OUT_T bias[4];
        tensorReadARM(biasesData, uint[](oc), bias);
        acc[0] += ACC_T(bias[0]);
        acc[1] += ACC_T(bias[1]);
        acc[2] += ACC_T(bias[2]);
        acc[3] += ACC_T(bias[3]);
    }
    uint index[] = {n, oy, ox, oc};
    OUT_T outData[4] = OUT_T[](OUT_T(acc[0]), OUT_T(acc[1]), OUT_T(acc[2]), OUT_T(acc[3]));
    tensorWriteARM(outputData, index, outData);
}
)"
;
constexpr std::string_view conv3dGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_T %in_t%
#define OUT_T %out_t%
#define WEIGHT_T %weight_t%
#define TYPE_ACC %acc_t_type%
#define ACC_T %acc_t%

#if TYPE_ACC == TYPE_INT64
    #define VEC4 dvec4
#elif TYPE_ACC == TYPE_INT32
    #define VEC4 ivec4
#else
    #define VEC4 vec4
#endif

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    int32_t inputZeroPoint;
    int32_t weightZeroPoint;
    int32_t pad[6];             // [d0, d1, top, bottom, left, right]
    int32_t stride[3];          // [d, y, x]
    int32_t dilation[3];        // [d, y, x]
} pushConstants;

layout(set = 0, binding = 0) uniform tensorARM<OUT_T, 5> outputData;       // [N, OD, OH, OW, OC]
layout(set = 1, binding = 0) uniform tensorARM<IN_T, 5> inputData;         // [N, ID, IH, IW, IC]
layout(set = 2, binding = 0) uniform tensorARM<WEIGHT_T, 5> weightsData;   // [OC, KD, KH, KW, IC]
layout(set = 3, binding = 0) uniform tensorARM<OUT_T, 1> biasesData;       // [BC]

void main() {
    uint[5] index;
    getIndex5(outputData, index);

    ACC_T acc = ACC_T(0);

    uint n = index[0];
    uint od = index[1];
    uint oy = index[2];
    uint ox = index[3];
    uint oc = index[4];

    uint id = od * pushConstants.stride[0] - pushConstants.pad[0];
    uint iy = oy * pushConstants.stride[1] - pushConstants.pad[2];
    uint ix = ox * pushConstants.stride[2] - pushConstants.pad[4];

    uint KD = tensorSizeARM(weightsData, 1);
    uint KH = tensorSizeARM(weightsData, 2);
    uint KW = tensorSizeARM(weightsData, 3);
    uint IC = tensorSizeARM(weightsData, 4);

    uint ID = tensorSizeARM(inputData, 1);
    uint IH = tensorSizeARM(inputData, 2);
    uint IW = tensorSizeARM(inputData, 3);

    for (uint kd = 0; kd < KD; kd++) {
        for (uint ky = 0; ky < KH; ky++) {
            for (uint kx = 0; kx < KW; kx++) {
                uint d = id + kd * pushConstants.dilation[0];
                uint y = iy + ky * pushConstants.dilation[1];
                uint x = ix + kx * pushConstants.dilation[2];

                if (d < ID && y < IH && x < IW) {
                    for (uint ic = 0; ic < IC; ic += 4) {
                        IN_T tempValue[4];
                        tensorReadARM(inputData, uint[](n, d, y, x, ic), tempValue);
                        VEC4 value = VEC4(tempValue[0], tempValue[1], tempValue[2], tempValue[3]);

 )"
R"(                       WEIGHT_T tempWeight[4];
                        tensorReadARM(weightsData, uint[](oc, kd, ky, kx, ic), tempWeight);
                        VEC4 weight = VEC4(tempWeight[0], tempWeight[1], tempWeight[2], tempWeight[3]);

                        VEC4 outValue = VEC4(value[0], value[1], value[2], value[3]) - pushConstants.inputZeroPoint;
                        VEC4 outWeight = VEC4(weight[0], weight[1], weight[2], weight[3]) - pushConstants.weightZeroPoint;
                        VEC4 mul = outValue * outWeight;

                        for (uint idx = 0; idx < 4 && ic + idx < IC; ++idx) {
                            acc += ACC_T(mul[idx]);
                        }
                    }
                }
            }
        }
    }

    OUT_T bias;
    tensorReadARM(biasesData, uint[](tensorSizeARM(biasesData, 0) == 1 ? 0 : oc), bias);
    bias += OUT_T(acc);

    tensorWriteARM(outputData, index, bias);
}
)"
;
constexpr std::string_view depthwise_conv2dGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_T %in_t%
#define OUT_T %out_t%
#define WEIGHT_T %weight_t%
#define TYPE_ACC %acc_t_type%
#define ACC_T %acc_t%

#if TYPE_ACC == TYPE_INT64
    #define VEC4 dvec4
#elif TYPE_ACC == TYPE_INT32
    #define VEC4 ivec4
#else
    #define VEC4 vec4
#endif

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    int32_t inputZeroPoint;
    int32_t weightZeroPoint;
    int32_t pad[4];
    int32_t stride[2];
    int32_t dilation[2];
} pushConstants;

layout(set = 0, binding = 0) uniform tensorARM<OUT_T, 4> outputData;       // [N, OH, OW, C * M]
layout(set = 1, binding = 0) uniform tensorARM<IN_T, 4> inputData;         // [N, H, W, C]
layout(set = 2, binding = 0) uniform tensorARM<WEIGHT_T, 4> weightsData;   // [KH, KW, C, M]
layout(set = 3, binding = 0) uniform tensorARM<OUT_T, 1> biasesData;       // [BC]

void main() {
    uint[4] index;
    getIndex4(outputData, index);

    const uint n = index[0];
    const uint oy = index[1];
    const uint ox = index[2];
    const uint ocm = index[3];
    const uint c = ocm / tensorSizeARM(weightsData, 3);
    const uint m = ocm % tensorSizeARM(weightsData, 3);

    const uint iy = oy * pushConstants.stride[0] - pushConstants.pad[0];
    const uint ix = ox * pushConstants.stride[1] - pushConstants.pad[2];

    ACC_T acc = ACC_T(0);

    for (uint ky = 0; ky < tensorSizeARM(weightsData, 0); ky++) {
        for (uint kx = 0; kx < tensorSizeARM(weightsData, 1); kx++) {
            const uint y = iy + ky * pushConstants.dilation[0];
            const uint x = ix + kx * pushConstants.dilation[1];

            if (y < tensorSizeARM(inputData, 1) && x < tensorSizeARM(inputData, 2)) {
                IN_T tempValue;
                uint index[] = {n, y, x, c};
                tensorReadARM(inputData, index, tempValue);
                ACC_T value = ACC_T(tempValue);

                WEIGHT_T tempWeight;
                uint weightIndex[] = {ky, kx, c, m};
                tensorReadARM(weightsData, weightIndex, tempWeight);
                ACC_T weight = ACC_T(tempWeight);

                ACC_T outValue = ACC_T(value) - ACC_T(pushConstants.inputZeroPoint);
                ACC_T outWeight = ACC_T(weight) - ACC_T(pushConstants.weightZeroPoint);

                acc += outValue * outWeight;
            }
        }
    }

    OUT_T bias;)"
R"(
    tensorReadARM(biasesData, uint[](tensorSizeARM(biasesData, 0) == 1 ? 0 : ocm), bias);
    bias += OUT_T(acc);

    tensorWriteARM(outputData, index, bias);
}
)"
;
constexpr std::string_view elementwise_binaryGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_T %in_t%
#define OUT_T %out_t%
#define TYPE_IN %in_t_type%

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    uint nanMode;
} pushConstants;

layout(constant_id = 0) const uint32_t RANK_IN = RANK_MAX;
layout(constant_id = 1) const uint32_t RANK_OUT = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<OUT_T, RANK_OUT> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_T, RANK_IN> inputData1;
layout(set = 2, binding = 0) uniform tensorARM<IN_T, RANK_IN> inputData2;

uint zeroExtend(int8_t v) { return uint8_t(v); }

uint zeroExtend(int16_t v) { return uint16_t(v); }

uint zeroExtend(int32_t v) { return v; }

// I don't think min or max will ever actually be used with bool inputs, but `applyMax` and `applyMin` are always
// defined. Since builtin min and max do not support bool inputs, we define them here.
bool min(bool a, bool b){
    return a && b;
}

bool max(bool a, bool b){
    return a || b;
}

#if IS_FLOAT(TYPE_IN)
OUT_T power(IN_T base, IN_T exponent) {
    // Positive numbers can be passed directly to pow()
    if (base >= IN_T(0)) {
        return OUT_T(pow(base, exponent));
    }
    // Most ICD produce NaN for all negative numbers, whereas we want to handle
    // the special cases where then exponent is power of 1.0 or power of 2.0
    else {
        // If exponent is power of 2.0, then output should be a positive number
        if (mod(exponent, IN_T(2.0)) == 0.0) {
            return OUT_T(pow(-base, exponent));
        }
        // If exponent is power of 1.0, then output should be a negative number
        else if (mod(exponent, IN_T(1.0)) == 0.0) {
            return OUT_T(-pow(-base, exponent));
        }
        // Else output should be NaN
        else {
            return OUT_T(NAN);
        }
    }
}
#endif

OUT_T applyMin(IN_T a, IN_T b, uint nanMode)
{
#if IS_FLOAT(TYPE_IN)
    if (isnan(a)) {
        return nanMode == NAN_MODE_PROPAGATE ? OUT_T(a) : OUT_T(b);
    }
    else if (isnan(b)) {
        return nanMode == NAN_MODE_PROPAGATE ? OUT_T(b) : OUT_T(a);
    }
#endif

    return OUT_T(min(a, b));
}

OUT_T applyMax(IN_T a, IN_T b, uint nanMode)
{
#if IS_FLOAT(TYPE_IN)
    if (isnan(a)) {
        return nanMode == NAN_MODE_PROPAGATE ? OUT_T(a) : OUT_T(b);
    }
    else if (isnan(b)) {
        return nanMode == )"
R"(NAN_MODE_PROPAGATE ? OUT_T(b) : OUT_T(a);
    }
#endif

    return OUT_T(max(a, b));
}

void main() {
    uint[RANK_OUT] index;
    getIndex(outputData, index);

    // Input 1 tensorARM
    uint[RANK_IN] inputShape1;
    uint[RANK_IN] inputIndex1;
    IN_T value1;

    getShape(inputShape1, inputData1);
    applyBroadcast(inputShape1, index, inputIndex1);
    tensorReadARM(inputData1, inputIndex1, value1);

    // Input 2 tensorARM
    uint[RANK_IN] inputShape2;
    uint[RANK_IN] inputIndex2;
    IN_T value2;

    getShape(inputShape2, inputData2);
    applyBroadcast(inputShape2, index, inputIndex2);
    tensorReadARM(inputData2, inputIndex2, value2);

    // Output
    OUT_T value;
    value = OUT_T(%operation%);

    tensorWriteARM(outputData, index, value);
}
)"
;
constexpr std::string_view elementwise_unaryGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%

layout(local_size_x = %warpX%) in;

layout(constant_id = 0) const uint32_t RANK = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, RANK> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, RANK> inputData1;

// Count leading zeros
uint clz(int32_t value) {
    uint i;

    for (i = 0; i < 32; i++) {
        if ((value & (1 << (31 - i))) != 0) {
            break;
        }
    }

    return i;
}

// Gaussian error function
// https://en.wikipedia.org/wiki/Error_function
//
// Error function is an integral from 0 to x
//   (2 / sqrt(pi)) * int(0, x) (exp(-t^2))
//
// The function is always calculated for positive x, with negatives handled through erf(-x) = erf(x).
//
// Uses different approximations for small and intermediate x, with an emprically determined cutoff at |x|=0.5.
// For small x, we use the series expansion defined in 7.6.2 at https://dlmf.nist.gov/7.6#
// (Digital Library of Mathematical Functions, NIST).
// For intermediate x, we use an approximation of the complimentary error function erfc(x) = 1 - erf(x).
// This approximation is described in section 5.2 in
// Dia, Yaya D. (2023). "Approximate Incomplete Integrals, Application to Complementary Error Function".
// SSRN Electronic Journal. doi:10.2139/ssrn.4487559. ISSN 1556-5068.
//
// Both approximations rely on erf(x) being closely related to exp(-x^2).
// The approximation for small x uses a function f(x) such that erf(x) = f(x) exp(-x^2).
// It then estimates f(x) by truncating it's Taylor expansion.
// The intermediate x approximation defines for x > 0 a function M(x) where erfc(x) = 1 - erf(x) = M(x) exp(-x^2),
// and uses a multi point Padé approximation for M(x).
//
// For large x (|x| > 4.0), the value of erf(|x|) is equal to 1.0 in single precision, so we simply return +/- 1.0.
//
float erf(float x) {
    // ==== Constant parameters begin ====
    // Coefficients for for small x implementation
    // Precomputed values of (2 / (2n + 1)) n from 12 to 1
    const float coeffs[12] = float[](
        0.08,                0.08695652173913043, 0.09523809523809523, 0.10526315789473684,
        0.11764705882352941, 0.13333333333333333, 0.15384615384615385, 0.18181818181818182,
        0.22222222222222222, 0.28571428571428571, 0.4,                 0.66666666666666666)"
R"(
    );

    // dividing by sqrt(Pi) gives gives better accuracy than precomputing 1 / sqrtPi and multiplying
    const float sqrtPi = 1.7724538509055159;

    // Implementation for large x
    // Numerator quadratics
    const vec2[5] pCoeffs = vec2[](
        vec2(3.47469513777439592, 12.07402036406381411),
        vec2(4.00561509202259545,  9.30596659485887898),
        vec2(5.95908795446633271,  9.19435612886969243),
        vec2(5.16722705817812584,  9.12661617673673262),
        vec2(2.71078540045147805,  5.80755613130301624)
    );

    // Denominator quadratics
    const vec2[5] qCoeffs = vec2[](
        vec2(3.47954057099518960, 12.06166887286239555),
        vec2(3.72068443960225092,  8.44319781003968454),
        vec2(3.90225704029924078,  6.36161630953880464),
        vec2(4.03296893109262491,  5.13578530585681539),
        vec2(4.11240942957450885,  4.48640329523408675)
    );

    // Lower order quotient polynomials
    const float p_0 = 0.56418958354775629;
    const float q_0 = 2.06955023132914151;

    // Cutoffs
    const float cutoff_low = 0.6;  // for deciding which approximation to use
    const float cutoff_high = 4.0; // above this value, erf(x) == 1.0 for float precision

    // ==== Constant parameters end ====

    const float s = sign(x);
    x = abs(x); // Always calculate erf(|x|)

    if (x > cutoff_high){
        // Large x; also catches inf
        return s; // returns +/- 1.0
    }

    // x squared; reused extensively
    const float x2 = x * x;

    if (x < cutoff_low){
        // Small x
        float tot = 1.0;
        // Calculate the sum of (2^n x^(2n+1) / (2n + 1)!!) for n from 1 to coeffs.length(),
        // where (2n + 1)!! = 1 * 3 * 5 * ... * (2n + 1).
        // This is the Taylor expansion (up to a rescaling) of erf(x) / exp(-x^2) around x = 0
        for (int i = 0; i < coeffs.length(); i++){
            tot = 1.0 + tot * coeffs[i] * x2;
        }
        tot *= 2.0 * x * exp(-x2);
        tot /= sqrtPi;

        return s * tot;
    }

    // Intermediate x
    // Estimate the complimentary error function erfc(x) = 1 - erf(x) from a Padé approximation of erfc(x) / exp(-x^2).
    // The numerator and denominator polynomials have been factorized into quadratic (or lower) factors.
    const vec3 terms = vec3(x2, x, 1.0); // Use vec3 for fast evaluation of the quadratic polynomial factors.
    float prod = p_0 / (x + q_0);
    for (int i = 0; i < pCoeffs.length(); i++) {
        float p = dot(terms, vec3(1.0, pCoeffs[i])); // numerator polynomial
        float q = dot(terms, vec3(1.0, qCoeffs[i])); // denominator polynomial
        prod *= p / q;
    }
    prod = 1.0 - prod * exp(-x2);
    return s * prod;
}

float tanh_clamped(float x)
{
    if(x > 10.0){
        return 1.0;
    }
    if(x < -10.0){
        return -1.0;
    }
    return tanh(x);
}

float log_guarded(float x) {
    return x < 0.0 ? NAN : log(x);
}

void main() {
    uint[RANK] index;
    getIndex(outputData, index);

    IN_OUT_T value1;
    tensorReadARM(inputData1, index, value1);

    IN_OUT_T value = isnan(float(value1)) ? IN_OUT_T(value1) : IN_OUT_T(%operation%);
    tensorWriteARM(outputData, index, value);
}
)"
;
constexpr std::string_view fft2dGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2024 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    float signValue;
} pushConstants;

layout(set = 0, binding = 0) uniform tensorARM<float, 3> outputRealData;
layout(set = 1, binding = 0) uniform tensorARM<float, 3> outputImagData;
layout(set = 2, binding = 0) uniform tensorARM<float, 3> inputRealData;
layout(set = 3, binding = 0) uniform tensorARM<float, 3> inputImagData;

void main() {
    uint[3] index;
    getIndex3(outputRealData, index);

    const uint[3] shape = {
        tensorSizeARM(outputRealData, 0),
        tensorSizeARM(outputRealData, 1),
        tensorSizeARM(outputRealData, 2),
    };

    uint on = index[0];
    uint oy = index[1];
    uint ox = index[2];

    double sumReal = 0.0;
    double sumImag = 0.0;

    for (uint iy = 0; iy < shape[1]; iy++) {
        for (uint ix = 0; ix < shape[2]; ix += 4) {
            vec4 ixs = vec4(ix, ix + 1, ix + 2, ix + 3);
            float valueReal[4];
            tensorReadARM(inputRealData, uint[](on, iy, ix), valueReal);
            vec4 valueRealVec = vec4(valueReal[0], valueReal[1], valueReal[2], valueReal[3]);

            float valueImag[4];
            tensorReadARM(inputImagData, uint[](on, iy, ix), valueImag);
            vec4 valueImagVec = vec4(valueImag[0], valueImag[1], valueImag[2], valueImag[3]);

            vec4 angles = pushConstants.signValue * 2.0f * PI * (float(iy * oy) / shape[1] + ixs * ox / shape[2]);
            sumReal += dot(valueRealVec, cos(angles)) + dot(valueImagVec, sin(angles));
            sumImag += -dot(valueRealVec, sin(angles)) + dot(valueImagVec, cos(angles));
        }
    }

    tensorWriteARM(outputRealData, index, float(sumReal));
    tensorWriteARM(outputImagData, index, float(sumImag));
}
)"
;
constexpr std::string_view gatherGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2024 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%
#define INDEX_T %index_t%

layout(local_size_x = %warpX%) in;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, 3> outputData;    // [N, W, C]
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, 3> valuesData;    // [N, K, C]
layout(set = 2, binding = 0) uniform tensorARM<INDEX_T, 2> indicesData;    // [N, W]

void main() {
    uint[3] index;
    getIndex3(outputData, index);

    INDEX_T k;
    tensorReadARM(indicesData, uint[](index[0], index[1]), k);

    IN_OUT_T value;
    tensorReadARM(valuesData, uint[](index[0], uint(k), index[2]), value);

    tensorWriteARM(outputData, index, value);
}
)"
;
constexpr std::string_view matmulGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_T %in_t%
#define OUT_T %out_t%
#define TYPE_OUT %out_t_type%

#if TYPE_OUT == TYPE_INT64
    #define VEC4 dvec4
#elif TYPE_OUT == TYPE_INT32
    #define VEC4 ivec4
#else
    #define VEC4 vec4
#endif

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    int32_t inputZeroPoint1;
    int32_t inputZeroPoint2;
} pushConstants;

layout(set = 0, binding = 0) uniform tensorARM<OUT_T, 3> outputData;   // [N, H, W]
layout(set = 1, binding = 0) uniform tensorARM<IN_T, 3> inputData1;    // [N, H, C]
layout(set = 2, binding = 0) uniform tensorARM<IN_T, 3> inputData2;    // [N, C, W]

void main() {
    uint[3] index;
    getIndex3(outputData, index);

    uint on = index[0];
    uint oy = index[1];
    uint ox = index[2];

    OUT_T acc = OUT_T(0);

    const uint IC = tensorSizeARM(inputData1, 2);
    for (uint c = 0; c < IC; c += 4) {
        IN_T value1[4];
        tensorReadARM(inputData1, uint[](on, oy, c), value1);

        IN_T value20, value21, value22, value23;
        tensorReadARM(inputData2, uint[](on, c, ox), value20);
        tensorReadARM(inputData2, uint[](on, c + 1, ox), value21);
        tensorReadARM(inputData2, uint[](on, c + 2, ox), value22);
        tensorReadARM(inputData2, uint[](on, c + 3, ox), value23);

        VEC4 val1 = VEC4(value1[0], value1[1], value1[2], value1[3]) - pushConstants.inputZeroPoint1;
        VEC4 val2 = VEC4(value20, value21, value22, value23) - pushConstants.inputZeroPoint2;
        VEC4 mul = val1 * val2;

        for (uint idx = 0; idx < 4 && c + idx < IC; ++idx) {
            acc += OUT_T(mul[idx]);
        }
    }

    tensorWriteARM(outputData, index, acc);
}
)"
;
constexpr std::string_view maxpool2dGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%
#define TYPE_IN_OUT %in_out_t_type%

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    uint kernel[2];
    uint stride[2];
    uint pad[4];
    uint nanMode;
} pushConstants;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, 4> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, 4> inputData;

void main() {
    uint[4] index;
    getIndex4(outputData, index);

    IN_OUT_T acc = IN_OUT_T(%in_out_t_lowest%);
    uint on = index[0];
    uint oy = index[1];
    uint ox = index[2];
    uint oc = index[3];

    uint iy = oy * pushConstants.stride[0] - pushConstants.pad[0];
    uint ix = ox * pushConstants.stride[1] - pushConstants.pad[2];

    for (uint ky = 0; ky < pushConstants.kernel[0]; ky++) {
        for (int kx = 0; kx < pushConstants.kernel[1]; kx++) {
            uint y = iy + ky;
            uint x = ix + kx;

            if (y < tensorSizeARM(inputData, 1) && x < tensorSizeARM(inputData, 2)) {
                IN_OUT_T value;
                tensorReadARM(inputData, uint[](on, y, x, oc), value);

#if IS_FLOAT(TYPE_IN_OUT)
                if (isnan(value)) {
                    if (pushConstants.nanMode == NAN_MODE_IGNORE) {
                        // Ignore value and continue
                        continue;
                    }
                    else {
                        // If any value is NaN, then the result must be NaN
                        tensorWriteARM(outputData, index, value);
                        return;
                    }
                }
#endif
                acc = max(acc, value);
            }
        }
    }

    tensorWriteARM(outputData, index, acc);
}
)"
;
constexpr std::string_view mulGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_T %in_t%
#define OUT_T %out_t%
#define TYPE_IN %in_t_type%

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    uint shift;
} pushConstants;

layout(constant_id = 0) const uint32_t RANK_IN = RANK_MAX;
layout(constant_id = 1) const uint32_t RANK_OUT = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<OUT_T, RANK_OUT> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_T, RANK_IN> inputData1;
layout(set = 2, binding = 0) uniform tensorARM<IN_T, RANK_IN> inputData2;

void main() {
    uint[RANK_OUT] index;
    getIndex(outputData, index);

    uint[RANK_IN] inputShape1;
    uint[RANK_IN] inputIndex1;
    IN_T value1;

    getShape(inputShape1, inputData1);
    applyBroadcast(inputShape1, index, inputIndex1);
    tensorReadARM(inputData1, inputIndex1, value1);

    uint[RANK_IN] inputShape2;
    uint[RANK_IN] inputIndex2;
    IN_T value2;

    getShape(inputShape2, inputData2);
    applyBroadcast(inputShape2, index, inputIndex2);
    tensorReadARM(inputData2, inputIndex2, value2);

#if IS_FLOAT(TYPE_IN)
    OUT_T result = OUT_T(value1) * OUT_T(value2);
#else
    int64_t result = int64_t(value1) * int64_t(value2);

    if (pushConstants.shift > 0) {
        result = (result + (int64_t(1) << (pushConstants.shift - 1))) >> pushConstants.shift;
    }
#endif

    tensorWriteARM(outputData, index, OUT_T(result));
}
)"
;
constexpr std::string_view negateGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%
#define ACC_T %acc_t%
#define MIN %in_out_t_lowest%
#define MAX %in_out_t_max%

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    int32_t inputZeroPoint;
    int32_t outputZeroPoint;
} pushConstants;

layout(constant_id = 0) const uint32_t RANK = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, RANK> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, RANK> inputData;

void main() {
    uint[RANK] index;
    getIndex(outputData, index);

    IN_OUT_T value;
    tensorReadARM(inputData, index, value);

    ACC_T res = ACC_T(pushConstants.inputZeroPoint) - ACC_T(value) + ACC_T(pushConstants.outputZeroPoint);
    res = isnan(float(value)) ? value : isinf(float(value)) ? -value : clamp(res, ACC_T(MIN), ACC_T(MAX));

    tensorWriteARM(outputData, index, IN_OUT_T(res));
}
)"
;
constexpr std::string_view padGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    double padConst;
} pushConstants;

layout(constant_id = 0) const uint32_t RANK = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, RANK> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, RANK> inputData;
layout(set = 2, binding = 0) uniform tensorARM<int32_t, 1> paddingData;

void main() {
    uint[RANK] index;
    getIndex(outputData, index);

    uint[RANK] inputShape;
    getShape(inputShape, inputData);

    uint[RANK] inputIndex;
    bool isPad = false;
    for (uint i = 0; i < RANK; i++) {
        int32_t padding;
        tensorReadARM(paddingData, uint[1](2*i), padding);

        inputIndex[i] = index[i] - padding;
        if (inputIndex[i] >= inputShape[i]) {
            isPad = true;
            break;
        }
    }

    IN_OUT_T value;
    if (isPad) {
        value = IN_OUT_T(pushConstants.padConst);
    } else {
        tensorReadARM(inputData, inputIndex, value);
    }

    tensorWriteARM(outputData, index, value);
}
)"
;
constexpr std::string_view reduceGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%
#define TYPE_IN_OUT %in_out_t_type%

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    uint axis;
    uint nanMode;
} pushConstants;

layout(constant_id = 0) const uint32_t RANK = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, RANK> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, RANK> inputData;

void main() {
    uint[RANK] index;
    getIndex(outputData, index);

    const uint dim = index[pushConstants.axis];

    IN_OUT_T result = IN_OUT_T(%init%);

    uint[RANK] inputShape;
    getShape(inputShape, inputData);

    for (uint i = 0; i < inputShape[pushConstants.axis]; i++) {
        index[pushConstants.axis] = i;
        IN_OUT_T value;
        tensorReadARM(inputData, index, value);

#if IS_FLOAT(TYPE_IN_OUT)
        if (isnan(value)) {
            if (pushConstants.nanMode == NAN_MODE_IGNORE) {
                // Ignore value and continue
                continue;
            }
            if (pushConstants.nanMode == NAN_MODE_PROPAGATE) {
                // If any value is NaN, then the result must be NaN
                result = value;
                break;
            }
        }
#endif

        result = IN_OUT_T(%operation%);
    }

    index[pushConstants.axis] = dim;
    tensorWriteARM(outputData, index, result);
}
)"
;
constexpr std::string_view rescaleGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_T %in_t%
#define MUL_T %mul_t%
#define OUT_T %out_t%

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    int32_t inputZeroPoint;
    int32_t outputZeroPoint;
} pushConstants;

layout(constant_id = 0) const uint32_t RANK = RANK_MAX;
layout(constant_id = 1) const uint32_t SCALE32 = 0;
layout(constant_id = 2) const uint32_t DOUBLE_ROUND = 0;
layout(constant_id = 3) const uint32_t PER_CHANNEL = 0;

layout(set = 0, binding = 0) uniform tensorARM<OUT_T, RANK> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_T, RANK> inputData;
layout(set = 2, binding = 0) uniform tensorARM<MUL_T, 1> multiplier;
layout(set = 3, binding = 0) uniform tensorARM<int8_t, 1> shiftData;

int32_t applyScale(int64_t value, int32_t multiplier, int8_t shift, bool doubleRound) {
    int64_t round = int64_t(1) << (shift - 1);

    if (doubleRound) {
        if (shift > 31) {
            if (value >= 0) {
                round += 1 << 30;
            }
            else {
                round -= 1 << 30;
            }
        }
    }

    int64_t result = value * multiplier;
    result += round;
    result >>= shift;

    return int32_t(result);
}

void main() {
    uint[RANK] index;
    getIndex(outputData, index);

    const bool scale32 = SCALE32 != 0;
    const bool doubleRound = DOUBLE_ROUND != 0;
    const bool perChannel = PER_CHANNEL != 0;
    const uint c = perChannel ? index[RANK - 1] : uint(0);

    IN_T val;
    tensorReadARM(inputData, index, val);
    int64_t value = int64_t(val) - int64_t(IN_T(pushConstants.inputZeroPoint));

    MUL_T mulVal;
    tensorReadARM(multiplier, uint[1](c), mulVal);

    int8_t shiftVal;
    tensorReadARM(shiftData, uint[1](c), shiftVal);

    int32_t result = applyScale(value, int32_t(mulVal), shiftVal, scale32 && doubleRound);
    result += OUT_T(pushConstants.outputZeroPoint);
    result = int32_t(clamp(result, OUT_T(%out_t_lowest%), OUT_T(%out_t_max%)));

    tensorWriteARM(outputData, index, OUT_T(result));
}
)"
;
constexpr std::string_view reshapeGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2024 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%

layout(local_size_x = %warpX%) in;

layout(constant_id = 0) const uint32_t RANK_IN = RANK_MAX;
layout(constant_id = 1) const uint32_t RANK_OUT = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, RANK_OUT> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, RANK_IN> inputData;

void main() {
    uint[RANK_OUT] index;
    getIndex(outputData, index);

    uint[RANK_IN] inputIndex;
    getIndex(inputData, inputIndex);

    IN_OUT_T value;

    tensorReadARM(inputData, inputIndex, value);
    tensorWriteARM(outputData, index, value);
}
)"
;
constexpr std::string_view resizeGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_T %in_t%
#define OUT_T %out_t%
#define TYPE_OUT %out_t_type%

#define NEAREST     1
#define BILINEAR    2

layout(local_size_x = %warpX%) in;

struct ND {
    int32_t n;
    int32_t d;
};

struct Scale {
    ND y;
    ND x;
};

struct YX {
    int32_t y;
    int32_t x;
};

layout(push_constant) uniform PushConstants {
    Scale scale;
    YX offset;
    YX border;
    uint mode;
} pushConstants;

layout(set = 0, binding = 0) uniform tensorARM<OUT_T, 4> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_T, 4> inputData;

int idivFloor(int numerator, int denominator) {
    int result = numerator / denominator;

    if (result * denominator > numerator) {
        result--;
    }

    return result;
}

void main() {
    uint[4] index;
    getIndex4(outputData, index);

    OUT_T acc = OUT_T(0);

    uint n = index[0];
    uint oy = index[1];
    uint ox = index[2];
    uint c = index[3];

    uint[4] inputShape = {
        tensorSizeARM(inputData, 0),
        tensorSizeARM(inputData, 1),
        tensorSizeARM(inputData, 2),
        tensorSizeARM(inputData, 3)
    };

#if IS_FLOAT(TYPE_OUT)
    OUT_T unit_y = OUT_T(1.0);
    OUT_T unit_x = OUT_T(1.0);
#else
    int16_t unit_y = int16_t(pushConstants.scale.y.n);
    int16_t unit_x = int16_t(pushConstants.scale.x.n);
#endif

    int32_t y = int32_t(oy * pushConstants.scale.y.d + pushConstants.offset.y);
    int16_t iy = int16_t(idivFloor(y, pushConstants.scale.y.n));
    int16_t ry = int16_t(y - iy * pushConstants.scale.y.n);

    int32_t x = int32_t(ox * pushConstants.scale.x.d + pushConstants.offset.x);
    int16_t ix = int16_t(idivFloor(x, pushConstants.scale.x.n));
    int16_t rx = int16_t(x - ix * pushConstants.scale.x.n);

#if IS_FLOAT(TYPE_OUT)
    OUT_T dy = OUT_T(ry) / OUT_T(pushConstants.scale.y.n);
    OUT_T dx = OUT_T(rx) / OUT_T(pushConstants.scale.x.n);
#else
    int16_t dy = ry;
    int16_t dx = rx;
#endif

    int16_t iy0 = int16_t(max(iy, 0));
    int16_t iy1 = int16_t(min(iy + 1, inputShape[1] - 1));
    int16_t ix0 = int16_t(max(ix, 0));
    int16_t ix1 = int16_t(min(ix + 1, inputShape[2] - 1));

    if (pushConstants.mode == BILINEAR) {
        IN_T v00;
        tensorReadARM(inputData, uint[](n, iy0, ix0, c), v00);

        IN_T v01;
        tensorReadARM(inputData, uint[](n, iy0, ix1, c), v01);

        IN_T v1)"
R"(0;
        tensorReadARM(inputData, uint[](n, iy1, ix0, c), v10);

        IN_T v11;
        tensorReadARM(inputData, uint[](n, iy1, ix1, c), v11);

        acc  = OUT_T(v00) * OUT_T(unit_y - dy) * OUT_T(unit_x - dx);
        acc += OUT_T(v01) * OUT_T(unit_y - dy) * OUT_T(dx);
        acc += OUT_T(v10) * OUT_T(dy) * OUT_T(unit_x - dx);
        acc += OUT_T(v11) * OUT_T(dy) * OUT_T(dx);
    } else if (pushConstants.mode == NEAREST) {
#if IS_FLOAT(TYPE_OUT)
        int32_t iy = (dy >= 0.5) ? iy1 : iy0;
        int32_t ix = (dx >= 0.5) ? ix1 : ix0;
#else
        int32_t iy = (2 * dy >= pushConstants.scale.y.n) ? iy1 : iy0;
        int32_t ix = (2 * dx >= pushConstants.scale.x.n) ? ix1 : ix0;
#endif

        IN_T value;
        tensorReadARM(inputData, uint[](n, iy, ix, c), value);

        acc = OUT_T(value);
    }

    tensorWriteARM(outputData, uint[](n, oy, ox, c), acc);
}
)"
;
constexpr std::string_view reverseGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2024 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    uint32_t axis;
} pushConstants;

layout(constant_id = 0) const uint32_t RANK = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, RANK> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, RANK> inputData;

void main() {
    uint[RANK] index;
    getIndex(outputData, index);

    uint[RANK] shape;
    getShape(shape, outputData);

    IN_OUT_T value;
    tensorReadARM(inputData, index, value);

    index[pushConstants.axis] = shape[pushConstants.axis] - 1 - index[pushConstants.axis];
    tensorWriteARM(outputData, index, value);
}
)"
;
constexpr std::string_view rfft2dGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2024-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

layout(local_size_x = %warpX%) in;

layout(set = 0, binding = 0) uniform tensorARM<float, 3> outputRealData;
layout(set = 1, binding = 0) uniform tensorARM<float, 3> outputImagData;
layout(set = 2, binding = 0) uniform tensorARM<float, 3> inputData;

void main() {
    uint[3] index;
    getIndex3(outputRealData, index);

    uint on = index[0];
    uint oy = index[1];
    uint ox = index[2];
    uint N = tensorSizeARM(inputData, 0);
    uint H = tensorSizeARM(inputData, 1);
    uint W = tensorSizeARM(inputData, 2);

    // Use Kahan summation to counteract cumulative errors in float summation
    float sumReal = 0.0;
    float sumImag = 0.0;
    precise float errorReal = 0.0;
    precise float errorImag = 0.0;

    bool skipImag = false;
    if (oy == 0 && (ox == 0 || ox == (W / 2))) {
        skipImag = true;
    } else if (oy == (H / 2) && (ox == 0 || ox == (W / 2))) {
        skipImag = true;
    }

    for (uint iy = 0; iy < H; iy++) {
        for (uint ix = 0; ix < W; ix += 4) {
            vec4 ixs = vec4(ix, ix + 1, ix + 2, ix + 3);

            float valueReal[4];
            tensorReadARM(inputData, uint[](on, iy, ix), valueReal);
            vec4 valueRealVec = vec4(valueReal[0], valueReal[1], valueReal[2], valueReal[3]);

            // Angles are fractional multiples of 2 pi with a fixed denominator.
            // Taking the numerators modulo the denominator maps the fractions to the range [0, 1),
            // giving angles in [0, 2 pi).
            // Mathematically this gives the same result for sin and cos but numerically it is
            // more accurate since we avoid large angles.
            vec4 angles = 2.0 * PI * mod(iy * oy * W + ixs * ox * H, W * H) / (W * H);

            // Compute next term in the sum and subtract the accumulated error from it
            float termReal = dot(valueRealVec, cos(angles)) - errorReal;
            // Compute new sum
            precise float sumNewReal = sumReal + termReal;
            // Compute new error; algebraically this is always 0
            errorReal = (sumNewReal - sumReal) - termReal;
            // Update sum
            sumReal = sumNewReal;

            if (!skipImag){
                float termImag = dot(valueRealVec, -sin(angles)) - errorImag;
                precise float sumNewImag = sumImag + termImag;
                )"
R"(errorImag = (sumNewImag - sumImag) - termImag;
                sumImag = sumNewImag;
            }
        }
    }

    // Write output
    tensorWriteARM(outputRealData, index, sumReal);
    tensorWriteARM(outputImagData, index, sumImag);
}
)"
;
constexpr std::string_view scatterGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2024 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%
#define INDEX_T %index_t%

layout(local_size_x = %warpX%) in;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, 3> outputData;    // [N, K, C]
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, 3> inputData;     // [N, W, C]
layout(set = 2, binding = 0) uniform tensorARM<IN_OUT_T, 3> valuesData;    // [N, K, C]
layout(set = 3, binding = 0) uniform tensorARM<INDEX_T, 2> indicesData;    // [N, W]

void main() {
    uint[3] index;
    getIndex3(outputData, index);

    IN_OUT_T value;
    tensorReadARM(valuesData, index, value);

    uint W = tensorSizeARM(indicesData, 1);
    for (uint w = 0; w < W; w++) {
        INDEX_T k;
        tensorReadARM(indicesData, uint[](index[0], w), k);

        if (k == index[1]) {
            tensorReadARM(inputData, uint[](index[0], w, index[2]), value);
            break;
        }
    }

    tensorWriteARM(outputData, index, value);
}
)"
;
constexpr std::string_view selectGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2024 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%

layout(local_size_x = %warpX%) in;

layout(constant_id = 0) const uint32_t RANK = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, RANK> outputData;
layout(set = 1, binding = 0) uniform tensorARM<uint8_t, RANK> inputData1;
layout(set = 2, binding = 0) uniform tensorARM<IN_OUT_T, RANK> inputData2;
layout(set = 3, binding = 0) uniform tensorARM<IN_OUT_T, RANK> inputData3;

void main() {
    uint[RANK] index;
    getIndex(outputData, index);

    uint[RANK] inputShape;
    uint[RANK] inputIndex;
    uint8_t value1;

    getShape(inputShape, inputData1);
    applyBroadcast(inputShape, index, inputIndex);
    tensorReadARM(inputData1, inputIndex, value1);

    IN_OUT_T result;

    if (value1 != 0) {
        getShape(inputShape, inputData2);
        applyBroadcast(inputShape, index, inputIndex);
        tensorReadARM(inputData2, inputIndex, result);
    } else {
        getShape(inputShape, inputData3);
        applyBroadcast(inputShape, index, inputIndex);
        tensorReadARM(inputData3, inputIndex, result);
    }

    tensorWriteARM(outputData, index, IN_OUT_T(result));
}
)"
;
constexpr std::string_view sliceGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2024 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */


#define IN_OUT_T %in_out_t%

layout(local_size_x = %warpX%) in;

layout(constant_id = 0) const uint32_t RANK = RANK_MAX;

layout(push_constant) uniform PushConstants {
    uint start[RANK];
} pushConstants;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, RANK> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, RANK> inputData;

void main() {
    uint[RANK] index;
    getIndex(outputData, index);

    uint[RANK] inputIndex;
    for (uint i = 0; i < inputIndex.length(); i++) {
        inputIndex[i] = index[i] + pushConstants.start[i];
    }

    IN_OUT_T value;
    tensorReadARM(inputData, inputIndex, value);

    tensorWriteARM(outputData, index, value);
}
)"
;
constexpr std::string_view tableGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2024 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_T %in_t%
#define OUT_T %out_t%

layout(local_size_x = %warpX%) in;

layout(constant_id = 0) const uint32_t RANK = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<OUT_T, RANK> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_T, RANK> inputData;
layout(set = 2, binding = 0) uniform tensorARM<IN_T, 1> tableData;

int32_t lookup(int8_t value) {
    IN_T tableValue;
    tensorReadARM(tableData, uint[](value + 128), tableValue);

    return tableValue;
}

int32_t lookup(int16_t value) {
    int32_t index = (int32_t(value) + 32768) >> 7;
    int32_t fraction = value & 0x7f;

    IN_T tableValue[2];
    tensorReadARM(tableData, uint[](index), tableValue);

    int32_t base = tableValue[0];
    int32_t next = tableValue[1];
    int32_t slope = next - base;
    int32_t result = (base << 7) + slope * fraction;

    return result;
}

void main() {
    uint[RANK] index;
    getIndex(outputData, index);

    IN_T value;
    tensorReadARM(inputData, index, value);

    tensorWriteARM(outputData, index, OUT_T(lookup(value)));
}
)"
;
constexpr std::string_view tileGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%

layout(local_size_x = %warpX%) in;

layout(constant_id = 0) const uint32_t RANK = RANK_MAX;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, RANK> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, RANK> inputData;

void main() {
    uint[RANK] index;
    getIndex(outputData, index);

    uint[RANK] inputShape;
    getShape(inputShape, inputData);

    uint[RANK] inputIndex;
    for (uint i = 0; i < RANK; i++) {
        inputIndex[i] = index[i] % inputShape[i];
    }

    IN_OUT_T value;
    tensorReadARM(inputData, inputIndex, value);

    tensorWriteARM(outputData, index, value);
}
)"
;
constexpr std::string_view transposeGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2024 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_OUT_T %in_out_t%

layout(local_size_x = %warpX%) in;

layout(constant_id = 0) const uint32_t RANK = RANK_MAX;

layout(push_constant) uniform PushConstants {
    uint perms[RANK];
} pushConstants;

layout(set = 0, binding = 0) uniform tensorARM<IN_OUT_T, RANK> outputData;
layout(set = 1, binding = 0) uniform tensorARM<IN_OUT_T, RANK> inputData;

void main() {
    uint[RANK] index;
    getIndex(outputData, index);

    uint inputIndex[RANK];
    for (uint i = 0; i < inputIndex.length(); i++) {
        inputIndex[pushConstants.perms[i]] = index[i];
    }

    IN_OUT_T value;
    tensorReadARM(inputData, inputIndex, value);

    tensorWriteARM(outputData, index, value);
}
)"
;
constexpr std::string_view transpose_conv2dGLSL =
R"(/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#version 460
#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_ARM_tensors : enable

// Maximum supported rank
#define RANK_MAX 6

#define NAN (0.0 / 0.0)
#define PI 3.141592653589793238462643383279502884197

// NAN Modes
#define NAN_MODE_PROPAGATE 1
#define NAN_MODE_IGNORE 2

// Types
#define TYPE_BOOL 0x6231   // "b1"
#define TYPE_INT8 0x6931   // "i1"
#define TYPE_INT16 0x6932  // "i2"
#define TYPE_INT32 0x6934  // "i4"
#define TYPE_INT64 0x6938  // "i8"
#define TYPE_HALF 0x6632   // "f2"
#define TYPE_FLOAT 0x6634  // "f4"
#define TYPE_DOUBLE 0x6638 // "f8"

#define IS_BOOL(t) (t == TYPE_BOOL)
#define IS_INTEGER(t) ((t >> 8) == 0x69)
#define IS_FLOAT(t) ((t >> 8) == 0x66)

#define applyBroadcast(shape, index, coords)                                                                           \
    {                                                                                                                  \
        for (int i = int(shape.length() - 1); i >= 0; i--) {                                                           \
            coords[i] = index[i];                                                                                      \
            if (shape[i] == 1) {                                                                                       \
                coords[i] = 0;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
    }

#define offsetToIndex(shape, offset, index)                                                                            \
    {                                                                                                                  \
        uint off = offset;                                                                                             \
        for (int i = int(index.length() - 1); i >= 0; i--) {                                                           \
            index[i] = off % shape[i];                                                                                 \
            off /= shape[i];                                                                                           \
        }                                                                                                              \
                                                                                                                       \
        if (off > 0) {                                                                                                 \
            return;                                                                                                    \
        }                                                                                                              \
    }

#define getShape(shape, tensorARM)                                                                                     \
    {                                                                                                                  \
        if (shape.length() == 6) {                                                                                     \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
            shape[5] = tensorSizeARM(tensorARM, 5);                                                                    \
        } else if (shape.length() == 5) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
            shape[4] = tensorSizeARM(tensorARM, 4);                                                                    \
        } else if (shape.length() == 4) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
            shape[3] = tensorSizeARM(tensorARM, 3);                                                                    \
        } else if (shape.length() == 3) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
            shape[2] = tensorSizeARM(tensorARM, 2);                                                                    \
        } else if (shape.length() == 2) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
            shape[1] = tensorSizeARM(tensorARM, 1);                                                                    \
        } else if (shape.length() == 1) {                                                                              \
            shape[0] = tensorSizeARM(tensorARM, 0);                                                                    \
        }                                                                                                              \
    }

#define getIndex(tensorARM, index)                                                                                     \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        getShape(shape, tensorARM);                                                                                    \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex2(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex3(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex4(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }

#define getIndex5(tensorARM, index)                                                                                    \
    {                                                                                                                  \
        const uint offset =                                                                                            \
            gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * gl_NumWorkGroups.x * gl_WorkGroupSize.x;               \
                                                                                                                       \
        uint[index.length()] shape;                                                                                    \
        shape[0] = tensorSizeARM(tensorARM, 0);                                                                        \
        shape[1] = tensorSizeARM(tensorARM, 1);                                                                        \
        shape[2] = tensorSizeARM(tensorARM, 2);                                                                        \
        shape[3] = tensorSizeARM(tensorARM, 3);                                                                        \
        shape[4] = tensorSizeARM(tensorARM, 4);                                                                        \
                                                                                                                       \
        offsetToIndex(shape, offset, index);                                                                           \
    }
/*
 * SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
 * SPDX-License-Identifier: Apache-2.0
 */

#define IN_T %in_t%
#define OUT_T %out_t%
#define WEIGHT_T %weight_t%
#define TYPE_ACC %acc_t_type%
#define ACC_T %acc_t%

#if TYPE_ACC == TYPE_INT64
    #define VEC4 dvec4
#elif TYPE_ACC == TYPE_INT32
    #define VEC4 ivec4
#else
    #define VEC4 vec4
#endif

layout(local_size_x = %warpX%) in;

layout(push_constant) uniform PushConstants {
    int32_t inputZeroPoint;
    int32_t weightZeroPoint;
    int32_t pad[4];
    int32_t stride[2];
} pushConstants;

layout(set = 0, binding = 0) uniform tensorARM<OUT_T, 4> outputData;       // [N, OH, OW, OC]
layout(set = 1, binding = 0) uniform tensorARM<IN_T, 4> inputData;         // [N, IH, IW, IC]
layout(set = 2, binding = 0) uniform tensorARM<WEIGHT_T, 4> weightsData;   // [OC, KH, KW, IC]
layout(set = 3, binding = 0) uniform tensorARM<OUT_T, 1> biasesData;       // [BC]

void main() {
    uint[4] index;
    getIndex4(outputData, index);

    const uint n = index[0];
    const uint oy = index[1];
    const uint ox = index[2];
    const uint oc = index[3];

    OUT_T tempAcc;
    tensorReadARM(biasesData, uint[](tensorSizeARM(biasesData, 0) == 1 ? 0 : oc), tempAcc);
    ACC_T acc = ACC_T(tempAcc);

    for (uint ky = 0; ky < tensorSizeARM(weightsData, 1); ky++) {
        for (uint kx = 0; kx < tensorSizeARM(weightsData, 2); kx++) {
            uint iy = oy - pushConstants.pad[0] - ky;
            uint ix = ox - pushConstants.pad[2] - kx;

            if (((iy % pushConstants.stride[0]) == 0) && ((ix % pushConstants.stride[1]) == 0)) {
                iy /= pushConstants.stride[0];
                ix /= pushConstants.stride[1];

                if ((iy < tensorSizeARM(inputData, 1)) && (ix < tensorSizeARM(inputData, 2))) {
                    const uint IC = tensorSizeARM(inputData, 3);
                    for (uint ic = 0; ic < IC; ic += 4) {
                        IN_T tempValue[4];
                        tensorReadARM(inputData, uint[](n, iy, ix, ic), tempValue);
                        VEC4 value = VEC4(tempValue[0], tempValue[1], tempValue[2], tempValue[3]);

                        WEIGHT_T tempWeight[4];
                        tensorReadARM(weightsData, uint[](oc, ky, kx, ic), tempWeight);
                        VEC4 weight = VEC4(tempWeight[0], tempWeight[1], tempWeight[2], tempWeight[3]);

                        VEC4 outValue = value - pushC)"
R"(onstants.inputZeroPoint;
                        VEC4 outWeight = weight - pushConstants.weightZeroPoint;
                        VEC4 mul = outValue * outWeight;

                        for (uint idx = 0; idx < 4 && ic + idx < IC; ++idx) {
                            acc += ACC_T(mul[idx]);
                        }
                    }
                }
            }
        }
    }

    tensorWriteARM(outputData, index, OUT_T(acc));
}
)"
;
const std::map<std::string_view, std::string_view> glslMap {
{ "argmax", argmaxGLSL },
{ "arithmetic_right_shift", arithmetic_right_shiftGLSL },
{ "avgpool2d", avgpool2dGLSL },
{ "cast", castGLSL },
{ "clamp", clampGLSL },
{ "concat", concatGLSL },
{ "conv2d", conv2dGLSL },
{ "conv3d", conv3dGLSL },
{ "depthwise_conv2d", depthwise_conv2dGLSL },
{ "elementwise_binary", elementwise_binaryGLSL },
{ "elementwise_unary", elementwise_unaryGLSL },
{ "fft2d", fft2dGLSL },
{ "gather", gatherGLSL },
{ "matmul", matmulGLSL },
{ "maxpool2d", maxpool2dGLSL },
{ "mul", mulGLSL },
{ "negate", negateGLSL },
{ "pad", padGLSL },
{ "reduce", reduceGLSL },
{ "rescale", rescaleGLSL },
{ "reshape", reshapeGLSL },
{ "resize", resizeGLSL },
{ "reverse", reverseGLSL },
{ "rfft2d", rfft2dGLSL },
{ "scatter", scatterGLSL },
{ "select", selectGLSL },
{ "slice", sliceGLSL },
{ "table", tableGLSL },
{ "tile", tileGLSL },
{ "transpose", transposeGLSL },
{ "transpose_conv2d", transpose_conv2dGLSL },
};

}