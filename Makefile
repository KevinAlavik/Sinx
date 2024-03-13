BUILD_DIR := build
BIN_DIR := bin
KERNEL_DIR := kernel
ARCH_DIR := arch
RAMDISK_DIR := initrd
GRUB_DIR := grub
ISO_DIR := public
GRUB_CFG := $(GRUB_DIR)/grub.cfg
BOOT_PATH := $(KERNEL_DIR)/multiboot/boot.asm
ISO_FILE := Sinx.iso

AS := nasm
AS_FLAGS := -f elf32

CC := i686-elf-gcc
CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(KERNEL_DIR)/include -I$(ARCH_DIR) -I$(KERNEL_DIR)

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

KERNEL_ASM_FILES := $(filter-out $(BOOT_PATH), $(call rwildcard,$(KERNEL_DIR)/,*.asm))
KERNEL_C_FILES := $(call rwildcard,$(KERNEL_DIR)/,*.c)
ARCH_ASM_FILES := $(call rwildcard,$(ARCH_DIR)/,*.asm)
ARCH_C_FILES := $(call rwildcard,$(ARCH_DIR)/,*.c)

INITRD_DIR := $(RAMDISK_DIR)
INITRD_FILES := $(wildcard $(RAMDISK_DIR)/*) $(wildcard $(RAMDISK_DIR)/*/*)

QEMU_ARGS := -serial stdio -vga std -name Sinx -boot d

.PHONY: all clean package

all: $(BIN_DIR)/kernel.img

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "  CC\t$<\n"
	@$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/%-asm.o: %.asm
	@mkdir -p $(dir $@)
	@printf "  AS\t$<\n"
	@$(AS) $(AS_FLAGS) $< -o $@

$(BUILD_DIR)/boot.o: $(BOOT_PATH)
	@mkdir -p $(BUILD_DIR)
	@printf "  AS\t$(BOOT_PATH)\n"
	@$(AS) $(AS_FLAGS) $(BOOT_PATH) -o $@

$(BIN_DIR)/kernel.img: $(BUILD_DIR)/boot.o $(KERNEL_ASM_FILES:%.asm=$(BUILD_DIR)/%-asm.o) $(KERNEL_C_FILES:%.c=$(BUILD_DIR)/%.o) $(ARCH_ASM_FILES:%.asm=$(BUILD_DIR)/%-asm.o) $(ARCH_C_FILES:%.c=$(BUILD_DIR)/%.o)
	@mkdir -p $(BIN_DIR)
	@printf "  LD\t$@\n"
	@$(CC) -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $(BUILD_DIR)/boot.o $(KERNEL_ASM_FILES:%.asm=$(BUILD_DIR)/%-asm.o) $(KERNEL_C_FILES:%.c=$(BUILD_DIR)/%.o) $(ARCH_ASM_FILES:%.asm=$(BUILD_DIR)/%-asm.o) $(ARCH_C_FILES:%.c=$(BUILD_DIR)/%.o) -lgcc

clean:
	@find $(BUILD_DIR) -type f -exec sh -c 'printf "  RM\t{}\n" && rm -f {}' \;
	@find $(BIN_DIR) -type f -exec sh -c 'printf "  RM\t{}\n" && rm -f {}' \;
	@printf "  RM\t$(ISO_FILE)\n"
	@rm -f $(ISO_FILE)

package: all $(BIN_DIR)/initrd
	@if [ ! -f "$(BIN_DIR)/kernel.img" ]; then \
		@echo "Error: Kernel file '$(BIN_DIR)/kernel.img' not found."; \
		exit 1; \
	fi
	@if [ ! -d "$(GRUB_DIR)" ]; then \
		@echo "Error: GRUB directory '$(GRUB_DIR)' not found."; \
		exit 1; \
	fi
	@printf "  MKDIR\t$(ISO_DIR)/boot/grub\n"
	@mkdir -p "$(ISO_DIR)/boot/grub"
	@printf "  CP\t$(BIN_DIR)/kernel.img\t-> $(ISO_DIR)/boot/kernel.img\n"
	@cp "$(BIN_DIR)/kernel.img" "$(ISO_DIR)/boot/kernel.img"
	@printf "  CP\t$(BIN_DIR)/initrd\t-> $(ISO_DIR)/boot/initrd\n"
	@cp "$(BIN_DIR)/initrd" "$(ISO_DIR)/boot/initrd"
	@printf "  CP\t$(GRUB_CFG)\t-> $(ISO_DIR)/boot/grub/grub.cfg\n"
	@cp "$(GRUB_CFG)" "$(ISO_DIR)/boot/grub/grub.cfg"
	@printf "  OUT\t$(ISO_FILE)\n"
	@grub-mkrescue -o "$(ISO_FILE)" "$(ISO_DIR)" > /dev/null 2>&1 || (echo "Failed to build ISO."; exit 1;)
	@printf "  RM\t$(ISO_DIR)\n"
	@rm -rf "$(ISO_DIR)"

$(BIN_DIR)/initrd: $(INITRD_FILES)
	@mkdir -p $(BIN_DIR)
	@printf "  GEN\t$@\n"
	@tar -cf $@ -C $(INITRD_DIR) .

qemu: package
	@printf "  QEMU\t$(ISO_FILE) {$(QEMU_ARGS)} \n\n"
	@qemu-system-i386 -cdrom $(ISO_FILE) $(QEMU_ARGS)
