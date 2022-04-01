EFI_CC		= clang -target x86_64-unknown-windows

EFI_CFLAGS	= $(COMMON_CFLAGS) -ffreestanding -fshort-wchar -mno-red-zone
EFI_LDFLAGS	= -nostdlib -Wl,-entry:efi_main -Wl,-subsystem:efi_application \
				-fuse-ld=lld-link

EFI_SRCS	= main.c
EFI_OBJS	= $(addprefix efi/, $(EFI_SRCS:.c=.o))

BOOTX64.EFI: $(EFI_OBJS)
	$(EFI_CC) -o $@ $^ $(EFI_LDFLAGS)

efi/%.o: efi/%.c
	$(EFI_CC) -c -o $@ $< $(CFLAGS)
