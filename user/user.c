// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <uapi/syscall.h>
#include <uapi/types.h>

void user_task_a(void);
void user_task_b(void);

void user_start(void) {
  int pid = 0;

  syscall_delay(1000000000);

  pid = syscall_clone();
  if (pid < 0) {
    syscall_write("Failed to clone user task a\n\r");
    syscall_exit();
    return;
  }

  if (pid == 0)
    user_task_a();
  else
    user_task_b();
}

void user_task_a(void) {
  while (true) {
    syscall_write("* Tick from user task a\n\r");
    syscall_delay(500000000);
  }
}

void user_task_b(void) {
  while (true) {
    syscall_write("* Tick from user task b\n\r");
    syscall_delay(500000000);
  }
}
