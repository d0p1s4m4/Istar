.DEFAULT_GOAL = all

CC	?= clang
LD	?= ld
RM	= rm -f

COMMON_CFLAGS	= -ansi -pedantic -Werror -Wextra -Wall -Iinclude
CFLAGS	= $(COMMON_CFLAGS)

include legacy/build.mk
include cli/build.mk
include efi/build.mk

all: istar-cli BOOTX64.EFI

clean:
	$(RM) istar.bin $(LEGACY_OBJS)
	$(RM) istar-cli $(CLI_OBJS)
	$(RM) BOOTX64.EFI $(EFI_OBJS)

re: clean all

run-legacy: istar.bin
	qemu-system-i386 -hda $^

OVMF.fd:
	wget 'https://retrage.github.io/edk2-nightly/bin/DEBUGX64_OVMF.fd' -O $@

run-efi: OVMF.fd BOOTX64.EFI
	mkdir -p ".test/EFI/BOOT"
	cp BOOTX64.EFI .test/EFI/BOOT
	qemu-system-x86_64 -enable-kvm -serial stdio -bios OVMF.fd \
						-drive file=fat:rw:./.test/,media=disk,format=raw
	

run: run-efi

.PHONY: all clean re run-legacy run-efi run
