CC	= i686-elf-gcc
LD	= i686-elf-ld
OBJCOPY = i686-elf-objcopy
AS	= nasm
RM	= rm -f

CFLAGS	= -ansi -pedantic -pedantic-errors -Wall -Werror -Wextra \
			-ffreestanding -fno-builtin -nostdlib -nostdinc -O2 \
			-Iinclude
ASFLAGS	= -felf32
LDFLAGS	= -nostdlib -Tstage2/linker.ld

TARGET	= istar.bin

all: $(TARGET)

$(TARGET): boot/boot.bin stage2/stage2.bin
	cat $^ /dev/zero | dd of=$@ bs=512 count=2880 iflag=fullblock

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.s.o: %.s
	$(AS) $(ASFLAGS) -o $@ $^

include boot/build.mk
include stage2/build.mk

clean:
	$(RM) $(OBJS) boot/boot.bin stage2/stage2.bin stage2/stage2.elf

fclean: clean
	$(RM) $(TARGET)

re: fclean all

.PHONY: all clean fclean re
