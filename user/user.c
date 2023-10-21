// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <uapi/bool.h>
#include <uapi/syscall.h>

void user_task_a(void);
void user_task_b(void);

void user_start(void) {
  int pid;

  pid = syscall_clone();
  if (pid < 0) {
    syscall_write("Failed to clone user task a\n");
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
    syscall_write("* Tick from user task a\n");
    syscall_cdelay(50000000);
  }
}

void user_task_b(void) {
  while (true) {
    syscall_write("* Tick from user task b\n");
    syscall_cdelay(50000000);
  }
}
