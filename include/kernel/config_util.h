// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_CONFIG_UTIL_H
#define KERNEL_CONFIG_UTIL_H

#include <kernel/bool.h>

#define CONFIG_ENABLED(config) (config == true)
#define CONFIG_DISABLED(config) (!CONFIG_ENABLED(config))

#endif // !KERNEL_CONFIG_UTIL_H
