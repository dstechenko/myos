set tui border-kind ascii
set tui border-mode normal
tui new-layout default status 1 {-horizontal src 1 asm 1} 1 {-horizontal cmd 1 regs 1} 1
layout default
target ext :3333
interrupt
add-symbol-file out/kernel.elf
b boot_init
set $x0 = 0
c