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
	log_info("Build commit hash:   ");
	log_info(BUILD_INFO_COMMIT_HASH);
	log_info("Build timestamp:     ");
	log_info(BUILD_INFO_TIMESTAMP);
	log_info("Build target arch:   ");
	log_info(BUILD_INFO_TARGET_ARCH);
	log_info("Build target board:  ");
	log_info(BUILD_INFO_TARGET_BOARD);
	log_info("Build target mode:   ");
	log_info(BUILD_INFO_TARGET_MODE);
	log_info("Build host arch:     ");
	log_info(BUILD_INFO_HOST_ARCH);
	log_info("Spinning now...");
}
