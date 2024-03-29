.DEFAULT_GOAL = all

CC	?= clang
LD	?= ld
RM	= rm -f

PREFIX ?= /usr/local

COMMON_CFLAGS	= -ansi -pedantic -Werror -Wextra -Wall -Iinclude -Wno-long-long
CFLAGS	= $(COMMON_CFLAGS)

include man/build.mk
include common/build.mk
include legacy/build.mk
include cli/build.mk
include efi/build.mk

all: istar-cli BOOTX64.EFI BOOTIA32.EFI

clean:
	$(RM) istar.bin $(LEGACY_OBJS)
	$(RM) istar-cli $(CLI_OBJS)
	$(RM) BOOTX64.EFI BOOTIA32.EFI $(EFI_OBJS)

re: clean all

run-legacy: istar.bin
	qemu-system-i386 -hda $^

OVMF.fd:
	wget 'https://retrage.github.io/edk2-nightly/bin/DEBUGX64_OVMF.fd' -O $@

OVMF32.fd:
	wget 'https://retrage.github.io/edk2-nightly/bin/DEBUGIa32_OVMF.fd' -O $@

run-efi-ia32: OVMF32.fd BOOTIA32.EFI
	mkdir -p ".test/EFI/BOOT"
	cp BOOTIA32.EFI .test/EFI/BOOT
	qemu-system-i386 -enable-kvm -serial stdio -bios OVMF.fd \
						-drive file=fat:rw:./.test/,media=disk,format=raw

run-efi: OVMF.fd BOOTX64.EFI
	mkdir -p ".test/EFI/BOOT"
	cp BOOTX64.EFI .test/EFI/BOOT
	qemu-system-x86_64 -enable-kvm -serial stdio -bios OVMF.fd \
						-drive file=fat:rw:./.test/,media=disk,format=raw
	
run: run-efi

install: istar-cli install-man
	install -d $(DESTDIR)$(PREFIX)/sbin/
	install istar-cli $(DESTDIR)$(PREFIX)/sbin/

.PHONY: all clean re run-legacy run-efi-ia32 run-efi run
