// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/log.h>

#include "entry.h"

static const char *type_to_string(const int type) {
  switch (type) {
  case ENTRY_SYN_INVALID_EL1t:
    return "SYN_INVALID_EL1t";
  case ENTRY_IRQ_INVALID_EL1t:
    return "IRQ_INVALID_EL1t";
  case ENTRY_FIQ_INVALID_EL1t:
    return "FIQ_INVALID_EL1t";
  case ENTRY_ERR_INVALID_EL1t:
    return "ERR_INVALID_EL1t";
  case ENTRY_SYN_INVALID_EL1h:
    return "SYN_INVALID_EL1h";
  case ENTRY_IRQ_INVALID_EL1h:
    return "IRQ_INVALID_EL1h";
  case ENTRY_FIQ_INVALID_EL1h:
    return "FIQ_INVALID_EL1h";
  case ENTRY_ERR_INVALID_EL1h:
    return "ERR_INVALID_EL1h";
  case ENTRY_SYN_INVALID_EL0_64:
    return "SYN_INVALID_EL0_64";
  case ENTRY_IRQ_INVALID_EL0_64:
    return "IRQ_INVALID_EL0_64";
  case ENTRY_FIQ_INVALID_EL0_64:
    return "FIQ_INVALID_EL0_64";
  case ENTRY_ERR_INVALID_EL0_64:
    return "ERR_INVALID_EL0_64";
  case ENTRY_SYN_INVALID_EL0_32:
    return "SYN_INVALID_EL0_32";
  case ENTRY_IRQ_INVALID_EL0_32:
    return "IRQ_INVALID_EL0_32";
  case ENTRY_FIQ_INVALID_EL0_32:
    return "FIQ_INVALID_EL0_32";
  case ENTRY_ERR_INVALID_EL0_32:
    return "ERR_INVALID_EL0_32";
  default:
    return "UNKNOWN";
  }
}

void entry_log_invalid_message(const int type, const unsigned long esr,
                               const unsigned long elr) {
  log_error("Entry type: %s, esr: %x, elr: %x", type_to_string(type), esr, elr);
}
