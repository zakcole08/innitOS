#!/usr/bin/env bash

if [[ -z $1 ]]; then
  KERNEL=/boot/vmlinuz-$(uname -r)
else
  KERNEL=$1
fi

kvm \
  -kernel $KERNEL \
  -initrd initramfs.img \
  -nographic \
  -append "console=ttyS0 rdinit=/sbin/innit"
