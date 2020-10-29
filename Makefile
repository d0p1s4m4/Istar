AS	= nasm

ASFLAGS	= -fbin

TARGET	= istar.bin

all: $(TARGET)

$(TARGET): src/boot.s
	$(AS) $(ASBIN) -o $@ $^
