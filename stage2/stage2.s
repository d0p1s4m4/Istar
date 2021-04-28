org 0x8000
bits 32

jmp start

%include 'stage2/vga.s'

msg_stage2: db "Istar: Hello stage2!", 0

start:
	call vga_clear
	mov si, msg_stage2
	call vga_print
	hlt