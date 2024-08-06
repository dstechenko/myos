// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#ifndef UAPI_BOOL_H
#define UAPI_BOOL_H

#define true 1
#define false 0

#ifndef __ASSEMBLER__
typedef _Bool bool;
#endif // !__ASSEMBLER__

// TODO(dstechenko): move out of user api?

#endif // !UAPI_BOOL_H
