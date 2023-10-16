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
    . = BOOT_LOAD_ADDRESS;
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
    section_pgd_boot_start = .;
    .pgd_boot :
    {
      . += PGD_SIZE;
    }
    section_pgd_boot_end = .;
    section_pgd_kernel_start = .;
    .pgd_kernel :
    {
      . += PGD_SIZE;
    }
    section_pgd_kernel_end = .;
    section_pgd_end = .;
    section_end = .;
}
