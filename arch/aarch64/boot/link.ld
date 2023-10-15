/**
 * Copyright (C) Dmytro Stechenko
 * License: http://www.gnu.org/licenses/gpl.html
 */

#include <asm/memory-defs.h>
#include <asm/page-defs.h>

#include <kernel/core/config.h>

ENTRY(BOOT_ENTRY_POINT_LABEL)

SECTIONS
{
    . = 0x80000;
    /* . = VIRTUAL_MEMORY_START; */
    . = ALIGN(PAGE_SIZE);
    section_start = .;
    BOOT_ENTRY_POINT_LABEL = .;
    section_text_start = .;
    .text :
    {
        KEEP(*(.text.boot))
        *(.text)
    }
    section_text_end = .;
     . = ALIGN(PAGE_SIZE);
    section_rodata_start = .;
    .rodata :
    {
        *(.rodata)
    }
    section_rodata_end = .;
     . = ALIGN(PAGE_SIZE);
    section_data_start = .;
    .data :
    {
        *(.data)
    }
    section_data_end = .;
     . = ALIGN(PAGE_SIZE);
    section_bss_start = .;
    .bss :
    {
        *(.bss)
    }
    section_bss_end = .;
    . = ALIGN(PAGE_SIZE);
    section_pgd_start = .;
    .pgd :
    {
      . += PGD_SIZE;
    }
    section_pgd_end = .;
    section_end = .;
}
