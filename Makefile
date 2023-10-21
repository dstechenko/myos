# Copyright (C) Dmytro Stechenko
# License: http://www.gnu.org/licenses/gpl.html

TARGET_ARCH  ?= aarch64
export TARGET_ARCH

TARGET_BOARD ?= bcm2837
export TARGET_BOARD

TARGET_MODE  ?= debug
export TARGET_MODE

ARCH_DIR    := arch
CONFIGS_DIR := configs
DRIVERS_DIR := drivers
OUT_DIR     := out
INC_DIR     := include
KERNEL_DIR  := kernel
TOOLS_DIR   := tools

SRC_DIRS    := $(ARCH_DIR) $(CONFIGS_DIR) $(DRIVERS_DIR) $(INC_DIRS) $(KERNEL_DIR)

ARCH_DIR := $(ARCH_DIR)/$(TARGET_ARCH)
BOOT_DIR := $(ARCH_DIR)/boot

GEN_DIR  := $(OUT_DIR)/gen

CONFIGS_ARCH_DIR  := $(ARCH_DIR)/configs
CONFIGS_BOARD_DIR := $(CONFIGS_DIR)/board/$(TARGET_BOARD)

KERNEL_ELF := $(OUT_DIR)/kernel.elf
KERNEL_IMG := $(OUT_DIR)/kernel.img

TOOLCHAIN := $(TOOLS_DIR)/cc/bin/$(TARGET_ARCH)-elf

AS  := $(TOOLCHAIN)-gcc
CC  := $(TOOLCHAIN)-gcc
DBG := gdb
LD  := $(TOOLCHAIN)-gcc
OD  := $(TOOLCHAIN)-objdump
OC  := $(TOOLCHAIN)-objcopy
VM  := qemu-system-$(TARGET_ARCH)

AS_FLAGS  := -c -g -mgeneral-regs-only -MMD
C_FLAGS   := -c -g -mgeneral-regs-only -ffreestanding -nostdlib -nostartfiles -Wall -Wextra -MMD
DBG_FLAGS := -q
LD_FLAGS  := -g -ffreestanding -nostdlib -nostartfiles
LD_LIBS   := -lgcc
PP_FLAGS  := -E -P -x c -D__ASSEMBLER__
VM_FLAGS  := -M raspi3b -serial null -serial stdio
OD_FLAGS  := -s -d

KERNEL_DIRS := $(KERNEL_DIR) $(ARCH_DIR) $(DRIVERS_DIR)
KERNEL_OBJS := $(shell find $(KERNEL_DIRS) -type f -name *.c -or -name *.S)
KERNEL_OBJS := $(KERNEL_OBJS:$(ARCH_DIR)/%.S=$(OUT_DIR)/%.o)
KERNEL_OBJS := $(KERNEL_OBJS:$(ARCH_DIR)/%.c=$(OUT_DIR)/%.o)
KERNEL_OBJS := $(KERNEL_OBJS:%.c=$(OUT_DIR)/%.o)
KERNEL_OBJS := $(KERNEL_OBJS:%.S=$(OUT_DIR)/%.o)

KERNEL_BUILD_INFO := $(GEN_DIR)/include/kernel/core/build_info.h
KERNEL_CONF       := $(GEN_DIR)/include/kernel/core/config.h
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
.PHONY: format install_deps install_cc dump-all
.PHONY: boot-vm boot-copy debug-vm serial

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

build-gen: $(KERNEL_CONF) $(KERNEL_BUILD_INFO)

build-pre: build-gen

build-main: build-pre build-target

build-post: build-main

build-all: build-post

clean:
	rm -rf $(OUT_DIR)

format:
	find $(SRC_DIRS) -name *.c -or -name *.h | xargs clang-format -i --style=file

format-diff:
	git diff -U0 --no-color | clang-format-diff -i -p1 -style=file

install-deps:
	$(TOOLS_DIR)/install_deps.sh

install-cc:
	$(TOOLS_DIR)/install_cc.sh

boot-vm: build-all
	$(VM) $(VM_FLAGS) -kernel $(KERNEL_IMG)

debug-boot-vm: build-all
	$(VM) $(VM_FLAGS) -s -S -kernel $(KERNEL_IMG) &
	$(DBG) $(DBG_FLAGS) -x $(TOOLS_DIR)/startup_boot.gdb

debug-kernel-vm: build-all
	$(VM) $(VM_FLAGS) -s -S -kernel $(KERNEL_IMG) &
	$(DBG) $(DBG_FLAGS) -x $(TOOLS_DIR)/startup_kernel.gdb

dump-all: build-all
	$(OD) $(OD_FLAGS) $(KERNEL_ELF) > $(KERNEL_ELF).dump

boot-copy: build-all
	cp $(KERNEL_IMG) /run/media/$(USER)/bootfs/kernel8.img

serial:
	picocom -b 115200 /dev/ttyUSB0

todo:
	grep -r . -e "TODO($(USER)): " || echo "No user TODOs found!"
