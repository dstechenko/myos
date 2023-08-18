// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl fork_return
fork_return:
  bl  task_schedule_tail
  blr x19
