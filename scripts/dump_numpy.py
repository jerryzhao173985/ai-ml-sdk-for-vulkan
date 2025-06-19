#!/usr/bin/env python3
#
# SPDX-FileCopyrightText: Copyright 2023-2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
# SPDX-License-Identifier: Apache-2.0
#
import argparse

try:
    import argcomplete
except:
    argcomplete = None
import numpy


def parse_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("files", metavar="file", nargs="+", help="NumPy data file")
    if argcomplete:
        argcomplete.autocomplete(parser)
    return parser.parse_args()


def main():
    args = parse_arguments()
    with numpy.printoptions(threshold=numpy.inf):
        for f in args.files:
            print(numpy.load(f))


if __name__ == "__main__":
    main()
