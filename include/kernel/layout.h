// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef KERNEL_LAYOUT_H
#define KERNEL_LAYOUT_H

// TODO(dstechenko): make these portable across compilers...
#define PACKED __attribute__((__packed__))
#define ALIGNED(val) __attribute__((aligned(val)))

#endif // !KERNEL_LAYOUT_H
