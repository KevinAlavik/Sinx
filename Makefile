BUILD_DIR := build
BIN_DIR := bin
KERNEL_DIR := kernel
BOOT_PATH := $(KERNEL_DIR)/boot.asm

AS := nasm
AS_FLAGS := -f elf32

CC := i686-elf-gcc
CC_FLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(KERNEL_DIR)/klibc

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

KERNEL_ASM_FILES := $(filter-out $(BOOT_PATH), $(call rwildcard,$(KERNEL_DIR)/,*.asm))
KERNEL_C_FILES := $(call rwildcard,$(KERNEL_DIR)/,*.c)

.PHONY: all
all: $(BIN_DIR)/kernel.img

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CC_FLAGS)

$(BUILD_DIR)/%.o: %.asm
	mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) $< -o $@

$(BUILD_DIR)/boot.o: $(BOOT_PATH)
	mkdir -p $(BUILD_DIR)
	$(AS) $(AS_FLAGS) $(BOOT_PATH) -o $@

$(BIN_DIR)/kernel.img: $(BUILD_DIR)/boot.o $(KERNEL_ASM_FILES:%.asm=$(BUILD_DIR)/%.o) $(KERNEL_C_FILES:%.c=$(BUILD_DIR)/%.o)
	$(CC) -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $(BUILD_DIR)/boot.o $(KERNEL_ASM_FILES:%.asm=$(BUILD_DIR)/%.o) $(KERNEL_C_FILES:%.c=$(BUILD_DIR)/%.o) -lgcc

clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*
