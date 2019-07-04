section .data
a db 1


section .text
global _start

f4:
ret

_start:

push byte 'a'
push dword 16
sub eax,eax
mov al,[esp+4]
mov byte [a],al

mov eax,4
mov ebx,1
mov ecx,a
mov edx,1
int 80h

mov eax,1
mov ebx,0


int 80h