// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_CORE_CONFIG_H
#define KERNEL_CORE_CONFIG_H

#include <uapi/bool.h>

#define CONFIG_SET(config, value) (config == value)
#define CONFIG_ENABLED(config) (CONFIG_SET(config, true))
#define CONFIG_DISABLED(config) (!CONFIG_ENABLED(config))

#endif // !KERNEL_CORE_CONFIG_H
