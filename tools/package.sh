#!/bin/bash

KERNEL_FILE="bin/kernel.img"
GRUB_DIR="grub"
ISO_DIR="public"
GRUB_CFG="$GRUB_DIR/grub.cfg"
ISO_FILE="Sinx.iso"

make

if [ ! -f "$KERNEL_FILE" ]; then
    echo "Error: Kernel file '$KERNEL_FILE' not found."
    exit 1
fi

if [ ! -d "$GRUB_DIR" ]; then
    echo "Error: GRUB directory '$GRUB_DIR' not found."
    exit 1
fi

mkdir -p "$ISO_DIR/boot/grub"

cp "$KERNEL_FILE" "$ISO_DIR/boot/kernel.img"
cp "$GRUB_CFG" "$ISO_DIR/boot/grub/grub.cfg"

grub-mkrescue -o "$ISO_FILE" "$ISO_DIR" > /dev/null 2>&1

if [ $? -eq 1 ]; then
    printf "\nFailed to build ISO.\n"
fi

rm -rf "$ISO_DIR"
