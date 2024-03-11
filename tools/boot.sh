#!/bin/bash
./tools/package.sh
printf "\n"
qemu-system-i386 -serial stdio -cdrom Sinx.iso ${@}
