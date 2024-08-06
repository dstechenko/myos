# myos

TODOs(progress):
- Rename non-debug mode into explicit eng/prod mode
- Refactor all the modules
- Add logs to each init step, init logs asap
- Make MMU optional, make SMP optional
- Update toolchain to the newest version
- Add lists and other structs
- Add memory allocator, speed up page allocator
- Add locks to task module
- Add idle tasks, cleanup in init, set priority, set affinity, dynamic max size
- Add sleep/yield, mutexes
- Add irq handlers on each core using local timers

TODOs(backlog):
- Build armstubs and package config out of the build files
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
