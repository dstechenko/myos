/**
 * Copyright (C) Dmytro Stechenko
 * License: http://www.gnu.org/licenses/gpl.html
 */

#include <asm/memory-defs.h>
#include <asm/page-defs.h>

#define VIRTUAL(label) AT(ADDR(label) - VIRTUAL_MEMORY_OFFSET)

ENTRY(BOOT_ENTRY_POINT_LABEL)

SECTIONS
{
  section_boot (BOOT_LOAD_ADDRESS) : {
    section_boot_start = .;
    KEEP(*(.text.boot))
    out/boot/boot*
    section_boot_end = .;
  }

  . = ALIGN(PAGE_SIZE);
  section_kernel_entry_point = .;
  . += VIRTUAL_MEMORY_OFFSET;

  section_kernel_entry : VIRTUAL(section_kernel_entry) {
    section_kernel_entry_start = .;
    KEEP(*(.text.entry))
    section_kernel_entry_end = .;
  }

  . = ALIGN(PAGE_SIZE);
  section_user : VIRTUAL(section_user) {
    section_user_start = .;
    out/user/user* (.text)
    out/user* (.text)
    out/user* (.rodata)
    out/user* (.data)
    out/user* (.bss)
    section_user_end = .;
  }

  /* Align this separately to make non-writable. */
  . = ALIGN(PAGE_SIZE);
  section_kernel_start = .;
  section_kernel_text : VIRTUAL(section_kernel_text) {
    section_kernel_text_start = .;
    *(.text)
    section_kernel_text_end = .;
  }
  . = ALIGN(PAGE_SIZE);
  section_kernel_rodata : VIRTUAL(section_kernel_rodata) {
    section_kernel_rodata_start = .;
    *(.rodata)
    section_kernel_rodata_end = .;
  }
  section_kernel_data : VIRTUAL(section_kernel_data) {
    section_kernel_data_start = .;
    *(.data)
    section_kernel_data_end = .;
  }
  section_kernel_bss : VIRTUAL(section_kernel_bss) {
    section_kernel_bss_start = .;
    *(.bss)
    section_kernel_bss_end = .;
  }
  . = ALIGN(PAGE_SIZE);
  section_kernel_end = .;
}
