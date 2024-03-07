#!/bin/bash
make clean      # So we can easly tell if it didnt compile
./package.sh    # Package the ISO using GRUB

qemu-system-i386 -serial stdio -cdrom Sinx.iso ${@} # Run using QEMU, with debugcon to stdio
