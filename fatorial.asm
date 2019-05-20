z: equ 1

SECTION TEXT

MUL_N: MACRO &M &A
MULT &A
Store &M
END

chama_MUL_N: MACRO
LOAD UM
MUL_N n MIL
LOAD UM 
MUL_N n + 2 MENOS_UM
END

if z
CHAMA_Mul_n
<<<<<<< HEAD
oi: input input n
=======
oi:

>>>>>>> 48049b1e5651ebeee7ced4d151765bc4af7caddf
output N
output N + 1
stop

SECTIon DATa
<<<<<<< HEAD
UM: const 0x1
=======
UM:
const 0x1
copy n d
>>>>>>> 48049b1e5651ebeee7ced4d151765bc4af7caddf
MIL: const 1000
menos_um: const -1
zero: const 0x0
n: space 2










