// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/types.h>
#include <kernel/log.h>

static const char *const log_entry_invalid_type[] = {
    "SYN_INVALID_EL1t",   "IRQ_INVALID_EL1t",   "FIQ_INVALID_EL1t",   "ERR_INVALID_EL1t",
    "SYN_INVALID_EL1h",   "IRQ_INVALID_EL1h",   "FIQ_INVALID_EL1h",   "ERR_INVALID_EL1h",
    "SYN_INVALID_EL0_64", "IRQ_INVALID_EL0_64", "FIQ_INVALID_EL0_64", "ERR_INVALID_EL0_64",
    "SYN_INVALID_EL0_32", "IRQ_INVALID_EL0_32", "FIQ_INVALID_EL0_32", "ERR_INVALID_EL0_32",
    "ERROR_SYN",          "ERROR_SYSCALL",      "ERROR_DATA_ABORT",
};

void entry_log_invalid_message(const uint8_t type, const uint64_t esr, const uint64_t elr,
                               const uint64_t far) {
  LOG_ERROR("Entry type: %s, esr: %lx, elr: %lx, far: %lx", log_entry_invalid_type[type], esr, elr, far);
}
