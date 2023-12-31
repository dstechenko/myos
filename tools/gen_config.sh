#!/bin/bash
# Copyright (C) Dmytro Stechenko
# License: http://www.gnu.org/licenses/gpl.html

set -euxo pipefail

CONFIG_OUT="${1}"
 CONFIG_IN="${@:2}"

echo "// Copyright (C) Dmytro Stechenko"                          >> $CONFIG_OUT
echo "// License: http://www.gnu.org/licenses/gpl.html"           >> $CONFIG_OUT
echo ""                                                           >> $CONFIG_OUT
echo "#ifndef KERNEL_CONFIG_H"                                    >> $CONFIG_OUT
echo "#define KERNEL_CONFIG_H"                                    >> $CONFIG_OUT
echo ""                                                           >> $CONFIG_OUT
echo "#include <kernel/config-defs.h>"                            >> $CONFIG_OUT
echo ""                                                           >> $CONFIG_OUT
for CONFIG_FILE in $CONFIG_IN
do
    cat "$CONFIG_FILE" | while read CONFIG_LINE || [ -n "$CONFIG_LINE" ];
    do
        [[ "${CONFIG_LINE}" = \#* ]] && continue
        [[ "${CONFIG_LINE}" = ""  ]] && continue
        echo "#undef CONFIG_$(cut -d ' ' -f1 <<< ${CONFIG_LINE})" >> $CONFIG_OUT
        echo "#define CONFIG_${CONFIG_LINE}"                      >> $CONFIG_OUT
    done
done
echo ""                                                           >> $CONFIG_OUT
echo "#endif // !KERNEL_CONFIG_H"                                 >> $CONFIG_OUT
