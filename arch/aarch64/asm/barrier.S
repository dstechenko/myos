// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl barrier_data_memory
.globl barrier_data_sync
.globl barrier_instruction_sync

barrier_data_memory:
  dmb ish
  ret

barrier_data_sync:
  dsb ish
  ret

barrier_instruction_sync:
  isb sy
  ret
