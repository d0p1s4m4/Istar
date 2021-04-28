
stage2/stage2.bin: stage2/stage2.s
	$(AS) $(ASFLAGS) -o $@ $^
