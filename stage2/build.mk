SRCS_ASM	=
SRCS_C		= stage2.c vga.c
OBJS		= $(addprefix stage2/, $(SRCS_ASM:.s=.s.o)) \
				$(addprefix stage2/, $(SRCS_C:.c=.o))

stage2/stage2.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

stage2/stage2.bin: stage2/stage2.elf
	$(OBJCOPY) -O binary $^ $@
