boot/boot.bin: boot/boot.s
	$(AS) -fbin -o $@ $^
