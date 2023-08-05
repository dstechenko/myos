// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

.globl sys_abort
sys_abort:
    // TODO: Should do this for all cores...
    wfe
    b       sys_abort
