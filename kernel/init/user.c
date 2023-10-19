// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/core/syscall.h>
#include <kernel/util/bool.h>

void user_task_a(void) {
  while (true) {
    syscall_write_invoke("Tick from user task a");
    syscall_cdelay_invoke(50000000);
  }
}

void user_task_b(void) {
  while (true) {
    syscall_write_invoke("Tick from user task b");
    syscall_cdelay_invoke(50000000);
  }
}

void user_start(void) {
  int pid;

  syscall_write_invoke("Run in user");

  pid = syscall_clone_invoke();
  if (pid < 0) {
    syscall_write_invoke("Failed to clone user task a");
    syscall_exit_invoke();
    return;
  }

  if (pid == 0)
    user_task_a();
  else
    user_task_b();
}
