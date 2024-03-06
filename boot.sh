#!/bin/bash
./package.sh # Package the ISO using GRUB

qemu-system-i386 -serial stdio -cdrom Sinx.iso # Run using QEMU, with serial to stdio
