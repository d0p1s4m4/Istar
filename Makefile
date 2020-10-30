AS	= nasm

ASFLAGS	= -fbin

SRCS	= boot.s stage2.s
OBJS	= $(addprefix src/, $(SRCS:.s=.s.o))

TARGET	= istar.bin

all: $(TARGET)

$(TARGET): $(OBJS)
	cat $^ /dev/zero | dd of=$@ bs=512 count=2880 iflag=fullblock

%.s.o: %.s
	$(AS) $(ASBIN) -o $@ $^
