#!/bin/bash
# Copyright (C) Dmytro Stechenko
# License: http://www.gnu.org/licenses/gpl.html

set -euxo pipefail

INFO_OUT="${1}"

echo "// Copyright (C) Dmytro Stechenko"                               >> $INFO_OUT
echo "// License: http://www.gnu.org/licenses/gpl.html"                >> $INFO_OUT
echo ""                                                                >> $INFO_OUT
echo "#ifndef KERNEL_BUILD_INFO_H"                                     >> $INFO_OUT
echo "#define KERNEL_BUILD_INFO_H"                                     >> $INFO_OUT
echo ""                                                                >> $INFO_OUT
echo "#define BUILD_INFO_COMMIT_HASH \"$(git rev-parse HEAD)\""        >> $INFO_OUT
echo "#define BUILD_INFO_TIMESTAMP \"$(date -u --iso-8601=seconds)Z\"" >> $INFO_OUT
echo "#define BUILD_INFO_TARGET_ARCH \"$TARGET_ARCH\""                 >> $INFO_OUT
echo "#define BUILD_INFO_TARGET_BOARD \"$TARGET_BOARD\""               >> $INFO_OUT
echo "#define BUILD_INFO_TARGET_MODE \"$TARGET_MODE\""                 >> $INFO_OUT
echo "#define BUILD_INFO_HOST_ARCH \"$(uname -m)\""                    >> $INFO_OUT
echo ""                                                                >> $INFO_OUT
echo "#endif // !KERNEL_BUILD_INFO_H"                                  >> $INFO_OUT
