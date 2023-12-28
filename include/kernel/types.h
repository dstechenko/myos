// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_TYPES_H
#define KERNEL_TYPES_H

#include <stddef.h>
#include <stdint.h>

#include <uapi/bool.h>

#define TYPE(name, def) typedef struct { def value; } name
#define ALIAS(name, def) typedef def name

#endif // !KERNEL_TYPES_H
