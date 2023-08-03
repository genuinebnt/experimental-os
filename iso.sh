#!/bin/sh
set -e
. ./build.sh
 
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
 
cp sysroot/boot/experimentalos.kernel isodir/boot/experimentalos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "experimentalos" {
	multiboot /boot/experimentalos.kernel
}
EOF
grub-mkrescue -o experimentalos.iso isodir