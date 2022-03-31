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

org 0x7C00
bits 16

jmp start
; skip bpb
times 0x5A - ($ - $$) db 0

;; ============================================================================
;; Data
;; ============================================================================
msg_hello: db "Istar: Hello World!", 0x0D, 0x0A, 0
msg_error_reset: db "Error: can't reset disk", 0x0D, 0x0A, 0
msg_error_stage2: db "Error: can't load stage 2", 0x0D, 0x0A, 0
msg_press_any_key_to_reboot: db "Press any key to reboot", 0x0D, 0x0A, 0

;; ----------------------------------------------------------------------------
;;  gdt 
;; ----------------------------------------------------------------------------
gdt: 
	db 0, 0, 0, 0, 0, 0, 0, 0
	db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10011011b, 11011111b, 0x0
	db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10010011b, 11011111b, 0x0
	.end:

gdt_ptr:
	dw gdt.end - gdt - 1
	dd gdt

;; ============================================================================
;; Function
;; ============================================================================
;; bios_print
;;      si (str)
;; ----------------------------------------------------------------------------
bios_print:
	lodsb
	or al, al
	jz .end
	mov ah, 0x0E
	int 0x10
	jmp bios_print
	.end:
		ret

;; ----------------------------------------------------------------------------
;; entry
;; ----------------------------------------------------------------------------
start:
	cli
    jmp 0x0:.canonicalize_cs_eip
    .canonicalize_cs_eip:
	; setup segments to zero
	xor ax, ax
	mov ds, ax
	mov es, ax

	; clear screen
	mov al, 0x03
	mov ah, 0
	int 0x10

	mov si, msg_hello
	call bios_print

	; reset disk to sector 0
	.reset_disk:
		xor ah, ah
		int 0x13
		jc .err_reset_disk

	mov ax, 0x800 ; stage 2 will be loader at 0x800:0
	mov es, ax
	xor bx, bx

	xor ch, ch
	mov cl, 0x02 ; sector n°2
	mov al, 0x01 ; read one sector
	mov ah, 0x02
	int 0x13
	jc .err_load_stage2

	lgdt [gdt_ptr]

	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp 0x08:.next

bits 32

	.next:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	jmp 0x8000

bits 16

	.end:
		hlt
		jmp $

	.wait_for_reboot:
		mov si, msg_press_any_key_to_reboot
		call bios_print
		xor ah, ah ; ah = 0 read char
		int 0x16   ; keyboard service
		int 0x19   ; reboot computer

	.err_reset_disk:
		mov si, msg_error_reset
		call bios_print
		jmp .wait_for_reboot

	.err_load_stage2:
		mov si, msg_error_stage2
		call bios_print
		jmp .wait_for_reboot

times 510 - ($ - $$) db 0x90
dw 0xAA55
