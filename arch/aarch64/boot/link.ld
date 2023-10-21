/**
 * Copyright (C) Dmytro Stechenko
 * License: http://www.gnu.org/licenses/gpl.html
 */

#include <asm/memory-defs.h>
#include <asm/page-defs.h>

ENTRY(BOOT_ENTRY_POINT_LABEL)

SECTIONS
{
    section_start = .;

    . = ALIGN(PAGE_SIZE);
    section_text_boot_start = .;
    .text_boot (BOOT_LOAD_ADDRESS) : { *(.text.boot) }
    section_text_boot_end = .;

    . = ALIGN(PAGE_SIZE);
    section_pgd_boot_start = .;
    .pgd_boot : { . += PGD_SIZE; }
    section_pgd_boot_end = .;

    . = ALIGN(PAGE_SIZE);
    section_pgd_kernel_start = .;
    .pgd_kernel : { . += PGD_SIZE; }
    section_pgd_kernel_end = .;

    section_kernel_start = .;
    . += VIRTUAL_MEMORY_START;

    . = ALIGN(PAGE_SIZE);
    section_entry_start = .;
    .text_entry : AT(ADDR(.text_entry) - VIRTUAL_MEMORY_START) { out/kernel/init/entry* (.text) }
    section_entry_end = .;

    . = ALIGN(PAGE_SIZE);
    section_user_start = .;
    .text_user : AT(ADDR(.text_user) - VIRTUAL_MEMORY_START) {
      out/kernel/init/user* (.text)
      out/kernel/core/user* (.text)
    }
    .rodata_user : AT(ADDR(.rodata_user) - VIRTUAL_MEMORY_START) { out/kernel/init/user* (.rodata) }
    .data_user : AT(ADDR(.data_user) - VIRTUAL_MEMORY_START) { out/kernel/init/user* (.data) }
    .bss_user : AT(ADDR(.bss_user) - VIRTUAL_MEMORY_START) { out/kernel/init/user* (.bss) }
    section_user_end = .;

    . = ALIGN(PAGE_SIZE);
    section_text_start = .;
    .text : AT(ADDR(.text) - VIRTUAL_MEMORY_START) { *(.text) }
    section_text_end = .;

     . = ALIGN(PAGE_SIZE);
    section_rodata_start = .;
    .rodata : AT(ADDR(.rodata) - VIRTUAL_MEMORY_START) { *(.rodata) }
    section_rodata_end = .;

     . = ALIGN(PAGE_SIZE);
    section_data_start = .;
    .data : AT(ADDR(.data) - VIRTUAL_MEMORY_START) { *(.data) }
    section_data_end = .;

     . = ALIGN(PAGE_SIZE);
    section_bss_start = .;
    .bss : AT(ADDR(.bss) - VIRTUAL_MEMORY_START) { *(.bss) }
    section_bss_end = .;

    section_end = .;
}
