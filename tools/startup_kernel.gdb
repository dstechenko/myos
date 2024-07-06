set tui border-kind ascii
set tui border-mode normal
tui new-layout default status 1 {-horizontal src 1 asm 1} 1 {-horizontal cmd 1 regs 1} 1
layout default
target ext :3333
add-symbol-file out/kernel.elf
b boot_jump_kernel
set $x0 = 0
c
add-symbol-file out/kernel.elf (section_kernel_text_start+0xFFFF000000000000)
b init_start
c