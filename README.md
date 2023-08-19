# myos

TODOs:
- Fix sized printing
- Driver config switch with no facade file - use ifdefs
- Add UART irqs to handle inputs
- Use local interrupt controller
- Extract ticks into global functionality
- Add driver subsystems (simple, static but organized)
- Prefix all board specific configs with board name
- Add libc primitives
- Add stack protector

Notes:
- UART pinout gpio#3 gnd, gpio#4 txd, gpio#5 rxd
- DTech usb-2-serial red 5v, green txd, white rxd
