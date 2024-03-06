BUILD_DIR := build
BIN_DIR := bin
KERNEL_DIR := kernel
BOOT_PATH := $(KERNEL_DIR)/boot.asm

AS := i686-elf-as
AS_FLAGS :=

CC := i686-elf-gcc
CC_FLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra

.PHONY: all
all: $(BIN_DIR)/kernel.img

$(BUILD_DIR)/kernel.o: $(KERNEL_DIR)/kernel.c
	$(CC) -c $< -o $@ $(CC_FLAGS)

$(BUILD_DIR)/boot.o: $(BOOT_PATH)
	mkdir -p $(BUILD_DIR)
	$(AS) $(AS_FLAGS) $(BOOT_PATH) -o $@

$(BIN_DIR)/kernel.img: $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o
	$(CC) -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o -lgcc

clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*
