# Copyright (C) Dmytro Stechenko
# License: http://www.gnu.org/licenses/gpl.html

# TODO(dstechenko): extract build params into a separate file

TARGET_ARCH  ?= aarch64
export TARGET_ARCH

TARGET_BOARD ?= bcm2711
export TARGET_BOARD

TARGET_MODE  ?= debug
export TARGET_MODE

TARGET_IF ?= ftdi/ft232h
export TARGET_IF

ARCH_DIR    := arch
CONFIGS_DIR := configs
DRIVERS_DIR := drivers
OUT_DIR     := out
INC_DIR     := include
KERNEL_DIR  := kernel
USER_DIR    := user
TOOLS_DIR   := tools

ARCH_DIR    := $(ARCH_DIR)/$(TARGET_ARCH)
BOOT_DIR    := $(ARCH_DIR)/boot
GEN_DIR     := $(OUT_DIR)/gen
SRC_DIRS    := $(ARCH_DIR) $(CONFIGS_DIR) $(DRIVERS_DIR) $(INC_DIRS) $(KERNEL_DIR) $(USER_DIR)
OCD_DIR     := $(TOOLS_DIR)/openocd/scripts

CONFIGS_ARCH_DIR  := $(ARCH_DIR)/configs
CONFIGS_BOARD_DIR := $(CONFIGS_DIR)/board/$(TARGET_BOARD)

KERNEL_ELF := $(OUT_DIR)/kernel.elf
KERNEL_IMG := $(OUT_DIR)/kernel.img

TOOLCHAIN := $(TOOLS_DIR)/cc/bin/$(TARGET_ARCH)-none-elf

AS  := $(TOOLCHAIN)-gcc
CC  := $(TOOLCHAIN)-gcc
DBG := $(TOOLCHAIN)-gdb
LD  := $(TOOLCHAIN)-gcc
OD  := $(TOOLCHAIN)-objdump
OC  := $(TOOLCHAIN)-objcopy
OCD := openocd

AS_FLAGS  := -c -g -mgeneral-regs-only -MMD
C_FLAGS   := -c -g -mgeneral-regs-only -ffreestanding -nostdlib -nostartfiles -Wall -Wextra -MMD
DBG_FLAGS := -q -tui
LD_FLAGS  := -g -ffreestanding -nostdlib -nostartfiles
LD_LIBS   := -lgcc
PP_FLAGS  := -E -P -x c -D__ASSEMBLER__
OD_FLAGS  := -s -d

KERNEL_DIRS := $(KERNEL_DIR) $(ARCH_DIR) $(DRIVERS_DIR) $(USER_DIR)
KERNEL_OBJS := $(shell find $(KERNEL_DIRS) -type f -name *.c -or -name *.S)
KERNEL_OBJS := $(KERNEL_OBJS:$(ARCH_DIR)/%.S=$(OUT_DIR)/%.o)
KERNEL_OBJS := $(KERNEL_OBJS:$(ARCH_DIR)/%.c=$(OUT_DIR)/%.o)
KERNEL_OBJS := $(KERNEL_OBJS:%.c=$(OUT_DIR)/%.o)
KERNEL_OBJS := $(KERNEL_OBJS:%.S=$(OUT_DIR)/%.o)

KERNEL_BUILD_INFO := $(GEN_DIR)/include/kernel/build-info.h
KERNEL_CONF       := $(GEN_DIR)/include/kernel/config.h
KERNEL_CONF_DIRS  := $(CONFIGS_DIR) $(CONFIGS_ARCH_DIR) $(CONFIGS_BOARD_DIR)
KERNEL_CONF_FILES := $(KERNEL_CONF_DIRS:%=%/config)

INC_DIRS := $(INC_DIR) $(GEN_DIR)/include $(ARCH_DIR)/include
INC_FLAGS := $(INC_DIRS:%=-I%)

LD_FILE := $(OUT_DIR)/boot/link.ld

ifeq ($(TARGET_MODE),)
KERNEL_CONF_MODE_FILES :=
else
KERNEL_CONF_MODE_FILES := $(KERNEL_CONF_DIRS:%=%/config_$(TARGET_MODE))
endif

KERNEL_CONF_FILES := $(KERNEL_CONF_FILES) $(KERNEL_CONF_MODE_FILES)

.PHONY: clean build-gen build-all build-pre build-post build-main
.PHONY: format format-diff todo boot-copy
.PHONY: debug-boot debug-kernel serial dump-all

$(KERNEL_CONF):
	mkdir -p $(@D)
	$(TOOLS_DIR)/gen_config.sh $@ $(KERNEL_CONF_FILES)

$(KERNEL_BUILD_INFO):
	mkdir -p $(@D)
	$(TOOLS_DIR)/gen_build_info.sh $@

$(OUT_DIR)/%.o: $(ARCH_DIR)/%.S
	mkdir -p $(@D)
	$(AS) $(AS_FLAGS) $(INC_FLAGS) -I$(<D) $< -o $@

$(OUT_DIR)/%.o: %.S
	mkdir -p $(@D)
	$(AS) $(AS_FLAGS) $(INC_FLAGS) -I$(<D) $< -o $@

$(OUT_DIR)/%.o: $(ARCH_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(C_FLAGS) $(INC_FLAGS) -I$(<D) $< -o $@

$(OUT_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(C_FLAGS) $(INC_FLAGS) -I$(<D) $< -o $@

$(OUT_DIR)/%.ld: $(ARCH_DIR)/%.ld
	mkdir -p $(@D)
	$(CC) $(PP_FLAGS) $(INC_FLAGS) -I$(<D) $< -o $@

$(OUT_DIR)/%.ld: %.ld
	mkdir -p $(@D)
	$(CC) $(PP_FLAGS) $(INC_FLAGS) -I$(<D) $< -o $@

build-target: $(KERNEL_OBJS) $(LD_FILE)
	mkdir -p $(@D)
	$(LD) $(LD_FLAGS) -T $(LD_FILE) -o $(KERNEL_ELF) $(KERNEL_OBJS) $(LDLIBS)
	$(OC) $(KERNEL_ELF) -O binary $(KERNEL_IMG)

clean:
	rm -rf $(OUT_DIR)

build-gen: $(KERNEL_CONF) $(KERNEL_BUILD_INFO)

build-pre: build-gen

build-main: build-pre build-target

build-post: build-main

build-all: clean build-post

dump-all: build-all
	$(OD) $(OD_FLAGS) $(KERNEL_ELF) > $(KERNEL_ELF).dump

format:
	find $(SRC_DIRS) -name *.c -or -name *.h | xargs clang-format -i --style=file

format-diff:
	git diff -U0 --no-color | clang-format-diff -i -p1 -style=file

debug-boot:
	$(DBG) $(DBG_FLAGS) -x $(TOOLS_DIR)/startup_boot.gdb

debug-kernel:
	$(DBG) $(DBG_FLAGS) -x $(TOOLS_DIR)/startup_kernel.gdb

debug-open:
	$(OCD) -f $(OCD_DIR)/interface/$(TARGET_IF).cfg -f $(OCD_DIR)/target/$(TARGET_BOARD).cfg

debug-cli:
	telnet 127.0.0.1 4444

boot-copy: dump-all
	diskutil mountDisk bootfs
	cp $(KERNEL_IMG) /Volumes/bootfs/kernel8.img
	diskutil unmountDisk bootfs

serial:
	picocom -b 115200 /dev/tty.usbserial-A9028XIR

todo:
	grep --recursive --exclude-dir=$(OUT_DIR) --regexp="TODO($(USER)): " || echo "No user TODOs found!"
