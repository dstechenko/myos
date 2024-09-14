// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl abort_and_wait

abort_and_wait:
  wfe
  b  abort_and_wait
