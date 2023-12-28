# myos

TODOs(progress):
- Expose jiffies in kernel
- Add sleep/yield, mutexes, per_cpu
- Add idle tasks, cleanup in init, set priority, set affinity, dynamic max size
- Add irq enabled/disabled/save/load
- Add memory allocator
- Add kernel/user testing framework
- Cover existing core functionality by tests

TODOs(backlog):
- Make code/data pages separation
- Add file systems
- Separate fork into user/kernel implementations
- Add UART irqs to handle inputs
- Refine syscall system with generated wrappers and arguments, syscall table
- Add qemu bcm overlay
- Driver config switch with no facade file - use ifdefs
- Use local interrupt controller, use priorities
- Extract ticks into global functionality
- Add stack protector
- Run all timers
- Add cpu registers breakdown doc strings
- Make crash reporter much better
- Dump kernel crash state into a carved out section
- Add comments and docs

Notes:
- UART pinout gpio#3 gnd, gpio#4 txd, gpio#5 rxd
- DTech usb-2-serial red 5v, green txd, white rxd, black gnd
