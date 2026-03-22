#!/usr/bin/env bash

kvm \
  -kernel /boot/vmlinuz-$(uname -r) \
  -initrd initramfs.img \
  -nographic \
  -append "console=ttyS0 rdinit=/sbin/innit"
