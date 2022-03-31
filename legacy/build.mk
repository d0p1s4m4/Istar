LEGACY_AS	= nasm
LEGACY_SRCS	= boot/boot.s stage2/stage2.s
LEGACY_OBJS	= $(addprefix legacy/, $(LEGACY_SRCS:.s=.bin))

istar.bin: $(LEGACY_OBJS)
	cat $^ /dev/zero | dd of=$@ bs=512 count=2880 iflag=fullblock

legacy/%.bin: legacy/%.s
	$(LEGACY_AS) -fbin -o $@ $<
