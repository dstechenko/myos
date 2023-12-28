# myos

TODOs(progress):
- Add irq handlers on each core, configure irq priorities
- Add kernel/user testing framework
- Add tests to existing modules

- Add sleep/yield, mutexes
- Add idle tasks, cleanup in init, set priority, set affinity, dynamic max size
- Add memory allocator

TODOs(backlog):
- Make code/data pages separation
- Add file systems
- Separate fork into user/kernel implementations
- Add UART irqs to handle inputs
- Refine syscall system with generated wrappers and arguments, syscall table
- Add qemu bcm overlay
- Driver config switch with no facade file - use ifdefs
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
