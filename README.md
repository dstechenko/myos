# myos

TODOs(progress):
- Prefix all board specific configs with board name
- Fix sized printing, extract printing and logging separately

TODOs(backlog):
- Add UART irqs to handle inputs
- Make kernel tasks exit by themselves and clean up
- Add irq enabled/disabled functions
- Separate fork into user/kernel implementations
- Refine syscall system with generated wrappers and arguments, syscall table
- Add comments and docs everywhere after vmem bits
- Add qemu bcm overlay
- Add task priority setting, unlimited task allocation
- Add atomics, spinlocks, mutexes, per_cpu and per_task variables
- Driver config switch with no facade file - use ifdefs
- Use local interrupt controller
- Extract ticks into global functionality
- Add driver subsystems (simple, static but organized)
- Add stack protector
- Add libc primitives

Notes:
- UART pinout gpio#3 gnd, gpio#4 txd, gpio#5 rxd
- DTech usb-2-serial red 5v, green txd, white rxd
