.DEFAULT_GOAL = all

CC	?= clang
LD	?= ld
RM	= rm -f

COMMON_CFLAGS	= -ansi -pedantic -Werror -Wextra -Wall
CFLAGS	= $(COMMON_CFLAGS)

include legacy/build.mk
include cli/build.mk

all: istar-cli

clean:
	$(RM) istar.bin $(LEGACY_OBJS)
	$(RM) istar-cli $(CLI_OBJS)

re: clean all

qemu: istar.bin
	qemu-system-i386 -hda $^

.PHONY: all clean fclean re qemu
