# Copyright (C) Dmytro Stechenko
# License: http://www.gnu.org/licenses/gpl.html

TARGET_ARCH := aarch64

ARCH_DIR    := arch/$(TARGET_ARCH)
BIN_DIR     := bin
BOOT_DIR    := $(ARCH_DIR)/boot
BUILD_DIR   := build
GEN_DIR     := gen
INC_DIR     := include
KERNEL_DIR  := kernel
TOOLS_DIR   := tools

KERNEL_ELF :=$(BIN_DIR)/kernel.elf
KERNEL_IMG :=$(BIN_DIR)/kernel8.img

TOOLCHAIN := $(TOOLS_DIR)/cc/bin/$(TARGET_ARCH)-elf

AS  := $(TOOLCHAIN)-as
CPP := $(TOOLCHAIN)-cpp
CC  := $(TOOLCHAIN)-gcc
LD  := $(TOOLCHAIN)-gcc
OD  := $(TOOLCHAIN)-objdump
OC  := $(TOOLCHAIN)-objcopy
VM  := qemu-system-$(TARGET_ARCH)

ASFLAGS  := -g
CFLAGS   := -g -ffreestanding -Wall -Wextra
LDFLAGS  := -g -ffreestanding -nostdlib
LDLIBS   := -lgcc
VMFLAGS  := -M raspi3b -serial stdio -no-reboot
ODFLAGS  := -D

INC_FILES := $(shell dir $(INC_DIR))
INC_FILES := $(INCS:%=-I$(INC_DIR)/%)

KERNEL_GENS := $(KERNEL_GENS:$(GEN_DIR)/%.c=$(BUILD_DIR)/%.o)
KERNEL_DIRS := $(KERNEL_DIR) $(ARCH_DIR)
KERNEL_OBJS := $(shell find $(KERNEL_DIRS) -type f -name *.c -or -name *.S)
KERNEL_OBJS := $(KERNEL_OBJS:$(ARCH_DIR)/%.S=$(BUILD_DIR)/%.o)
KERNEL_OBJS := $(KERNEL_OBJS:$(ARCH_DIR)/%.c=$(BUILD_DIR)/%.o)
KERNEL_OBJS := $(KERNEL_OBJS:%.c=$(BUILD_DIR)/%.o)
KERNEL_OBJS := $(KERNEL_OBJS:%.S=$(BUILD_DIR)/%.o)
KERNEL_OBJS := $(BUILD_DIR)/boot/boot.o $(BUILD_DIR)/boot/entry.o $(KERNEL_GENS) $(KERNEL_OBJS)

$(KERNEL_IMG): $(KERNEL_OBJS)
	mkdir -p $(@D)
	$(LD) $(LDFLAGS) -T $(BOOT_DIR)/link.ld -o $(KERNEL_ELF) $^ $(LDLIBS)
	$(OC) $(KERNEL_ELF) -O binary $(KERNEL_IMG)

$(BUILD_DIR)/%.o: $(ARCH_DIR)/%.S
	mkdir -p $(@D)
	$(AS) $(ASFLAGS) -c -I$(<D) $< -o $@

$(BUILD_DIR)/%.o: %.S
	mkdir -p $(@D)
	$(AS) $(ASFLAGS) -c -I$(<D) $< -o $@

$(BUILD_DIR)/%.o: $(ARCH_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_FILES) -I$(<D) -c $< -o $@

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

.PHONY: vm_boot
vm_boot: $(KERNEL_IMG)
	$(VM) $(VMFLAGS) -kernel bin/kernel8.img &
