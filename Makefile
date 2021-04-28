AS	= nasm
RM	= rm -f

ASFLAGS	= -fbin

TARGET	= istar.bin

all: $(TARGET)

$(TARGET): boot/boot.bin stage2/stage2.bin
	cat $^ /dev/zero | dd of=$@ bs=512 count=2880 iflag=fullblock

include boot/build.mk
include stage2/build.mk

clean:
	$(RM) $(OBJS) boot/boot.bin stage2/stage2.bin

fclean: clean
	$(RM) $(TARGET)

re: fclean all

qemu: $(TARGET)
	qemu-kvm -hda $^

.PHONY: all clean fclean re qemu
