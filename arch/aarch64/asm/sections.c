// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/sections.h>
#include <kernel/log.h>
#include <kernel/memory-ops.h>
#include <kernel/ptrs.h>

SECTIONS(section_kernel_entry);
SECTIONS(section_kernel);
SECTIONS(section_kernel_text);
SECTIONS(section_kernel_rodata);
SECTIONS(section_kernel_data);
SECTIONS(section_kernel_bss);
SECTIONS(section_user);

void sections_init(void) {
  memory_zero(ADR_TO_PTR(SECTIONS_START(section_kernel_bss)), SECTIONS_LENGTH(section_kernel_bss));
}

void sections_debug(void) {
  LOG_DEBUG("Memory locations:");
  LOG_DEBUG("  Kernel entry start  - %lx", SECTIONS_START(section_kernel_entry));
  LOG_DEBUG("  Kernel entry end    - %lx", SECTIONS_END(section_kernel_entry));
  LOG_DEBUG("  Kernel start        - %lx", SECTIONS_START(section_kernel));
  LOG_DEBUG("  Kernel end          - %lx", SECTIONS_END(section_kernel));
  LOG_DEBUG("  Kernel text start   - %lx", SECTIONS_START(section_kernel_text));
  LOG_DEBUG("  Kernel text end     - %lx", SECTIONS_END(section_kernel_text));
  LOG_DEBUG("  Kernel rodata start - %lx", SECTIONS_START(section_kernel_rodata));
  LOG_DEBUG("  Kernel rodata end   - %lx", SECTIONS_END(section_kernel_rodata));
  LOG_DEBUG("  Kernel data start   - %lx", SECTIONS_START(section_kernel_data));
  LOG_DEBUG("  Kernel data end     - %lx", SECTIONS_END(section_kernel_data));
  LOG_DEBUG("  Kernel bss start    - %lx", SECTIONS_START(section_kernel_bss));
  LOG_DEBUG("  Kernel bss end      - %lx", SECTIONS_END(section_kernel_bss));
  LOG_DEBUG("  User start          - %lx", SECTIONS_START(section_user));
  LOG_DEBUG("  User end            - %lx", SECTIONS_END(section_user));
}
