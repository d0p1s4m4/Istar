CC	?= gcc
LD	?= ld
AS	= nasm
RM	= rm -f

ASFLAGS	= -fbin
CFLAGS	= -ansi -pedantic -Werror -Wextra -Wall

all: istar-cli

istar-cli: cli/main.o istar.bin.o
	$(CC) -o $@ $^

istar.bin: boot/boot.bin stage2/stage2.bin
	cat $^ /dev/zero | dd of=$@ bs=512 count=2880 iflag=fullblock

boot/boot.bin: boot/boot.s
	$(AS) -fbin -o $@ $<

stage2/stage2.bin: stage2/stage2.s
	$(AS) $(ASFLAGS) -o $@ $<

cli/main.o: cli/main.c
	$(CC) -o $@ -c $(CFLAGS) $<

istar.bin.o: istar.bin
	$(LD) -r -b binary -o $@ $<

clean:
	$(RM) istar-cli istar.bin istar.bin.o boot/boot.bin stage2/stage2.bin
	$(RM) cli/main.o

fclean: clean
	$(RM) $(TARGET)

re: fclean all

qemu: istar.bin
	qemu-system-i386 -hda $^

.PHONY: all clean fclean re qemu
