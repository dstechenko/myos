target remote localhost:1234
add-symbol-file out/kernel.elf
b boot_jump_kernel
c
add-symbol-file out/kernel.elf (section_kernel_text_start+0xFFFF000000000000)
b init_start
c
del 1
del 2
