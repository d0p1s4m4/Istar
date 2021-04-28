%define VGA_BUFFER 0xB8000
%define VGA_WIDTH 80
%define VGA_HEIGHT 25

vga_clear:
	mov eax, VGA_BUFFER
	mov cx, VGA_WIDTH*VGA_HEIGHT
	.loop:
		mov word [eax], 0x0020
		add eax, 0x2
		dec cx
		jcxz .end
		jmp .loop
	.end:
		ret

vga_print:
	mov ecx, VGA_BUFFER
	mov ah, 0x0E
	.loop:
		lodsb
		or al, al
		jz .end
		mov word [ecx], ax
		add ecx, 0x2
		jmp .loop
	.end:
		ret
