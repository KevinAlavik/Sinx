BUILD_DIR := build
BIN_DIR := bin
KERNEL_DIR := kernel
ARCH_DIR := arch
BOOT_PATH := $(KERNEL_DIR)/multiboot/boot.asm

AS := nasm
AS_FLAGS := -f elf32

CC := i686-elf-gcc
CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(KERNEL_DIR)/include -I$(ARCH_DIR) -I$(KERNEL_DIR)

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

KERNEL_ASM_FILES := $(filter-out $(BOOT_PATH), $(call rwildcard,$(KERNEL_DIR)/,*.asm))
KERNEL_C_FILES := $(call rwildcard,$(KERNEL_DIR)/,*.c)
ARCH_ASM_FILES := $(call rwildcard,$(ARCH_DIR)/,*.asm)
ARCH_C_FILES := $(call rwildcard,$(ARCH_DIR)/,*.c)

.PHONY: all
all: $(BIN_DIR)/kernel.img

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "  CC $<\n"
	@$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	@printf "  AS $<\n"
	@$(AS) $(AS_FLAGS) $< -o $@

$(BUILD_DIR)/boot.o: $(BOOT_PATH)
	@mkdir -p $(BUILD_DIR)
	@printf "  AS $(BOOT_PATH)\n"
	@$(AS) $(AS_FLAGS) $(BOOT_PATH) -o $@

$(BIN_DIR)/kernel.img: $(BUILD_DIR)/boot.o $(KERNEL_ASM_FILES:%.asm=$(BUILD_DIR)/%.o) $(KERNEL_C_FILES:%.c=$(BUILD_DIR)/%.o) $(ARCH_ASM_FILES:%.asm=$(BUILD_DIR)/%.o) $(ARCH_C_FILES:%.c=$(BUILD_DIR)/%.o)
	@mkdir -p $(BIN_DIR)
	@printf "  LD $@\n"
	@$(CC) -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $(BUILD_DIR)/boot.o $(KERNEL_ASM_FILES:%.asm=$(BUILD_DIR)/%.o) $(KERNEL_C_FILES:%.c=$(BUILD_DIR)/%.o) $(ARCH_ASM_FILES:%.asm=$(BUILD_DIR)/%.o) $(ARCH_C_FILES:%.c=$(BUILD_DIR)/%.o) -lgcc

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR) Sinx.iso
	@printf "Removed build files\n"
