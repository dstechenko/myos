// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl abort
abort:
  // TODO: Should do this for all cores...
  wfe
  b       abort
