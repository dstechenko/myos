// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl regs_get_priv
regs_get_priv:
    // Read from the system register for exception levels.
    // EL0 least priv, EL3 the most.
    mrs x0, CurrentEL
    // Shift right by two because the first 2 bits are reserved
    // and are always zero.
    lsr x0, x0, #2
    ret
