bits 16
org 0x0


jmp start

msg_hello db "Stage 2: Hello World!", 0x0D, 0x0A, 0

bios_print:
	lodsb
	or al, al
	jz .end
	mov ah, 0x0E
	int 0x10
	jmp bios_print
	.end:
		ret

start:
	mov ax, 0x100
	mov ds, ax
	mov es, ax

	mov si, msg_hello
	call bios_print

	jmp $