/*
Copyright (C) Dmytro Stechenko
License: http://www.gnu.org/licenses/gpl.html
*/

ENTRY(_start)

SECTIONS
{
    . = 0x80000;
    . = ALIGN(4096);
    __start = .;
    __text_start = .;
    .text :
    {
        KEEP(*(.text.boot))
        *(.text)
    }
    __text_end = .;
     . = ALIGN(4096);
    __rodata_start = .;
    .rodata :
    {
        *(.rodata)
    }
    __rodata_end = .;
     . = ALIGN(4096);
    __data_start = .;
    .data :
    {
        *(.data)
    }
    __data_end = .;
     . = ALIGN(4096);
    __bss_start = .;
    .bss :
    {
        *(.bss)
    }
    __bss_end = .;
    __bss_size = __bss_end - __bss_start;
    __end = .;
}
