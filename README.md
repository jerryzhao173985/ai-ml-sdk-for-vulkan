# ML SDK for Vulkan®

ML SDK for Vulkan® is an SDK to facilitate the development of projects using
the Arm® Vulkan® ML extensions.

## Content

This repository contains scripts to facilitate building all ML SDK components,
utilities, and documentation.

## Build all ML SDK components

The build system must have:

- CMake 3.25 or later.
- C/C++ 17 compiler: GCC, or optionally Clang on Linux and MSVC on Windows®.
- Python 3.10 or later. Required python libraries for building are listed in
  `tooling-requirements.txt`.
- Flatbuffers flatc compiler.

For building ML SDK components, run the following command:

```bash
$SDK_PATH/sw/sdk/scripts/build.py
```

The build artifacts can be installed into a specified location by passing the
option `--install` with the required path.

To create an archive with the build artifacts, add the option `--package`. The
archive will be stored in the provided location.

## Build the documentation

To build the documentation, run the following command:

```bash
$SDK_PATH/sw/sdk/scripts/build.py --doc
```

## More command line options

For more command line options, consult the program help:

```bash
$SDK_PATH/sw/sdk/scripts/build.py --help
```

## License

[Apache-2.0](LICENSES/Apache-2.0.txt)

## Security

If you believe you have discovered a security issue please refer to the
[Security Section](SECURITY.md)

## Trademark notice

Arm® is a registered trademarks of Arm Limited (or its subsidiaries) in the US
and/or elsewhere.

Khronos®, Vulkan® and SPIR-V™ are registered trademarks of the
[Khronos® Group](https://www.khronos.org/legal/trademarks).
