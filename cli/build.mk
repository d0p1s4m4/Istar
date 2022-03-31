CLI_SRCS	= main.c
CLI_OBJS	= $(addprefix cli/, $(CLI_SRCS:.c=.o)) istar.bin.o

istar-cli: $(CLI_OBJS)
	$(CC) -o $@ $^

cli/%.o: cli/%.c
	$(CC) -o $@ -c $(CFLAGS) $<

istar.bin.o: istar.bin
	$(LD) -r -b binary -o $@ $<
