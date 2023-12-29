// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl abort_and_wait

// TODO(dstechenko): Should do this for all cores and print state
abort_and_wait:
  wfe
  b  abort_and_wait
