bits 32

global _start
_start:

mov byte [0xB8100], 'H'
mov byte [0xB8102], 'e'
mov byte [0xB8104], 'l'
mov byte [0xB8106], 'l'
mov byte [0xB8108], 'o'
mov byte [0xB810A], ' '
mov byte [0xB810C], '3'
mov byte [0xB810E], '2'
mov byte [0xB8110], 'b'
mov byte [0xB8112], 'i'
mov byte [0xB8114], 't'
mov byte [0xB8116], '!'

jmp $
