BUILD_DIR := build
BIN_DIR := bin
KERNEL_DIR := kernel
BOOT_PATH := $(KERNEL_DIR)/boot.asm
KERNEL_ENTRY := $(KERNEL_DIR)/kernel.c

AS := nasm
AS_FLAGS := -f elf32

CC := i686-elf-gcc
CC_FLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra

$(BUILD_DIR)/boot.o: $(BOOT_PATH)
	$(AS) $(AS_FLAGS) $(BOOT_PATH) -o $(BUILD_DIR)/boot.o

$(BUILD_DIR)/kernel.o: $(KERNEL_ENTRY)
	$(CC) -c $(KERNEL_ENTRY) -o $(BUILD_DIR)/kernel.o $(CC_FLAGS)

$(BIN_DIR)/kernel.img: $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o
	$(CC) -T linker.ld -o $(BIN_DIR)/kernel.img -ffreestanding -O2 -nostdlib $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o -lgcc