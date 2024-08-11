# myos

Current:
- Make SMP setup optional
- Build armstubs/config out of the project files

Next:
- Make kernel fail on NULL access
- Add SMP capability to task module (locks, per cpu queues)
- Add irq handlers on each core using local timers
- Make MMU setup optional
- Add memory allocator
- Speed up page allocator
- Add task sleep and yield
- Add mutex/semaphore
- Make code/data pages separation
- Add UART irqs to handle inputs
- Add stack protector
- Migrate to GIC
- Implement IPIs to halt other cores
- Make crash reporter (using IPIs)
- Dump kernel crash state into a carved out section for reading
- Add user binary loading format
- Add lookup tables (idr, bit-mapped arrays)

Notes:
- UART pinout gpio#3 gnd, gpio#4 txd, gpio#5 rxd
- DTech usb-2-serial red 5v, green txd, white rxd, black gnd
