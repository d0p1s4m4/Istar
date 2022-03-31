; Copyright (c) 2021, d0p1
; All rights reserved.
;
; Redistribution and use in source and binary forms, with or without
; modification, are permitted provided that the following conditions are met:
;
; 1. Redistributions of source code must retain the above copyright notice, this
;    list of conditions and the following disclaimer.
;
; 2. Redistributions in binary form must reproduce the above copyright notice,
;    this list of conditions and the following disclaimer in the documentation
;    and/or other materials provided with the distribution.
;
; 3. Neither the name of the copyright holder nor the names of its
;    contributors may be used to endorse or promote products derived from
;    this software without specific prior written permission.
;
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
; IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
; DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
; FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
; DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
; SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
; CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
; OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
; OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
