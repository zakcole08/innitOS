#!/usr/bin/env bash

if [[ -z "$1" ]]; then
  KERNEL=/boot/vmlinuz-$(uname -r)
else
  KERNEL="$1"
fi

if [[ ! -f "$KERNEL" ]]; then
  echo "FAILURE: could not open $KERNEL. No such file or directory."
fi


#kvm \
#  -kernel "$KERNEL" \
#  -initrd initramfs.img \
#  -nographic \
#  -append "console=ttyS0 rdinit=/sbin/innit"

kvm \
  -kernel "$KERNEL" \
  -drive format=raw,file=innitOS.img \
  -append "root=/dev/sda rw"
