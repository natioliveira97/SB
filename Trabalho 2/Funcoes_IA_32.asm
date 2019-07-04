;Funções de input e output IA-32

section .data
a dd 0,0,0
num dd 3
char db 'char',0ah

section .text

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LerInteiro:

; Reserva 13 bytes na pilha para lidar com os 11 caracteres possiveis de um numero de
; 32 bits, mais um caracter para o sinal, mais um para o enter

enter 13, 0 


mov eax,3	; Codigo para leitura
mov ebx,0	; Codigo para teclado
mov ecx,ebp 
sub ecx,13	; ecx aponta para o topo da pilha
mov edx,13	; Máximo de 13 caracteres para leitura
int 80h

push eax  	

sub 	 eax,eax
mov 	 ecx,10
cmp byte [ebp-13],'-'
je 	 	 neg


mov 	 esi,-13 ; Número positivo
jmp 	 transformaC2I

neg:
mov 	 esi,-12 ; Número negativo, primeiro caracter é sinal


;Transforma os caracteres em inteiro e armazena em eax
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
mov 	 ebx,-1  ; Se o número lido for negativo, multiplica eax por -1
imul 	 ebx


; Move o resultado para o endereço de memória passado pela pilha

fimI:
mov 	 ebx,[ebp+8]
mov 	 [ebx],eax

; Retorna  quantidade de caracteres lidos em eax
pop eax

leave
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

EscreverInteiro:
enter 0,0

mov 	 ebx,[ebp+8]  ; ebx contém o endereço do número a ser escrito
mov 	 eax,[ebx]    ; eax contém o número a ser escrito             
sub 	 esi,esi
mov 	 ecx,10       ; Base decimal                                     

mov 	 ebx,1
cmp 	 eax,0        ; Se o número for negativo, coloca essa informação em ebx e transforma eax para posistivo
jge 	 transformaI2C
mov 	 ebx,-1
imul 	 ebx


; Transforma um número inteiro em sequência de caracteres
transformaI2C:
sub 	 edx,edx
idiv 	 ecx
add 	 edx,'0'   ; Utiliza o resto da divisão por 10
sub 	 esp,1
mov byte [esp],dl
inc 	 esi
cmp 	 eax,0     ; Enquanto a divisão inteira não for 0, continua iterando
jne 	 transformaI2C

cmp 	 ebx,0
jge		 imprimeI


; Se ebx for menor que 0, o número é negativo
sub 	 esp,1
mov byte [esp],'-'
inc 	 esi

imprimeI:
mov 	 eax,4    ; Código para escrita
mov 	 ebx,1    ; Código para tela do terminal
mov	 	 ecx,esp  ; Os caracteres a serem escritos estão no topo da pilha
mov	 	 edx,esi
int 80h

; Retorna  quantidade de caracteres escritos em eax

leave
ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LerChar:
enter 2,0  ; Considera o caracter lido e o enter

mov eax,3   ; Codigo para leitura
mov ebx,0   ; Codigo para teclado
mov ecx,ebp
sub ecx,2   ; ecx aponta para o topo da pilha
mov edx,2   ; Máximo de 2 caracteres
int 80h


; Move o caractere lido para o endereço passado pela pilha
mov 	 ebx,[ebp+8]
mov 	 cl,[ebp-2]
mov 	 [ebx],cl

; Retorna  quantidade de caracteres lidos em eax

leave
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

EscreverChar:
enter 0,0

mov eax,4
mov ebx,1
mov ecx,[ebp+8]
mov edx,1
int 80h

; Retorna  quantidade de caracteres escritos em eax

leave
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LerString:
enter 0,0

mov eax,3         ; Codigo para leitura
mov ebx,0         ; Codigo para teclado
mov ecx,[ebp+8]   ; Endereço para onde a string deve ser lida
mov edx,[ebp+12]  ; Máximo de caracteres
int 80h

; Retorna  quantidade de caracteres lidos em eax

leave
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

EscreverString:
enter 0,0

mov esi,1

; Verifica em que posição está o enter (0ah)
acha_enter:
mov eax,[ebp+8]
cmp byte [eax+esi-1],0ah
je  imprime_s
inc esi
cmp esi,[ebp+12]          ; Quantidade máxima da caracteres
jl acha_enter


; Imprime até o enter ou até a quantidade máxima de caracteres, o que vier primeiro

imprime_s:
mov eax,4
mov ebx,1
mov ecx,[ebp+8]
mov edx,esi
int 80h

; Retorna  quantidade de caracteres escritos em eax

leave
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LerHexa:
enter 9,0

mov eax,3   ; Codigo para leitura 
mov ebx,0   ; Codigo para teclado 
mov ecx,ebp
sub ecx,9   ; ecx aponta para o topo da pilha
mov edx,9   ; Máximo de 9 caracteres, o que inclui os 8 caracteres do número e o enter
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

; Retorna  quantidade de caracteres lidos em eax
pop 	 eax
leave
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

EscreverHexa:
enter 0,0
mov 	 ebx,[ebp+8]  ; ebx contém o endereço do número a ser escrito  
mov 	 eax,[ebx]    ; eax contém o número a ser escrito              
sub 	 esi,esi  
mov 	 ecx,16       ; Base hexadecimal                                 

transformaH2C:
sub 	 edx,edx
idiv 	 ecx
cmp 	 edx,10
jge 	 letra

; Se o número for menor que 10, tranforma para um número em ASCII
add 	 edx,'0'
jmp 	 empilha


;Se o número estiver na faixa 10-15, tranforma para letra em ASCII
letra:
add 	 edx,'a'-10


empilha:
sub 	 esp,1
mov byte [esp],dl
inc 	 esi
cmp 	 eax,0
jne 	 transformaH2C

imprimeH:
mov 	 eax,4    ; Código para escrita
mov 	 ebx,1    ; Código para tela do terminal
mov	 	 ecx,esp  ; Os caracteres a serem escritos estão no topo da pilha
mov	 	 edx,esi
int 80h

; Retorna  quantidade de caracteres escritos em eax

leave
ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

global _start
_start:

push DWORD a
call LerInteiro
pop DWORD eax
push DWORD a
call EscreverInteiro
push DWORD 8
push DWORD char
call LerChar
call EscreverChar
call EscreverString
pop  DWORD eax
pop  DWORD eax
push DWORD a
call LerHexa
call EscreverHexa



mov eax,1
mov ebx,0
int 80h