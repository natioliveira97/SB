zero: equ 0
SECTION TEXT

MUL_N: MACRO &M &A
Store &M
LOAD &A
END

CHAMA_N: MACRO &E &F
MULT &F
DIV &E
if 0
MUL_N T V
MUL_N W Z
END

CHAMA_N J K

;INPUT N
;LOAD N
;FAT: SUB ONE
;JMPZ FIM
;STORE AUX
;MUL_N N k
;LOAD AUX
;JMP FAT
;FIM: OUTPUT N
;STOP
SECTION DATA
AUX: SPACE
N: SPACE
ONE: CONST 1
