#
# SPDX-FileCopyrightText: Copyright 2025 Arm Limited and/or its affiliates <open-source-office@arm.com>
# SPDX-License-Identifier: Apache-2.0
#

# syntax=docker/dockerfile:1.10

ARG ubuntu_version=22.04
FROM ubuntu:$ubuntu_version
ARG user=myuser
ARG uid=1000

ENV LANG=C.UTF-8

RUN apt-get update
RUN apt-get install -y \
    build-essential \
    doxygen \
    git \
    libgtest-dev \
    ninja-build \
    python3 \
    python3-pip \
    python3-venv \
    sudo \
    vulkan-tools

RUN pip install \
    cmake

RUN useradd -m -u $uid -U $user && \
    echo "$user ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

USER $user
