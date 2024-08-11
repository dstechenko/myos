// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/export.h>

// TODO(dstechenko): Should do this for all cores and print state
abort_and_wait:
  wfe
  b  abort_and_wait
EXPORT(abort_and_wait);
