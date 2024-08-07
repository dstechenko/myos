# myos

Progress:
- Add linked lists (listhead)
- Add cpu registers breakdown doc strings and accessors
- Add irq handlers on each core using local timers
- Add SMP capability to task module (locks, per cpu queues)
- Make MMU setup optional
- Make SMP setup optional
- Add lookup tables (idr)
- Add memory allocator
- Speed up page allocator
- Add task sleep/yield/mutex
- Build armstubs/config out of the project files
- Make code/data pages separation
- Add UART irqs to handle inputs
- Add stack protector
- Migrate to GIC
- Implement IPIs
- Make crash reporter (using IPI)
- Dump kernel crash state into a carved out section
- Add user binary loading format

Notes:
- UART pinout gpio#3 gnd, gpio#4 txd, gpio#5 rxd
- DTech usb-2-serial red 5v, green txd, white rxd, black gnd
