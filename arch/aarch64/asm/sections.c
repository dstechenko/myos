// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <asm/sections.h>

#include <kernel/logging/log.h>

SECTION_LABEL(section_kernel_entry_start);
SECTION_LABEL(section_kernel_entry_end);
SECTION_LABEL(section_kernel_start);
SECTION_LABEL(section_kernel_end);
SECTION_LABEL(section_kernel_text_start);
SECTION_LABEL(section_kernel_text_end);
SECTION_LABEL(section_kernel_rodata_start);
SECTION_LABEL(section_kernel_rodata_end);
SECTION_LABEL(section_kernel_data_start);
SECTION_LABEL(section_kernel_data_end);
SECTION_LABEL(section_kernel_bss_start);
SECTION_LABEL(section_kernel_bss_end);
SECTION_LABEL(section_user_start);
SECTION_LABEL(section_user_end);

void debug_sections(void) {
  LOG_DEBUG("Memory locations:");
  LOG_DEBUG("  Kernel entry start  - %lx", SECTION_ADR(section_kernel_entry_start));
  LOG_DEBUG("  Kernel entry end    - %lx", SECTION_ADR(section_kernel_entry_end));
  LOG_DEBUG("  Kernel start        - %lx", SECTION_ADR(section_kernel_start));
  LOG_DEBUG("  Kernel end          - %lx", SECTION_ADR(section_kernel_end));
  LOG_DEBUG("  Kernel text start   - %lx", SECTION_ADR(section_kernel_text_start));
  LOG_DEBUG("  Kernel text end     - %lx", SECTION_ADR(section_kernel_text_end));
  LOG_DEBUG("  Kernel rodata start - %lx", SECTION_ADR(section_kernel_rodata_start));
  LOG_DEBUG("  Kernel rodata end   - %lx", SECTION_ADR(section_kernel_rodata_end));
  LOG_DEBUG("  Kernel data start   - %lx", SECTION_ADR(section_kernel_data_start));
  LOG_DEBUG("  Kernel data end     - %lx", SECTION_ADR(section_kernel_data_end));
  LOG_DEBUG("  Kernel bss start    - %lx", SECTION_ADR(section_kernel_bss_start));
  LOG_DEBUG("  Kernel bss end      - %lx", SECTION_ADR(section_kernel_bss_end));
  LOG_DEBUG("  User start          - %lx", SECTION_ADR(section_user_start));
  LOG_DEBUG("  User end            - %lx", SECTION_ADR(section_user_end));
}
