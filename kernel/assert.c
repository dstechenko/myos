// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/assert.h>

#include <asm/abort.h>
#include <kernel/log.h>

void abort()
{
	log_error("Aborting the execution...");
	sys_abort();
}

void assert(const bool cond, const char *ctx)
{
	if (!cond) {
		log_error("Failed assert on: %s", ctx);
		abort();
	}
}
