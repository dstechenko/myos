#!/bin/bash
# Copyright (C) Dmytro Stechenko
# License: http://www.gnu.org/licenses/gpl.html

sudo dnf install qemu
sudo dnf install make automake gcc gcc-c++ kernel-devel clang-tools-extra nasm
sudo dnf install bison flex
sudo dnf install gmp gmp-devel mpfr mpfr-devel libmpc libmpc-devel
