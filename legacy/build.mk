LEGACY_AS	= nasm
LEGACY_CC	= clang

LEGACY_TARGET	= i686-unknown-elf
LEGACY_CFLAGS	= $(COMMON_CFLAGS)  -ffreestanding -fno-builtin -D__LEGACY_BIOS__
LEGACY_LDFLAGS	= -T legacy/stage2/linker.ld -nostdlib

LEGACY_SRCS	= boot/boot.s stage2/stage2.s
LEGACY_STAGE2_SRCS = entry.s vga.s
LEGACY_STAGE2_OBJS = $(addprefix legacy/stage2/, $(LEGACY_STAGE2_SRCS:.s=.o))
#						$(addprefix common/, $(COMMON_SRCS:.c=.legacy.o))
LEGACY_OBJS	= $(addprefix legacy/, $(LEGACY_SRCS:.s=.bin))

istar.bin: $(LEGACY_OBJS)
	cat $^ /dev/zero | dd of=$@ bs=512 count=2880 iflag=fullblock

legacy/boot/%.bin: legacy/boot/%.s
	$(LEGACY_AS) -fbin -o $@ $<

legacy/stage2/%.bin: $(LEGACY_STAGE2_OBJS)
	$(LEGACY_CC) -target $(LEGACY_TARGET) $(LEGACY_LDFLAGS) $^ -o $@

legacy/stage2/%.o: legacy/stage2/%.s
	$(LEGACY_AS) -f elf -o $@ $<

common/%.legacy.o: common/%.c
	$(LEGACY_CC) -target $(LEGACY_TARGET) -c -o $@ $< $(LEGACY_CFLAGS)
