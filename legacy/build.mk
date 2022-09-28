LEGACY_AS	= nasm
LEGACY_SRCS	= boot/boot.s stage2/stage2.s
LEGACY_STAGE2_DEPS = $(addprefix legacy/stage2/, vga.s)
LEGACY_OBJS	= $(addprefix legacy/, $(LEGACY_SRCS:.s=.bin))

istar.bin: $(LEGACY_OBJS)
	cat $^ /dev/zero | dd of=$@ bs=512 count=2880 iflag=fullblock

legacy/boot/%.bin: legacy/boot/%.s
	$(LEGACY_AS) -fbin -o $@ $<

legacy/stage2/%.bin: legacy/stage2/%.s $(LEGACY_STAGE2_DEPS)
	$(LEGACY_AS) -fbin -o $@ $<
