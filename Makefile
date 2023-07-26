# Copyright (C) Dmytro Stechenko
# License: http://www.gnu.org/licenses/gpl.html

TARGET_ARCH  := aarch64
TARGET_BOARD := bcm2837

ARCH_DIR    := arch/$(TARGET_ARCH)
BOOT_DIR    := $(ARCH_DIR)/boot
DRIVERS_DIR := drivers
OUT_DIR     := out
INC_DIR     := include
KERNEL_DIR  := kernel
TOOLS_DIR   := tools

KERNEL_ELF :=$(OUT_DIR)/kernel.elf
KERNEL_IMG :=$(OUT_DIR)/kernel8.img

TOOLCHAIN := $(TOOLS_DIR)/cc/bin/$(TARGET_ARCH)-elf

AS  := $(TOOLCHAIN)-as
CPP := $(TOOLCHAIN)-cpp
CC  := $(TOOLCHAIN)-gcc
LD  := $(TOOLCHAIN)-gcc
OD  := $(TOOLCHAIN)-objdump
OC  := $(TOOLCHAIN)-objcopy
VM  := qemu-system-$(TARGET_ARCH)

ASFLAGS  := -g
CFLAGS   := -g -ffreestanding -nostdlib -nostartfiles -mgeneral-regs-only -Wall -Wextra -MMD
LDFLAGS  := -g -ffreestanding -nostdlib
LDLIBS   := -lgcc
VMFLAGS  := -M raspi3b -serial stdio -no-reboot
ODFLAGS  := -D

KERNEL_DIRS := $(KERNEL_DIR) $(ARCH_DIR) $(DRIVERS_DIR)
KERNEL_OBJS := $(shell find $(KERNEL_DIRS) -type f -name *.c -or -name *.S)
KERNEL_OBJS := $(KERNEL_OBJS:$(ARCH_DIR)/%.S=$(OUT_DIR)/%.o)
KERNEL_OBJS := $(KERNEL_OBJS:$(ARCH_DIR)/%.c=$(OUT_DIR)/%.o)
KERNEL_OBJS := $(KERNEL_OBJS:%.c=$(OUT_DIR)/%.o)
KERNEL_OBJS := $(KERNEL_OBJS:%.S=$(OUT_DIR)/%.o)
KERNEL_OBJS := $(OUT_DIR)/boot/boot.o $(OUT_DIR)/boot/entry.o $(KERNEL_OBJS)

$(KERNEL_IMG): $(KERNEL_OBJS)
	mkdir -p $(@D)
	$(LD) $(LDFLAGS) -T $(BOOT_DIR)/link.ld -o $(KERNEL_ELF) $^ $(LDLIBS)
	$(OC) $(KERNEL_ELF) -O binary $(KERNEL_IMG)

$(OUT_DIR)/%.o: $(ARCH_DIR)/%.S
	mkdir -p $(@D)
	$(AS) $(ASFLAGS) -c -I$(<D) $< -o $@

$(OUT_DIR)/%.o: %.S
	mkdir -p $(@D)
	$(AS) $(ASFLAGS) -c -I$(<D) $< -o $@

$(OUT_DIR)/%.o: $(ARCH_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(<D) -c $< -o $@

$(OUT_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(<D) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OUT_DIR)

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
	$(VM) $(VMFLAGS) -kernel $(KERNEL_IMG) &
