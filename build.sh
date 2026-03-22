#!/usr/bin/env bash

mkdir -p rootfs/{proc,sys,bin,sbin}

gcc -static src/innit.c -o src/innit
gcc -static src/mishell.c -o src/mishell
mv src/mishell rootfs/bin
mv src/innit rootfs/sbin
cd rootfs
find . | cpio -o -H newc | gzip > ../initramfs.img
