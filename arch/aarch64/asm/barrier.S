// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/export.h>

barrier_data_mem:
  dmb ish
  ret
EXPORT(barrier_data_mem);

barrier_data_sync:
  dsb sy
  ret
EXPORT(barrier_data_sync);

barrier_inst_sync:
  isb sy
  ret
EXPORT(barrier_inst_sync);

barrier_event:
  sev
  ret
EXPORT(barrier_event);
