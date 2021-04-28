%define VGA_BUFFER 0xB8000
%define VGA_WIDTH 80
%define VGA_HEIGHT 25

%define CRTC_ADDR_REG 0x3D4
%define CRTC_DATA_REG 0x3D5
%define CRTC_CURSOR_START_REG 0x0A
%define CRTC_DISABLE_CURSOR 0b00100000

vga_x: db 0
vga_y: db 0

vga_init:
	; disasble cursor
	pushf
	mov dx, CRTC_ADDR_REG
	mov al, CRTC_CURSOR_START_REG
	out dx, al
	
	mov dx, CRTC_DATA_REG
	mov al, CRTC_DISABLE_CURSOR
	out dx, al

	; clear screen
	call vga_clear
	popf
	ret

vga_clear:
	mov edi, VGA_BUFFER
	mov ecx, VGA_WIDTH*VGA_HEIGHT/2
	mov eax, 0x00200020
	cld
	rep stosd
	ret

vga_putchar:
	mov bh, 0x0F
	mov bl, al
	xor ecx, ecx
	xor eax, eax

	cmp bl, 0x0A
	jne .print
	inc byte [vga_y]
	mov byte [vga_x], 0x00
	jmp .end
	.print:
		mov cl, byte [vga_y]
		mov eax, VGA_WIDTH*2
		mul ecx
		mov cl, byte [vga_x]
		add eax, ecx
		add eax, VGA_BUFFER
		mov word [eax], bx
		add byte [vga_x], 0x02
	.end:
		ret

vga_putstr:
	.loop:
		lodsb
		or al, al
		jz .end
		call vga_putchar
		jmp .loop
	.end:
		ret
