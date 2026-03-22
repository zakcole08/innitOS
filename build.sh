#!/usr/bin/env bash

# colours
GRN='\e[32m'
RED='\e[31m'
RST='\e[0m'

# vars
INNIT_SRC="src/innit.c"
MISHELL_SRC="src/mishell.c"
INNIT_DST="rootfs/sbin/innit"
MISHELL_DST="rootfs/bin/mishell"

mkdir -p rootfs/{proc,sys,bin,sbin}
if [[ $? -ne 0 ]]; then
  echo -e "${RED}FAILED: create folders: rootfs, rootfs/{proc,sys,bin,sbin}${RST}"
  exit 1
else
  echo -e "${GRN}Created folders: rootfs, rootfs/{proc,sys,bin,sbin}${RST}"
fi

gcc -static $INNIT_SRC -o $INNIT_DST
if [[ $? -ne 0 ]]; then
  echo -e "${RED}FAILED: compile $INNIT_DST${RST}"
else
  echo -e "${GRN}Compiled $INNIT_DST${RST}"
fi
gcc -static $MISHELL_SRC -o $MISHELL_DST
if [[ $? -ne 0 ]]; then
  echo -e "${RED}FAILED: compile $MISHELL_DST${RST}"
else
  echo -e "${GRN}Compiled $MISHELL_DST${RST}"
fi

cd rootfs
find . | cpio -o -H newc | gzip > ../initramfs.img
if [[ $? -ne 0 ]]; then
  echo -e "${RED}FAILED: create initramfs.img${RST}"
else
  echo -e "${GRN}Created initramfs.img${RST}"
fi
