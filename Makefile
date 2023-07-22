# Copyright (C) Dmytro Stechenko
# License: http://www.gnu.org/licenses/gpl.html

TARGET_ARCH := aarch64

INC_DIR     := include
BIN_DIR     := bin
GEN_DIR     := gen
BUILD_DIR   := build
TOOLS_DIR   := tools

KERNEL_ELF_TARGET :=$(BIN_DIR)/kernel.elf
KERNEL_IMG_TARGET :=$(BIN_DIR)/kernel8.img

TOOLCHAIN := $(TOOLS_DIR)/cc/bin/$(TARGET_ARCH)-elf

AS  := $(TOOLCHAIN)-as
CPP := $(TOOLCHAIN)-cpp
CC  := $(TOOLCHAIN)-gcc
LD  := $(TOOLCHAIN)-gcc
OD  := $(TOOLCHAIN)-objdump
OC  := $(TOOLCHAIN)-objcopy
VM  := qemu-system-$(TARGET_ARCH)

ASFLAGS  := -g -O
CFLAGS   := -g -O -ffreestanding -Wall -Wextra
LDFLAGS  := -nostdlib
LDLIBS   := -lgcc
VMFLAGS  := -no-reboot -drive
ODFLAGS  := -D

INC_FILES := $(shell dir $(INC_DIR))
INC_FILES := $(INCS:%=-I$(INC_DIR)/%)

$(BUILD_DIR)/%.o: %.S
	mkdir -p $(@D)
	$(AS) $(ASFLAGS) -c -I$(<D) $< -o $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_FILES) -I$(<D) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR) $(GEN_DIR)

.PHONY: format
format:
	find $(SRC_DIR) -name *.c -or -name *.h | xargs clang-format -i --style=file
	find $(INC_DIR)               -name *.h | xargs clang-format -i --style=file

.PHONY: install_deps
install_deps:
	$(TOOLS_DIR)/install_deps.sh

.PHONY: install_cc
install_cc:
	$(TOOLS_DIR)/install_cc.sh
