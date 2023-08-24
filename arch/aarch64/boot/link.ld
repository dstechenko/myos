/**
 * Copyright (C) Dmytro Stechenko
 * License: http://www.gnu.org/licenses/gpl.html
 */

#include <asm/page.h>
#include <asm/memory.h>

ENTRY(_start)

SECTIONS
{
    /* TODO: move this out into an arch specific property */
    . = 0x80000;
    . = ALIGN(PAGE_SIZE);
    section_start = .;
    /* TODO: move this out into a board specific property */
    _start = .;
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
    section_page_global_directory_start = .;
    .page_global_directory :
    {
      . += PAGE_GLOBAL_DIRECTORY_SIZE;
    }
    section_page_global_directory_end = .;
    section_end = .;
}
