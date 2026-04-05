CC = gcc
CFLAGS = -Wall -static -I src/mishell/commands # Include "command.h"
DISK_IMG = innitOS.img
DISK_SIZE = 512
MOUNT_DIR = ./mnt_disk

GCC_URL = https://musl.cc/x86_64-linux-musl-native.tgz
GCC_STAMP = rootfs/usr/bin/gcc
TCC_URL = https://github.com/Tiny-C-Compiler/tinycc-mirror-repository.git
TCC_STAMP = rootfs/usr/bin/tcc

all: $(DISK_IMG)

binaries:
	@mkdir -p rootfs/bin rootfs/sbin rootfs/usr rootfs/tmp rootfs/dev rootfs/proc rootfs/sys
	$(CC) $(CFLAGS) src/innit.c src/utils/*.c -o rootfs/sbin/init
	$(CC) $(CFLAGS) src/mishell/mishell.c src/mishell/commands/*.c src/utils/*.c -o rootfs/bin/mishell

$(GCC_STAMP):
	@echo "Bundling GCC Toolchain..."
	curl -L $(GCC_URL) -o gcc_toolchain.tgz
	mkdir -p tmp_gcc
	tar -xzf gcc_toolchain.tgz -C tmp_gcc --strip-components=1
	cp -ra tmp_gcc/* rootfs/usr/
	rm -rf tmp_gcc gcc_toolchain.tgz
	@touch $(GCC_STAMP)

$(TCC_STAMP):
	@echo "Building TCC..."
	@if [ ! -d tmp_tcc ]; then git clone $(TCC_URL) tmp_tcc; fi
	cd tmp_tcc && ./configure --prefix=/usr
	cd tmp_tcc && make
	mkdir -p rootfs/usr/lib rootfs/usr/include rootfs/usr/bin
	cd tmp_tcc && make install DESTDIR=$(PWD)/rootfs
	@touch $(TCC_STAMP)

$(DISK_IMG): binaries $(GCC_STAMP)
	@echo "Baking Disk Image..."
	dd if=/dev/zero of=$(DISK_IMG) bs=1M count=$(DISK_SIZE)
	mkfs.ext4 -F $(DISK_IMG)
	@mkdir -p $(MOUNT_DIR)
	sudo mount $(DISK_IMG) $(MOUNT_DIR)
	sudo cp -ra rootfs/* $(MOUNT_DIR)/
	@# Create basic device nodes so the screen/keyboard work
	sudo mkdir -p $(MOUNT_DIR)/dev
	sudo umount $(MOUNT_DIR)
	@rmdir $(MOUNT_DIR)
	@echo "Success! Run with: qemu-system-x86_64 -kernel bzImage -drive format=raw,file=$(DISK_IMG) -append \"root=/dev/sda rw\""

clean:
	rm -rf rootfs/usr/* rootfs/bin/* rootfs/sbin/* $(DISK_IMG)

.PHONY: all binaries clean
