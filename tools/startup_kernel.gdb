target remote localhost:1234
add-symbol-file out/kernel.elf
b boot_jump_kernel
c
add-symbol-file out/kernel.elf (section_text_start+0xFFFF000000000000)
b kernel_start
c
