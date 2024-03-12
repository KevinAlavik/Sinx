BUILD_DIR := build
BIN_DIR := bin
KERNEL_DIR := kernel
ARCH_DIR := arch
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

QEMU_ARGS := -serial stdio --enable-kvm

.PHONY: all clean package

all: $(BIN_DIR)/kernel.img

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "  CC $<"
	@$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/%-asm.o: %.asm
	@mkdir -p $(dir $@)
	@echo "  AS $<"
	@$(AS) $(AS_FLAGS) $< -o $@

$(BUILD_DIR)/boot.o: $(BOOT_PATH)
	@mkdir -p $(BUILD_DIR)
	@echo "  AS $(BOOT_PATH)"
	@$(AS) $(AS_FLAGS) $(BOOT_PATH) -o $@

$(BIN_DIR)/kernel.img: $(BUILD_DIR)/boot.o $(KERNEL_ASM_FILES:%.asm=$(BUILD_DIR)/%-asm.o) $(KERNEL_C_FILES:%.c=$(BUILD_DIR)/%.o) $(ARCH_ASM_FILES:%.asm=$(BUILD_DIR)/%-asm.o) $(ARCH_C_FILES:%.c=$(BUILD_DIR)/%.o)
	@mkdir -p $(BIN_DIR)
	@echo "  LD $@"
	@$(CC) -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $(BUILD_DIR)/boot.o $(KERNEL_ASM_FILES:%.asm=$(BUILD_DIR)/%-asm.o) $(KERNEL_C_FILES:%.c=$(BUILD_DIR)/%.o) $(ARCH_ASM_FILES:%.asm=$(BUILD_DIR)/%-asm.o) $(ARCH_C_FILES:%.c=$(BUILD_DIR)/%.o) -lgcc

clean:
	@find $(BUILD_DIR) -type f -exec sh -c 'echo "  RM {}" && rm -f {}' \;
	@find $(BIN_DIR) -type f -exec sh -c 'echo "  RM {}" && rm -f {}' \;
	@echo "  RM $(ISO_FILE)"
	@rm -f $(ISO_FILE)

package: all
	@if [ ! -f "$(BIN_DIR)/kernel.img" ]; then \
	    echo "Error: Kernel file '$(BIN_DIR)/kernel.img' not found."; \
	    exit 1; \
	fi
	@if [ ! -d "$(GRUB_DIR)" ]; then \
	    echo "Error: GRUB directory '$(GRUB_DIR)' not found."; \
	    exit 1; \
	fi
	@echo "  MKDIR $(ISO_DIR)/boot/grub"
	@mkdir -p "$(ISO_DIR)/boot/grub"
	@echo "  CP $(BIN_DIR)/kernel.img -> $(ISO_DIR)/boot/kernel.img"
	@cp "$(BIN_DIR)/kernel.img" "$(ISO_DIR)/boot/kernel.img"
	@echo "  CP $(GRUB_CFG) -> $(ISO_DIR)/boot/grub/grub.cfg"
	@cp "$(GRUB_CFG)" "$(ISO_DIR)/boot/grub/grub.cfg"
	@echo "  OUT $(ISO_FILE)"
	@grub-mkrescue -o "$(ISO_FILE)" "$(ISO_DIR)" > /dev/null 2>&1 || (echo "Failed to build ISO."; exit 1;)
	@echo "  RM $(ISO_DIR)"
	@rm -rf "$(ISO_DIR)"

qemu: package
	@printf "  QEMU $(ISO_FILE) {$(QEMU_ARGS)} \n\n"
	@qemu-system-i386 -cdrom $(ISO_FILE) $(QEMU_ARGS)