// Copyright (C) Dmytro Stechenko
// License: http://www.gnu.org/licenses/gpl.html

#include <kernel/entry.h>

#include <kernel/build_info.h>
#include <kernel/config.h>
#include <kernel/log.h>

void kernel_entry(void)
{
	log_init();
	log_info("MyOS boot complete!");
	log_info(">");
	log_info("Build commit hash:   %s", BUILD_INFO_COMMIT_HASH);
	log_info("Build timestamp:     %s", BUILD_INFO_TIMESTAMP);
	log_info("Build target arch:   %s", BUILD_INFO_TARGET_ARCH);
	log_info("Build target board:  %s", BUILD_INFO_TARGET_BOARD);
	log_info("Build target mode:   %s", BUILD_INFO_TARGET_MODE);
	log_info("Build host arch:     %s", BUILD_INFO_HOST_ARCH);
	log_info(">");
	log_debug("Logging test:");
	log_debug("%c", 'c');
	log_debug("%d", 123);
	log_debug("%o", 123);
	log_debug("%x", 123);
	log_info("Spinning now...");
}
