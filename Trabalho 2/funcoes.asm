
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;							Funcoes                          ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LerInteiro:
enter 13, 0 
mov eax,3	
mov ebx,0	
mov ecx,ebp
sub ecx,13	
mov edx,13	
int 80h
push eax  	
sub 	 eax,eax
mov 	 ecx,10
cmp byte [ebp-13],'-'
je 	 	 neg
mov 	 esi,-13 ; Numero positivo
jmp 	 transformaC2I
neg:
mov 	 esi,-12 ; Numero negativo, primeiro caracter eh sinal
transformaC2I:
sub byte [ebp+esi],'0'
sub      ebx,ebx
mov 	 bl,[ebp+esi]
add 	 eax,ebx
inc 	 esi
cmp byte [ebp+esi],0ah
je 		 pronto
imul 	 ecx
jmp 	 transformaC2I
pronto:
cmp byte [ebp-13],'-'
jne 	 fimI
mov 	 ebx,-1
imul 	 ebx
fimI:
mov 	 ebx,[ebp+8]
mov 	 [ebx],eax
pop eax
leave
ret

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
sub 	 esp,1
mov byte [esp],dl
inc 	 esi
cmp 	 eax,0
jne 	 transformaI2C
cmp 	 ebx,0
jge		 imprimeI
sub 	 esp,1
mov byte [esp],'-'
inc 	 esi
imprimeI:
mov 	 eax,4
mov 	 ebx,1
mov	 	 ecx,esp
mov	 	 edx,esi
int 80h
leave
ret

LerChar:
enter 2,0
mov eax,3
mov ebx,0
mov ecx,ebp
sub ecx,2
mov edx,2
int 80h
mov 	 ebx,[ebp+8]
mov 	 cl,[ebp-2]
mov 	 [ebx],ecx
leave
ret

EscreverChar:
enter 0,0
mov eax,4
mov ebx,1
mov ecx,[ebp+8]
mov edx,1
int 80h
leave
ret

LerString:
enter 0,0
mov eax,3
mov ebx,0
mov ecx,[ebp+8]
mov edx,[ebp+12]
int 80h
leave
ret

EscreverString:
enter 0,0
mov eax,4
mov ebx,1
mov ecx,[ebp+8]
mov edx,[ebp+12]
int 80h
leave
ret

LerHexa:
enter 9,0
mov eax,3
mov ebx,0
mov ecx,ebp
sub ecx,9
mov edx,9
int 80h
push 	 eax
sub 	 eax,eax
mov 	 esi,-9
transformaC2H:
cmp byte [ebp+esi],'9'
jg 	 	 Nnumber1
sub byte [ebp+esi],'0'
jmp 	 iteracao
Nnumber1:
cmp byte [ebp+esi],'F'
jg 	 	 Nnumber2
add byte [ebp+esi],10-'A'
jmp 	 iteracao
Nnumber2:
add byte [ebp+esi],10-'a'
iteracao:
sub ebx, ebx
mov BYTE bl, [ebp+esi]
add 	 eax, ebx
inc 	 esi
cmp byte [ebp+esi],0ah
je 		 fim
shl 	 eax,4
jmp 	 transformaC2H
fim:
mov 	 ebx,[ebp+8]
mov 	 [ebx],eax
pop 	 eax
leave
ret


EscreverHexa:
enter 0,0
mov 	 ebx,[ebp+8]
mov 	 eax,[ebx]
sub 	 esi,esi
mov 	 ecx,16
transformaH2C:
sub 	 edx,edx
idiv 	 ecx
cmp 	 edx,10
jge 	 letra
add 	 edx,'0'
jmp 	 empilha
letra:
add 	 edx,'a'-10
empilha:
sub 	 esp,1
mov byte [esp],dl
inc 	 esi
cmp 	 eax,0
jne 	 transformaH2C
imprimeH:
mov 	 eax,4
mov 	 ebx,1
mov	 	 ecx,esp
mov	 	 edx,esi
int 80h
leave
ret
