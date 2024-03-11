#!/bin/bash
./tools/package.sh
echo "------------------------"
qemu-system-i386 -serial stdio -cdrom Sinx.iso ${@}
