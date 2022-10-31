EFI_CC			= clang

EFI_TARGET_IA32	= i686-unknown-windows
EFI_TARGET_X64	= x86_64-unknown-windows

EFI_CFLAGS		= $(COMMON_CFLAGS) -ffreestanding -fshort-wchar -mno-red-zone \
					-fno-builtin -O1 -D__EFI__
EFI_LDFLAGS		= -fno-builtin -nostdlib -Wl,-entry:efi_main -Wl,-subsystem:efi_application \
					-fuse-ld=lld-link

EFI_SRCS		= main.c console.c memory.c fs.c efi.c wchar.c
EFI_X64_OBJS	= $(addprefix efi/, $(EFI_SRCS:.c=.x64.o)) \
					$(addprefix common/, $(COMMON_SRCS:.c=.x64.o))
EFI_IA32_OBJS	= $(addprefix efi/, $(EFI_SRCS:.c=.ia32.o)) \
					$(addprefix common/, $(COMMON_SRCS:.c=.ia32.o))
EFI_OBJS 		= $(EFI_IA32_OBJS) $(EFI_X64_OBJS)

BOOTX64.EFI: $(EFI_X64_OBJS)
	$(EFI_CC) -target $(EFI_TARGET_X64) -o $@ $^ $(EFI_LDFLAGS)

BOOTIA32.EFI: $(EFI_IA32_OBJS)
	$(EFI_CC)  -target $(EFI_TARGET_IA32) -o $@ $^ $(EFI_LDFLAGS)

efi/%.x64.o: efi/%.c
	$(EFI_CC) -target $(EFI_TARGET_X64) -c -o $@ $< $(EFI_CFLAGS)

efi/%.ia32.o: efi/%.c
	$(EFI_CC) -target $(EFI_TARGET_IA32) -c -o $@ $< $(EFI_CFLAGS)

common/%.x64.o: common/%.c
	$(EFI_CC) -target $(EFI_TARGET_X64) -c -o $@ $< $(EFI_CFLAGS)

common/%.ia32.o: common/%.c
	$(EFI_CC) -target $(EFI_TARGET_IA32) -c -o $@ $< $(EFI_CFLAGS)
