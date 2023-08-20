// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl abort

// TODO: Should do this for all cores and print state
abort:
  wfe
  b  abort
