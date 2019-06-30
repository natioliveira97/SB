;Funções de imput e output IA-32

section .data
a dd 0,0,0
num dd 3
char db 'char',0ah

section .text

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LerInteiro:
enter 13,0

mov eax,3
mov ebx,0
mov ecx,ebp
sub ecx,13
mov edx,13
int 80h

mov [a],eax

sub 	 eax,eax
mov 	 ecx,10
cmp byte [ebp-13],'-'
je 	 	 neg

mov 	 esi,-13
jmp 	 transformaC2I

neg:
mov 	 esi,-12

transformaC2I:
sub byte [ebp+esi],'0'
sub      ebx,ebx
mov 	 bl,[ebp+esi]
add 	 eax,ebx
inc 	 esi
cmp 	 byte [ebp+esi],0ah
je 		 fim
imul 	 ecx
jmp 	 transformaC2I


pronto:
cmp byte [ebp-13],'-'
jne 	 fim
mov 	 ebx,-1
imul 	 ebx

fim:
mov 	 ebx,[ebp+8]
mov 	 [ebx],eax

mov eax,[a]

leave
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

EscreverInteiro:
enter 0,0

mov 	 ebx,[ebp+8]
mov 	 eax,[ebx]
sub 	 esi,esi
mov 	 ecx,10

mov 	 ebx,1
cmp 	 eax,0
jge 	 transformaI2C
mov 	 ebx,-1
imul 	 ebx

transformaI2C:
sub 	 edx,edx
idiv 	 ecx
add 	 edx,'0'
;sub 	 esp,1
;mov byte [esp],dl
inc 	 esi
cmp 	 eax,0
jne 	 transformaI2C

cmp 	 ebx,0
jge		 imprime

;sub 	 esp,1
;mov byte [esp],'-'
inc 	 esi

imprime:
mov 	 eax,4
mov 	 ebx,1
mov	 	 ecx,esp
mov	 	 edx,esi
int 80h

leave
ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LerChar:
enter 2,0

mov eax,3
mov ebx,0
mov ecx,ebp
sub ecx,2
mov edx,2
int 80h

mov 	 ebx,[ebp+8]
mov 	 ecx,[ebp-2]
mov 	 [ebx],ecx

leave
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

EscreverChar:
enter 0,0

mov ebx,[ebp]

mov eax,4
mov ebx,1
;mov ecx,[ebp+8]
;mov edx,1
;int 80h

leave
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LerString:
enter 0,0

mov eax,3
mov ebx,0
mov ecx,[ebp+8]
mov edx,[ebp+12]
int 80h

leave
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

EscreverString:
enter 0,0

mov eax,4
mov ebx,1
mov ecx,[ebp+8]
mov edx,[ebp+12]
int 80h

leave
ret




global _start
_start:
push char
;call EscreverChar


mov eax,1
mov ebx,0
int 80h