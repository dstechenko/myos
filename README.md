# myos

TODOs(progress):
- Add atomics, spinlocks, mutexes, per_cpu and per_task variables
- Add idle tasks, tasks cleanup
- Add barriers (io, compilers)
- Add irq enabled/disabled/save/load functions
- Add a simple allocation mechanism
- Expose jiffies in kernel
- Add kernel/user testing framework
- Cover existing core functionality by tests

TODOs(backlog):
- Make code/data pages separation
- Add file systems
- Make kernel tasks exit by themselves and clean up
- Separate fork into user/kernel implementations
- Add UART irqs to handle inputs
- Refine syscall system with generated wrappers and arguments, syscall table
- Add comments and docs everywhere after vmem bits
- Add qemu bcm overlay
- Add task priority setting, unlimited task allocation
- Driver config switch with no facade file - use ifdefs
- Use local interrupt controller
- Extract ticks into global functionality
- Add driver subsystems (simple, static but organized)
- Add driver init for print not hardcoded, take deps
- Add stack protector
- Add libc primitives
- Run all timers
- Add cpu core asm code
- Add cpu registers breakdown doc strings
- Flip syscall and syscall-invoke
- Make crash reporter much better
- Dump kernel crash state into a carved out section

Notes:
- UART pinout gpio#3 gnd, gpio#4 txd, gpio#5 rxd
- DTech usb-2-serial red 5v, green txd, white rxd, black gnd
