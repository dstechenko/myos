// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/log.h>

#include "entry.h"

static const char *const invalid_message_type[] = {
    "SYN_INVALID_EL1t",   "IRQ_INVALID_EL1t",   "FIQ_INVALID_EL1t",
    "ERR_INVALID_EL1t",   "SYN_INVALID_EL1h",   "IRQ_INVALID_EL1h",
    "FIQ_INVALID_EL1h",   "ERR_INVALID_EL1h",   "SYN_INVALID_EL0_64",
    "IRQ_INVALID_EL0_64", "FIQ_INVALID_EL0_64", "ERR_INVALID_EL0_64",
    "SYN_INVALID_EL0_32", "IRQ_INVALID_EL0_32", "FIQ_INVALID_EL0_32",
    "ERR_INVALID_EL0_32",
};

void entry_log_invalid_message(const int type, const unsigned long esr,
                               const unsigned long elr) {
  log_error("Entry type: %s, esr: %x, elr: %x", invalid_message_type[type], esr,
            elr);
}
