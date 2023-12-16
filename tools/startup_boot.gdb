target remote localhost:1234
add-symbol-file out/kernel.elf
b boot_start
c
del 1
