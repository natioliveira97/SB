section .text
global _start
_start:
j1: mov DWORD eax, [zero]
mov DWORD [dois], eax
mov eax, 1
mov ebx, 0
int 80h
section .data
zero dd 0
dois dd 2
