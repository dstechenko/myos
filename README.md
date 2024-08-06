# myos

TODOs:
- Add logs to each init step, init logs asap
- Make MMU optional, make SMP optional
- Add lists and other structs
- Add memory allocator, speed up page allocator
- Add locks to task module
- Add idle tasks, cleanup in init, set priority, set affinity, dynamic max size
- Add sleep/yield, mutexes
- Add irq handlers on each core using local timers
- Build armstubs and package config out of the build files
- Make code/data pages separation
- Add UART irqs to handle inputs
- Add stack protector
- Run all timers
- Add cpu registers breakdown doc strings
- Make crash reporter much better
- Dump kernel crash state into a carved out section

Notes:
- UART pinout gpio#3 gnd, gpio#4 txd, gpio#5 rxd
- DTech usb-2-serial red 5v, green txd, white rxd, black gnd
