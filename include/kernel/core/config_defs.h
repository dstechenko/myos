// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_CORE_CONFIG_H
#define KERNEL_CORE_CONFIG_H

#include <kernel/util/bool.h>

#define CONFIG_ENABLED(config) (config == true)
#define CONFIG_DISABLED(config) (!CONFIG_ENABLED(config))

#endif // !KERNEL_CORE_CONFIG_H
