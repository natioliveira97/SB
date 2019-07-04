# Trabalho 2

## Informações

Natalia Oliveira Borges - 16/0015863

Lívia Gomes Costa Fonseca - 16/0034078

Esse trabalho foi feito usando a linguagem de programação C++11, compilado usando g++ em ambiente Linux Ubuntu 16.04.

O GitHub do projeto pode ser acessado pelo [link](https://github.com/natioliveira97/SB).

As funções de input e output em assembly estão comentadas no arquivo Funcoes_IA_32.asm

## Objetivos

### Parte 1

O objetivo da parte 1 do trabalho é criar um compilador que traduz o assembly inventado usado no trabalho passado para assembly IA32.

### Parte 2

O objetivo da parte 2 do trabalho é a partir do arquivo IA32 de saída da parte 1, criar um arquivo executável em formato elf.


## Conteúdo do pacote

### Parte 1

- scanner.cpp
- scanner.hpp
- parser.cpp
- parser.hpp
- pre_processor.cpp
- pre_processor.hpp
- compilador.cpp
- compilador.hpp
- funcoes.asm

### Parte 2

- scanner.cpp
- scanner.hpp
- parserIA_32.cpp
- parserIA_32.hpp
- montador_IA32.cpp
- montador_IA32.hpp
- elf.cpp


## Bibliotecas utilizadas:

- iostream
- fstream
- regex
- cstdlib
- cstdio
- elfio



## Como compilar:

### Parte 1

Para compilar a primeira parte do trabalho faça:

```bash
make
```

## Como executar:

### Parte 1

Para executar a primeira parte do trabalho faça:

```bash
./tradutor myprogram.asm
```

### Parte 2

Para compilar e executar

```bash
g++ elf.cpp -o elf && ./elf && chmod +x teste && ./teste
```


## Saída do programa

### Parte 1

Esse programa recebe um arquivo myprogram.asm e retorna um arquivo em formato assembly IA32 myprogram.s.


### Parte 2

Não conseguimos implementar o completamente o tradutor de IA-32 para código máquina.
Utilizando o comando objdump, obtivemos o código máquina do arquivo teste.s e criamos o executável no formato elf.
O arquivo resultante se chama teste. Ele imprime o caractere 'a'.
