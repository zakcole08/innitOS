CC      = gcc
CFLAGS  = -Wall -static -Isrc/mishell/commands # -I lets us use #include "command.h" easily
ROOTFS  = rootfs
SRC_DIR = src
IMG     = initramfs.img

INNIT_SRC   = $(SRC_DIR)/innit.c
MISHELL_MAIN = $(SRC_DIR)/mishell/mishell.c
COMMAND_SRCS = $(wildcard $(SRC_DIR)/mishell/commands/*.c)

ALL_SHELL_SRCS = $(MISHELL_MAIN) $(COMMAND_SRCS)
SHELL_OBJS     = $(ALL_SHELL_SRCS:.c=.o)

# Destinations
INNIT_DST   = $(ROOTFS)/sbin/innit
MISHELL_DST = $(ROOTFS)/bin/mishell

# --- Rules ---

all: $(IMG)

$(IMG): $(INNIT_DST) $(MISHELL_DST)
	@echo "Creating Image..."
	mkdir -p $(ROOTFS)/{proc,sys,bin,sbin}
	cd $(ROOTFS) && find . | cpio -o -H newc | gzip > ../$(IMG)

$(MISHELL_DST): $(SHELL_OBJS)
	@mkdir -p $(ROOTFS)/bin
	$(CC) $(CFLAGS) -o $@ $(SHELL_OBJS)

$(INNIT_DST): $(INNIT_SRC)
	@mkdir -p $(ROOTFS)/sbin
	$(CC) $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(IMG) $(INNIT_DST) $(MISHELL_DST)
	find . -name "*.o" -type f -delete
