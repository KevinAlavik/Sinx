#!/bin/bash
./package.sh
printf "\n------------------------\n"
qemu-system-i386 -serial stdio -cdrom Sinx.iso ${@}
