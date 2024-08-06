// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl barrier_data_mem
.globl barrier_data_sync
.globl barrier_inst_sync

barrier_data_mem:
  dmb ish
  ret

barrier_data_sync:
  dsb sy
  ret

barrier_inst_sync:
  isb sy
  ret
