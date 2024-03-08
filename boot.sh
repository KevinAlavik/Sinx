#!/bin/bash
./package.sh    # Package the ISO using GRUB and xorriso
qemu-system-i386 -serial stdio -cdrom Sinx.iso ${@} # Run using QEMU, with debugcon to stdio
